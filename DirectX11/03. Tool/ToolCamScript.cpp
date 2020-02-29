#include "stdafx.h"
#include "ToolCamScript.h"

#include <Engine/KeyMgr.h>
#include <Engine/Camera.h>
#include <Engine/Core.h>


CToolCamScript::CToolCamScript()
	: CScript(0)
	, m_fSpeed(100.f)
	, m_fMul(1.f)
	, m_isNavMeshCreate(false)
	, m_isNavMeshModify(false)
	, m_selectNavMesh(nullptr)
{
}

CToolCamScript::~CToolCamScript()
{
}

CGameObject * CToolCamScript::GetClickNavMesh()
{
	Matrix projectionMatrix = Object()->Camera()->GetProjMat();
	DirectX::XMVECTOR projectionDeterminant = DirectX::XMMatrixDeterminant(projectionMatrix);
	Matrix inverseProjectionMatrix = DirectX::XMMatrixInverse(&projectionDeterminant, projectionMatrix);

	Matrix viewMatrix = Object()->Camera()->GetViewMat();
	DirectX::XMVECTOR viewDeterminant = DirectX::XMMatrixDeterminant(viewMatrix);
	Matrix inverseViewMatrix = DirectX::XMMatrixInverse(&viewDeterminant, viewMatrix);

	RECT windowRect = {};
	GetWindowRect(CCore::GetInst()->GetWindowHwnd(), &windowRect);

	float clientRectWidth = windowRect.right - windowRect.left;
	float clientRectHeight = windowRect.bottom - windowRect.top;

	DirectX::XMVECTOR mouseClickPosition = DirectX::XMVectorSet(
		(2 * (float)(CKeyMgr::GetInst()->GetMousePos().x - (clientRectWidth / 2))) / (float)clientRectWidth,
		(2 * (float)((clientRectHeight / 2) - CKeyMgr::GetInst()->GetMousePos().y)) / (float)clientRectHeight,
		1.f,
		0.f);

	mouseClickPosition = DirectX::XMVector3Transform(mouseClickPosition, inverseProjectionMatrix);
	mouseClickPosition = DirectX::XMVector3Transform(mouseClickPosition, inverseViewMatrix);

	VTX triangleMesh[3];
	triangleMesh[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	triangleMesh[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	triangleMesh[2].vPos = Vec3(0.5f, -0.5f, 0.f);

	for (int index = 0; index < CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"NavMesh")->GetParentObject().size(); index++)
	{
		Matrix navMeshMatrix = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"NavMesh")->GetParentObject()[index]->Collider3D()->GetWorldMat();
		Vec3 triangleWorldPos[3] = {};

		for (UINT i = 0; i < 3; ++i)
		{
			triangleWorldPos[i] = XMVector3TransformCoord(triangleMesh[i].vPos, navMeshMatrix);
		}

		DirectX::XMVECTOR cameraWorldPosition = Transform()->GetWorldPos();
		DirectX::XMVECTOR mouseClickDirection = mouseClickPosition - cameraWorldPosition;
		mouseClickDirection = DirectX::XMVector3Normalize(mouseClickDirection);

		float clickPoistionToTargetDist = 0.f;

		bool isObjectTriangleClick = DirectX::TriangleTests::Intersects(
			mouseClickPosition,
			mouseClickDirection,
			triangleWorldPos[0],
			triangleWorldPos[1],
			triangleWorldPos[2],
			clickPoistionToTargetDist
		);

		if (isObjectTriangleClick == true)
		{
			return CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"NavMesh")->GetParentObject()[index];
		}
	}

	return nullptr;
}

void CToolCamScript::RotateAxisRadian(CGameObject* rotateMesh, Vec3 rotateAxis, float rotateAngle, Vec3 & inOutScale, Vec3 & inOutRotate, Vec3 &inOutPosition)
{
	VTX triangleMesh[3];
	triangleMesh[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	triangleMesh[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	triangleMesh[2].vPos = Vec3(0.5f, -0.5f, 0.f);

	Matrix selectNavMeshMatrix = rotateMesh->Transform()->GetWorldMat();
	Vec3 selectTriangleWorldPos[3] = {};
	for (UINT i = 0; i < 3; ++i)
	{
		selectTriangleWorldPos[i] = XMVector3TransformCoord(triangleMesh[i].vPos, selectNavMeshMatrix);
	}

	//Vec3 rotateAxis = selectTriangleWorldPos[0] - selectTriangleWorldPos[1];

	Matrix axisRotateResult = XMMatrixRotationAxis(rotateAxis, GetRadian(rotateAngle));

	Vec3 selectNavMeshPosition = rotateMesh->Transform()->GetLocalPos();
	Vec3 selectNavMeshScale = rotateMesh->Transform()->GetLocalScale();
	Vec3 selectNavMeshRotate = rotateMesh->Transform()->GetLocalRot();

	Vec3 selectNavMeshVertexToAxis = rotateAxis - selectTriangleWorldPos[1];
	selectNavMeshPosition += selectNavMeshVertexToAxis;

	Matrix navMeshMatTrans = XMMatrixTranslation(selectNavMeshPosition.x, selectNavMeshPosition.y, selectNavMeshPosition.z);

	Matrix navMeshMatScale = XMMatrixScaling(selectNavMeshScale.x, selectNavMeshScale.y, selectNavMeshScale.z);

	Matrix navMeshMatRotation = XMMatrixRotationX(selectNavMeshRotate.x);
	navMeshMatRotation *= XMMatrixRotationY(selectNavMeshRotate.y);
	navMeshMatRotation *= XMMatrixRotationZ(selectNavMeshRotate.z);

	Matrix movedSelectNavMeshToAxisMatrix = navMeshMatScale * navMeshMatRotation * navMeshMatTrans;
	movedSelectNavMeshToAxisMatrix *= axisRotateResult;

	XMVECTOR resultScale;
	XMVECTOR resultPosition;
	XMVECTOR resultQuaternionRotate;

	XMMatrixDecompose(&resultScale, &resultQuaternionRotate, &resultPosition, movedSelectNavMeshToAxisMatrix);

	Vec3 inputRotate;
	Vec3 inputPosition = resultPosition;
	inputPosition -= selectNavMeshVertexToAxis;
	Vec3 inputScale = resultScale;

	// roll (x-axis rotation)
	Vector4 q = resultQuaternionRotate;
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	inputRotate.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = 2 * (q.w * q.y - q.z * q.x);
	if (std::abs(sinp) >= 1)
		inputRotate.y = std::copysign(XM_PI / 2, sinp); // use 90 degrees if out of range
	else
		inputRotate.y = std::asin(sinp);

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	inputRotate.z = std::atan2(siny_cosp, cosy_cosp);

	inOutScale = inputScale;
	inOutRotate = inputRotate;
	inOutPosition = inputPosition;
}

void CToolCamScript::start()
{
}

void CToolCamScript::update()
{
	Vec3 vPos = Transform()->GetLocalPos();	

	Vec3 vFront = Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT);
	Vec3 vRight = Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT);

	if (KEYHOLD(KEY_TYPE::KEY_W))
	{
		vPos += (vFront * DT * m_fSpeed * m_fMul);
	}
	if (KEYHOLD(KEY_TYPE::KEY_S))
	{
		vPos += (-vFront * DT * m_fSpeed * m_fMul);
	}
	if (KEYHOLD(KEY_TYPE::KEY_A))
	{
		vPos += (-vRight * DT * m_fSpeed * m_fMul);
	}
	if (KEYHOLD(KEY_TYPE::KEY_D))
	{
		vPos += (vRight * DT * m_fSpeed * m_fMul);
	}

	if (KEYHOLD(KEY_TYPE::KEY_RBTN))
	{
		Vec2 vDragDir = CKeyMgr::GetInst()->GetDragDir();

		Vec3 vRot = Transform()->GetLocalRot();
		vRot.y += DT * vDragDir.x * 1.3f;
		vRot.x -= DT * vDragDir.y * 1.3f;
		Transform()->SetLocalRot(vRot);
	}

	if (KEYHOLD(KEY_TYPE::KEY_LSHIFT))
	{
		m_fMul += DT * 5.f;
	}
	if (KEYAWAY(KEY_TYPE::KEY_LSHIFT))
	{
		m_fMul = 1.f;
	}

	Transform()->SetLocalPos(vPos);


	if (KEYTAB(KEY_TYPE::KEY_NUM7))
	{
		m_isNavMeshCreate = true;
	}
	else if (KEYTAB(KEY_TYPE::KEY_NUM8))
	{
		m_isNavMeshCreate = false;
	}


	if (m_isNavMeshCreate == true)
	{
		if (KEYTAB(KEY_TYPE::KEY_LBTN))
		{
			m_selectNavMesh = nullptr;

			m_selectNavMesh = GetClickNavMesh();
		}
		else if (KEYAWAY(KEY_TYPE::KEY_LBTN))
		{
			if (m_selectNavMesh != nullptr)
			{
				CGameObject* clickUpObject = GetClickNavMesh();

				if (clickUpObject == m_selectNavMesh)
				{
					//선택한 Nav Mesh의 크기, 회전값을 조정하고자 하는 경우다.
					m_isNavMeshModify = true;
				}
				else
				{
					m_isNavMeshModify = false;

					if (clickUpObject != nullptr)
					{
						//새로운 Nav Mesh를 기존의 Nav Mesh에 붙인다.

						//Old Nav Mesh의 각도를 제한을 가하기 위해 필요한 각도값을 구한다
						float rollbackRadian = 0.f;
						{
							Vec3 oldNavMeshUpVector = clickUpObject->Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT) * -1;
							oldNavMeshUpVector.Normalize();

							Vec3 worldUpVector = Vec3(0.f, 1.f, 0.f);

							rollbackRadian = acosf(oldNavMeshUpVector.Dot(worldUpVector));
							rollbackRadian *= -1.f;
						}

						//Old Nav Mesh 각도 조절
						Vec3 calculatedOldNavMeshPos;
						Vec3 calculatedOldNavMeshScale;
						Vec3 calculatedOldNavMeshRotate;
						Matrix calculatedOldNavMeshMatrix;
						{
							VTX triangleMesh[3];
							triangleMesh[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
							triangleMesh[1].vPos = Vec3(0.5f, 0.5f, 0.f);
							triangleMesh[2].vPos = Vec3(0.5f, -0.5f, 0.f);

							Matrix selectNavMeshMatrix = clickUpObject->Collider3D()->GetWorldMat();
							Vec3 selectTriangleWorldPos[3] = {};
							for (UINT i = 0; i < 3; ++i)
							{
								selectTriangleWorldPos[i] = XMVector3TransformCoord(triangleMesh[i].vPos, selectNavMeshMatrix);
							}

							Vec3 rotateAxis = selectTriangleWorldPos[0] - selectTriangleWorldPos[1];

							Matrix axisRotateResult = XMMatrixRotationAxis(rotateAxis, -rollbackRadian);

							Vec3 selectNavMeshPosition = clickUpObject->Transform()->GetLocalPos();
							Vec3 selectNavMeshScale = clickUpObject->Transform()->GetLocalScale();
							Vec3 selectNavMeshRotate = clickUpObject->Transform()->GetLocalRot();

							Vec3 selectNavMeshVertexToAxis = rotateAxis - selectTriangleWorldPos[1];
							selectNavMeshPosition += selectNavMeshVertexToAxis;

							Matrix navMeshMatTrans = XMMatrixTranslation(selectNavMeshPosition.x, selectNavMeshPosition.y, selectNavMeshPosition.z);

							Matrix navMeshMatScale = XMMatrixScaling(selectNavMeshScale.x, selectNavMeshScale.y, selectNavMeshScale.z);

							Matrix navMeshMatRotation = XMMatrixRotationX(selectNavMeshRotate.x);
							navMeshMatRotation *= XMMatrixRotationY(selectNavMeshRotate.y);
							navMeshMatRotation *= XMMatrixRotationZ(selectNavMeshRotate.z);

							Matrix movedSelectNavMeshToAxisMatrix = navMeshMatScale * navMeshMatRotation * navMeshMatTrans;

							movedSelectNavMeshToAxisMatrix *= axisRotateResult;

							XMVECTOR resultScale;
							XMVECTOR resultPosition;
							XMVECTOR resultQuaternionRotate;

							XMMatrixDecompose(&resultScale, &resultQuaternionRotate, &resultPosition, movedSelectNavMeshToAxisMatrix);

							Vec3 inputRotate;
							Vec3 inputPosition = resultPosition;
							inputPosition -= selectNavMeshVertexToAxis;
							Vec3 inputScale = resultScale;

							// roll (x-axis rotation)
							double sinr_cosp = 2 * (resultQuaternionRotate.vector4_f32[3] * resultQuaternionRotate.vector4_f32[0] + resultQuaternionRotate.vector4_f32[1] * resultQuaternionRotate.vector4_f32[2]);
							double cosr_cosp = 1 - 2 * (resultQuaternionRotate.vector4_f32[0] * resultQuaternionRotate.vector4_f32[0] + resultQuaternionRotate.vector4_f32[1] * resultQuaternionRotate.vector4_f32[1]);
							inputRotate.x = std::atan2(sinr_cosp, cosr_cosp);

							// pitch (y-axis rotation)
							double sinp = 2 * (resultQuaternionRotate.vector4_f32[3] * resultQuaternionRotate.vector4_f32[1] - resultQuaternionRotate.vector4_f32[2] * resultQuaternionRotate.vector4_f32[0]);
							if (std::abs(sinp) >= 1)
								inputRotate.y = std::copysign(XM_PI / 2, sinp); // use 90 degrees if out of range
							else
								inputRotate.y = std::asin(sinp);

							// yaw (z-axis rotation)
							double siny_cosp = 2 * (resultQuaternionRotate.vector4_f32[3] * resultQuaternionRotate.vector4_f32[2] + resultQuaternionRotate.vector4_f32[0] * resultQuaternionRotate.vector4_f32[1]);
							double cosy_cosp = 1 - 2 * (resultQuaternionRotate.vector4_f32[1] * resultQuaternionRotate.vector4_f32[1] + resultQuaternionRotate.vector4_f32[2] * resultQuaternionRotate.vector4_f32[2]);
							inputRotate.z = std::atan2(siny_cosp, cosy_cosp);

							calculatedOldNavMeshPos = inputPosition;
							calculatedOldNavMeshScale = inputScale;
							calculatedOldNavMeshRotate = inputRotate;


							Matrix matScale = XMMatrixScaling(inputScale.x, inputScale.y, inputScale.z);

							Matrix matRotation = XMMatrixRotationX(inputRotate.x);
							matRotation *= XMMatrixRotationY(inputRotate.y);
							matRotation *= XMMatrixRotationZ(inputRotate.z);

							Matrix matTrans = XMMatrixTranslation(inputPosition.x, inputPosition.y, inputPosition.z);

							calculatedOldNavMeshMatrix = matScale * matRotation * matTrans;
						}

						//New Nav Mesh y축 위치 조절
						Vec3 calculatedNewNavMeshPos;
						Vec3 calculatedNewNavMeshScale;
						Vec3 calculatedNewNavMeshRotate;
						Matrix calculatedNewNavMeshMatrix;
						{
							Vec3 newNavMeshPosition = m_selectNavMesh->Transform()->GetLocalPos();
							newNavMeshPosition.y = calculatedOldNavMeshPos.y;
							m_selectNavMesh->Transform()->SetLocalPos(newNavMeshPosition);

							calculatedNewNavMeshPos = m_selectNavMesh->Transform()->GetLocalPos();
							calculatedNewNavMeshScale = m_selectNavMesh->Transform()->GetLocalScale();
							calculatedNewNavMeshRotate = m_selectNavMesh->Transform()->GetLocalRot();

							Matrix matScale = XMMatrixScaling(calculatedNewNavMeshScale.x, calculatedNewNavMeshScale.y, calculatedNewNavMeshScale.z);

							Matrix matRotation = XMMatrixRotationX(calculatedNewNavMeshRotate.x);
							matRotation *= XMMatrixRotationY(calculatedNewNavMeshRotate.y);
							matRotation *= XMMatrixRotationZ(calculatedNewNavMeshRotate.z);

							Matrix matTrans = XMMatrixTranslation(calculatedNewNavMeshPos.x, calculatedNewNavMeshPos.y, calculatedNewNavMeshPos.z);

							calculatedNewNavMeshMatrix = matScale * matRotation * matTrans;
						}

						//크기
						//우선 새로운 Nav와 기존의 Nav와 가장 가까운 선분이 무엇인지 찾는다.
						{
							Vec3 newNavMeshPosition = m_selectNavMesh->Transform()->GetLocalPos();

							VTX triangleMesh[3];
							triangleMesh[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
							triangleMesh[1].vPos = Vec3(0.5f, 0.5f, 0.f);
							triangleMesh[2].vPos = Vec3(0.5f, -0.5f, 0.f);


							Matrix oldNavMeshMatrix = calculatedOldNavMeshMatrix;
							Vec3 oldTriangleWorldPos[3] = {};
							for (UINT i = 0; i < 3; ++i)
							{
								oldTriangleWorldPos[i] = XMVector3TransformCoord(triangleMesh[i].vPos, oldNavMeshMatrix);
							}


							Vec3 old0to1Vector = oldTriangleWorldPos[1]- oldTriangleWorldPos[0];
							Vec3 old1to2Vector = oldTriangleWorldPos[2] - oldTriangleWorldPos[1];
							Vec3 old2to0Vector = oldTriangleWorldPos[0] - oldTriangleWorldPos[2];

							Vec3 old0toNewNavVector = newNavMeshPosition - oldTriangleWorldPos[0];
							Vec3 old1toNewNavVector = newNavMeshPosition - oldTriangleWorldPos[1];
							Vec3 old2toNewNavVector = newNavMeshPosition - oldTriangleWorldPos[2];

							Vec3 nearVertexs[2];
							if (old0toNewNavVector.Cross(old0to1Vector).y > 0.f)
							{
								nearVertexs[0] = oldTriangleWorldPos[0];
								nearVertexs[1] = oldTriangleWorldPos[1];
							}
							else if (old1toNewNavVector.Cross(old1to2Vector).y > 0.f)
							{
								nearVertexs[0] = oldTriangleWorldPos[1];
								nearVertexs[1] = oldTriangleWorldPos[2];
							}
							else if (old2toNewNavVector.Cross(old2to0Vector).y > 0.f)
							{
								nearVertexs[0] = oldTriangleWorldPos[0];
								nearVertexs[1] = oldTriangleWorldPos[2];
							}


							Matrix newNavMeshMatrix = calculatedNewNavMeshMatrix;
							Vec3 newTriangleWorldPos[3] = {};
							for (UINT i = 0; i < 3; ++i)
							{
								newTriangleWorldPos[i] = XMVector3TransformCoord(triangleMesh[i].vPos, newNavMeshMatrix);
							}

							float oldNavMeshLineDist = Vector3::Distance(nearVertexs[0], nearVertexs[1]);
							float newNavMeshLineDist = Vector3::Distance(newTriangleWorldPos[0], newTriangleWorldPos[1]);

							float scaleXRation = oldNavMeshLineDist / newNavMeshLineDist;
							Vec3 newNavMeshScale = m_selectNavMesh->Transform()->GetLocalScale();
							newNavMeshScale.x *= scaleXRation;
							m_selectNavMesh->Transform()->SetLocalScale(newNavMeshScale);
						}
						

						//회전
						{
							Vec3 newNavMeshPosition = m_selectNavMesh->Transform()->GetLocalPos();
							Vec3 oldNavMeshPosition = clickUpObject->Transform()->GetLocalPos();

							VTX triangleMesh[3];
							triangleMesh[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
							triangleMesh[1].vPos = Vec3(0.5f, 0.5f, 0.f);
							triangleMesh[2].vPos = Vec3(0.5f, -0.5f, 0.f);


							Matrix oldNavMeshMatrix = calculatedOldNavMeshMatrix;
							Vec3 oldTriangleWorldPos[3] = {};
							for (UINT i = 0; i < 3; ++i)
							{
								oldTriangleWorldPos[i] = XMVector3TransformCoord(triangleMesh[i].vPos, oldNavMeshMatrix);
							}


							Vec3 old0to1Vector = oldTriangleWorldPos[1] - oldTriangleWorldPos[0];
							Vec3 old1to2Vector = oldTriangleWorldPos[2] - oldTriangleWorldPos[1];
							Vec3 old2to0Vector = oldTriangleWorldPos[0] - oldTriangleWorldPos[2];

							Vec3 old0toNewNavVector = newNavMeshPosition - oldTriangleWorldPos[0];
							Vec3 old1toNewNavVector = newNavMeshPosition - oldTriangleWorldPos[1];
							Vec3 old2toNewNavVector = newNavMeshPosition - oldTriangleWorldPos[2];

							Vec3 nearVertexs[2];
							if (old0toNewNavVector.Cross(old0to1Vector).y > 0.f)
							{
								nearVertexs[0] = oldTriangleWorldPos[0];
								nearVertexs[1] = oldTriangleWorldPos[1];
							}
							else if (old1toNewNavVector.Cross(old1to2Vector).y > 0.f)
							{
								nearVertexs[0] = oldTriangleWorldPos[1];
								nearVertexs[1] = oldTriangleWorldPos[2];
							}
							else if (old2toNewNavVector.Cross(old2to0Vector).y > 0.f)
							{
								nearVertexs[0] = oldTriangleWorldPos[0];
								nearVertexs[1] = oldTriangleWorldPos[2];
							}


							Matrix newNavMeshMatrix = calculatedNewNavMeshMatrix;
							Vec3 newTriangleWorldPos[3] = {};
							for (UINT i = 0; i < 3; ++i)
							{
								newTriangleWorldPos[i] = XMVector3TransformCoord(triangleMesh[i].vPos, newNavMeshMatrix);
							}

							Vec3 oldTriangleVector1 = oldTriangleWorldPos[1] - oldTriangleWorldPos[0];
							Vec3 oldTriangleVector2 = oldTriangleWorldPos[2] - oldTriangleWorldPos[0];
							Vec3 oldTriangleCross = oldTriangleVector1.Cross(oldTriangleVector2);

							Vec3 oldNearVertexVector = nearVertexs[0] - nearVertexs[1];

							Vec3 oldNearTangent = oldTriangleCross.Cross(oldNearVertexVector);
							oldNearTangent.Normalize();

							Vec3 newToOldMeshVector = oldNavMeshPosition - newNavMeshPosition;
							newToOldMeshVector.Normalize();

							float debugValue = newToOldMeshVector.Dot(oldNearTangent);
							if (newToOldMeshVector.Dot(oldNearTangent) < 0.f)
							{
								oldNearTangent *= -1.f;
							}

							Vec3 newTriangleVector1 = newTriangleWorldPos[1] - newTriangleWorldPos[0];
							Vec3 newTriangleVector2 = newTriangleWorldPos[2] - newTriangleWorldPos[0];
							Vec3 newTriangleCross = newTriangleVector1.Cross(newTriangleVector2);

							Vec3 newNearVertexVector = newTriangleWorldPos[1] - newTriangleWorldPos[0];

							Vec3 newNearTangent = newNearVertexVector.Cross(newTriangleCross);
							newNearTangent.y = 0.f;
							newNearTangent.Normalize();


							Vec3 oldNearTangentNewNearTangentCross = oldNearTangent.Cross(newNearTangent);
							if (oldNearTangentNewNearTangentCross.y > 0.f)
							{
								//left
								float moveRotateY = oldNearTangent.Dot(newNearTangent);
								moveRotateY = acos(moveRotateY);
								moveRotateY = GetAngle(moveRotateY);
								moveRotateY = 360.f - moveRotateY;
								moveRotateY = GetRadian(moveRotateY);

								Vec3 newNavMeshNowRotate = m_selectNavMesh->Transform()->GetLocalRot();
								newNavMeshNowRotate.y = moveRotateY;
								m_selectNavMesh->Transform()->SetLocalRot(newNavMeshNowRotate);

							}
							else
							{
								//right

								float moveRotateY = oldNearTangent.Dot(newNearTangent);
								moveRotateY = acos(moveRotateY);
								moveRotateY = GetAngle(moveRotateY);
								moveRotateY = GetRadian(moveRotateY);

								Vec3 newNavMeshNowRotate = m_selectNavMesh->Transform()->GetLocalRot();
								newNavMeshNowRotate.y = moveRotateY;
								m_selectNavMesh->Transform()->SetLocalRot(newNavMeshNowRotate);
							}
						}

						{
							//이동 전에 New Nav Mesh를 Old Nav Mesh와 같은 회전량으로 만들어준다.
							VTX triangleMesh[3];
							triangleMesh[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
							triangleMesh[1].vPos = Vec3(0.5f, 0.5f, 0.f);
							triangleMesh[2].vPos = Vec3(0.5f, -0.5f, 0.f);

							Matrix newNavMeshMatrix = m_selectNavMesh->Collider3D()->GetWorldMat();
							Vec3 newTriangleWorldPos[3] = {};
							for (UINT i = 0; i < 3; ++i)
							{
								newTriangleWorldPos[i] = XMVector3TransformCoord(triangleMesh[i].vPos, newNavMeshMatrix);
							}

							Vec3 rotateAxis = newTriangleWorldPos[0] - newTriangleWorldPos[1];

							Matrix axisRotateResult = XMMatrixRotationAxis(rotateAxis, -rollbackRadian);

							Vec3 newNavMeshPosition = m_selectNavMesh->Transform()->GetLocalPos();
							Vec3 newNavMeshScale = m_selectNavMesh->Transform()->GetLocalScale();
							Vec3 newNavMeshRotate = m_selectNavMesh->Transform()->GetLocalRot();

							Vec3 newNavMeshVertexToAxis = rotateAxis - newTriangleWorldPos[1];
							newNavMeshPosition += newNavMeshVertexToAxis;

							Matrix navMeshMatTrans = XMMatrixTranslation(newNavMeshPosition.x, newNavMeshPosition.y, newNavMeshPosition.z);

							Matrix navMeshMatScale = XMMatrixScaling(newNavMeshScale.x, newNavMeshScale.y, newNavMeshScale.z);

							Matrix navMeshMatRotation = XMMatrixRotationX(newNavMeshRotate.x);
							navMeshMatRotation *= XMMatrixRotationY(newNavMeshRotate.y);
							navMeshMatRotation *= XMMatrixRotationZ(newNavMeshRotate.z);

							Matrix movedNewNavMeshToAxisMatrix = navMeshMatScale * navMeshMatRotation * navMeshMatTrans;

							movedNewNavMeshToAxisMatrix *= axisRotateResult;

							XMVECTOR resultScale;
							XMVECTOR resultPosition;
							XMVECTOR resultQuaternionRotate;

							XMMatrixDecompose(&resultScale, &resultQuaternionRotate, &resultPosition, movedNewNavMeshToAxisMatrix);

							Vec3 inputRotate;
							Vec3 inputPosition = resultPosition;
							inputPosition -= newNavMeshVertexToAxis;
							Vec3 inputScale = resultScale;

							// roll (x-axis rotation)
							double sinr_cosp = 2 * (resultQuaternionRotate.vector4_f32[3] * resultQuaternionRotate.vector4_f32[0] + resultQuaternionRotate.vector4_f32[1] * resultQuaternionRotate.vector4_f32[2]);
							double cosr_cosp = 1 - 2 * (resultQuaternionRotate.vector4_f32[0] * resultQuaternionRotate.vector4_f32[0] + resultQuaternionRotate.vector4_f32[1] * resultQuaternionRotate.vector4_f32[1]);
							inputRotate.x = std::atan2(sinr_cosp, cosr_cosp);

							// pitch (y-axis rotation)
							double sinp = 2 * (resultQuaternionRotate.vector4_f32[3] * resultQuaternionRotate.vector4_f32[1] - resultQuaternionRotate.vector4_f32[2] * resultQuaternionRotate.vector4_f32[0]);
							if (std::abs(sinp) >= 1)
								inputRotate.y = std::copysign(XM_PI / 2, sinp); // use 90 degrees if out of range
							else
								inputRotate.y = std::asin(sinp);

							// yaw (z-axis rotation)
							double siny_cosp = 2 * (resultQuaternionRotate.vector4_f32[3] * resultQuaternionRotate.vector4_f32[2] + resultQuaternionRotate.vector4_f32[0] * resultQuaternionRotate.vector4_f32[1]);
							double cosy_cosp = 1 - 2 * (resultQuaternionRotate.vector4_f32[1] * resultQuaternionRotate.vector4_f32[1] + resultQuaternionRotate.vector4_f32[2] * resultQuaternionRotate.vector4_f32[2]);
							inputRotate.z = std::atan2(siny_cosp, cosy_cosp);

							m_selectNavMesh->Transform()->SetLocalRot(inputRotate);
							m_selectNavMesh->Transform()->SetLocalPos(inputPosition);
							m_selectNavMesh->Transform()->SetLocalScale(inputScale);
						}

						////이동
						{
							Vec3 newNavMeshPosition = calculatedNewNavMeshPos;

							VTX triangleMesh[3];
							triangleMesh[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
							triangleMesh[1].vPos = Vec3(0.5f, 0.5f, 0.f);
							triangleMesh[2].vPos = Vec3(0.5f, -0.5f, 0.f);

							Matrix oldNavMeshMatrix = clickUpObject->Transform()->GetWorldMat();
							Vec3 oldTriangleWorldPos[3] = {};
							for (UINT i = 0; i < 3; ++i)
							{
								oldTriangleWorldPos[i] = XMVector3TransformCoord(triangleMesh[i].vPos, oldNavMeshMatrix);
							}


							Vec3 old0to1Vector = oldTriangleWorldPos[1] - oldTriangleWorldPos[0];
							Vec3 old1to2Vector = oldTriangleWorldPos[2] - oldTriangleWorldPos[1];
							Vec3 old2to0Vector = oldTriangleWorldPos[0] - oldTriangleWorldPos[2];

							Vec3 old0toNewNavVector = newNavMeshPosition - oldTriangleWorldPos[0];
							Vec3 old1toNewNavVector = newNavMeshPosition - oldTriangleWorldPos[1];
							Vec3 old2toNewNavVector = newNavMeshPosition - oldTriangleWorldPos[2];

							Vec3 nearVertexs[2];
							if (old0toNewNavVector.Cross(old0to1Vector).y > 0.f)
							{
								nearVertexs[0] = oldTriangleWorldPos[0];
								nearVertexs[1] = oldTriangleWorldPos[1];
							}
							else if (old1toNewNavVector.Cross(old1to2Vector).y > 0.f)
							{
								nearVertexs[0] = oldTriangleWorldPos[1];
								nearVertexs[1] = oldTriangleWorldPos[2];
							}
							else if (old2toNewNavVector.Cross(old2to0Vector).y > 0.f)
							{
								nearVertexs[0] = oldTriangleWorldPos[0];
								nearVertexs[1] = oldTriangleWorldPos[2];
							}


							Vec3 newNavScale = m_selectNavMesh->Transform()->GetLocalScale();
							Matrix matScale = XMMatrixScaling(newNavScale.x, newNavScale.y, newNavScale.z);

							Vec3 newNavRotate = m_selectNavMesh->Transform()->GetLocalRot();
							Matrix matRotation = XMMatrixRotationX(newNavRotate.x);
							matRotation *= XMMatrixRotationY(newNavRotate.y);
							matRotation *= XMMatrixRotationZ(newNavRotate.z);

							Vec3 newNavPosition = m_selectNavMesh->Transform()->GetLocalPos();
							
							Matrix matTrans = XMMatrixTranslation(newNavPosition.x, newNavPosition.y, newNavPosition.z);

							Matrix newNavMeshMatrix = matScale * matRotation * matTrans;

							Vec3 newTriangleWorldPos[3] = {};
							for (UINT i = 0; i < 3; ++i)
							{
								newTriangleWorldPos[i] = XMVector3TransformCoord(triangleMesh[i].vPos, newNavMeshMatrix);
							}

							float nearToNewDist1 = Vec3::Distance(nearVertexs[0], newTriangleWorldPos[0]);
							float nearToNewDist2 = Vec3::Distance(nearVertexs[1], newTriangleWorldPos[0]);

							if (nearToNewDist1 < nearToNewDist2)
							{
								Vec3 movePosition = nearVertexs[0] - newTriangleWorldPos[0];

								Vec3 nowNewNavMeshPosition = m_selectNavMesh->Transform()->GetLocalPos();
								nowNewNavMeshPosition += movePosition;
								m_selectNavMesh->Transform()->SetLocalPos(nowNewNavMeshPosition);
							}
							else
							{
								Vec3 movePosition = nearVertexs[1] - newTriangleWorldPos[0];

								Vec3 nowNewNavMeshPosition = m_selectNavMesh->Transform()->GetLocalPos();
								nowNewNavMeshPosition += movePosition;
								m_selectNavMesh->Transform()->SetLocalPos(nowNewNavMeshPosition);
							}
						}


					}

				}
			}
			else
			{
				m_isNavMeshModify = false;
			}

		}
	}


	if (m_isNavMeshModify == true)
	{
		if (KEYTAB(KEY_TYPE::KEY_I))
		{
			//scale front
			Vec3 selectNavMeshScale = m_selectNavMesh->Transform()->GetLocalScale();
			selectNavMeshScale.y += 100.f;
			m_selectNavMesh->Transform()->SetLocalScale(selectNavMeshScale);


			Vec3 selectNavMeshPosition = m_selectNavMesh->Transform()->GetLocalPos();

			Vec3 moveDirection = (m_selectNavMesh->Transform()->GetLocalDir(DIR_TYPE::DIR_UP)*-1.f);

			selectNavMeshPosition += 50.f * moveDirection;
			m_selectNavMesh->Transform()->SetLocalPos(selectNavMeshPosition);
		}

		if (KEYTAB(KEY_TYPE::KEY_K))
		{
			//scale back
			Vec3 selectNavMeshScale = m_selectNavMesh->Transform()->GetLocalScale();
			selectNavMeshScale.y -= 100.f;
			m_selectNavMesh->Transform()->SetLocalScale(selectNavMeshScale);


			Vec3 selectNavMeshPosition = m_selectNavMesh->Transform()->GetLocalPos();

			Vec3 moveDirection = (m_selectNavMesh->Transform()->GetLocalDir(DIR_TYPE::DIR_UP)*-1.f);

			selectNavMeshPosition -= 50.f * moveDirection;
			m_selectNavMesh->Transform()->SetLocalPos(selectNavMeshPosition);
		}

		if (KEYTAB(KEY_TYPE::KEY_U))
		{
			Vec3 changeScale;
			Vec3 changeRotate;
			Vec3 changePosition;

			VTX triangleMesh[3];
			triangleMesh[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
			triangleMesh[1].vPos = Vec3(0.5f, 0.5f, 0.f);
			triangleMesh[2].vPos = Vec3(0.5f, -0.5f, 0.f);

			Matrix selectNavMeshMatrix = m_selectNavMesh->Transform()->GetWorldMat();
			Vec3 selectTriangleWorldPos[3] = {};
			for (UINT i = 0; i < 3; ++i)
			{
				selectTriangleWorldPos[i] = XMVector3TransformCoord(triangleMesh[i].vPos, selectNavMeshMatrix);
			}

			Vec3 rotateAxis = selectTriangleWorldPos[0] - selectTriangleWorldPos[1];

			RotateAxisRadian(m_selectNavMesh, rotateAxis, -10.f, changeScale, changeRotate, changePosition);

			m_selectNavMesh->Transform()->SetLocalScale(changeScale);
			m_selectNavMesh->Transform()->SetLocalRot(changeRotate);
			m_selectNavMesh->Transform()->SetLocalPos(changePosition);
		}
		
		if (KEYTAB(KEY_TYPE::KEY_O))
		{
			Vec3 changeScale;
			Vec3 changeRotate;
			Vec3 changePosition;

			VTX triangleMesh[3];
			triangleMesh[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
			triangleMesh[1].vPos = Vec3(0.5f, 0.5f, 0.f);
			triangleMesh[2].vPos = Vec3(0.5f, -0.5f, 0.f);

			Matrix selectNavMeshMatrix = m_selectNavMesh->Transform()->GetWorldMat();
			Vec3 selectTriangleWorldPos[3] = {};
			for (UINT i = 0; i < 3; ++i)
			{
				selectTriangleWorldPos[i] = XMVector3TransformCoord(triangleMesh[i].vPos, selectNavMeshMatrix);
			}

			Vec3 rotateAxis = selectTriangleWorldPos[0] - selectTriangleWorldPos[1];

			RotateAxisRadian(m_selectNavMesh, rotateAxis, -10.f, changeScale, changeRotate, changePosition);

			m_selectNavMesh->Transform()->SetLocalScale(changeScale);
			m_selectNavMesh->Transform()->SetLocalRot(changeRotate);
			m_selectNavMesh->Transform()->SetLocalPos(changePosition);
		}
	}
}

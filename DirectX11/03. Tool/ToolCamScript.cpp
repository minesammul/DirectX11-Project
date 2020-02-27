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

				}
				else
				{
					if (clickUpObject != nullptr)
					{
						//새로운 Nav Mesh를 기존의 Nav Mesh에 붙인다.

						//크기
						//우선 새로운 Nav와 기존의 Nav와 가장 가까운 선분이 무엇인지 찾는다.
						{
							Vec3 newNavMeshPosition = m_selectNavMesh->Transform()->GetLocalPos();

							VTX triangleMesh[3];
							triangleMesh[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
							triangleMesh[1].vPos = Vec3(0.5f, 0.5f, 0.f);
							triangleMesh[2].vPos = Vec3(0.5f, -0.5f, 0.f);

							Matrix oldNavMeshMatrix = clickUpObject->Collider3D()->GetWorldMat();
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


							Matrix newNavMeshMatrix = m_selectNavMesh->Collider3D()->GetWorldMat();
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

							Matrix oldNavMeshMatrix = clickUpObject->Collider3D()->GetWorldMat();
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


							Matrix newNavMeshMatrix = m_selectNavMesh->Collider3D()->GetWorldMat();
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


						//이동
						{
							Vec3 newNavMeshPosition = m_selectNavMesh->Transform()->GetLocalPos();

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
		}
	}

}

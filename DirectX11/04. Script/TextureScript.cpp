#include "stdafx.h"
#include "TextureScript.h"

#include <Camera.h>


CTextureScript::CTextureScript():
	CScript((UINT)SCRIPT_TYPE::TEXTURESCRIPT)
{
	UValue = 0.f;
	
}


CTextureScript::~CTextureScript()
{
}

void CTextureScript::start()
{
	cloneMtrl = Object()->MeshRender()->GetCloneMaterial();
	CResPtr<CTexture> texture = Object()->Animator2D()->GetCurAnim()->GetNowFrameData().pTex;
	cloneMtrl->SetData(SHADER_PARAM::TEX_0, &texture);

	beforeMainCameraPosition = Object()->Transform()->GetLocalPos();
}

void CTextureScript::update()
{
	vector<CCamera*> cameras = CSceneMgr::GetInst()->GetCurScene()->GetCamera();
	CCamera* mainCamera = nullptr;
	for (int index = 0; index < cameras.size(); index++)
	{
		CCamera* curCamera = cameras[index];

		if (curCamera->Object()->GetName().compare(L"MainCamera") == 0)
		{
			mainCamera = curCamera;
			break;
		}
	}

	if (mainCamera != nullptr)
	{
		Vec3 mainCameraPosition = mainCamera->Object()->Transform()->GetLocalPos();
		//Vec3 objectPosition = Object()->Transform()->GetLocalPos();
		//objectPosition.x = mainCameraPosition.x;
		//objectPosition.y = mainCameraPosition.y;
		//Object()->Transform()->SetLocalPos(objectPosition);

		if (beforeMainCameraPosition.x < mainCameraPosition.x)
		{
			cloneMtrl = Object()->MeshRender()->GetCloneMaterial();
			UValue += U_VALUE;
			cloneMtrl->SetData(SHADER_PARAM::FLOAT_0, &UValue);
		}
		else if(beforeMainCameraPosition.x > mainCameraPosition.x)
		{
			cloneMtrl = Object()->MeshRender()->GetCloneMaterial();
			UValue -= U_VALUE;
			cloneMtrl->SetData(SHADER_PARAM::FLOAT_0, &UValue);
		}
		else
		{

		}

		beforeMainCameraPosition = mainCameraPosition;
	}

}

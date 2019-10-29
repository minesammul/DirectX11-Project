#include "stdafx.h"
#include "Z2FadeScript.h"

#include <Camera.h>

CZ2FadeScript::CZ2FadeScript() : 
	CScript((UINT)SCRIPT_TYPE::Z2FADESCRIPT)
{
}


CZ2FadeScript::~CZ2FadeScript()
{
}

void CZ2FadeScript::start()
{
	alphaValue = 1.f;
	isStart = true;
}

void CZ2FadeScript::update()
{
	if (isStart == true)
	{
		cloneMtrl = Object()->MeshRender()->GetCloneMaterial();
		alphaValue -= 0.01f;
		cloneMtrl->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);

		if (alphaValue <= 0.f)
		{
			isStart = false;
			alphaValue = 1.f;
		}

		vector<CCamera*> cameras = CSceneMgr::GetInst()->GetCurScene()->GetCamera();
		if (cameras.empty() == false)
		{
			for (int index = 0; index < cameras.size(); index++)
			{
				if (cameras[index]->Object()->GetName().compare(L"MainCamera") == 0)
				{
					Vec3 cameraPosition = cameras[index]->Object()->Transform()->GetLocalPos();
					Vec3 objectPosition = Object()->Transform()->GetLocalPos();
					objectPosition.x = cameraPosition.x;
					objectPosition.y = cameraPosition.y;

					Object()->Transform()->SetLocalPos(objectPosition);
					break;
				}
			}
		}
	}
}

#include "stdafx.h"
#include "SSN011PlayerUIScript.h"

#include "SSN002PlayerScript.h"

CSSN011PlayerUIScript::CSSN011PlayerUIScript():
	CScript((UINT)SCRIPT_TYPE::SSN011PLAYERUISCRIPT)
{
}


CSSN011PlayerUIScript::~CSSN011PlayerUIScript()
{
}

void CSSN011PlayerUIScript::start()
{
	for (int index = 0; index < Object()->GetChild().size(); index++)
	{
		wstring findObjectName = Object()->GetChild()[index]->GetName();
		if (findObjectName.compare(L"PlayerHPBar") == 0)
		{
			playerHPBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"PlayerSPBar") == 0)
		{
			playerSPBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"MonsterHPBar") == 0)
		{
			monsterHPBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"PlayerHPProgressBar") == 0)
		{
			playerHPProgressBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"PlayerSPProgressBar") == 0)
		{
			playerSPProgressBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"MonsterHPProgressBar") == 0)
		{
			monsterHPProgressBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"PlayerHPDecreaseBar") == 0)
		{
			playerHPDecreaseBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"PlayerSPDecreaseBar") == 0)
		{
			playerSPDecreaseBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"MonsterHPDecreaseBar") == 0)
		{
			monsterHPDecreaseBar = Object()->GetChild()[index];
		}
	}

	{
		playerHPBar->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));

		CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"UIMtrl");
		playerHPBar->MeshRender()->SetMaterial(pMtrl);

		CResPtr<CTexture> findTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\HpBar.png");
		playerHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &findTexture);

		int alphaOn = 1;
		playerHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
	}

	{
		playerSPBar->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));

		CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"UIMtrl");
		playerSPBar->MeshRender()->SetMaterial(pMtrl);

		CResPtr<CTexture> findTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\HpBar.png");
		playerSPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &findTexture);

		int alphaOn = 1;
		playerSPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
	}

	{
		monsterHPBar->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));

		CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"UIMtrl");
		monsterHPBar->MeshRender()->SetMaterial(pMtrl);

		CResPtr<CTexture> findTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\StaminaBar.png");
		monsterHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &findTexture);

		int alphaOn = 0;
		monsterHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
	}

	{
		playerHPProgressBar->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));

		CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"UIMtrl");
		playerHPProgressBar->MeshRender()->SetMaterial(pMtrl);

		CResPtr<CTexture> findTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\ProgressBar.png");
		playerHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &findTexture);
		
		int alphaOn = 1;
		playerHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
	}

	{
		playerSPProgressBar->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));

		CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"UIMtrl");
		playerSPProgressBar->MeshRender()->SetMaterial(pMtrl);

		CResPtr<CTexture> findTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\ProgressBar.png");
		playerSPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &findTexture);

		int alphaOn = 1;
		playerSPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
	}

	{
		monsterHPProgressBar->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));

		CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"UIMtrl");
		monsterHPProgressBar->MeshRender()->SetMaterial(pMtrl);

		CResPtr<CTexture> findTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\ProgressBar.png");
		monsterHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &findTexture);

		int alphaOn = 0;
		monsterHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
	}

	{
		playerHPDecreaseBar->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));

		CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"UIMtrl");
		playerHPDecreaseBar->MeshRender()->SetMaterial(pMtrl);

		CResPtr<CTexture> findTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\DecreaseBar.png");
		playerHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &findTexture);

		int alphaOn = 1;
		playerHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
	}

	{
		playerSPDecreaseBar->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));

		CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"UIMtrl");
		playerSPDecreaseBar->MeshRender()->SetMaterial(pMtrl);

		CResPtr<CTexture> findTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\DecreaseBar.png");
		playerSPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &findTexture);

		int alphaOn = 1;
		playerSPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
	}

	{
		monsterHPDecreaseBar->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));

		CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"UIMtrl");
		monsterHPDecreaseBar->MeshRender()->SetMaterial(pMtrl);

		CResPtr<CTexture> findTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\DecreaseBar.png");
		monsterHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &findTexture);

		int alphaOn = 0;
		monsterHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
	}

	{
		Vec3 progressBarScale = playerHPProgressBar->Transform()->GetLocalPos();
		progressBarScale.x = 500.f;
		progressBarScale.y = 25.f;
		playerHPProgressBar->Transform()->SetLocalScale(progressBarScale);

		Vec3 progressBarPosition = playerHPProgressBar->Transform()->GetLocalPos();
		progressBarPosition.x = -350.f;
		progressBarPosition.y = 300.f;
		progressBarPosition.z = 3.f;
		playerHPProgressBar->Transform()->SetLocalPos(progressBarPosition);


		Vec3 decreaseBarScale = playerHPDecreaseBar->Transform()->GetLocalPos();
		decreaseBarScale.x = 500.f;
		decreaseBarScale.y = 10.f;
		playerHPDecreaseBar->Transform()->SetLocalScale(decreaseBarScale);

		Vec3 decreaseBarPosition = playerHPDecreaseBar->Transform()->GetLocalPos();
		decreaseBarPosition.x = -350.f;
		decreaseBarPosition.y = 300.f;
		decreaseBarPosition.z = 2.f;
		playerHPDecreaseBar->Transform()->SetLocalPos(decreaseBarPosition);


		Vec3 hpBarScale = playerHPBar->Transform()->GetLocalPos();
		hpBarScale.x = 500.f;
		hpBarScale.y = 10.f;
		playerHPBar->Transform()->SetLocalScale(hpBarScale);

		Vec3 hpBarPosition = playerHPBar->Transform()->GetLocalPos();
		hpBarPosition.x = -350.f;
		hpBarPosition.y = 300.f;
		hpBarPosition.z = 1.f;
		playerHPBar->Transform()->SetLocalPos(hpBarPosition);
	}

	{
		Vec3 progressBarScale = playerSPProgressBar->Transform()->GetLocalPos();
		progressBarScale.x = 500.f;
		progressBarScale.y = 25.f;
		playerSPProgressBar->Transform()->SetLocalScale(progressBarScale);

		Vec3 progressBarPosition = playerSPProgressBar->Transform()->GetLocalPos();
		progressBarPosition.x = -350.f;
		progressBarPosition.y = 280.f;
		progressBarPosition.z = 3.f;
		playerSPProgressBar->Transform()->SetLocalPos(progressBarPosition);


		Vec3 decreaseBarScale = playerSPDecreaseBar->Transform()->GetLocalPos();
		decreaseBarScale.x = 500.f;
		decreaseBarScale.y = 10.f;
		playerSPDecreaseBar->Transform()->SetLocalScale(decreaseBarScale);

		Vec3 decreaseBarPosition = playerSPDecreaseBar->Transform()->GetLocalPos();
		decreaseBarPosition.x = -350.f;
		decreaseBarPosition.y = 280.f;
		decreaseBarPosition.z = 2.f;
		playerSPDecreaseBar->Transform()->SetLocalPos(decreaseBarPosition);


		Vec3 spBarScale = playerSPBar->Transform()->GetLocalPos();
		spBarScale.x = 500.f;
		spBarScale.y = 10.f;
		playerSPBar->Transform()->SetLocalScale(spBarScale);

		Vec3 spBarPosition = playerHPBar->Transform()->GetLocalPos();
		spBarPosition.x = -350.f;
		spBarPosition.y = 280.f;
		spBarPosition.z = 1.f;
		playerSPBar->Transform()->SetLocalPos(spBarPosition);
	}

	{
		Vec3 progressBarScale = monsterHPProgressBar->Transform()->GetLocalPos();
		progressBarScale.x = 700.f;
		progressBarScale.y = 25.f;
		monsterHPProgressBar->Transform()->SetLocalScale(progressBarScale);

		Vec3 progressBarPosition = monsterHPProgressBar->Transform()->GetLocalPos();
		progressBarPosition.x = 0.f;
		progressBarPosition.y = -250.f;
		progressBarPosition.z = 3.f;
		monsterHPProgressBar->Transform()->SetLocalPos(progressBarPosition);


		Vec3 decreaseBarScale = monsterHPDecreaseBar->Transform()->GetLocalPos();
		decreaseBarScale.x = 700.f;
		decreaseBarScale.y = 10.f;
		monsterHPDecreaseBar->Transform()->SetLocalScale(decreaseBarScale);

		Vec3 decreaseBarPosition = monsterHPDecreaseBar->Transform()->GetLocalPos();
		decreaseBarPosition.x = 0.f;
		decreaseBarPosition.y = -250.f;
		decreaseBarPosition.z = 2.f;
		monsterHPDecreaseBar->Transform()->SetLocalPos(decreaseBarPosition);


		Vec3 spBarScale = monsterHPBar->Transform()->GetLocalPos();
		spBarScale.x = 700.f;
		spBarScale.y = 10.f;
		monsterHPBar->Transform()->SetLocalScale(spBarScale);

		Vec3 spBarPosition = playerHPBar->Transform()->GetLocalPos();
		spBarPosition.x = 0.f;
		spBarPosition.y = -250.f;
		spBarPosition.z = 1.f;
		monsterHPBar->Transform()->SetLocalPos(spBarPosition);
	}

	playerHPBarInitScaleX = playerHPBar->Transform()->GetLocalScale().x;
	playerSPBarInitScaleX = playerSPBar->Transform()->GetLocalScale().x;
	monsterHPBarInitScaleX = monsterHPBar->Transform()->GetLocalScale().x;

	playerHPBarInitPositionX = playerHPBar->Transform()->GetLocalPos().x;
	playerSPBarInitPositionX = playerSPBar->Transform()->GetLocalPos().x;
	monsterHPBarInitPositionX = monsterHPBar->Transform()->GetLocalPos().x;

	vector<CGameObject*> findObject;
	CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"Player", findObject);

	int playerMaxHP = 0;
	int playerMaxSP = 0;
	for (int index = 0; index < findObject[0]->GetScripts().size(); index++)
	{
		if (findObject[0]->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN002PLAYERSCRIPT)
		{
			CSSN002PlayerScript* playerScript = dynamic_cast<CSSN002PlayerScript*>(findObject[0]->GetScripts()[index]);
			playerMaxHP = playerScript->GetPlayerHP();
			playerMaxSP = playerScript->GetPlayerSP();
			break;
		}
	}

	playerHPRatio = playerHPBarInitScaleX / playerMaxHP;
	playerSPRatio = playerSPBarInitScaleX / playerMaxSP;
}

void CSSN011PlayerUIScript::update()
{
	CResPtr<CTexture> hpTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\HpBar.png");
	playerHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &hpTexture);
	monsterHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &hpTexture);

	CResPtr<CTexture> spTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\StaminaBar.png");
	playerSPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &spTexture);

	CResPtr<CTexture> progressTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\ProgressBar.png");
	playerHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &progressTexture);
	playerSPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &progressTexture);
	monsterHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &progressTexture);

	CResPtr<CTexture> decreaseTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\DecreaseBar.png");
	playerHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &decreaseTexture);
	playerSPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &decreaseTexture);
	monsterHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &decreaseTexture);
}

void CSSN011PlayerUIScript::OnMonsterUI()
{
	int alphaOn = 1;
	monsterHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
	monsterHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
	monsterHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
}

void CSSN011PlayerUIScript::OffMonsterUI()
{
	int alphaOn = 0;
	monsterHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
	monsterHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
	monsterHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::INT_0, &alphaOn);
}

void CSSN011PlayerUIScript::SetMonsterHPRation(int maxHP)
{
	monsterHPRatio = monsterHPBarInitScaleX / maxHP;
}

void CSSN011PlayerUIScript::CalculationPlayerHPUI(int nowHP)
{
	if (nowHP > 0)
	{
		float changePlayerHPBarScaleX = nowHP * playerHPRatio;
		float movePlayerHPBarPositionXValue = playerHPBarInitScaleX - changePlayerHPBarScaleX;
		movePlayerHPBarPositionXValue /= 2;

		Vec3 playerHPBarScale = playerHPBar->Transform()->GetLocalScale();
		playerHPBarScale.x = changePlayerHPBarScaleX;
		playerHPBar->Transform()->SetLocalScale(playerHPBarScale);

		Vec3 playerHPBarPosition = playerHPBar->Transform()->GetLocalPos();
		playerHPBarPosition.x = playerHPBarInitPositionX - movePlayerHPBarPositionXValue;
		playerHPBar->Transform()->SetLocalPos(playerHPBarPosition);
	}
	else
	{
		Vec3 playerHPBarScale = playerHPBar->Transform()->GetLocalScale();
		playerHPBarScale.x = 0.f;
		playerHPBar->Transform()->SetLocalScale(playerHPBarScale);
	}
}

void CSSN011PlayerUIScript::CalculationPlayerSPUI(int nowSP)
{
	if (nowSP > 0)
	{
		float changePlayerSPBarScaleX = nowSP * playerSPRatio;
		float movePlayerSPBarPositionXValue = playerSPBarInitScaleX - changePlayerSPBarScaleX;
		movePlayerSPBarPositionXValue /= 2;

		Vec3 playerSPBarScale = playerSPBar->Transform()->GetLocalScale();
		playerSPBarScale.x = changePlayerSPBarScaleX;
		playerSPBar->Transform()->SetLocalScale(playerSPBarScale);

		Vec3 playerSPBarPosition = playerSPBar->Transform()->GetLocalPos();
		playerSPBarPosition.x = playerSPBarInitPositionX - movePlayerSPBarPositionXValue;
		playerSPBar->Transform()->SetLocalPos(playerSPBarPosition);
	}
	else
	{
		Vec3 playerSPBarScale = playerSPBar->Transform()->GetLocalScale();
		playerSPBarScale.x = 0.f;
		playerSPBar->Transform()->SetLocalScale(playerSPBarScale);
	}
}

void CSSN011PlayerUIScript::CalculationMonsterHPUI(int nowHP)
{
	if (nowHP > 0)
	{
		float changeMonsterHPBarScaleX = nowHP * monsterHPRatio;
		float moveMonsterHPBarPositionXValue = monsterHPBarInitScaleX - changeMonsterHPBarScaleX;
		moveMonsterHPBarPositionXValue /= 2;

		Vec3 monsterHPBarScale = monsterHPBar->Transform()->GetLocalScale();
		monsterHPBarScale.x = changeMonsterHPBarScaleX;
		monsterHPBar->Transform()->SetLocalScale(monsterHPBarScale);

		Vec3 monsterHPBarPosition = monsterHPBar->Transform()->GetLocalPos();
		monsterHPBarPosition.x = monsterHPBarInitPositionX - moveMonsterHPBarPositionXValue;
		monsterHPBar->Transform()->SetLocalPos(monsterHPBarPosition);
	}
	else
	{
		Vec3 monsterHPBarScale = monsterHPBar->Transform()->GetLocalScale();
		monsterHPBarScale.x = monsterHPBarInitScaleX;
		monsterHPBar->Transform()->SetLocalScale(monsterHPBarScale);

		OffMonsterUI();
	}
}

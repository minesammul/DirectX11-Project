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

void CSSN011PlayerUIScript::SetUIComponent(CGameObject* uiObject, wstring textureName, float alphaValue, Vec3 scale, Vec3 position)
{
	uiObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));

	CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"UIMtrl");
	uiObject->MeshRender()->SetMaterial(pMtrl);

	CResPtr<CTexture> findTexture = CResMgr::GetInst()->FindRes<CTexture>(textureName);
	uiObject->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &findTexture);
	uiObject->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);


	uiObject->Transform()->SetLocalScale(scale);
	uiObject->Transform()->SetLocalPos(position);
}

void CSSN011PlayerUIScript::FadeInOutMonsterDieText()
{
	if(isMonsterDie == true)
	{
		static float alphaValue = 0.f;
		static bool isFadeIn = true;

		if (isFadeIn == true)
		{
			alphaValue += CTimeMgr::GetInst()->GetDeltaTime() * 0.5f;

			if (alphaValue >= 1.f)
			{
				alphaValue = 1.f;
				isFadeIn = false;
			}

			float textBackgroundAlpha = alphaValue * 2.f;

			if (textBackgroundAlpha >= 1.f)
			{
				textBackgroundAlpha = 1.f;
			}

			textBackground->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &textBackgroundAlpha);
			monsterDieText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);
			monsterDieEffectText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);


		}
		else
		{
			alphaValue -= CTimeMgr::GetInst()->GetDeltaTime() * 0.5f;

			if (alphaValue <= 0.f)
			{
				isMonsterDie = false;
				isFadeIn = true;
				alphaValue = 0.f;
			}

			textBackground->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);
			monsterDieText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);
			monsterDieEffectText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);
		}

	}
}

void CSSN011PlayerUIScript::FadeInOutPlayerDieText()
{
	if (isPlayerDie == true)
	{
		static float alphaValue = 0.f;

		alphaValue += CTimeMgr::GetInst()->GetDeltaTime() * 0.5f;

		if (alphaValue >= 1.f)
		{
			alphaValue = 1.f;
		}

		float textBackgroundAlpha = alphaValue * 2.f;

		if (textBackgroundAlpha >= 1.f)
		{
			textBackgroundAlpha = 1.f;
		}

		textBackground->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &textBackgroundAlpha);
		playerDieText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);
	}
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
		else if (findObjectName.compare(L"MonsterDieText") == 0)
		{
			monsterDieText = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"MonsterDieEffectText") == 0)
		{
			monsterDieEffectText = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"PlayerDieText") == 0)
		{
			playerDieText = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"TextBackground") == 0)
		{
			textBackground = Object()->GetChild()[index];
		}

	}

	SetUIComponent(playerHPBar, L"Texture\\UI\\HpBar.png", 1.f, Vec3(500.f, 10.f, 1.f), Vec3(-350.f, 300.f, 10.f));
	SetUIComponent(playerSPBar, L"Texture\\UI\\StaminaBar.png", 1.f, Vec3(500.f, 10.f, 1.f), Vec3(-350.f, 280.f, 10.f));
	SetUIComponent(monsterHPBar, L"Texture\\UI\\HpBar.png", 1.f, Vec3(700.f, 10.f, 1.f), Vec3(0.f, -250.f, 10.f));

	SetUIComponent(playerHPProgressBar, L"Texture\\UI\\ProgressBar.png", 1.f, Vec3(500.f, 25.f, 1.f), Vec3(-350.f, 300.f, 30.f));
	SetUIComponent(playerSPProgressBar, L"Texture\\UI\\ProgressBar.png", 1.f, Vec3(500.f, 25.f, 1.f), Vec3(-350.f, 280.f, 30.f));
	SetUIComponent(monsterHPProgressBar, L"Texture\\UI\\ProgressBar.png", 0.f, Vec3(700.f, 25.f, 1.f), Vec3(0.f, -250.f, 30.f));

	SetUIComponent(playerHPDecreaseBar, L"Texture\\UI\\DecreaseBar.png", 1.f, Vec3(500.f, 10.f, 1.f), Vec3(-350.f, 300.f, 20.f));
	SetUIComponent(playerSPDecreaseBar, L"Texture\\UI\\DecreaseBar.png", 1.f, Vec3(500.f, 10.f, 1.f), Vec3(-350.f, 280.f, 20.f));
	SetUIComponent(monsterHPDecreaseBar, L"Texture\\UI\\DecreaseBar.png", 0.f, Vec3(700.f, 10.f, 1.f), Vec3(0.f, -250.f, 20.f));

	SetUIComponent(monsterDieText, L"Texture\\UI\\MonsterDieUI.png", 0.f, Vec3(2048.f, 192.f, 1.f), Vec3(0.f, 0.f, 5.f));
	SetUIComponent(monsterDieEffectText, L"Texture\\UI\\MonsterDieUIPostEffect.png", 0.f, Vec3(2048.f, 192.f, 1.f), Vec3(0.f, 0.f, 4.f));
	SetUIComponent(playerDieText, L"Texture\\UI\\PlayerDieUI.png", 0.f, Vec3(2048.f, 192.f, 1.f), Vec3(0.f, 0.f, 5.f));
	SetUIComponent(textBackground, L"Texture\\UI\\MENU_KUROOBI.png", 0.f, Vec3(3072.f, 192.f, 1.f), Vec3(0.f, 0.f, 6.f));


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

	isPlayerDie = false;
	isMonsterDie = false;
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

	CResPtr<CTexture> monsterDieUITexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\MonsterDieUI.png");
	monsterDieText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &monsterDieUITexture);

	CResPtr<CTexture> monsterDieEffectUITexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\MonsterDieUIPostEffect.png");
	monsterDieEffectText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &monsterDieEffectUITexture);

	CResPtr<CTexture> playerDieUITexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\PlayerDieUI.png");
	playerDieText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &playerDieUITexture);

	CResPtr<CTexture> textBackgroundTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\MENU_KUROOBI.png");
	textBackground->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &textBackgroundTexture);

	FadeInOutMonsterDieText();
	FadeInOutPlayerDieText();
}

void CSSN011PlayerUIScript::OnMonsterUI()
{
	float alphaOn = 1.f;
	monsterHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaOn);
	monsterHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaOn);
	monsterHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaOn);
}

void CSSN011PlayerUIScript::OffMonsterUI()
{
	float alphaOn = 0.f;
	monsterHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaOn);
	monsterHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaOn);
	monsterHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaOn);
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

		isPlayerDie = false;
	}
	else
	{
		Vec3 playerHPBarScale = playerHPBar->Transform()->GetLocalScale();
		playerHPBarScale.x = 0.f;
		playerHPBar->Transform()->SetLocalScale(playerHPBarScale);

		isPlayerDie = true;
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

		isMonsterDie = true;
	}
}

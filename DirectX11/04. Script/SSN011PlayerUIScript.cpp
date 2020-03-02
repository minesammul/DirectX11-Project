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
	if(mIsOnMonsterDieTextUI == true)
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

			mTextBackground->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &textBackgroundAlpha);
			mMonsterDieText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);
			mMonsterDieEffectText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);


		}
		else
		{
			alphaValue -= CTimeMgr::GetInst()->GetDeltaTime() * 0.5f;

			if (alphaValue <= 0.f)
			{
				mIsOnMonsterDieTextUI = false;
				isFadeIn = true;
				alphaValue = 0.f;
			}

			mTextBackground->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);
			mMonsterDieText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);
			mMonsterDieEffectText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);
		}

	}
}

void CSSN011PlayerUIScript::FadeInOutPlayerDieText()
{
	if (mIsOnPlayerDieTextUI == true)
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

		mTextBackground->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &textBackgroundAlpha);
		mPlayerDieText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);
	}
}

void CSSN011PlayerUIScript::FindUIObject()
{
	for (int index = 0; index < Object()->GetChild().size(); index++)
	{
		wstring findObjectName = Object()->GetChild()[index]->GetName();
		if (findObjectName.compare(L"PlayerHPBar") == 0)
		{
			mPlayerHPBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"PlayerSPBar") == 0)
		{
			mPlayerSPBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"MonsterHPBar") == 0)
		{
			mMonsterHPBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"PlayerHPProgressBar") == 0)
		{
			mPlayerHPProgressBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"PlayerSPProgressBar") == 0)
		{
			mPlayerSPProgressBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"MonsterHPProgressBar") == 0)
		{
			mMonsterHPProgressBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"PlayerHPDecreaseBar") == 0)
		{
			mPlayerHPDecreaseBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"PlayerSPDecreaseBar") == 0)
		{
			mPlayerSPDecreaseBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"MonsterHPDecreaseBar") == 0)
		{
			mMonsterHPDecreaseBar = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"MonsterDieText") == 0)
		{
			mMonsterDieText = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"MonsterDieEffectText") == 0)
		{
			mMonsterDieEffectText = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"PlayerDieText") == 0)
		{
			mPlayerDieText = Object()->GetChild()[index];
		}
		else if (findObjectName.compare(L"TextBackground") == 0)
		{
			mTextBackground = Object()->GetChild()[index];
		}

	}
}

void CSSN011PlayerUIScript::start()
{
	FindUIObject();

	SetUIComponent(mPlayerHPBar, L"Texture\\UI\\HpBar.png", 1.f, Vec3(500.f, 10.f, 1.f), Vec3(-350.f, 300.f, 10.f));
	SetUIComponent(mPlayerSPBar, L"Texture\\UI\\StaminaBar.png", 1.f, Vec3(500.f, 10.f, 1.f), Vec3(-350.f, 280.f, 10.f));
	SetUIComponent(mMonsterHPBar, L"Texture\\UI\\HpBar.png", 1.f, Vec3(700.f, 10.f, 1.f), Vec3(0.f, -250.f, 10.f));

	SetUIComponent(mPlayerHPProgressBar, L"Texture\\UI\\ProgressBar.png", 1.f, Vec3(500.f, 25.f, 1.f), Vec3(-350.f, 300.f, 30.f));
	SetUIComponent(mPlayerSPProgressBar, L"Texture\\UI\\ProgressBar.png", 1.f, Vec3(500.f, 25.f, 1.f), Vec3(-350.f, 280.f, 30.f));
	SetUIComponent(mMonsterHPProgressBar, L"Texture\\UI\\ProgressBar.png", 0.f, Vec3(700.f, 25.f, 1.f), Vec3(0.f, -250.f, 30.f));

	SetUIComponent(mPlayerHPDecreaseBar, L"Texture\\UI\\DecreaseBar.png", 1.f, Vec3(500.f, 10.f, 1.f), Vec3(-350.f, 300.f, 20.f));
	SetUIComponent(mPlayerSPDecreaseBar, L"Texture\\UI\\DecreaseBar.png", 1.f, Vec3(500.f, 10.f, 1.f), Vec3(-350.f, 280.f, 20.f));
	SetUIComponent(mMonsterHPDecreaseBar, L"Texture\\UI\\DecreaseBar.png", 0.f, Vec3(700.f, 10.f, 1.f), Vec3(0.f, -250.f, 20.f));

	SetUIComponent(mMonsterDieText, L"Texture\\UI\\MonsterDieUI.png", 0.f, Vec3(2048.f, 192.f, 1.f), Vec3(0.f, 0.f, 5.f));
	SetUIComponent(mMonsterDieEffectText, L"Texture\\UI\\MonsterDieUIPostEffect.png", 0.f, Vec3(2048.f, 192.f, 1.f), Vec3(0.f, 0.f, 4.f));
	SetUIComponent(mPlayerDieText, L"Texture\\UI\\PlayerDieUI.png", 0.f, Vec3(2048.f, 192.f, 1.f), Vec3(0.f, 0.f, 5.f));
	SetUIComponent(mTextBackground, L"Texture\\UI\\MENU_KUROOBI.png", 0.f, Vec3(3072.f, 192.f, 1.f), Vec3(0.f, 0.f, 6.f));


	mPlayerHPBarInitScaleX = mPlayerHPBar->Transform()->GetLocalScale().x;
	mPlayerSPBarInitScaleX = mPlayerSPBar->Transform()->GetLocalScale().x;
	mMonsterHPBarInitScaleX = mMonsterHPBar->Transform()->GetLocalScale().x;

	mPlayerHPBarInitPositionX = mPlayerHPBar->Transform()->GetLocalPos().x;
	mPlayerSPBarInitPositionX = mPlayerSPBar->Transform()->GetLocalPos().x;
	mMonsterHPBarInitPositionX = mMonsterHPBar->Transform()->GetLocalPos().x;

	mIsOnPlayerDieTextUI = false;
	mIsOnMonsterDieTextUI = false;

	mIsBGM = false;
	mBGMVolume = 0.0f;

	mPlayerHPRatio = 1.f;
	mPlayerSPRatio = 1.f;

	mMonsterHPRatio = 1.f;

	OffMonsterUI();
}

void CSSN011PlayerUIScript::update()
{
	CResPtr<CTexture> hpTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\HpBar.png");
	mPlayerHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &hpTexture);
	mMonsterHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &hpTexture);

	CResPtr<CTexture> spTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\StaminaBar.png");
	mPlayerSPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &spTexture);

	CResPtr<CTexture> progressTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\ProgressBar.png");
	mPlayerHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &progressTexture);
	mPlayerSPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &progressTexture);
	mMonsterHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &progressTexture);

	CResPtr<CTexture> decreaseTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\DecreaseBar.png");
	mPlayerHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &decreaseTexture);
	mPlayerSPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &decreaseTexture);
	mMonsterHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &decreaseTexture);

	CResPtr<CTexture> monsterDieUITexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\MonsterDieUI.png");
	mMonsterDieText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &monsterDieUITexture);

	CResPtr<CTexture> monsterDieEffectUITexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\MonsterDieUIPostEffect.png");
	mMonsterDieEffectText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &monsterDieEffectUITexture);

	CResPtr<CTexture> playerDieUITexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\PlayerDieUI.png");
	mPlayerDieText->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &playerDieUITexture);

	CResPtr<CTexture> textBackgroundTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\MENU_KUROOBI.png");
	mTextBackground->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &textBackgroundTexture);

	FadeInOutMonsterDieText();
	FadeInOutPlayerDieText();

	if (mIsBGM == true)
	{
		if (mBGMVolume < 0.5f)
		{
			mBGMVolume += CTimeMgr::GetInst()->GetDeltaTime() * 0.1f;
		}
		else
		{
			mBGMVolume = 0.5f;
		}

		CResPtr<CSound> pSound = CResMgr::GetInst()->Load<CSound>(L"IronGolemBGM.mp3", L"Sound\\IronGolemBGM.mp3");
		pSound->SetVolume(mBGMVolume);
	}
	else
	{
		if (mBGMVolume <= 0.f)
		{
			mBGMVolume = 0.f;
			CResPtr<CSound> pSound = CResMgr::GetInst()->Load<CSound>(L"IronGolemBGM.mp3", L"Sound\\IronGolemBGM.mp3");
			pSound->Stop();
		}
		else
		{
			mBGMVolume -= CTimeMgr::GetInst()->GetDeltaTime() * 0.1f;
			CResPtr<CSound> pSound = CResMgr::GetInst()->Load<CSound>(L"IronGolemBGM.mp3", L"Sound\\IronGolemBGM.mp3");
			pSound->SetVolume(mBGMVolume);
		}
	}
}

void CSSN011PlayerUIScript::OnMonsterUI()
{
	float alphaOn = 1.f;
	mMonsterHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaOn);
	mMonsterHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaOn);
	mMonsterHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaOn);

	// Sound 파일 로딩
	mIsBGM = true;
	CResPtr<CSound> pSound = CResMgr::GetInst()->Load<CSound>(L"IronGolemBGM.mp3", L"Sound\\IronGolemBGM.mp3");
	pSound->Play(1);
	pSound->SetVolume(0.0f);
}

void CSSN011PlayerUIScript::OffMonsterUI()
{
	float alphaOn = 0.f;
	mMonsterHPBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaOn);
	mMonsterHPProgressBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaOn);
	mMonsterHPDecreaseBar->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alphaOn);
	
	mIsBGM = false;
}

void CSSN011PlayerUIScript::SetMonsterHPRation(int maxHP)
{
	mMonsterHPRatio = mMonsterHPBarInitScaleX / maxHP;
}

void CSSN011PlayerUIScript::SetPlayerHPRation(int maxHP)
{
	mPlayerHPRatio = mPlayerHPBarInitScaleX / maxHP;
}

void CSSN011PlayerUIScript::SetPlayerSPRation(int maxSP)
{
	mPlayerSPRatio = mPlayerSPBarInitScaleX / maxSP;
}

void CSSN011PlayerUIScript::CalculationPlayerHPUI(int nowHP)
{
	if (nowHP > 0)
	{
		float changePlayerHPBarScaleX = nowHP * mPlayerHPRatio;
		float movePlayerHPBarPositionXValue = mPlayerHPBarInitScaleX - changePlayerHPBarScaleX;
		movePlayerHPBarPositionXValue /= 2;

		Vec3 playerHPBarScale = mPlayerHPBar->Transform()->GetLocalScale();
		playerHPBarScale.x = changePlayerHPBarScaleX;
		mPlayerHPBar->Transform()->SetLocalScale(playerHPBarScale);

		Vec3 playerHPBarPosition = mPlayerHPBar->Transform()->GetLocalPos();
		playerHPBarPosition.x = mPlayerHPBarInitPositionX - movePlayerHPBarPositionXValue;
		mPlayerHPBar->Transform()->SetLocalPos(playerHPBarPosition);

		mIsOnPlayerDieTextUI = false;
	}
	else
	{
		Vec3 playerHPBarScale = mPlayerHPBar->Transform()->GetLocalScale();
		playerHPBarScale.x = 0.f;
		mPlayerHPBar->Transform()->SetLocalScale(playerHPBarScale);

		mIsOnPlayerDieTextUI = true;
	}
}

void CSSN011PlayerUIScript::CalculationPlayerSPUI(int nowSP)
{
	if (nowSP > 0)
	{
		float changePlayerSPBarScaleX = nowSP * mPlayerSPRatio;
		float movePlayerSPBarPositionXValue = mPlayerSPBarInitScaleX - changePlayerSPBarScaleX;
		movePlayerSPBarPositionXValue /= 2;

		Vec3 playerSPBarScale = mPlayerSPBar->Transform()->GetLocalScale();
		playerSPBarScale.x = changePlayerSPBarScaleX;
		mPlayerSPBar->Transform()->SetLocalScale(playerSPBarScale);

		Vec3 playerSPBarPosition = mPlayerSPBar->Transform()->GetLocalPos();
		playerSPBarPosition.x = mPlayerSPBarInitPositionX - movePlayerSPBarPositionXValue;
		mPlayerSPBar->Transform()->SetLocalPos(playerSPBarPosition);
	}
	else
	{
		Vec3 playerSPBarScale = mPlayerSPBar->Transform()->GetLocalScale();
		playerSPBarScale.x = 0.f;
		mPlayerSPBar->Transform()->SetLocalScale(playerSPBarScale);
	}
}

void CSSN011PlayerUIScript::CalculationMonsterHPUI(int nowHP)
{
	if (nowHP > 0)
	{
		float changeMonsterHPBarScaleX = nowHP * mMonsterHPRatio;
		float moveMonsterHPBarPositionXValue = mMonsterHPBarInitScaleX - changeMonsterHPBarScaleX;
		moveMonsterHPBarPositionXValue /= 2;

		Vec3 monsterHPBarScale = mMonsterHPBar->Transform()->GetLocalScale();
		monsterHPBarScale.x = changeMonsterHPBarScaleX;
		mMonsterHPBar->Transform()->SetLocalScale(monsterHPBarScale);

		Vec3 monsterHPBarPosition = mMonsterHPBar->Transform()->GetLocalPos();
		monsterHPBarPosition.x = mMonsterHPBarInitPositionX - moveMonsterHPBarPositionXValue;
		mMonsterHPBar->Transform()->SetLocalPos(monsterHPBarPosition);

		mIsOnMonsterDieTextUI = false;
	}
	else
	{
		Vec3 monsterHPBarScale = mMonsterHPBar->Transform()->GetLocalScale();
		monsterHPBarScale.x = mMonsterHPBarInitScaleX;
		mMonsterHPBar->Transform()->SetLocalScale(monsterHPBarScale);

		OffMonsterUI();

		mIsOnMonsterDieTextUI = true;
	}
}

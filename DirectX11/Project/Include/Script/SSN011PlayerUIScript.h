#pragma once
#include <Script.h>

class CSSN011PlayerUIScript : public CScript
{
private:
	CGameObject* mPlayerHPBar;
	CGameObject* mPlayerSPBar;
	CGameObject* mMonsterHPBar;

	CGameObject* mPlayerHPProgressBar;
	CGameObject* mPlayerSPProgressBar;
	CGameObject* mMonsterHPProgressBar;

	CGameObject* mPlayerHPDecreaseBar;
	CGameObject* mPlayerSPDecreaseBar;
	CGameObject* mMonsterHPDecreaseBar;

	CGameObject* mTextBackground;
	CGameObject* mMonsterDieText;
	CGameObject* mMonsterDieEffectText;
	CGameObject* mPlayerDieText;

	CGameObject* mUseItemBackground;
	CGameObject* mUseItemSlot;
	CGameObject* mUseItem;
	
	CGameObject* mBossClearLight;

	float mPlayerHPBarInitScaleX;
	float mPlayerSPBarInitScaleX;
	float mMonsterHPBarInitScaleX;

	float mPlayerHPBarInitPositionX;
	float mPlayerSPBarInitPositionX;
	float mMonsterHPBarInitPositionX;

	float mPlayerHPRatio;
	float mPlayerSPRatio;

	float mMonsterHPRatio;

	bool mIsOnPlayerDieTextUI;
	bool mIsOnMonsterDieTextUI;

	bool mIsFadeInOutBossClear;

public:
	CSSN011PlayerUIScript();
	~CSSN011PlayerUIScript();

private:
	void SetUIComponent(CGameObject* uiObject, wstring textureName, float alphaValue, float rgbMulValue, Vec3 scale, Vec3 position);
	void FadeInOutMonsterDieText();
	void FadeInOutPlayerDieText();
	void FindUIObject();
	void FadeInOutBossClear();

public:
	virtual void start();
	virtual void update();

	void OnMonsterUI();
	void OffMonsterUI();
	
	void StartBossClearLight();

	void SetMonsterHPRation(int maxHP);
	void SetPlayerHPRation(int maxHP);
	void SetPlayerSPRation(int maxSP);

	void CalculationPlayerHPUI(int nowHP);
	void CalculationPlayerSPUI(int nowSP);
	void CalculationMonsterHPUI(int nowHP);
	void CalculationPlayerHealUI(int maxHealCount, int nowHealCount);
};


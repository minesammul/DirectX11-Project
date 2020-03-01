#pragma once
#include <Script.h>

class CSSN011PlayerUIScript : public CScript
{
private:
	CGameObject* playerHPBar;
	CGameObject* playerSPBar;
	CGameObject* monsterHPBar;

	CGameObject* playerHPProgressBar;
	CGameObject* playerSPProgressBar;
	CGameObject* monsterHPProgressBar;

	CGameObject* playerHPDecreaseBar;
	CGameObject* playerSPDecreaseBar;
	CGameObject* monsterHPDecreaseBar;

	CGameObject* textBackground;
	CGameObject* monsterDieText;
	CGameObject* monsterDieEffectText;
	CGameObject* playerDieText;

	float playerHPBarInitScaleX;
	float playerSPBarInitScaleX;
	float monsterHPBarInitScaleX;

	float playerHPBarInitPositionX;
	float playerSPBarInitPositionX;
	float monsterHPBarInitPositionX;

	float playerHPRatio;
	float playerSPRatio;

	float monsterHPRatio;

	bool isPlayerDie;
	bool isMonsterDie;

	bool isBGM;
	float bgmVolume;

public:
	CSSN011PlayerUIScript();
	~CSSN011PlayerUIScript();

private:
	void SetUIComponent(CGameObject* uiObject, wstring textureName, float alphaValue, Vec3 scale, Vec3 position);
	void FadeInOutMonsterDieText();
	void FadeInOutPlayerDieText();

public:
	virtual void start();
	virtual void update();

	void OnMonsterUI();
	void OffMonsterUI();

	void SetMonsterHPRation(int maxHP);

	void CalculationPlayerHPUI(int nowHP);

	void CalculationPlayerSPUI(int nowSP);

	void CalculationMonsterHPUI(int nowHP);


};


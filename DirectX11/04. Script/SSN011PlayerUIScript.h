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

	float playerHPBarInitScaleX;
	float playerSPBarInitScaleX;
	float monsterHPBarInitScaleX;

	float playerHPBarInitPositionX;
	float playerSPBarInitPositionX;
	float monsterHPBarInitPositionX;

	float playerHPRatio;
	float playerSPRatio;

	float monsterHPRatio;

public:
	CSSN011PlayerUIScript();
	~CSSN011PlayerUIScript();

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


#pragma once
#include <Script.h>

class CMonsterResponseScript : public CScript
{
private:
	map<wstring, CResPtr<CPrefab>> monsterPrefab;
	//CResPtr<CPrefab>	monsterPrefab;
	CResPtr<CPrefab>	monsterSpawnEffectPrefab;

	bool isSpawn;

public:
	CMonsterResponseScript();
	~CMonsterResponseScript();

public:
	virtual void start();
	virtual void OnCollisionEnter(CCollider2D* _pOther);
};


#pragma once
#include "Script.h"

class CPlayerScript :
	public CScript
{
private:
	CResPtr<CPrefab>	m_pBulletPrefab;
	CResPtr<CMaterial>  m_pOriginMtrl;
	CResPtr<CMaterial>  m_pCloneMtrl;

public:	
	virtual void start();
	virtual void update();

	virtual void OnEnable();
	virtual void OnDisable();

	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);

private:
	void CreateBullet();
	CLONE(CPlayerScript);

	void CheckAnim();

public:
	CPlayerScript();
	virtual ~CPlayerScript();
};



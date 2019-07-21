#pragma once
#include "Object.h"
class Enemy :	public Object
{
private:
	bool m_bGone;

public:
	Enemy();
	~Enemy();

	void Update() override;
	TObject CreateObject() override;

	void SetGone(bool gone)
	{
		m_bGone = gone;
	}
};


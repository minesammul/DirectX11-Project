#pragma once
#include <Animator3D.h>
class CSSN002PlayerScript;

class PlayerState
{
private:
	int mUseSPAmount;

public:
	PlayerState();
	~PlayerState();

public:
	virtual void Init(CSSN002PlayerScript* playerScript) = 0;
	virtual void Update(CSSN002PlayerScript* playerScript) = 0;

	int GetUseSPAmount() { return mUseSPAmount; }
	void SetUseSPAmount(int useSPAmount) { mUseSPAmount = useSPAmount; }
};


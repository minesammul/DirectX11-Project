#pragma once
#include <Script.h>

class CSSN012SkyBoxScript : public CScript
{
private:
	Vec2 mUV;

	float mUVSpeed;

	CResPtr<CTexture> mBeforeTexture;
	CResPtr<CTexture> mAfterTexture;

	Vec2 mBlendRatio;

	float mBlendSpeed;

	bool mIsBlendStart;

public:
	CSSN012SkyBoxScript();
	~CSSN012SkyBoxScript();

private:
	void BlendTexture();
	void MoveUV();

public:
	virtual void start();
	virtual void update();

	void StartBlendSky(CResPtr<CTexture> blendTexture, float blendSpeed);
	void SetUVSpeed(float speed) { mUVSpeed = speed; }
};


#include "stdafx.h"
#include "BulletScript.h"

CBulletScript::CBulletScript()
	: CScript((UINT)SCRIPT_TYPE::BULLETSCRIPT)
	, m_fSpeed(200.f)
	, direction(Vec3(1.f, 0.f, 0.f))
	, distance(Vec3(0.f, 0.f, 0.f))
	, isDestroy(false)
	, isEffectStart(false)
{
}

CBulletScript::~CBulletScript()
{
}

void CBulletScript::start()
{
}

void CBulletScript::update()
{
	Vec3 position = Transform()->GetLocalPos();
	direction = XMVector2Normalize(direction);

	position.x += direction.x * m_fSpeed * DT;
	position.y += direction.y * m_fSpeed * DT;

	Transform()->SetLocalPos(position);

	distance.x += direction.x * m_fSpeed * DT;
	distance.y += direction.y * m_fSpeed * DT;

	if (isEffectStart == false)
	{
		if (Object()->Animator2D()->GetCurAnim()->IsPlay() == false)
		{
			Object()->Animator2D()->GetCurAnim()->Play();
		}

		Vec3 nowDistance = XMVector2Length(distance);
		if (nowDistance.x > MAX_DISTANCE)
		{
			isEffectStart = true;
			effectAnimation = Object()->Animator2D()->FindAnim(L"Effect");
			if (effectAnimation != nullptr)
			{
				Object()->Animator2D()->SetCurAnim(effectAnimation);
				Object()->Animator2D()->GetCurAnim()->Play();
			}
		}
	}
	else
	{
		if (effectAnimation != nullptr)
		{
			if (Object()->Animator2D()->GetCurAnim()->IsFinish() == true)
			{
				if (isDestroy == false)
				{
					DeleteObject(Object());
					isDestroy = true;
				}

			}
		}
		else
		{
			if (isDestroy == false)
			{
				DeleteObject(Object());
				isDestroy = true;
			}
		}
	}

}

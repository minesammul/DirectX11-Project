#include "stdafx.h"
#include "SSN006WeaponEquipScript.h"

#include <Animator3D.h>

CSSN006WeaponEquipScript::CSSN006WeaponEquipScript() : 
	CScript((UINT)SCRIPT_TYPE::SSN006WEAPONEQUIPSCRIPT)
{
}


CSSN006WeaponEquipScript::~CSSN006WeaponEquipScript()
{
}

void CSSN006WeaponEquipScript::start()
{
	for (int index = 0; index < Object()->GetParent()->Animator3D()->GetVectorBone()->size(); index++)
	{
		wstring nowBoneName = (*Object()->GetParent()->Animator3D()->GetVectorBone())[index].strBoneName;
		if (nowBoneName.compare(L"R_Hand") == 0)
		{
			mFindEquipMeshIndex = index;
		}
	}

	mInitialPosition = Object()->Transform()->GetLocalPos();
	mInitialRotate = Object()->Transform()->GetLocalRot();
}

void CSSN006WeaponEquipScript::update()
{
	Vec3 nowEquipMeshPosition = Object()->GetParent()->Animator3D()->GetVectorWorldMatrixComponent(mFindEquipMeshIndex).vTranslate;
	nowEquipMeshPosition += mInitialPosition;

	Vec4 nowEquipMeshQuterialRotate = Object()->GetParent()->Animator3D()->GetVectorWorldMatrixComponent(mFindEquipMeshIndex).qRot;
	Vec3 nowEquipMeshRotate = Vec3(nowEquipMeshQuterialRotate.x, nowEquipMeshQuterialRotate.y, nowEquipMeshQuterialRotate.z);
	nowEquipMeshRotate += mInitialRotate;

	Object()->Transform()->SetLocalPos(nowEquipMeshPosition);
	Object()->Transform()->SetLocalRot(nowEquipMeshRotate);
}

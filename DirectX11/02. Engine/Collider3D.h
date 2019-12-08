#pragma once
#include "Component.h"
#include "ResPtr.h"
#include "Mesh.h"
#include "Material.h"

class CCollider3D :	public CComponent
{
private:
	static vector<CResPtr<CMaterial>>	g_vecColMtrl;	// �浹ü���� ��� �� Material Pool
	static CResPtr<CMaterial>			g_pOriginMtrl;  // �浹ü�� ����� ���� Material

public:
	static void CreateMaterial();
	static CResPtr<CMaterial> GetCloneMtrl();
	static void ClearMaterial();


private:
	Vec3				m_vOffset;	// Object �� ���� �����ǥ
	Vec3				m_vFinalPos;// Transform ��ġ + Offset

	Vec3				m_vScale;	// �߰��� �������� ũ�� ������
	Vec3				m_vFinalScale; // Transform ũ�� * �浹ü ũ��

	COLLIDER3D_TYPE		m_eType;
	Matrix				m_matColWorld; // �浹ü ���� ���

	UINT				m_iColCount;

	CResPtr<CMesh>		m_pMesh;
	CResPtr<CMaterial>  m_pCurMtrl;

public:
	virtual void update();
	virtual void finalupdate();

public:
	void SetOffset(const Vec3& _vOffset) { m_vOffset = _vOffset;}
	const Vec3& GetOffset() { return m_vOffset; }

	void SetScale(const Vec3& _vScale) { m_vScale = _vScale;}
	const Vec3& GetScale() { return m_vScale; }

	Vec3 GetFinalPositon() { return m_vFinalPos; }
	Vec3 GetFinalScale() { return m_vFinalScale; }

	void SetColliderType(COLLIDER3D_TYPE _eType);
	COLLIDER3D_TYPE GetCollider3DType() { return m_eType; }

	const Matrix& GetWorldMat() { return m_matColWorld; }

	void OnCollisionEnter(CCollider3D* _pOther);
	void OnCollision(CCollider3D* _pOther);
	void OnCollisionExit(CCollider3D* _pOther);

	void UpdateData();
	void render();

	virtual void SaveToScene(FILE* _pFile);
	virtual void LoadFromScene(FILE* _pFile);

	CLONE(CCollider3D);

public:
	CCollider3D();
	virtual ~CCollider3D();
};


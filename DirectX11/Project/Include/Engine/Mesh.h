#pragma once
#include "Resource.h"


#include "ResPtr.h"
#include "Shader.h"
#include "Texture.h"
#include "FBXLoader.h"

struct tIndexInfo
{
	ID3D11Buffer*		pIB;
	UINT				iIdxCount;
	DXGI_FORMAT			eFormat;
	D3D11_BUFFER_DESC	tIdxDesc;
	void*				pIdxSysMem;
};

class CShader;

class CMesh :
	public CResource
{
private:
	ID3D11Buffer*						m_pVB;		// Vertex buffer	
	ID3D11InputLayout*					m_pLayout;	// InputLayout

	UINT								m_iOffset;
	UINT								m_iOffsetInst;

	UINT								m_iVtxSize;
	UINT								m_iVtxCount;
	void*								m_pVtxMem;

	D3D11_BUFFER_DESC					m_tVtxDesc;
	vector<tIndexInfo>					m_vecIdxInfo;

	vector<D3D11_INPUT_ELEMENT_DESC>	m_vecLayout;
	ID3DBlob*							m_pVtxBlob;

	// Animation3D
	vector<tMTAnimClip>					m_vecAnimClip;
	vector<tMTBone>						m_vecBones;
	CResPtr<CTexture>					m_pBoneTex;
	CResPtr<CTexture>					m_pBeforeBoneTex;

public:
	void render(UINT _iSubset = 0);
	void render_instancing(UINT _iSubset = 0);
	void render_particle(UINT _iParticleCount);

public:
	void CreateMesh(UINT _iVtxSize, UINT _iVtxCount, D3D11_USAGE _eVtxUsage, void* _pVtx,
		UINT _iIdxCount, D3D11_USAGE _eIdxUsage, DXGI_FORMAT _eIdxFormat, void* _pIdx);

	void CreateMesh(UINT _iVtxCount, UINT _iVtxSize, D3D11_USAGE _eVtxUsage, void* _pVtxSysMem
		, vector<tIndexInfo>& _IdxInfo);

	static CMesh* CreateFromContainer(CFBXLoader & _loader, int index);

	void AddInputLayout(const char* _pSemanticName, UINT _iSemanticIdx, DXGI_FORMAT _eFormat
		, UINT _iInputSlot, UINT _iInstancing, D3D11_INPUT_CLASSIFICATION _eClass = D3D11_INPUT_PER_VERTEX_DATA);

	UINT GetSubsetCount() { return m_vecIdxInfo.size(); }
	void* GetVtxSysMem() { return m_pVtxMem; }

public:
	const vector<tMTBone>* GetBones() { return &m_vecBones; }
	void SetBoneTex(CResPtr<CTexture> _pTex) { m_pBoneTex = _pTex; }
	void SetBeforeBoneTex(CResPtr<CTexture> _pTex) { m_pBeforeBoneTex = _pTex; }
	const vector<tMTAnimClip>* GetAnimClip() { return &m_vecAnimClip; }
	tMTAnimClip GetAnimClip(int index) { return m_vecAnimClip[index]; }
	void SetAnimClip(vector<tMTAnimClip> animClip)
	{
		m_vecAnimClip.clear();
		m_vecAnimClip = animClip;
	}

	CResPtr<CTexture> GetBoneTex() { return m_pBoneTex; }
	CResPtr<CTexture> GetBeforeBoneTex() { return m_pBeforeBoneTex; }
	bool IsAnimMesh() { return !m_vecAnimClip.empty(); }

	void SetLayout(CResPtr<CShader> _pShader, bool _bInstancing = false);

	virtual void Load(const wstring& _strFilePath);
	virtual void Save();
	virtual bool LoadFromScene(FILE* _pFile);
public:
	CMesh();
	virtual ~CMesh();
};


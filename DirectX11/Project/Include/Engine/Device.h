#pragma once
#include "ResPtr.h"
#include "Texture.h"

class CConstBuffer;

class CDevice
{
	SINGLE(CDevice);

private:
	ID3D11Device*				m_pDevice;				// 장치 메모리 관리
	ID3D11DeviceContext*		m_pContext;				// 그래픽스 파이프 라인 및 렌더링 
	

	UINT						m_iQuality;

	map<wstring, CConstBuffer*>	m_mapConstBuffer;
	tResolution					m_tRes;

public:
	int init();

	ID3D11Device* GetDevice() { return m_pDevice; }
	ID3D11DeviceContext* GetContext() { return m_pContext; }	

	void CreateConstBuffer(const wstring& _strKey, UINT _iSize, UINT _iRegister);
	CConstBuffer* FindConstBuffer(const wstring& _strKey);

	const tResolution& GetResolution() { return m_tRes; }
};


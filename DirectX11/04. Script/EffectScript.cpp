#include "stdafx.h"
#include "EffectScript.h"


CEffectScript::CEffectScript() : 
	CScript((UINT)SCRIPT_TYPE::EFFECTSCRIPT)
{
}


CEffectScript::~CEffectScript()
{
}

void CEffectScript::start()
{
	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\Player.pref", L"Prefab\\Player.pref");
	monsterPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\Player.pref");
}

void CEffectScript::update()
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_Z) == KEY_STATE::STATE_TAB)
	{
		/*
			CScript* pNewScript = CScriptMgr::GetScript(strScriptName.GetBuffer());
			GetTarget()->AddComponent(pNewScript);
		*/
		
		//vector<CScript*> prefabInputScripts;
		map<UINT, CScript*> prefabInputScripts;

		vector<UINT> prefabScriptTypes = monsterPrefab->GetScriptType();
		vector<wstring> allScriptInfo;
		CScriptMgr::GetScriptInfo(allScriptInfo);

		for (int scriptIndex = 0; scriptIndex < prefabScriptTypes.size(); scriptIndex++)
		{
			UINT scriptType = prefabScriptTypes[scriptIndex];
			wstring scriptName = allScriptInfo[scriptType];
			CScript* prefabScript = CScriptMgr::GetScript(scriptName);
			prefabInputScripts[scriptType] = prefabScript;
		}

		Instantiate(monsterPrefab, Transform()->GetLocalPos(), prefabInputScripts);
	}
}

#include "stdafx.h"
#include "TileMapScript.h"
#include "TileScript.h"
#include <iomanip>


CTileMapScript::CTileMapScript() : 
	CScript((UINT)SCRIPT_TYPE::TILEMAPSCRIPT)
{
	for (int tileIndex = 0; tileIndex < 1024; tileIndex++)
	{
		referecneTileIndexData[tileIndex] = -1;
	}
}


CTileMapScript::~CTileMapScript()
{
}


void CTileMapScript::awake()
{
	tilesetScript = nullptr;

	for (int layerIndex = 0; layerIndex < MAX_LAYER; layerIndex++)
	{
		CLayer* curLayer = CSceneMgr::GetInst()->GetCurScene()->GetLayer(layerIndex);
		if (curLayer == nullptr)
		{
			continue;
		}

		vector<CGameObject*> curGameObject = curLayer->GetParentObject();

		for (int gameObjectIndex = 0; gameObjectIndex < curGameObject.size(); gameObjectIndex++)
		{
			vector<CScript*> curScript = curGameObject[gameObjectIndex]->GetScripts();

			for (int scriptIndex = 0; scriptIndex < curScript.size(); scriptIndex++)
			{
				if (curScript[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::TILESCRIPT)
				{
					tilesetScript = curScript[scriptIndex];
				}
			}
		}
	}

	CResPtr<CTexture> tileTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\No Animation Tile\\16x16\\16x16Tileset.png");
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_1, &tileTexture);

	int inputGridCount = gridCount;
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &inputGridCount);

	int textureTileCount = 487;
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &textureTileCount);

}


void CTileMapScript::update()
{
	/*tTileMap tileData = Object()->MeshRender()->GetSharedMaterial()->GetTileData();
	for (int index = 0; index < 1024; index++)
	{
		referecneTileIndexData[index] = tileData.referenceTileIndex[index];
	}*/

	CGameObject* curObject = Object();
	if (tilesetScript != nullptr)
	{
		if (CSceneMgr::GetInst()->GetMousePickingObject() != nullptr)
		{
			if (CSceneMgr::GetInst()->GetMousePickingObject()->GetID() == curObject->GetID())
			{
				if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN) == KEY_STATE::STATE_TAB)
				{
					startMousePosition = CKeyMgr::GetInst()->GetMousePos();
				}

				if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN) == KEY_STATE::STATE_HOLD)
				{
					DirectX::XMVECTOR mousePickingPosition = CSceneMgr::GetInst()->GetMousePickingPosition();
					Vec3 objectScale = Object()->Transform()->GetLocalScale();
					Vec3 objectPosition = Object()->Transform()->GetLocalPos();

					POINT nowMousePosition;
					nowMousePosition.x = startMousePosition.x - CKeyMgr::GetInst()->GetMousePos().x;
					nowMousePosition.y = startMousePosition.y - CKeyMgr::GetInst()->GetMousePos().y;

					mousePickingPosition.vector4_f32[0] -= nowMousePosition.x;
					mousePickingPosition.vector4_f32[1] += nowMousePosition.y;

					int gridX = mousePickingPosition.vector4_f32[0] + objectScale.x / 2;
					int gridY = (mousePickingPosition.vector4_f32[1] - objectScale.y / 2)*(-1);

					gridX -= objectPosition.x;
					gridY += objectPosition.y;

					float gridSizeX = objectScale.x / gridCount;
					float gridSizeY = objectScale.y / gridCount;

					int selectGridColumn = gridX / gridSizeX;
					int selectGridRow = gridY / gridSizeY;

					CTileScript* curTileScript = dynamic_cast<CTileScript*>(tilesetScript);

					int selectedTilesetIndex = curTileScript->GetSelectTileIndex();

					int selectedGridIndex = selectGridColumn + selectGridRow * gridCount;

					referecneTileIndexData[selectedGridIndex] = selectedTilesetIndex;


					//Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_2, &selectTileIndex);
					Object()->MeshRender()->GetSharedMaterial()->SetTileData(referecneTileIndexData);
				}
			}
		}

	}


}

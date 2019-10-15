#include "stdafx.h"
#include "TileMapScript.h"
#include "TileScript.h"
#include <Camera.h>


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

	if (tilesetScript->Object()->IsActive()==false)
	{
		tilesetScript = nullptr;
	}

	//
	CResPtr<CTexture> tileTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\No Animation Tile\\16x16\\16x16Tileset.png");
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_1, &tileTexture);

	int inputGridCount = GRID_COUNT;
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &inputGridCount);

	int textureTileCount = 487;
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &textureTileCount);

	Object()->MeshRender()->GetSharedMaterial()->SetTileData(referecneTileIndexData);

	//
	vector<CCamera*> cameras = CSceneMgr::GetInst()->GetCurScene()->GetCamera();
	for (int cameraIndex = 0; cameraIndex < cameras.size(); cameraIndex++)
	{
		if (cameras[cameraIndex]->IsValiedLayer(Object()->GetLayerIdx()))
		{
			tileMapCamera = cameras[cameraIndex];
			break;
		}
	}
}


void CTileMapScript::update()
{
	EditTileMap();
	EditMoveTileMap();
}

void CTileMapScript::SaveToScene(FILE * _pFile)
{
	for (int index = 0; index < 1024; ++index)
	{
		int tileIndex = referecneTileIndexData[index];
		fwrite(&tileIndex, sizeof(int), 1, _pFile);
	}
}

void CTileMapScript::LoadFromScene(FILE * _pFile)
{
	for (int index = 0; index < 1024; ++index)
	{
		int tileIndex = -1;
		fread(&tileIndex, sizeof(int), 1, _pFile);
		referecneTileIndexData[index] = tileIndex;
	}
}

void CTileMapScript::EditTileMap()
{
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

					nowMousePosition.x *= tileMapCamera->GetScale();
					nowMousePosition.y *= tileMapCamera->GetScale();

					mousePickingPosition.vector4_f32[0] -= nowMousePosition.x;
					mousePickingPosition.vector4_f32[1] += nowMousePosition.y;

					int gridX = mousePickingPosition.vector4_f32[0] + objectScale.x / 2;
					int gridY = (mousePickingPosition.vector4_f32[1] - objectScale.y / 2)*(-1);

					gridX -= objectPosition.x;
					gridY += objectPosition.y;

					float gridSizeX = objectScale.x / GRID_COUNT;
					float gridSizeY = objectScale.y / GRID_COUNT;

					int selectGridColumn = gridX / gridSizeX;
					int selectGridRow = gridY / gridSizeY;

					CTileScript* curTileScript = dynamic_cast<CTileScript*>(tilesetScript);

					int selectedTilesetIndex = curTileScript->GetSelectTileIndex();

					int selectedGridIndex = selectGridColumn + selectGridRow * GRID_COUNT;

					referecneTileIndexData[selectedGridIndex] = selectedTilesetIndex;

					Object()->MeshRender()->GetSharedMaterial()->SetTileData(referecneTileIndexData);
				}
			}
		}

	}
}

void CTileMapScript::EditMoveTileMap()
{
	if (tilesetScript != nullptr)
	{
		if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A) == KEY_STATE::STATE_HOLD)
		{
			Vec3 ObjectPosition = Object()->Transform()->GetLocalPos();
			ObjectPosition.x -= TILE_MOVE_SPEED * DT;
			Object()->Transform()->SetLocalPos(ObjectPosition);
		}
		else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D) == KEY_STATE::STATE_HOLD)
		{
			Vec3 ObjectPosition = Object()->Transform()->GetLocalPos();
			ObjectPosition.x += TILE_MOVE_SPEED * DT;
			Object()->Transform()->SetLocalPos(ObjectPosition);
		}

		if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W) == KEY_STATE::STATE_HOLD)
		{
			Vec3 ObjectPosition = Object()->Transform()->GetLocalPos();
			ObjectPosition.y += TILE_MOVE_SPEED * DT;
			Object()->Transform()->SetLocalPos(ObjectPosition);
		}
		else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_S) == KEY_STATE::STATE_HOLD)
		{
			Vec3 ObjectPosition = Object()->Transform()->GetLocalPos();
			ObjectPosition.y -= TILE_MOVE_SPEED * DT;
			Object()->Transform()->SetLocalPos(ObjectPosition);
		}

		if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_Q) == KEY_STATE::STATE_TAB)
		{
			float nowCameraScale = tileMapCamera->GetScale();
			nowCameraScale *= TILE_SCALE_MULTI_VALUE;
			tileMapCamera->SetScale(nowCameraScale);
		}
		else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_E) == KEY_STATE::STATE_TAB)
		{
			float nowCameraScale = tileMapCamera->GetScale();
			nowCameraScale /= TILE_SCALE_MULTI_VALUE;
			tileMapCamera->SetScale(nowCameraScale);
		}
	}
}

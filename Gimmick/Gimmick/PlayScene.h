#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Gimmick.h"
#include "Map.h"
#include "Camera.h"
#include "HUD.h"
#include "QuadTree.h"


class CPlayScene : public CScene
{
protected:

	CGimmick* player;					// A play scene has to have player, right? 
	CMap* map;
	CQuadTree* quadTree;
	CCamera* camera;
	CHUD* HUD;

	int _xLeft, _xRight;
	int _yTop, _yBot;

	bool isReSetPlayerPos = false;

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> listObj;
	vector<LPGAMEOBJECT> ani_fronts;
	vector<LPGAMEOBJECT> ani_backs;

	/*void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);*/
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP_TEXTURES(string line);
	void _ParseSection_CAMERA(string line);
	void _ParseSection_MAP(string line);


public:

	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CGimmick* GetPlayer() { return player; }

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};
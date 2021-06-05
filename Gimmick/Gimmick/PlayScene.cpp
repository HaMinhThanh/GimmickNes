#include <iostream>
#include <fstream>

#include "PlayScene.h"
#include "Utils.h"
#include "Define.h"

#include "Textures.h"
#include "Sprites.h"
#include "Animations.h"

#include "Portal.h"
#include "Star.h"

#include "Brick.h"
#include "ScrollBar.h"
#include "Slide.h"
#include "Pipes.h"
#include "MovingBrick.h"
#include "AniBrick.h"

#include "Bomb.h"
#include "Water.h"
#include "MiniBomb.h"
#include "KingElectrode.h"
#include "NarrowSpot.h"
#include "Worm.h"
#include "Cannon.h"
#include "CannonBall.h"
#include "Electrode.h"
#include "Sound.h"

#include "Treasures.h"
#include "Medicine.h"
#include "BombItem.h"
#include "Fireball.h"

#include "HiddenObject.h"


using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_MAP_TEXTURES	3
#define SCENE_SECTION_MAP	4
#define SCENE_SECTION_CAMERA 5


//// OBJECT
#define OBJECT_TYPE_GIMMICK	1
#define	OBJECT_TYPE_STAR 2

// Ground
#define OBJECT_TYPE_BRICK	4
#define OBJECT_TYPE_SLIDE	5
#define OBJECT_TYPE_SCROLLBAR_INCREASE	6
#define OBJECT_TYPE_SCROLLBAR_DECREASE	7
#define OBJECT_TYPE_MOVING_BRICK	8
#define OBJECT_TYPE_ANI_BRICK	9
#define OBJECT_TYPE_WATER	10
#define OBJECT_TYPE_HIDDEN	11
#define OBJECT_TYPE_PIPE	12
#define OBJECT_TYPE_ANI_BRICK_1	13

// Enemy
#define OBJECT_TYPE_BOMB			21
#define OBJECT_TYPE_MINIBOMB		22
#define OBJECT_TYPE_CANNON			23
#define OBJECT_TYPE_CANNONBALL		24
#define OBJECT_TYPE_WORM			25
#define OBJECT_TYPE_NARROWSPOT		26
#define OBJECT_TYPE_ELECTRODE		27
#define OBJECT_TYPE_KING_ELECTRODE	28

// Item
#define OBJECT_TYPE_TREASURE	31
#define OBJECT_TYPE_MEDICINE	32
#define OBJECT_TYPE_BOMB_ITEM	33
#define OBJECT_TYPE_FIREBALL	34

// Effect


#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	bool isObj = true;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{

	case OBJECT_TYPE_GIMMICK:
	{
		isObj = false;

		obj = CGimmick::GetInstance(x, y);

		CGame* game = CGame::GetInstance();

		obj->SetPosition(x, y);

		if (game->isSwitchScene) {
			obj->SetPosition(game->playerX, game->playerY);
			game->isSwitchScene = false;
		}
		/*else {
			obj->SetPosition(x, y);
		}*/

		//obj->SetPosition(x, y);
		obj->BackUpPos(x, y);

		float reX = atof(tokens[4].c_str());
		float reY = atof(tokens[5].c_str());

		game->playerX = reX;
		game->playerY = reY;

		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);

		player = (CGimmick*)obj;

		DebugOut(L"[INFO] Player object created!\n");
	}
	break;

	case OBJECT_TYPE_BRICK:
		obj = new CBrick();
		break;

	case OBJECT_TYPE_STAR:
		obj = new CStar();
		break;

	case OBJECT_TYPE_ANI_BRICK:
		obj = new CAniBrick(0);
		isObj = false;

		ani_backs.push_back(obj);

		break;

	case OBJECT_TYPE_ANI_BRICK_1:
		obj = new CAniBrick(1);
		isObj = false;

		ani_fronts.push_back(obj);

		break;

	case OBJECT_TYPE_WATER:

		obj = new CWater();
		break;

	case OBJECT_TYPE_SLIDE:
	{
		float d = atof(tokens[4].c_str());
		float s = atof(tokens[5].c_str());

		obj = new CSlide(x, y, d, s);
	}
	break;

	case OBJECT_TYPE_SCROLLBAR_INCREASE:
		obj = new CScrollBar(SCROLLBAR_TYPE_INCREASE);
		break;

	case OBJECT_TYPE_SCROLLBAR_DECREASE:
		obj = new CScrollBar(SCROLLBAR_TYPE_DECREASE);
		break;

	case OBJECT_TYPE_MOVING_BRICK:
	{
		int min = atof(tokens[4].c_str());
		int max = atof(tokens[5].c_str());
		int type = atof(tokens[6].c_str());

		obj = new CMovingBrick(min, max, type);
	}
	break;

	case OBJECT_TYPE_BOMB:
		obj = new CBomb(x, y);
		break;

	case OBJECT_TYPE_MINIBOMB:
		obj = new CMiniBomb();
		break;

	case OBJECT_TYPE_CANNON:
	{
		int n = atof(tokens[4].c_str());
		obj = new CCannon(x, y, n);
	}
	break;

	case OBJECT_TYPE_NARROWSPOT:
		obj = new CNarrowSpot(x, y);
		break;

	case OBJECT_TYPE_WORM:
		obj = new CWorm(x, y);
		break;

	case OBJECT_TYPE_KING_ELECTRODE:
		obj = new CKingElectrode(x, y);
		break;

	case OBJECT_TYPE_ELECTRODE:
		obj = new CElectrode(x, y);
		break;

	case OBJECT_TYPE_TREASURE:
	{
		int w = atof(tokens[4].c_str());
		int h = atof(tokens[5].c_str());

		obj = new CTreasures(w, h);
	}
	break;

	case OBJECT_TYPE_MEDICINE:
	{
		int type = atof(tokens[4].c_str());

		obj = new CMedicine(x, y, type);
	}
	break;

	case OBJECT_TYPE_BOMB_ITEM:
		obj = new CBombItem(x, y);
		break;

	case OBJECT_TYPE_FIREBALL:
		obj = new CFireBall(x, y);
		break;

	case OBJECT_TYPE_PIPE:
	{
		int t = atof(tokens[4].c_str());

		obj = new CPipes(x, y, t);
	}
	break;

	case OBJECT_TYPE_HIDDEN:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		int cam_l = atof(tokens[6].c_str());
		int cam_r = atof(tokens[7].c_str());
		int type = atof(tokens[8].c_str());

		obj = new CHiddenObject(x, y, w, h, cam_l, cam_r, type);

	}
	break;

	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		float caml = atof(tokens[7].c_str());
		float camr = atof(tokens[8].c_str());

		obj = new CPortal(x, y, r, b, scene_id, caml, camr);

		DebugOut(L"Portal %d", scene_id);
	}
	break;

	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	if (!dynamic_cast<CGimmick*>(obj))
		obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);

	if (isObj) {
		//objects.push_back(obj);
		quadTree->insertEntity(obj);
	}
}

void CPlayScene::_ParseSection_MAP_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 4) return; // skip invalid lines

	int IDMap = atoi(tokens[0].c_str());
	int row = atoi(tokens[1].c_str());
	int column = atoi(tokens[2].c_str());
	int IDTileSet = atoi(tokens[3].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(IDTileSet);

	int index = IDMap;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			DebugOut(L"ok");
			CSprites::GetInstance()->Add(index, j * 32, i * 32, j * 32 + 32, i * 32 + 32, tex);
			index = index + 1;
		}
	}
}

void CPlayScene::_ParseSection_CAMERA(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2)return;	// skip invalid lines
	_xLeft = atoi(tokens[0].c_str());
	_xRight = atoi(tokens[1].c_str());
	_yTop = atoi(tokens[2].c_str());
	_yBot = atoi(tokens[3].c_str());

	//CGame::GetInstance()->SetCamBoundary(_xLeft, _xRight, _yTop);
	camera->SetCamBoundary(_xLeft, _xRight, _yTop);
	//camera->SetYBoundary(_yBot);
	if (CGame::GetInstance()->isSwitchScene)
		camera->SetCamBoundary(camera->oLeft, camera->oRight, 0);
}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 4) return; // skip invalid lines
	wstring filePath = ToWSTR(tokens[0]);
	int column = atoi(tokens[1].c_str());
	int row = atoi(tokens[2].c_str());
	int index = atoi(tokens[3].c_str());
	int align = atoi(tokens[4].c_str());
	map->SetValueInMap(row, column, index, align);
	map->LoadMap(filePath);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = column * 32;
	r.bottom = row * 32;

	quadTree = new CQuadTree(1, r);
}

void CPlayScene::Load()
{
	_xLeft = _xRight = _yTop = -1;

	map = CMap::GetInstance();
	camera = CCamera::GetInstance();
	HUD = CHUD::GetInstance();

	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		/*if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}*/
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[MAP_TEXTURES]") {
			section = SCENE_SECTION_MAP_TEXTURES; continue;
		}
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}
		if (line == "[CAMERA]") {
			section = SCENE_SECTION_CAMERA; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
			/*case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;*/
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAP_TEXTURES: _ParseSection_MAP_TEXTURES(line); break;
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		case SCENE_SECTION_CAMERA: _ParseSection_CAMERA(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	coObjects.clear();
	listObj.clear();

	/*for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}*/

	float camX, camY;
	camera->GetCamPos(camX, camY);

	quadTree->getAllEntitiesOnCam(coObjects, camX, camY);

	for (int i = 0; i < coObjects.size(); i++)
		listObj.push_back(coObjects[i]);

	for (size_t i = 0; i < coObjects.size(); i++)
	{
		coObjects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	player->Update(dt, &coObjects);

	// skip update if colide uiwth portal
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();

	float xRight, xLeft, yTop, yBot;

	camera->GetCamBoundary(xLeft, xRight, yTop);
	yBot = camera->GetYBoundary();

	cx -= game->GetScreenWidth() / 2;

	if (cx < xLeft)
		cx = xLeft;

	if (cx > xRight - SCREEN_WIDTH + 32) // cong them 32 vi thieu 1 frame
		cx = xRight - SCREEN_WIDTH + 32;

	if (cy > 0) {

		int index = cy / SCREEN_HEIGHT_MAP;
		yTop = SCREEN_HEIGHT_MAP * index;

	}
	else {

		player->SetState(GIMMICK_STATE_DIE);
	}
	camera->SetCamPos((int)cx, (int)yTop);

	HUD->Update(dt);
}

void CPlayScene::Render()
{

	vector<LPGAMEOBJECT> coObjects;

	if (player == NULL) return;

	float camx, camy;
	camera->GetCamPos(camx, camy);

	quadTree->getAllEntitiesOnCam(coObjects, camx, camy);

	float cx, cy;

	camera->GetCamPos(cx, cy);

	map->DrawMap(cx, cy);

	for (int i = 0; i < ani_backs.size(); i++)
		ani_backs[i]->Render();

	for (int i = 0; i < listObj.size(); i++)
		listObj[i]->Render();

	if (player != NULL)
		player->Render();

	for (int i = 0; i < ani_fronts.size(); i++)
		ani_fronts[i]->Render();

	HUD->Render();

}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();

	listObj.clear();

	for (int i = 0; i < ani_fronts.size(); i++)
		delete ani_fronts[i];

	ani_fronts.clear();

	for (int i = 0; i < ani_backs.size(); i++)
		delete ani_backs[i];

	ani_backs.clear();

	delete quadTree;
	quadTree = NULL;

	//player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CGimmick* gimmick = ((CPlayScene*)scence)->GetPlayer();

	gimmick->OnKeyDown(KeyCode);

	switch (KeyCode)
	{
	case DIK_S:
		if (gimmick->GetJumping() == 0)
		{
			gimmick->SetState(GIMMICK_STATE_JUMP);

			gimmick->SetJumping(1);

			if (gimmick->GetDoubleJumpStart() == 0)
			{
				//gimmick->SetState(MARIO_STATE_JUMP_HIGH_SPEED);
				gimmick->SetDoubleJumpStart();

			}
		}
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CGame* game = CGame::GetInstance();

	CGimmick* gimmick = ((CPlayScene*)scence)->GetPlayer();

	gimmick->OnKeyUp(KeyCode);

	switch (KeyCode)
	{
	case DIK_S:
		gimmick->ResetDoubleJumpStart();
		break;

	case DIK_T:
		gimmick->SetPosition(960, 240);
		break;

	case DIK_Y:
		gimmick->SetPosition(128, 272);
		break;
	case DIK_F:
		gimmick->energy = 4;
		break;

	case DIK_1:
		game->SwitchScene(MAP_ID_1A);
		//gimmick->SetPosition(128, 272);
		break;
	case DIK_2:
		game->SwitchScene(MAP_ID_1B);
		break;

	case DIK_3:
		game->SwitchScene(MAP_ID_1C);
		break;
	case DIK_U:
		gimmick->SetPosition(736, 480);
		break;
	case DIK_7:
		gimmick->SetPosition(1424, 256);
		break;
	case DIK_8:
		gimmick->SetPosition(1344, 432);
		break;

	// Bo sung: scene shortcuts
	case DIK_F1:
		game->SwitchScene(MAP_ID_2A);
	case DIK_F2:
		game->SwitchScene(MAP_ID_2B);
	case DIK_F7:
		game->SwitchScene(MAP_ID_7);


	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{

	CGame* game = CGame::GetInstance();

	CGimmick* gimmick = ((CPlayScene*)scence)->GetPlayer();

	gimmick->KeyState(states);

}
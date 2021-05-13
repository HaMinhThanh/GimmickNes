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
		obj->SetPosition(x, y);
		obj->BackUpPos(x, y);

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
		break;

	case OBJECT_TYPE_ANI_BRICK_1:
		obj = new CAniBrick(1);
		isObj = false;

		ani_front.push_back(obj);

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

	case OBJECT_TYPE_TREASURE:
	{
		int w = atof(tokens[4].c_str());
		int h = atof(tokens[5].c_str());

		obj = new CTreasures(w, h);
	}
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

		obj = new CPortal(x, y, r, b, scene_id);

		DebugOut(L"Portal %d", scene_id);
	}
	break;

	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);

	if (isObj)
		objects.push_back(obj);
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
	camera->SetYBoundary(_yBot);
}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 4) return; // skip invalid lines
	wstring filePath = ToWSTR(tokens[0]);
	int row = atoi(tokens[2].c_str());
	int column = atoi(tokens[1].c_str());
	int index = atoi(tokens[3].c_str());
	int align = atoi(tokens[4].c_str());
	map->SetValueInMap(row, column, index, align);
	map->LoadMap(filePath);
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

	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
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

	if (cy < yBot ) {

		int index = cy / SCREEN_HEIGHT_MAP;
		yTop = SCREEN_HEIGHT_MAP * index;
	}
	else {

		player->SetState(GIMMICK_STATE_DIE);
	}

	camera->SetCamPos((int)cx, (int)yTop);

}

void CPlayScene::Render()
{
	if (player == NULL) return;

	float cx, cy;

	camera->GetCamPos(cx, cy);

	map->DrawMap(cx, cy);

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	if (player != NULL)
		player->Render();

	for (int i = 0; i < ani_front.size(); i++)
		ani_front[i]->Render();

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

	for (int i = 0; i < ani_front.size(); i++)
		delete ani_front[i];

	objects.clear();

	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CGimmick* gimmick = ((CPlayScene*)scence)->GetPlayer();

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

	switch (KeyCode)
	{
	case DIK_S:
		gimmick->ResetDoubleJumpStart();
		break;

	case DIK_T:
		gimmick->SetPosition(960, 140);
		break;

	case DIK_Y:
		gimmick->SetPosition(128, 114);
		break;

	case DIK_1:
		game->SwitchScene(MAP_ID_1A);
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
		gimmick->SetPosition(1424, 320);
		break;
	case DIK_8:
		gimmick->SetPosition(1344, 144);
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();

	CGimmick* gimmick = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Mario die 
	if (gimmick->GetState() == GIMMICK_STATE_DIE || gimmick->GetState()== GIMMICK_STATE_PIPING) return;

	if (game->IsKeyDown(DIK_RIGHT)) {

		gimmick->key_down = 1;

		if (!gimmick->isScrollBar && !gimmick->isSlide) {

			gimmick->SetState(GIMMICK_STATE_WALKING_RIGHT);
		}

		else if (gimmick->isSlide && !gimmick->isScrollBar) {

			if (gimmick->direct_slide == GIMMICK_TREND_SLIDE_RIGHT)

				gimmick->SetState(GIMMICK_STATE_SLIDE_UP);

			else
				gimmick->SetState(GIMMICK_STATE_SLIDE_DOWN);
		}
		else if (!gimmick->isSlide && gimmick->isScrollBar) {

			if (gimmick->trendScrollBar == GIMMICK_TREND_SCROLLBAR_INCREASE)

				gimmick->SetState(GIMMICK_STATE_INCREASE);

			else
				gimmick->SetState(GIMMICK_STATE_DECREASE);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT)) {

		gimmick->key_down = -1;

		if (!gimmick->isScrollBar && !gimmick->isSlide) {

			gimmick->SetState(GIMMICK_STATE_WALKING_LEFT);
		}

		else if (gimmick->isSlide && !gimmick->isScrollBar) {

			if (gimmick->direct_slide == GIMMICK_TREND_SLIDE_LEFT)

				gimmick->SetState(GIMMICK_STATE_SLIDE_UP);

			else
				gimmick->SetState(GIMMICK_STATE_SLIDE_DOWN);
		}
		else if (!gimmick->isSlide && gimmick->isScrollBar) {

			if (gimmick->trendScrollBar == GIMMICK_TREND_SCROLLBAR_DECREASE)

				gimmick->SetState(GIMMICK_STATE_INCREASE);

			else
				gimmick->SetState(GIMMICK_STATE_DECREASE);
		}
	}
	else if (gimmick->isScrollBar || gimmick->isSlide || gimmick->isAutoGo) {

		//gimmick->key_down = 0;

		gimmick->SetState(GIMMICK_STATE_AUTO_GO);
	}
	else if (gimmick->vy == 0 /*&& gimmick->vx != 0*/) {

		//gimmick->key_down = 0;

		gimmick->SetState(GIMMICK_STATE_IDLE);
	}


	if (game->IsKeyDown(DIK_A)) {

		if (gimmick->loading == 0 && gimmick->star->isActive == false) {

			gimmick->SetLoadingStar();
			gimmick->StarLoading();
			Sound::GetInstance()->Play("Shot", 0, 1);
		}
	}
	else {

		if (gimmick->loading == 2 && gimmick->isCanShot) {

			gimmick->ShotStar();
		}
		else {

			gimmick->ReSetLoading();
		}
	}
}
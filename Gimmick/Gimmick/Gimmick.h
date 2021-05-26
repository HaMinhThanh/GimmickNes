#pragma once
#include "GameObject.h"
#include "Star.h"
#include "LoadingStar.h"
#include "ScrollBar.h"
#include "Die.h"
#include "Bomb.h"

#define GIMMICK_WALKING_SPEED		0.06f 
#define GIMMICK_AUTO_GO_SPEED		0.03f
//0.1f
#define GIMMICK_JUMP_SPEED_Y		0.24f		//changed '-' in cpp
//#define GIMMICK_JUMP_SPEED_Y_2		-0.1f	isnt used
#define GIMMICK_DOUBLE_JUMP_SPEED		0.24f	//changed '-' in cpp
#define GIMMICK_JUMP_HIGHT_SPEED_Y		0.15f	//changed '-' in cpp

// slide speed
#define GIMMICK_SLIDE_UP_SPEED_X_1		0.05f
#define GIMMICK_SLIDE_UP_SPEED_X_2		0.075f
#define GIMMICK_SLIDE_DOWN_SPEED_X_1		0.125f
#define GIMMICK_SLIDE_DOWN_SPEED_X_2		0.1f

#define GIMMICK_SLIDE_UP_SPEED_Y_1		0.05f
#define GIMMICK_SLIDE_UP_SPEED_Y_2		0.04f
#define GIMMICK_SLIDE_DOWN_SPEED_Y_1		0.125f
#define GIMMICK_SLIDE_DOWN_SPEED_Y_2		0.05f

#define GIMMICK_JUMP_DEFLECT_SPEED -0.2f
#define GIMMICK_GRAVITY			-0.0008f
#define GIMMICK_DIE_DEFLECT_SPEED	 -0.5f
#define GIMMiCK_UNTOUCHABLE_TIME 4000

#define GIMMICK_STATE_IDLE			0
#define GIMMICK_STATE_WALKING_RIGHT	100
#define GIMMICK_STATE_WALKING_LEFT	200
#define GIMMICK_STATE_JUMP			300
#define GIMMICK_STATE_COLISION		400
#define MARIO_STATE_JUMP_HIGH_SPEED	500
#define GIMMICK_STATE_SLIDE_DOWN	600
#define GIMMICK_STATE_SLIDE_UP		700
#define GIMMICK_STATE_INCREASE		800
#define GIMMICK_STATE_DECREASE		900
#define GIMMICK_STATE_AUTO_GO		1000
#define GIMMICK_STATE_PIPING		1100
#define GIMMICK_STATE_DIE			9999

#define GIMMICK_ANI_IDLE_RIGHT		0
#define GIMMICK_ANI_IDLE_LEFT			1
#define GIMMICK_ANI_WALKING_RIGHT		2
#define GIMMICK_ANI_WALKING_LEFT		3
#define GIMMICK_ANI_JUMPING_RIGHT		4
#define GIMMICK_ANI_JUMPING_LEFT		5
#define GIMMICK_ANI_COLISION_RIGHT		6
#define GIMMICK_ANI_COLISION_LEFT		7

#define GIMMICK_BBOX_WIDTH  16
#define GIMMICK_BBOX_HEIGHT 19
#define GIMMICK_BBOX_HORN	4

// declare time
#define GIMMICK_TIME_LOADING_STAR	1000
#define GIMMICK_TIME_WAIT_RESET		2000
#define LOADING_STAR_ALIGN		8

#define GIMMICK_JUMP_BBOX_HEIGHT 24

#define MAX_ENERGY		4
#define MEDICINE_ITEM_INDEX		1
#define BOMB_ITEM_INDEX			2
#define FIREBALL_ITEM_INDEX		3

// trend of dynamic ground
#define GIMMICK_TREND_SLIDE_RIGHT	1
#define GIMMICK_TREND_SLIDE_LEFT	-1

#define GIMMICK_TREND_SCROLLBAR_INCREASE	1
#define GIMMICK_TREND_SCROLLBAR_DECREASE	-1


class CGimmick : public CGameObject
{
	static CGimmick* _instance;

public:

	int untouchable;
	DWORD untouchable_start;

	int waitToReset = 0;
	DWORD time_reset = 0;

	DWORD doubleJump_start = 0;
	DWORD time_maxjumping = 0;

	float start_x;			// initial position of Gimmick at scene
	float start_y;

	int jump = 0;
	int maxjumping = 0;
	bool isMaxJumping = false;

	bool isAutoGo = false;		// use for narrorw spot, ...


public:

	// Object depend
	CStar* star = NULL;					// star weapon of gimmick
	CLoadingStar* load_star = NULL;		// loading star effect when A key was pressed
	CDie* die_effect = NULL;			// effect when die
	CGameObject* obj = NULL;			// follow this obj if was idle state

	// new star
	DWORD time_load = 0;
	int loading = 0;

	// slide
	bool isSlide = false;				// check for sliding
	int slide_size;						// size of slide
	int direct_slide;
	int direct_go;						// trend of slide
	int key_down = 0;

	float slide_vx, slide_vy;

	bool isColisionWithBrick = true;	// if gimmick is sliding will not collide w brick

	bool isGoThrough = false;

	// pipe
	bool isPiping = false;		// checking gimmick is piping
	float pipeVx, pipeVy;		// set speed when piping

	// scrollbar
	bool isScrollBar = false;
	int trendScrollBar;
	float addVx;

	// Game parameter
	int score;
	int rest;
	int energy;
	int item = 0;
	int numItem = 0;

	bool isFollow = false;		// follow blob, moving brick when at the these's head
	bool isNotCollide = false;	// 

public:

	static CGimmick* GetInstance(float x, float y);

	CGimmick(float x = 0.0f, float y = 0.0f);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();
	void StartReset() { waitToReset = 1; time_reset = GetTickCount(); }
	void SetAniDie();

	void SetJumping(int jump) { this->jump = jump; };
	int GetJumping() { return jump; };

	void FollowObject(LPGAMEOBJECT obj);

	// Check for double jump
	DWORD GetDoubleJumpStart() { return doubleJump_start; }
	void StartJumpingMax() { maxjumping = 1, time_maxjumping = GetTickCount(); }
	void ResetDoubleJumpStart() { doubleJump_start = 0; }
	void SetDoubleJumpStart() { doubleJump_start = GetTickCount(); }

	// set slide
	void isCanSlide(vector<LPGAMEOBJECT>& listObj);
	float isOnTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float x, float y);
	void Slide_reset();

	// Star and Loading star
	void StarLoading() { time_load = GetTickCount(); loading = 1; }
	void ReSetLoading() { time_load = 0; loading = 0; }

	bool isCanShot = false;
	void ShotStar();
	void isPrepareShot();

	void SetLoadingStar();

	// KeyBoard
	void KeyState(BYTE* state);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	// Collision
	void collideWithEnemies(vector<LPCOLLISIONEVENT> coEvents, float& min_tx, float& min_ty, float& nx, float& ny, float& rdx, float& rdy);

	// HUD
	int GetScore() { return score; }
	int GetRest() { return rest; }
	int GetEnergy() { return energy; }

	int GetItem() { return item; }
};


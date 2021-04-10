﻿#pragma once
#include "GameObject.h"
#include "Star.h"
#include "LoadingStar.h"
#include "ScrollBar.h"
#include "Die.h"

#define GIMMICK_WALKING_SPEED		0.06f 
#define GIMMICK_AUTO_GO_SPEED		0.2f
//0.1f
#define GIMMICK_JUMP_SPEED_Y		0.24f
#define MARIO_JUMP_SPEED_Y_2		-0.1f
#define MARIO_DOUBLE_JUMP_SPEED	0.245f
#define MARIO_JUMP_HIGHT_SPEED_Y		0.12f

#define GIMMICK_JUMP_DEFLECT_SPEED 0.2f
#define GIMMICK_GRAVITY			0.0008f
#define GIMMICK_DIE_DEFLECT_SPEED	 0.5f
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

// trend of dynamic ground
#define GIMMICK_TREND_SLIDE_RIGHT	1
#define GIMMICK_TREND_SLIDE_LEFT	-1

#define GIMMICK_TREND_SCROLLBAR_INCREASE	1
#define GIMMICK_TREND_SCROLLBAR_DECREASE	-1


class CGimmick : public CGameObject
{
	static CGimmick* _instance;

	int untouchable;
	DWORD untouchable_start;

	int waitToReset = 0;
	DWORD time_reset = 0;

	DWORD doubleJump_start = 0;
	DWORD time_maxjumping = 0;

	float start_x;			// initial position of Mario at scene
	float start_y;

	int jump = 0;
	int maxjumping = 0;
	bool isMaxJumping = false;

	int shootFire = 0;
	int holdStar = 0;
public:
	
	// Object depend
	CStar* star = NULL;
	CLoadingStar* load_star = NULL;
	CDie* die_effect = NULL;

	// Backup position
	float backupX;
	float backupY;

	// new star
	DWORD time_load = 0;
	int loading = 0;

	// slide
	bool isSlide = false;
	int trendSlide;
	bool isColisionWithBrick = true;

	// scrollbar
	bool isScrollBar = false;
	int trendScrollBar;
	float addVx;

	// Game parameter
	int score;
	int rest;
	int energy;
	int item;
	
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

	// Check for double jump
	DWORD GetDoubleJumpStart() { return doubleJump_start; }
	void StartJumpingMax() { maxjumping = 1, time_maxjumping = GetTickCount(); }
	void ResetDoubleJumpStart() { doubleJump_start = 0; }
	void SetDoubleJumpStart() { doubleJump_start = GetTickCount(); }

	// set slide
	void isCanSlide(vector<LPGAMEOBJECT>& listObj);

	void StarLoading() { time_load = GetTickCount(); loading = 1; }
	void ReSetLoading() { time_load = 0; loading = 0; }

	bool isCanShot = false;
	void ShotStar();
	void isPrepareShot();

	void SetLoadingStar();	

	// HUD
	int GetScore() { return score; }
	int GetRest() { return rest; }
	int GetEnergy() { return energy; }

};


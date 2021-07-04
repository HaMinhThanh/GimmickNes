#pragma once

#include "GameObject.h"
#include "WindWall.h"
#include "WhiteBall.h"

#define SHADOW_POS_MAX		1990
#define SHADOW_POS_MIN		1806

#define SHADOW_SPEED_X		0.03f
#define SHADOW_SPEED_Y		0.03f

#define SHADOW_CLOAK_LIVE	3
#define SHADOW_NINJA_LIVE	5

#define SHADOW_STATE_CLOAK
#define SHADOW_STATE_LANKY_FELLOW
#define SHADOW_STATE_CRAZY_NINJA
#define SHADOW_STATE_ATTACK
#define SHADOW_STATE_HURT

#define SHADOW_ANI_CLOAK			0
#define SHADOW_ANI_LANKY_FELLOW		1
#define SHADOW_ANI_CRAZY_NINJA		2
#define SHADOW_ANI_ATTACK			3
#define SHADOW_ANI_HURT				4

#define BALL_NUMBER		3

#define SHADOW_ATTACK_TIME		1000
#define SHADOW_CRAZY_TIME		1200
#define SHADOW_HURT_TIME		600
#define SHADOW_LANKY_TIME		2000

class CShadow : public CGameObject
{
	//int max, min;
public:

	CWindWall* wall;
	vector<CWhiteBall*> ListBall;

	int live = 3;

	bool shoting = false;

	bool isCloak;
	bool isLanky;
	bool isNinja;
	bool isAttack;
	bool isHurt;

	DWORD time_attack = 0;
	DWORD time_crazy = 0;
	DWORD time_hurt = 0;
	DWORD time_lanky = 0;

	int attack = 0;
	int crazy = 0;
	int hurt = 0;
	int lanky = 0;


public:
	CShadow(float x, float y);
	~CShadow();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	void StartAttack() { time_attack = GetTickCount(); attack = 1; }
	void StartCrazy() { time_crazy = GetTickCount(); crazy = 1; }
	void StartHurt() { time_hurt = GetTickCount(); hurt = 1; }
	void StartLanky() { time_lanky = GetTickCount(); lanky = 1; }
};


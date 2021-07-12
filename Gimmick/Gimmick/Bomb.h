#pragma once
#include "Enemy.h"
#include "GameObject.h"

#define BOMB_STATE_WALKING_RIGHT	100
#define BOMB_STATE_WALKING_LEFT		200
#define BOMB_STATE_FLY_UP		300
#define BOMB_STATE_FLY_DOWN			400
#define BOMB_STATE_SLIDE_UP			500
#define BOMB_STATE_SLIDE_DOWN			600
#define BOMB_STATE_SCROLLBAR_IN			700
#define BOMB_STATE_SCROLLBAR_DE			800
#define BOMB_STATE_DIE				900

#define BOMB_GRAVITY				-0.0005f

#define BOMB_SPEED_X				0.05f
#define BOMB_SPEED_Y_NORMAL			0.18f
#define BOMB_SPEED_Y_COLLISION		-0.03f
#define BOMB_SPEED_FLY_X			0.05f
#define BOMB_SPEED_FLY_Y			0.03f

#define BOMB_ITEM_NON			0
#define BOMB_ITEM_BOMB			1
#define BOMB_ITEM_MEDICINE		2
#define BOMB_ITEM_FIREBALL		3

#define BOMB_BBOX_WIDTH		16
#define BOMB_BBOX_HEIGHT	16

#define BOMB_MAX_DISTANCE_WITH_GIMMICK	80
#define BOMB_JUMP_ALIGN		5

#define BOMB_WAIT_FLYING			7000
#define BOMB_FLYING_UP_TIME			3000
#define BOMB_FLYING_DOWN_TIME		4000

class CBomb: public CGameObject
{
public:

	bool isDie = false;

	bool isScrollBar = false;
	bool isSlide = false;

	int go_direct = 0;

	int item;

	bool isFlying = false;

	DWORD waitToFly = 0;
	int flying = 0;

	DWORD flyingUp = 0;
	int flyUp = 0;

	DWORD flyingDown = 0;
	int flyDown = 0;

public:


	CBomb(float x, float y, int item);
	~CBomb();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);

	void Jumping() { vy = BOMB_SPEED_Y_NORMAL; }

	void StartFlying() { flying = 1; waitToFly = GetTickCount(); }
	void StartFlyUp() { flyUp = 1; flyingUp = GetTickCount(); }
	void StartFlyDown() { flyDown = 1; flyingDown = GetTickCount(); }
};


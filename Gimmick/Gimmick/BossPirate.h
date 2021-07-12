#pragma once
#include "Enemy.h"
#include "GameObject.h"

#define BOMB_STATE_DAMAGED	111

#define BOMB_STATE_WALKING_RIGHT	100
#define BOMB_STATE_WALKING_LEFT		200
#define BOMB_STATE_FLY_RIGHT		300
#define BOMB_STATE_FLY_LEFT			400
#define BOMB_STATE_SLIDE_UP			500
#define BOMB_STATE_SLIDE_DOWN			600
#define BOMB_STATE_SCROLLBAR_IN			700
#define BOMB_STATE_SCROLLBAR_DE			800
#define BOMB_STATE_DIE				900

#define BOMB_GRAVITY				-0.0005f

#define PBOSS_SPEED_X				0.08f
#define PBOSS_SPEED_Y_NORMAL			0.1f
#define PBOSS_SPEED_Y_DAMAGED			0.17f
#define BOMB_SPEED_Y_COLLISION		-0.03f

#define BOMB_ITEM_NON			0
#define BOMB_ITEM_BOMB			1
#define BOMB_ITEM_MEDICINE		2
#define BOMB_ITEM_FIREBALL		3

#define PBOSS_BBOX_WIDTH	32
#define PBOSS_BBOX_HEIGHT	32

#define BOMB_MAX_DISTANCE_WITH_GIMMICK	52
#define BOMB_JUMP_ALIGN		5

class CBossPirate : public CGameObject
{
public:

	bool isDie = false;

	DWORD waitToFly = 0;
	int flying = 0;

	bool isScrollBar = false;
	bool isSlide = false;

	int go_direct = 0;

	int item;

public:

	int damaged = 0;
	CBossPirate(float x, float y, int item);
	~CBossPirate();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);

	void Jumping() { vy = PBOSS_SPEED_Y_NORMAL; }

	void StartFlying() { flying = 1; waitToFly = GetTickCount(); }
};


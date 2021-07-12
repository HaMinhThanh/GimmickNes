#pragma once
#include "Enemy.h"
#include "GameObject.h"

#define CAT_STATE_WALKING_RIGHT	100
#define CAT_STATE_WALKING_LEFT		200
#define CAT_STATE_IDLE_LEFT		300
#define CAT_STATE_IDLE_RIGHT			400
#define CAT_STATE_SLIDE_UP			500
#define CAT_STATE_SLIDE_DOWN			600
#define CAT_STATE_SCROLLBAR_IN			700
#define CAT_STATE_SCROLLBAR_DE			800
#define CAT_STATE_DIE				900

#define CAT_GRAVITY				-0.0005f

#define CAT_SPEED_X				0.05f
#define CAT_SPEED_Y_NORMAL			0.18f
#define CAT_SPEED_Y_COLLISION		-0.03f

#define CAT_BBOX_WIDTH		24
#define CAT_BBOX_HEIGHT		20

#define CAT_MAX_DISTANCE_WITH_GIMMICK	80
#define CAT_JUMP_ALIGN		5
#define CAT_TYLE_CAT	1

class CCat : public CGameObject
{
public:
	CCat(int type);
	int type;
	bool isDie = false;
	DWORD waitToFly = 0;
	int flying = 0;

	bool isScrollBar = false;
	bool isSlide = false;
	int shoot = 0;
	int go_direct = 0;

public:

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);

	void Jumping() { vy = CAT_SPEED_Y_NORMAL; }

	void StartFlying() { flying = 1; waitToFly = GetTickCount(); }
};

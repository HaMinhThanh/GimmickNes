#pragma once
#include "Enemy.h"
#include "GameObject.h"

#define BOMB_STATE_WALKING_RIGHT	100
#define BOMB_STATE_WALKING_LEFT		200
#define BOMB_STATE_FLY_RIGHT		300
#define BOMB_STATE_FLY_LEFT			400
#define BOMB_STATE_DIE				900

#define BOMB_GRAVITY				0.0005f

#define BOMB_SPEED_X				0.05f
#define BOMB_SPEED_Y_NORMAL			0.18f
#define BOMB_SPEED_Y_COLLISION		0.03f

#define BOMB_BBOX_WIDTH		16
#define BOMB_BBOX_HEIGHT	16

#define BOMB_MAX_DISTANCE_WITH_GIMMICK	80
#define BOMB_JUMP_ALIGN		5

class CBomb: public CGameObject
{
public:
	CBomb(float x, float y);
	~CBomb();

public:

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);

	void Jumping() { vy = -BOMB_SPEED_Y_NORMAL; }
};


#pragma once

#include "GameObject.h"
#include "Bomb.h"

#define KING_SPEED_X	0.01f
#define KING_SPEED_Y	0.05f

#define KING_ANI_WALKING	0
#define KING_ANI_IDLE		1
#define KING_ANI_DIE		1

#define POS_MAX_X	80
#define POS_MIN_X	48

#define KING_MAX_LIVE		3

#define KING_BBOX_WIDTH		32
#define KING_BBOX_HEIGHT	32

#define KING_BBOX_BULB		7

#define BOMB_NUMBER			5
#define TIME_SHOT			500

#define BOMB_SPEED_VX		0.03f
#define BOMB_SPEED_VY		0.03f

class CKingElectrode : public CGameObject
{
	//int max, min;
public:

	int live;
	bool isDie = false;
	bool isShotBomb = false;
	int shoting = 0;
	DWORD time_shot = 0;
	
	vector<CBomb*> ListBomb;

public:
	CKingElectrode(float x, float y);
	~CKingElectrode();

	void StartShot() { shoting = 1;  time_shot = GetTickCount(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};


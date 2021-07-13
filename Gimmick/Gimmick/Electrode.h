#pragma once

#include "GameObject.h"

#define ELECTRODE_GRAVITY		-0.007f
#define ELECTRODE_SPEED_X		0.02f
#define ELECTRODE_SPEED_Y		0.2f

#define ELECTRODE_BBOX_WIDTH	16
#define ELECTRODE_BBOX_HEIGHT	21

#define ELECTRODE_BBOX_BULB		6

#define ELECTRODE_ANI_WALKING_RIGHT		2
#define ELECTRODE_ANI_WALKING_LEFT		3
#define ELECTRODE_ANI_IDLE_RIGHT		0
#define ELECTRODE_ANI_IDLE_LEFT			1
#define ELECTRODE_ANI_DIE				4

#define ELECTRODE_DISTANCE_GIMMICK		64

#define WINDOW_OPEN_SPRITES_1		80021
#define WINDOW_OPEN_SPRITES_2		80022
#define WINDOW_OPEN_SPRITES_3		80023
#define WINDOW_CLOSE_SPRITE			80024

class CElectrode: public CGameObject
{
public:
	
	bool isActive = false;
	bool isIdle = false;
	bool isDie = false;

public:
	CElectrode(float x, float y);
	~CElectrode();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};


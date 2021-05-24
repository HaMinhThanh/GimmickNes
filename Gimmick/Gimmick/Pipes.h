#pragma once

#include "GameObject.h"

#define PIPE_BBOX_WIDTH		16
#define PIPE_BBOX_HEIGHT	16

#define PIPE_SPEED_X	0.1f
#define PIPE_SPEED_Y	0.1f

class CPipes: public CGameObject
{
public:

	CPipes(float x, float y, int type);
	~CPipes();

	bool isDeversed;
	int type;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects);
	void Render();	

};


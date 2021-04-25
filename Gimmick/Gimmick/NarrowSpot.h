#pragma once
#include "GameObject.h"

class CNarrowSpot : public CGameObject
{
public:

	CNarrowSpot(float x, float y);
	~CNarrowSpot();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};


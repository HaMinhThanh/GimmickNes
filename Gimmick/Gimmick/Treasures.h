#pragma once

#include "GameObject.h"

class CTreasures: public CGameObject
{
public:
	CTreasures(int width, int hight);
	~CTreasures();

	int width, height;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

};


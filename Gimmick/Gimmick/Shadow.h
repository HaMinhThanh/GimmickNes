#pragma once

#include "GameObject.h"

class CShadow : public CGameObject
{
	//int max, min;
public:


public:
	CShadow(float x, float y);
	~CShadow();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};


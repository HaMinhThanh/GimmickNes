#pragma once

#include "GameObject.h"

class CPipes: public CGameObject
{
public:

	CPipes(int x1, int x2, int t, int w, int h);
	~CPipes();

	int xLeft, xRight, yTop;

	int width, height;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects);
	void Render();	

};


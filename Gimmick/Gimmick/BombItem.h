#pragma once
#include "GameObject.h"

#define ITEM_GRAVITY		-0.0007f

#define BOMB_ITEM_SPRITE		70004

#define BOMB_ITEM_BBOX_WIDTH		10
#define BOMB_ITEM_BBOX_HEIGHT		14

class CBombItem : public CGameObject
{
public:

	CBombItem(float _x, float _y);
	~CBombItem();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};


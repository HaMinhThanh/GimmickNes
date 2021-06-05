#pragma once
#include "GameObject.h"
#include "Enemy.h"


#define TURTLE_GRAVITY		-0.007f
#define TURTLE_SPEED_X		0.02f
#define TURTLE_SPEED_Y		0.1f

#define TURTLE_BBOX_WIDTH	16
#define TURTLE_BBOX_HEIGHT	16


#define TURTLE_ANI_IDLE_RIGHT		0
#define TURTLE_ANI_IDLE_LEFT		1
#define TURTLE_ANI_WALKING_RIGHT	2
#define TURTLE_ANI_WALKING_LEFT		3
#define TURTLE_ANI_DIE				4

class GreenTurtle : public CGameObject
{
private:
	GreenTurtle(float x, float y);
	~GreenTurtle();

	bool isDie = false;


	bool isScrollBar = false;
	bool isSlide = false;

	int moving_direction = 0;

public:

	void Update(vector<LPGAMEOBJECT>* coObjects);
	void Render();
	//void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);

};


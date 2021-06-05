#include "GreenTurtle.h"
#include "Brick.h"
#include "ScrollBar.h"
#include "Gimmick.h"

GreenTurtle::GreenTurtle(float _x, float _y)
{
	this->x = _x;
	this->y = _y;

	SetState(TURTLE_ANI_WALKING_LEFT);
}

GreenTurtle::~GreenTurtle()
{
}

void GreenTurtle::Render()
{
	int state = GetState();

	if (state == TURTLE_ANI_WALKING_RIGHT)
		animation_set->at(0)->Render(x, y);

	else if (state == TURTLE_ANI_WALKING_LEFT)
		animation_set->at(1)->Render(x, y);

	else if (state == TURTLE_ANI_IDLE_RIGHT)
		animation_set->at(2)->Render(x, y);

	else if (state == TURTLE_ANI_IDLE_RIGHT)
		animation_set->at(3)->Render(x, y);

	else if (state == TURTLE_ANI_DIE)
		animation_set->at(4)->Render(x, y);
	else if (vx > 0)
		animation_set->at(0)->Render(x, y);
	else
		animation_set->at(1)->Render(x, y);
}

void GreenTurtle::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state) {

	case BOMB_STATE_WALKING_RIGHT:
		vx = BOMB_SPEED_X;
		break;

	case BOMB_STATE_WALKING_LEFT:
		vx = -BOMB_SPEED_X;
		break;
	case BOMB_STATE_SCROLLBAR_IN:
	{
		if (moving_direction == 1)
			vx = 0.075f;
		else if (moving_direction == -1)
			vx = -0.025f;
	}
	break;

	case BOMB_STATE_SCROLLBAR_DE:
	{
		if (moving_direction == 1)
			vx = 0.025f;
		else if (moving_direction == -1)
			vx = -0.075f;
	}
	break;

	case BOMB_STATE_SLIDE_UP:
		break;
	case BOMB_STATE_SLIDE_DOWN:
		break;
	case BOMB_STATE_FLY_RIGHT:
		break;

	case BOMB_STATE_FLY_LEFT:
		break;

	case BOMB_STATE_DIE:
		vy = BOMB_SPEED_Y_NORMAL;
		vx *= -1;
		isFinish = true;

		break;
	}
}

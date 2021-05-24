#include "Pipes.h"

CPipes::CPipes(float x, float y, int type)
{
	isDeversed = false;

	if (type == 1) {

		vx = -PIPE_SPEED_X;
		vy = 0;
	}
	else if (type == 2) {

		vx = -PIPE_SPEED_X;
		vy = -PIPE_SPEED_Y;
	}
	else if (type == 3) {

		vx = 0;
		vy = -PIPE_SPEED_Y;
	}
	else if (type == 4) {

		vx = PIPE_SPEED_X;
		vy = -PIPE_SPEED_Y;
	}
	else if (type == 5) {

		vx = PIPE_SPEED_X;
		vy = 0;
	}
	else if (type == 6) {

		vx = PIPE_SPEED_X;
		vy = PIPE_SPEED_Y;
	}
	else if (type == 7) {

		vx = 0;
		vy = PIPE_SPEED_Y;
	}
	else if (type == 8) {

		vx = -PIPE_SPEED_X;
		vy = PIPE_SPEED_Y;
	}
	
}

CPipes::~CPipes()
{
}

void CPipes::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + PIPE_BBOX_WIDTH;
	bottom = y + PIPE_BBOX_HEIGHT;
}

void CPipes::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CPipes::Render()
{
}

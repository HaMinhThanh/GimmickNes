#include "Die.h"

CDie::CDie(float x, float y)
{
	isFinish = false;

	x1 = x2 = x3 = x4 = x5 = x6 = x7 = x8 = x;
	y1 = y2 = y3 = y4 = y5 = y6 = y7 = y8 = y;
}

CDie::~CDie()
{
}

void CDie::TurnToBegin(float x, float y)
{
	x1 = x2 = x3 = x4 = x5 = x6 = x7 = x8 = x;
	y1 = y2 = y3 = y4 = y5 = y6 = y7 = y8 = y;
}

void CDie::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}

void CDie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isRender == 1) {

		if (GetTickCount() - time_render >= DIE_EFFECT_TIME) {

			isRender = 0;
			time_render = 0;

			isFinish = true;
		}
		else if (GetTickCount() - time_render >= DIE_EFFECT_TIME - 800) {

			ani = DIE_EFFECT_ANI_4;
		}
		else if (GetTickCount() - time_render >= DIE_EFFECT_TIME - 1300) {

			ani = DIE_EFFECT_ANI_3;
		}
		else if (GetTickCount() - time_render >= DIE_EFFECT_TIME - 1800) {

			ani = DIE_EFFECT_ANI_2;
		}
		else {
			ani = DIE_EFFECT_ANI_1;
		}
	}

	CGameObject::Update(dt, coObjects);

	x1 += -SPEED_X * dt;
	x2 += -SPEED_X * 0.75 * dt;
	x3 += 0;
	x4 += SPEED_X * 0.75 * dt;
	x5 += SPEED_X * dt;
	x6 += SPEED_X * 0.75 * dt;
	x7 += 0;
	x8 += -SPEED_X * dt;

	y1 += 0;
	y2 += -SPEED_Y * 0.75 * dt;
	y3 += -SPEED_Y * dt;
	y4 += -SPEED_Y * 0.75 * dt;
	y5 += 0;
	y6 += SPEED_Y * 0.75 * dt;
	y7 += SPEED_Y * dt;
	y8 += SPEED_Y * 0.75 * dt;

}

void CDie::Render()
{
	if (isRender == 1) {

		CSprites::GetInstance()->Get(ani)->Draw(x1, y1);
		CSprites::GetInstance()->Get(ani)->Draw(x2, y2);
		CSprites::GetInstance()->Get(ani)->Draw(x3, y3);
		CSprites::GetInstance()->Get(ani)->Draw(x4, y4);
		CSprites::GetInstance()->Get(ani)->Draw(x5, y5);
		CSprites::GetInstance()->Get(ani)->Draw(x6, y6);
		CSprites::GetInstance()->Get(ani)->Draw(x7, y7);
		CSprites::GetInstance()->Get(ani)->Draw(x8, y8);
	}
}

#include "WindWall.h"
#include "Camera.h"
#include "Define.h"

CWindWall::CWindWall(float _x, float _y)
{
	x = _x;
	y = _y;

	backupX = x;
	backupY = y;

	isFinish = false;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(WALL_ANIMATION_SET);

	this->SetAnimationSet(ani_set);
}

CWindWall::~CWindWall()
{
}

void CWindWall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 10;
	bottom = y - 50;
}

void CWindWall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;

	float camx, camy;
	CCamera::GetInstance()->GetCamPos(camx, camy);

	if (x< camx || x> camx + SCREEN_WIDTH || y< camy || y> camy + SCREEN_HEIGHT_MAP) {

		SetPosition(backupX, backupY);

	}
}

void CWindWall::Render()
{
	animation_set->at(0)->Render(x, y);
}

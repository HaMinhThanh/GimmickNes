#include "HiddenObject.h"


CHiddenObject::CHiddenObject(float _x, float _y, float _w, float _h, int cam_l, int cam_r)
{
	x = _x;
	y = _y;

	w = _w;
	h = _h;

	cam_left = cam_l;
	cam_right = cam_r;
}

CHiddenObject::~CHiddenObject()
{
}

void CHiddenObject::BackUpCam(int _backup_camLeft, int _backup_camRight)
{
	backup_camLeft = _backup_camLeft; 
	backup_camRight = _backup_camRight;

	isBackUp = true;
}

void CHiddenObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + w;
	bottom = y + h;
}

void CHiddenObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CHiddenObject::Render()
{
}

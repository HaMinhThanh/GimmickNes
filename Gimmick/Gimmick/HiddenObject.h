#pragma once
#include "GameObject.h"

#define HIDDEN_TYPE_CHANGE_CAMERA		1

class CHiddenObject : public CGameObject
{
public:

	CHiddenObject( float x, float y, float w, float h, int cam_left, int cam_right);
	~CHiddenObject();

	float x, y, w, h;
	int cam_left, cam_right;

	int backup_camLeft, backup_camRight;
	bool isBackUp = false;

	void BackUpCam(int _backup_camLeft, int _backup_camRight);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};


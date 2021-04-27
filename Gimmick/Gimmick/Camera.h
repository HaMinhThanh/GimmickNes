#pragma once
class CCamera
{
public:
	static CCamera* __instance;

	CCamera();
	~CCamera();

	float cam_x = 0.0f;
	float cam_y = 0.0f;

	int _xLeft, _xRight, _yTop, _yBot;
	bool isMovingCam = false;

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	void GetCamPos(float& x, float& y) { x = cam_x; y = cam_y; }

	int GetYBoundary() { return _yBot; }

	void SetCamBoundary(float x1, float x2, float t) { _xLeft = x1; _xRight = x2; _yTop = t; }
	void GetCamBoundary(float& x1, float& x2, float& t) { x1 = _xLeft; x2 = _xRight; t = _yTop; }

	void SetYBoundary(int b) { _yBot = b; }

	void MovingCamX(float cx);

	static CCamera* GetInstance();

};


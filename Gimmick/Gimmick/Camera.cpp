#include "Camera.h"
#include <cstddef>

#include "Define.h"

CCamera* CCamera::__instance = NULL;

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

//RECT CCamera::GetBound()
//{
//	RECT r;
//
//	r.left = _xLeft;
//	r.right = _xLeft + SCREEN_WIDTH;
//	r.top = _yTop;
//	r.bottom = _yTop + SCREEN_HEIGHT_MAP;
//
//	return r;
//}

void CCamera::MovingCamX(float xCam)
{
	
}

CCamera* CCamera::GetInstance()
{
	if (__instance == NULL) __instance = new CCamera();
	return __instance;
}

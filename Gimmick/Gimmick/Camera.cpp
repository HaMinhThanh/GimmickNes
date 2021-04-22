#include "Camera.h"
#include <cstddef>

CCamera* CCamera::__instance = NULL;

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

void CCamera::MovingCamX(float xCam)
{
	
}

CCamera* CCamera::GetInstance()
{
	if (__instance == NULL) __instance = new CCamera();
	return __instance;
}

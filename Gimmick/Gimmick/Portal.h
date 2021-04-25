#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
public:

	int scene_id = 0;	// target scene to switch to 

	int width;
	int height;
public:

	CPortal(float l, float t, float r, float b, int scene_id);
	~CPortal();

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetSceneId() { return scene_id; }
};
#pragma once
#include "GameObject.h"

class CBuilding : public GameObject
{
public:
	CBuilding();
	CBuilding(Vec3 pos, float size, Vec4 color, OBJECT_TYPE type);
	virtual ~CBuilding();

	virtual void Draw(Renderer *g_Renderer);						// ������Ʈ �׸���
	virtual void Draw(Renderer *g_Renderer, unsigned int textureID);		// ������Ʈ �׸���
	virtual void Update(float fTimeElapsed);						// ������ ������Ʈ
};


#pragma once
#include "GameObject.h"

class CBuilding : public GameObject
{
public:
	CBuilding();
	CBuilding(Vec3 pos, float size, Vec4 color, OBJECT_TYPE type);
	virtual ~CBuilding();

	virtual void Draw(Renderer *g_Renderer);						// 오브젝트 그리기
	virtual void Draw(Renderer *g_Renderer, unsigned int textureID);		// 오브젝트 그리기
	virtual void Update(float fTimeElapsed);						// 프레임 업데이트
};


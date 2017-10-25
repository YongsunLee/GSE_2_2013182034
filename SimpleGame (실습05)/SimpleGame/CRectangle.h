#pragma once
#include "GameObject.h"

class CRectangle : public GameObject
{
private:

public:
	CRectangle();
	CRectangle(Vec3 pos, float size, Vec4 color);
	virtual ~CRectangle();

	void IsInitialized(Vec3 pos, float size, Vec4 color);

	virtual void Draw(Renderer *g_Renderer);		// 오브젝트 생성
	virtual void Update(float fTimeElapsed);		// 프레임 업데이트
};


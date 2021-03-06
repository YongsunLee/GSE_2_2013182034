#pragma once
#include "GameObject.h"

class CRectangle : public GameObject
{
private:

public:
	CRectangle();
	CRectangle(OBJECT_TYPE type);
	CRectangle(Vec3 pos, float size, Vec4 color, OBJECT_TYPE type);
	virtual ~CRectangle();

	void IsInitialized(Vec3 pos, float size, Vec4 color, OBJECT_TYPE type);

	virtual void Draw(Renderer *g_Renderer);		// 오브젝트 생성
	virtual void Update(float fTimeElapsed);		// 프레임 업데이트
};


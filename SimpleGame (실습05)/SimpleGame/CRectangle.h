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

	virtual void Draw(Renderer *g_Renderer);		// ������Ʈ ����
	virtual void Update(float fTimeElapsed);		// ������ ������Ʈ
};


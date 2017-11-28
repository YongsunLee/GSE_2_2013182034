#pragma once
#include "GameObject.h"

class CRectangle : public GameObject
{
private:
	float m_maxLife;
	float HP;
public:
	CRectangle();
	CRectangle(OBJECT_TYPE type);
	CRectangle(Vec3 pos, float size, Vec4 color, OBJECT_TYPE type);
	virtual ~CRectangle();

	void IsInitialized(Vec3 pos, float size, Vec4 color, OBJECT_TYPE type);
	void SetMaxLife() { m_maxLife = m_nLife; };

	virtual void Draw(Renderer *g_Renderer);		// ������Ʈ ����
	virtual void Update(float fTimeElapsed);		// ������ ������Ʈ
};


#pragma once
#include "GameObject.h"

class CBuilding : public GameObject
{
public:
	CBuilding();
	CBuilding(Vec3 pos, float size, Vec4 color, OBJECT_TYPE type);
	virtual ~CBuilding();

	void SetMaxHP() { m_maxLife = m_nLife; };

	virtual void Draw(Renderer *g_Renderer);						// ������Ʈ �׸���
	virtual void Draw(Renderer *g_Renderer, unsigned int textureID);		// ������Ʈ �׸���
	virtual void Update(float fTimeElapsed);						// ������ ������Ʈ
private:
	float m_maxLife;
	float HP;
	char LifeText[10];
};


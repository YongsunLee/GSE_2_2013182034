#pragma once
#include "GameObject.h"

class CBuilding : public GameObject
{
public:
	CBuilding();
	CBuilding(Vec3 pos, float size, Vec4 color, OBJECT_TYPE type);
	virtual ~CBuilding();

	void SetMaxHP() { m_maxLife = m_nLife; };

	virtual void Draw(Renderer *g_Renderer);						// 오브젝트 그리기
	virtual void Draw(Renderer *g_Renderer, unsigned int textureID);		// 오브젝트 그리기
	virtual void Update(float fTimeElapsed);						// 프레임 업데이트
private:
	float m_maxLife;
	float HP;
	char LifeText[10];
};


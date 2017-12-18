#pragma once
#include "GameObject.h"

class CRectangle : public GameObject
{
private:
	float m_maxLife;
	float HP;
	int SeqX = 0;
	float SeqXTimer = 0.f;
	int SeqY = 0;

public:
	CRectangle();
	CRectangle(OBJECT_TYPE type);
	CRectangle(Vec3 pos, float size, Vec4 color, OBJECT_TYPE type);
	virtual ~CRectangle();

	void IsInitialized(Vec3 pos, float size, Vec4 color, OBJECT_TYPE type);
	void SetMaxLife() { m_maxLife = m_nLife; };

	virtual void Draw(Renderer *g_Renderer);								// 오브젝트 생성
	virtual void Draw(Renderer *g_Renderer, unsigned int textureID);		// 텍스쳐 오브젝트 생성
	virtual void Update(float fTimeElapsed);								// 프레임 업데이트
};


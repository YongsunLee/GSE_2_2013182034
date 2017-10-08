#pragma once
#include "GameObject.h"

class CRectangle : public GameObject
{
private:
	Vec3 m_nPosition;		// 위치 (x, y, z)
	Vec4 m_nColor;			// 색상 (r, g, b, a)
	Vec4 m_nOOBB;			// 충돌 박스 위치 LTOP_x, LTOP_y, RBOT_x, RBOT_y
	float m_nSize;			// 크기
	float m_nMass;			// 질량
	float m_nSpeed;			// 이동속도 ( 하위 오브젝트 )

public:
	CRectangle();
	CRectangle(Vec3 pos, float size, Vec4 color);
	virtual ~CRectangle();

	void IsInitialized(Vec3 pos, float size, Vec4 color);

	virtual void BuildObject(Renderer *g_Renderer);		// 오브젝트 생성
	virtual void Update();								// 프레임 업데이트
};


#pragma once

#include "stdafx.h"
#include "Renderer.h"

class GameObject
{
protected:
	Vec3 m_nPosition;		// 위치 (x, y, z)
	Vec4 m_nColor;			// 색상 (r, g, b, a)
	Vec4 m_nOOBB;			// 충돌 박스 위치 LTOP_x, LTOP_y, RBOT_x, RBOT_y
	Vec3 m_nDir;
	float m_nSize;			// 크기
	float m_nMass;			// 질량
	float m_nSpeed;			// 이동속도

public:
	GameObject();
	virtual ~GameObject();

	//-------------------
	virtual void Move(float speed);
	virtual void Rotate(Vec3 pxmf3Axis, float fAngle);
	//-------------------

	virtual void Draw(Renderer *g_Renderer);		// 오브젝트 생성
	virtual void Update();								// 프레임 업데이트


	//-----------  Get,  Set  -----------------------
	virtual void SetOOBB();								// 충돌박스

	virtual void SetPosition(Vec3 pos);
	Vec3 GetPosition();

	virtual void SetColor(Vec4 color);
	Vec4 GetColor();

	virtual void SetSize(float size);
	virtual void SetMass(float mass);
	virtual void SetSpeed(float speed);
};


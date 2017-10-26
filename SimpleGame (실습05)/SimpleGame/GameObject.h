#pragma once

#include "stdafx.h"
#include "Renderer.h"

class GameObject
{
protected:
	Vec3 m_nPosition;		// 위치 (x, y, z)
	Vec4 m_nColor;			// 색상 (r, g, b, a)
	Vec3 m_nDir;			// 방향
	
	float m_nSize;			// 크기
	float m_nMass;			// 질량
	float m_nSpeed;			// 이동속도
	float m_nLife;			// 생명

	OOBB m_nOOBB;			// 충돌 박스 위치 LTOP_x, LTOP_y, RBOT_x, RBOT_y
	bool m_bCollision;
public:
	GameObject();
	virtual ~GameObject();

	//-------------------
	virtual void Move(float speed);
	virtual void Rotate(Vec3 pxmf3Axis, float fAngle);
	//-------------------

	virtual void Draw(Renderer *g_Renderer);			// 오브젝트 생성
	virtual void Update(float fTimeElapsed);								// 프레임 업데이트

	// ----------------- 충돌 체크--------------------
	virtual void SetOOBB();								// 충돌박스
	virtual bool Collision(GameObject *gObject);
	virtual void SetCollision(bool status);
	virtual bool GetCollision();
	//------------------------------------------------

	//-----------  Get,  Set  -----------------------
	virtual void SetPosition(Vec3 pos);
	Vec3 GetPosition();

	virtual void SetColor(Vec4 color);
	Vec4 GetColor();

	virtual void SetDir(Vec3 dir);

	virtual void SetSize(float size);
	virtual void SetMass(float mass);
	virtual void SetSpeed(float speed);

	virtual void SetLife(float life);
};


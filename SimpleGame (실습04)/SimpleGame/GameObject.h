#pragma once

#include "stdafx.h"
#include "Renderer.h"

class GameObject
{
protected:
	Vec3 m_nPosition;		// ��ġ (x, y, z)
	Vec4 m_nColor;			// ���� (r, g, b, a)
	Vec4 m_nOOBB;			// �浹 �ڽ� ��ġ LTOP_x, LTOP_y, RBOT_x, RBOT_y
	Vec3 m_nDir;
	float m_nSize;			// ũ��
	float m_nMass;			// ����
	float m_nSpeed;			// �̵��ӵ�

public:
	GameObject();
	virtual ~GameObject();

	//-------------------
	virtual void Move(float speed);
	virtual void Rotate(Vec3 pxmf3Axis, float fAngle);
	//-------------------

	virtual void Draw(Renderer *g_Renderer);		// ������Ʈ ����
	virtual void Update();								// ������ ������Ʈ


	//-----------  Get,  Set  -----------------------
	virtual void SetOOBB();								// �浹�ڽ�

	virtual void SetPosition(Vec3 pos);
	Vec3 GetPosition();

	virtual void SetColor(Vec4 color);
	Vec4 GetColor();

	virtual void SetSize(float size);
	virtual void SetMass(float mass);
	virtual void SetSpeed(float speed);
};


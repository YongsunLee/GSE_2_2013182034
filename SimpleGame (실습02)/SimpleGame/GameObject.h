#pragma once

#include "stdafx.h"
#include "Renderer.h"

class GameObject
{
private:
	Vec3 m_nPosition;		// ��ġ (x, y, z)
	Vec4 m_nColor;			// ���� (r, g, b, a)
	Vec4 m_nOOBB;			// �浹 �ڽ� ��ġ LTOP_x, LTOP_y, RBOT_x, RBOT_y
	float m_nSize;			// ũ��
	float m_nMass;			// ����
	float m_nSpeed;			// �̵��ӵ� ( ���� ������Ʈ )

public:
	GameObject();
	virtual ~GameObject();

	//-------------------
	void Move(Vec3 dir, float speed);
	void Rotate(Vec3 pxmf3Axis, float fAngle);
	//-------------------

	virtual void BuildObject(Renderer *g_Renderer);		// ������Ʈ ����
	virtual void Update();								// ������ ������Ʈ

	virtual void SetOOBB();								// �浹�ڽ�
	
	virtual void SetPosition(Vec3 pos);
	Vec3 GetPosition();

	virtual void SetColor(Vec4 color);
	virtual void SetSize(float size);
	virtual void SetMass(float mass);
};


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
	GameObject(Vec3 pos, float size, Vec4 color);
	~GameObject();

	void IsInitialized(Vec3 pos, float size, Vec4 color);

	//-------------------
	void Move(Vec3 dir, float speed);
	//-------------------

	void BuildObject(Renderer *g_Renderer);		// ������Ʈ ����
	void Update();			// ������ ������Ʈ

	void SetOOBB();			// �浹�ڽ�
	void SetPosition(Vec3 pos);
	void SetColor(Vec4 color);
	void SetSize(float size);
	void SetMass(float mass);
};


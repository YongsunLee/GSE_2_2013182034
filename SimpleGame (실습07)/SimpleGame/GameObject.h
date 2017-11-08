#pragma once

#include "stdafx.h"
#include "Renderer.h"

class GameObject
{
protected:
	Vec3 m_nPosition;		// ��ġ (x, y, z)
	Vec4 m_nColor;			// ���� (r, g, b, a)
	Vec3 m_nDir;			// ����
	
	float m_nSize;			// ũ��
	float m_nMass;			// ����
	float m_nSpeed;			// �̵��ӵ�

	OOBB m_nOOBB;			// �浹 �ڽ� ��ġ LTOP_x, LTOP_y, RBOT_x, RBOT_y
	bool m_bCollision;		// �浹 Ȯ��

	float m_nLife;			// ����
	float m_nLifeTime;		// ����ð�

	OBJECT_TYPE m_type;

public:
	GameObject();
	virtual ~GameObject();

	//-------------------
	virtual void Move(float speed);
	virtual void Rotate(Vec3 pxmf3Axis, float fAngle);
	//-------------------

	virtual void Draw(Renderer *g_Renderer);								// ������Ʈ �׸���
	virtual void Draw(Renderer *g_Renderer, unsigned int textureID);				// ������Ʈ �׸���(texture)
	virtual void Update(float fTimeElapsed);								// ������ ������Ʈ

	// ----------------- �浹 üũ--------------------
	virtual void SetOOBB();								// �浹�ڽ�
	virtual bool Collision(GameObject *gObject1, GameObject *gObject2);
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
	virtual float GetLife();

	virtual float GetLifeTime();

	virtual void SetType(OBJECT_TYPE type);
	virtual OBJECT_TYPE GetType();
};


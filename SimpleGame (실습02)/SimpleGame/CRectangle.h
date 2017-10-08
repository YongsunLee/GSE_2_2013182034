#pragma once
#include "GameObject.h"

class CRectangle : public GameObject
{
private:
	Vec3 m_nPosition;		// ��ġ (x, y, z)
	Vec4 m_nColor;			// ���� (r, g, b, a)
	Vec4 m_nOOBB;			// �浹 �ڽ� ��ġ LTOP_x, LTOP_y, RBOT_x, RBOT_y
	float m_nSize;			// ũ��
	float m_nMass;			// ����
	float m_nSpeed;			// �̵��ӵ� ( ���� ������Ʈ )

public:
	CRectangle();
	CRectangle(Vec3 pos, float size, Vec4 color);
	virtual ~CRectangle();

	void IsInitialized(Vec3 pos, float size, Vec4 color);

	virtual void BuildObject(Renderer *g_Renderer);		// ������Ʈ ����
	virtual void Update();								// ������ ������Ʈ
};


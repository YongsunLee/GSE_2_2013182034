#include "stdafx.h"
#include "GameObject.h"
//--------------------------------------------------------------------
// ������ �Ҹ���
GameObject::GameObject()
{
	// �ʱ�ȭ
	m_nPosition = {0.0f, 0.0f, 0.0f};
	m_nColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_nOOBB = { 0.0f,0.0f,0.0f,0.0f };
	m_nMass = 0.0f;
	m_nSize = 0.0f;
}

GameObject::~GameObject()
{
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// ȸ��, �̵�
void GameObject::Move(Vec3 dir, float speed)
{
	if (m_nPosition.x > WINDOWWIDTH / 2)
		dir.x = -dir.x;
	else if (m_nPosition.x < -(WINDOWWIDTH / 2))
		dir.x = -dir.x;

	SetPosition(Vec3{ m_nPosition.x + dir.x * speed, 
					  m_nPosition.y + dir.y * speed, 
					  m_nPosition.z + dir.z * speed });
}

void GameObject::Rotate(Vec3 vec3Axis, float fAngle)
{
}
//--------------------------------------------------------------------


// �׸���
void GameObject::BuildObject(Renderer *g_Renderer)
{
	
}

// �ִϸ��̼�
void GameObject::Update()
{
	
}

// �浹üũ �ڽ�
void GameObject::SetOOBB()
{
}


//--------------------------------------------------------------------
// Set, Get
void GameObject::SetPosition(Vec3 pos)
{
	m_nPosition = pos;
}

Vec3 GameObject::GetPosition()
{
	return Vec3(m_nPosition);
}

void GameObject::SetColor(Vec4 color)
{
	m_nColor = color;
}

Vec4 GameObject::GetColor()
{
	return Vec4(m_nColor);
}

void GameObject::SetSize(float size)
{
	m_nSize = size;
}

void GameObject::SetMass(float mass)
{
	m_nMass = mass;
}
//--------------------------------------------------------------------

#include "stdafx.h"
#include "GameObject.h"
//--------------------------------------------------------------------
// 생성자 소멸자
GameObject::GameObject()
{
	// 초기화
	m_nPosition = {0.0f, 0.0f, 0.0f};
	m_nColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_nOOBB = { 0.0f,0.0f,0.0f,0.0f };
	m_nMass = 0.0f;
	m_nSize = 0.0f;
	m_nDir = {0.0f, 0.0f, 0.0f};
}

GameObject::~GameObject()
{
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// 회전, 이동
void GameObject::Move(float speed)
{
	if (m_nPosition.x > WINDOWWIDTH / 2)
		m_nDir.x = -abs(m_nDir.x);
	else if (m_nPosition.x < -(WINDOWWIDTH / 2))
		m_nDir.x = abs(m_nDir.x);

	if (m_nPosition.y > WINDOWHEIGHT/ 2)
		m_nDir.y = -abs(m_nDir.y);
	else if (m_nPosition.y < -(WINDOWHEIGHT / 2))
		m_nDir.y = abs(m_nDir.y);

	SetPosition(Vec3{ m_nPosition.x + (m_nDir.x * speed), 
					  m_nPosition.y + (m_nDir.y * speed), 
					  m_nPosition.z + (m_nDir.z * speed) });
}

void GameObject::Rotate(Vec3 vec3Axis, float fAngle)
{
}
//--------------------------------------------------------------------


// 그리기
void GameObject::Draw(Renderer *g_Renderer)
{
	
}

// 애니메이션
void GameObject::Update()
{
	
}

// 충돌체크 박스
void GameObject::SetOOBB()
{
	m_nOOBB = {m_nPosition.x - m_nSize , m_nPosition.y - m_nSize, m_nPosition.x + m_nSize, m_nPosition.y + m_nSize};
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

void GameObject::SetSpeed(float speed)
{
	m_nSpeed = speed;
}
//--------------------------------------------------------------------

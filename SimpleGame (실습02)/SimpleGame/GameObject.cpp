#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{
	// 초기화
	m_nPosition = {0.0f, 0.0f, 0.0f};
	m_nColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_nOOBB = { 0.0f,0.0f,0.0f,0.0f };
	m_nMass = 0.0f;
	m_nSize = 0.0f;
}

GameObject::GameObject(Vec3 pos, float size, Vec4 color)
{
	m_nPosition = pos;
	m_nColor = color;
	m_nSize = size;
}

GameObject::~GameObject()
{
}

void GameObject::IsInitialized(Vec3 pos, float size, Vec4 color)
{
	m_nPosition = pos;
	m_nColor = color;
	m_nSize = size;
}

void GameObject::Move(Vec3 dir, float speed)
{
	SetPosition(Vec3{ m_nPosition.x + dir.x * speed, m_nPosition.y + dir.y * speed, m_nPosition.z + dir.z * speed });
}

void GameObject::BuildObject(Renderer *g_Renderer)
{
	// 테스트용 사각형 함수 호출
	g_Renderer->DrawSolidRect(m_nPosition.x, m_nPosition.y, m_nPosition.z, 
							  m_nSize, 
							  m_nColor.r, m_nColor.g, m_nColor.b, m_nColor.a);

}

void GameObject::Update()
{
	// 테스트용 무브함수
	Move(Vec3{1, 0, 0}, 2.0f);
}

void GameObject::SetOOBB()
{
	
}

void GameObject::SetPosition(Vec3 pos)
{
	m_nPosition = pos;
}

void GameObject::SetColor(Vec4 color)
{
	m_nColor = color;
}

void GameObject::SetSize(float size)
{
	m_nSize = size;
}

void GameObject::SetMass(float mass)
{
	m_nMass = mass;
}

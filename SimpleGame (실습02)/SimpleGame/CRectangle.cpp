#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle()
{
	// 초기화
	m_nPosition = { 0.0f, 0.0f, 0.0f };
	m_nColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_nOOBB = { 0.0f,0.0f,0.0f,0.0f };
	m_nMass = 0.0f;
	m_nSize = 0.0f;
}

CRectangle::CRectangle(Vec3 pos, float size, Vec4 color)
{
	m_nPosition = pos;
	m_nColor = color;
	m_nSize = size;
}

CRectangle::~CRectangle()
{
}

void CRectangle::IsInitialized(Vec3 pos, float size, Vec4 color)
{
	m_nPosition = pos;
	m_nColor = color;
	m_nSize = size;
}

void CRectangle::BuildObject(Renderer * g_Renderer)
{
	// 테스트용 사각형 함수 호출
	g_Renderer->DrawSolidRect(m_nPosition.x, m_nPosition.y, m_nPosition.z,
		m_nSize,
		m_nColor.r, m_nColor.g, m_nColor.b, m_nColor.a);

}

void CRectangle::Update()
{
	// 테스트용 무브함수
	GameObject::Move(Vec3{ 1, 0, 0 }, 2.0f);
}

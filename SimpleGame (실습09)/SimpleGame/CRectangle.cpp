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
	m_nDir	= { 0.0f, 0.0f, 0.0f };
	m_nLife = 0.f;
}

CRectangle::CRectangle(Vec3 pos, float size, Vec4 color, OBJECT_TYPE type)
{
	m_nPosition = pos;
	m_nColor = color;
	m_nSize = size;
	m_objectType = type;
}

CRectangle::~CRectangle()
{
}

void CRectangle::IsInitialized(Vec3 pos, float size, Vec4 color, OBJECT_TYPE type)
{
	m_nPosition = pos;
	m_nColor = color;
	m_nSize = size;
	m_objectType = type;
}

void CRectangle::Draw(Renderer * g_Renderer)
{
	// 테스트용 사각형 함수 호출
	g_Renderer->DrawSolidRect(m_nPosition.x, m_nPosition.y, m_nPosition.z,
							  m_nSize,
							  m_nColor.r, m_nColor.g, m_nColor.b, m_nColor.a, 0.3);

}

void CRectangle::Update(float fTimeElapsed)
{
	// 테스트용 무브함수
	Move(m_nSpeed * fTimeElapsed * 30);

	m_arrowTimer += fTimeElapsed;
}

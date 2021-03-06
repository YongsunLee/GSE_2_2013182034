#include "stdafx.h"
#include "Building.h"

CBuilding::CBuilding()
{
	// �ʱ�ȭ
	m_nPosition = { 0.0f, 0.0f, 0.0f };
	m_nColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_nOOBB = { 0.0f,0.0f,0.0f,0.0f };
	m_nMass = 0.0f;
	m_nSize = 0.0f;
	m_nDir = { 0.0f, 0.0f, 0.0f };
	m_nLife = 0.f;

	
}

CBuilding::CBuilding(Vec3 pos, float size, Vec4 color, OBJECT_TYPE type)
{
	m_nPosition = pos;
	m_nColor = color;
	m_nSize = size;
	m_type = type;
}

CBuilding::~CBuilding()
{
}

void CBuilding::Draw(Renderer * g_Renderer)
{
	g_Renderer->DrawSolidRect(m_nPosition.x, m_nPosition.y, m_nPosition.z,
		m_nSize,
		m_nColor.r, m_nColor.g, m_nColor.b, m_nColor.a);
}

void CBuilding::Draw(Renderer * g_Renderer, unsigned int textureID)
{
	g_Renderer->DrawTexturedRect(m_nPosition.x, m_nPosition.y, m_nPosition.z,
		m_nSize,
		m_nColor.r, m_nColor.g, m_nColor.b, m_nColor.a, textureID);
}

void CBuilding::Update(float fTimeElapsed)
{
	
}

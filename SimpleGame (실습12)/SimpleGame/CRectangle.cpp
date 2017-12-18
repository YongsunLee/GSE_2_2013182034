#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle() 
{
	// �ʱ�ȭ
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
	// �Ѿ�, ȭ���̸� �׳� �簢��
	g_Renderer->DrawSolidRect(m_nPosition.x, m_nPosition.y, m_nPosition.z,
							  m_nSize,
							  m_nColor.r, m_nColor.g, m_nColor.b, m_nColor.a, 0.3);

	
}

void CRectangle::Draw(Renderer * g_Renderer, unsigned int textureID)
{
	if (m_objectType == OBJECT_TYPE::OBJECT_CHARACTER) {
		g_Renderer->DrawTexturedRectSeq(m_nPosition.x, m_nPosition.y, m_nPosition.z,
			m_nSize,
			m_nColor.r, m_nColor.g, m_nColor.b, m_nColor.a,
			textureID,
			SeqX,
			SeqY,
			4,
			4,
			0.3);

		// ĳ���� HP��
		if (m_teamType == OBJECT_TYPE::TEAM_1) {
			g_Renderer->DrawSolidRectGauge(m_nPosition.x, m_nPosition.y + m_nSize, m_nPosition.z,
				m_nSize, 5.f,
				1.0f, 0.0f, 0.0f, 1.0f,
				HP,
				0.3f);
		}
		else {
			g_Renderer->DrawSolidRectGauge(m_nPosition.x, m_nPosition.y + m_nSize, m_nPosition.z,
				m_nSize, 5.f,
				0.0f, 1.0f, 0.0f, 1.0f,
				HP,
				0.3f);
		}
	}

	if (m_objectType == OBJECT_TYPE::OBJECT_BULLET) {
		if (timeInSeconed <= 1.0f) {
			g_Renderer->DrawParticle(m_nPosition.x, m_nPosition.y, m_nPosition.z,
				m_nSize,
				1,1,1,max(0, 1 - timeInSeconed),
				m_nDir.x * -5.f, m_nDir.y * -5.f,
				textureID,
				timeInSeconed,
				0.3);
		}
	}
}

void CRectangle::Update(float fTimeElapsed)
{
	// ȭ�� �浹 üũ(Dir) �� ���� �ִϸ��̼�(SeqY)
	if (m_nPosition.x > WINDOWWIDTH / 2) {
		SeqY = 1;
		m_nDir.x = -abs(m_nDir.x);
	}
	else if (m_nPosition.x < -(WINDOWWIDTH / 2)) {
		SeqY = 2;
		m_nDir.x = abs(m_nDir.x);
	}

	if (m_nPosition.y > WINDOWHEIGHT / 2) {
		SeqY = 0;
		m_nDir.y = -abs(m_nDir.y);
	}
	else if (m_nPosition.y < -(WINDOWHEIGHT / 2)) {
		SeqY = 3;
		m_nDir.y = abs(m_nDir.y);
	}

	// �׽�Ʈ�� �����Լ�
	Move(m_nSpeed * fTimeElapsed);

	// ȭ�� Ÿ�̸�
	m_arrowTimer += fTimeElapsed;

	// ü�¹� �ִϸ��̼�
	HP = m_nLife / m_maxLife;

	// �ִϸ��̼�
	SeqXTimer += fTimeElapsed;
	if (SeqXTimer > 0.5f) {
		SeqX += 1;
		SeqXTimer = 0.f;
	} 
	
	if (SeqX >= 4) SeqX = 0;

	timeInSeconed += fTimeElapsed;
}

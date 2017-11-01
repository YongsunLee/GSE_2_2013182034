#include "stdafx.h"
#include "SceneMgr.h"
#include "Renderer.h"
#include "GameObject.h"
#include "CRectangle.h"


CSceneMgr::CSceneMgr()
{
}

CSceneMgr::~CSceneMgr()
{
	delete m_pObject;
}


void CSceneMgr::inIt()
{
	// 한번에 여러 오브젝트 생성
	m_nObject = 1;
	m_pObject = new CRectangle[m_nObject];

	for (int i = 0; i < m_nObject; ++i) {
		m_pObject[i].SetPosition(Vec3{ 0, 0, 0 });
		m_pObject[i].SetDir(Vec3{ 1.f, 0.f, 0.f});
		m_pObject[i].SetColor(Vec4{ 1.f, 1.f, 0.f, 1.f });
		m_pObject[i].SetSize(50.f);
		m_pObject[i].SetSpeed(0.0f);
		m_pObject[i].SetOOBB();
		m_pObject[i].SetType(OBJECT_TYPE::OBJECT_BUILDING);
		m_pObject[i].SetLife(500.f);
	}

}

void CSceneMgr::AddClickObject(float x, float y)
{
	m_nClickObject = 1;
	m_pClickObject = new CRectangle[MAX_OBJECT_COUNT];

	for (int i = 0; i < m_nClickObject; ++i) {
		m_pClickObject[i].SetPosition(Vec3{ x, y, 0 });
		m_pClickObject[i].SetDir(Vec3{ 1.f, 0.f, 0.f });
		m_pClickObject[i].SetColor(Vec4{ 1.f, 1.f, 1.f, 1.f });
		m_pClickObject[i].SetSize(10.f);
		m_pClickObject[i].SetSpeed(0.0f);
		m_pClickObject[i].SetOOBB();
		m_pClickObject[i].SetType(OBJECT_TYPE::OBJECT_BUILDING);
		m_pClickObject[i].SetLife(10.f);
	}
}

void CSceneMgr::Update()
{
	UpdateFPS();

	for (int i = 0; i < m_nObject; ++i)			m_pObject[i].Update(m_fTimeElapsed);
	for (int i = 0; i < m_nClickObject; ++i)	m_pClickObject[i].Update(m_fTimeElapsed);

	for (int i = 0; i < m_nClickObject; ++i) {
		if (m_pObject[0].Collision(&m_pObject[0], &m_pClickObject[i])) {
			if (m_pObject[0].GetType() == OBJECT_BUILDING  && 
				m_pClickObject[i].GetType() == OBJECT_CHARACTER) {

				m_pObject[0].SetLife(m_pObject[0].GetLife() - m_pClickObject[i].GetLife());

				m_pObject[0].SetColor(Vec4{ 0.f, 0.f, 1.f, 0.f });
			}
		}
		else {
			m_pObject[0].SetColor(Vec4{1,1,0,1});
		}
	}
	
	

}

void CSceneMgr::Draw(Renderer * g_Renderer)
{
	for (int i = 0; i < m_nObject; ++i)			m_pObject[i].Draw(g_Renderer);
	for (int i = 0; i < m_nClickObject; ++i)	m_pClickObject[i].Draw(g_Renderer);
}

void CSceneMgr::UpdateFPS()
{
	static float timeElapsed = 0.f;
	static DWORD lastTime = timeGetTime();

	DWORD curTime = timeGetTime();
	float timeDelta = ((curTime - lastTime) * 0.001f);

	m_fTimeElapsed = timeDelta;

	lastTime = curTime;
}


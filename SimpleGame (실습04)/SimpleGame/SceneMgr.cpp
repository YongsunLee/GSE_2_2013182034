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
	m_nObject = 100;
	m_pObject = new CRectangle[m_nObject];

	default_random_engine dre;
	uniform_int_distribution<> ui_xPos((-WINDOWWIDTH / 2.0), (WINDOWWIDTH / 2.0));
	uniform_int_distribution<> ui_yPos((-WINDOWHEIGHT / 2.0), (WINDOWHEIGHT / 2.0));
	uniform_int_distribution<> ui_speed(1.0f, 10.f);

	dre.seed(chrono::system_clock::now().time_since_epoch().count());

	for (int i = 0; i < m_nObject; ++i) {

		float xPos = ui_xPos(dre);
		float yPos = ui_yPos(dre);
		float speed = ui_speed(dre);

		m_pObject[i].SetPosition(Vec3{ xPos, yPos, 0 });
		m_pObject[i].SetColor(Vec4{ 1.f, 1.f, 1.f, 1.f });
		m_pObject[i].SetSize(10.f);
		m_pObject[i].SetSpeed(speed);

	}
}

void CSceneMgr::Update()
{
	for (int i = 0; i < m_nObject; ++i)
		m_pObject[i].Update();
}

void CSceneMgr::Draw(Renderer * g_Renderer)
{
	for (int i = 0 ; i < m_nObject; ++i)
		m_pObject[i].Draw(g_Renderer);
}


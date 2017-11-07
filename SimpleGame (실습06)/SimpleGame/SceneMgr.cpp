#include "stdafx.h"
#include "SceneMgr.h"
#include "Renderer.h"
#include "GameObject.h"
#include "CRectangle.h"
#include "Building.h"


CSceneMgr::CSceneMgr()
{
	m_gRenderer = new Renderer(WINDOWWIDTH, WINDOWHEIGHT);

	if (!m_gRenderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

}

CSceneMgr::~CSceneMgr()
{
	delete m_gRenderer;
}


void CSceneMgr::inIt()
{
	// 건물 가운데의 빌딩
	CBuilding* building = new CBuilding(Vec3{ 0,0,0 },50.f, Vec4{ 1,1,0,0 },OBJECT_TYPE::OBJECT_BUILDING);
	building->SetLife(500.f);

	m_pBuilding.push_back(building);

}

void CSceneMgr::AddClickObject(float x, float y)
{
	// 캐릭터
	if (m_pObject.size() < MAX_OBJECT_COUNT) {
		CRectangle* character = new CRectangle(Vec3{x, y, 0}, 10.f, Vec4{1,1,1,1}, OBJECT_TYPE::OBJECT_CHARACTER);
		character->SetLife(10.f);
		character->SetDir(Vec3{ 1,0,0 });
		character->SetSpeed(10.f);

		m_pObject.push_back(character);
	}
}

void CSceneMgr::Collision()
{
	int collisionCount = 0;

	for (int i = 0; i < m_pBuilding.size(); i++)
	{
		collisionCount = 0;
		if (m_pBuilding[i] != NULL)
		{
			for (int j = 0; j < m_pObject.size(); j++)
			{
				if (m_pObject[j] != NULL)
				{
					m_pBuilding[i]->SetOOBB();
					m_pObject[j]->SetOOBB();
					if (m_pBuilding[i]->Collision(m_pBuilding[i], m_pObject[j]))
					{
						collisionCount++;
					}
				}
			}
			if (collisionCount > 0)
			{
				m_pBuilding[i]->SetColor(Vec4{ 1,0,0,1 });
			}
			else
			{
				m_pBuilding[i]->SetColor(Vec4{ 1,1,0,1 });
			}
		}
	}

}

void CSceneMgr::Update()
{
	UpdateFPS();

	for (auto &p : m_pBuilding)		p->Update(m_fTimeElapsed);
	for (auto &p : m_pObject)		p->Update(m_fTimeElapsed);
	
	Collision();
}

void CSceneMgr::Draw()
{
	for (auto &p : m_pBuilding)		p->Draw(m_gRenderer);
	for (auto &p : m_pObject)		p->Draw(m_gRenderer);
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


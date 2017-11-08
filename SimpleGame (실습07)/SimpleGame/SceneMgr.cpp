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

	m_textureID = m_gRenderer->CreatePngTexture("./Resource/fire.png");
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

void CSceneMgr::DeleteObject(vector<GameObject*> cont, int index)
{
	if (cont[index] != NULL) {
		cont.erase(cont.begin() + index);
	}
}

void CSceneMgr::Collision()
{
	int collisionCount = 0;

	// Building
	for (int i = 0; i < m_pBuilding.size(); i++)
	{
		collisionCount = 0;
		if (m_pBuilding[i] != NULL)
		{
			// Character
			for (int j = 0; j < m_pObject.size(); j++)
			{
				if (m_pObject[j] != NULL)
				{
					m_pBuilding[i]->SetOOBB();
					m_pObject[j]->SetOOBB();
					if (m_pBuilding[i]->Collision(m_pBuilding[i], m_pObject[j]))
					{
						collisionCount++;
						m_pBuilding[i]->SetLife(m_pBuilding[i]->GetLife() - m_pObject[j]->GetLife());
						//DeleteObject(m_pObject, j);
					}
				}
			}

			// Arrow
			for (int j = 0; j < m_pArrow.size(); j++)
			{
				if (m_pArrow[j] != NULL)
				{
					m_pBuilding[i]->SetOOBB();
					m_pArrow[j]->SetOOBB();
					if (m_pBuilding[i]->Collision(m_pBuilding[i], m_pArrow[j]))
					{
						collisionCount++;
						m_pBuilding[i]->SetLife(m_pBuilding[i]->GetLife() - m_pArrow[j]->GetLife());
						//DeleteObject(m_pArrow, j);
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

	// Character
	for (int i = 0; i < m_pObject.size(); i++)
	{
		collisionCount = 0;
		if (m_pObject[i] != NULL)
		{
			// Building
			for (int j = 0; j < m_pBuilding.size(); j++)
			{
				if (m_pBuilding[j] != NULL)
				{
					m_pObject[i]->SetOOBB();
					m_pBuilding[j]->SetOOBB();
					if (m_pObject[i]->Collision(m_pObject[i], m_pBuilding[j]))
					{
						collisionCount++;
						m_pObject[i]->SetLife(m_pObject[i]->GetLife() - m_pBuilding[j]->GetLife());
						//DeleteObject(m_pObject, j);
					}
				}
			}

			// Arrow
			for (int j = 0; j < m_pArrow.size(); j++)
			{
				if (m_pArrow[j] != NULL)
				{
					m_pObject[i]->SetOOBB();
					m_pArrow[j]->SetOOBB();
					if (m_pObject[i]->Collision(m_pObject[i], m_pArrow[j]))
					{
						collisionCount++;
						m_pObject[i]->SetLife(m_pObject[i]->GetLife() - m_pArrow[j]->GetLife());
						//DeleteObject(m_pArrow, j);
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

	float bulletTimer = 0.f;
	bulletTimer += m_fTimeElapsed * 5.f;
	if (bulletTimer >= 0.5f) {
		for (int i = 0; i < m_pBuilding.size(); ++i) {
			CRectangle* bullet = new CRectangle(m_pBuilding[i]->GetPosition(), 4.f, Vec4{ 1,0,0,1 }, OBJECT_TYPE::OBJECT_BULLET);
			bullet->SetDir(Vec3{1,1,1});
			bullet->SetLife(10.f);
			bullet->SetSpeed(20.f);
			m_pBullet.push_back(bullet);
		}
		bulletTimer = 0.f;
	}

	float arrowTimer = 0.f;
	arrowTimer += m_fTimeElapsed * 10;
	if (arrowTimer >= 0.5f) {
		for (int i = 0; i < m_pObject.size(); ++i) {
			CRectangle* arrow = new CRectangle(m_pObject[i]->GetPosition(), 2.f, Vec4{ 0,1,0,1 }, OBJECT_TYPE::OBJECT_ARROW);
			arrow->SetDir(Vec3{ 1,1,0 });
			arrow->SetSpeed(10.f);
			arrow->SetLife(10.f);
			m_pArrow.push_back(arrow);
		}
		arrowTimer = 0.f;
	}

	// 체력 고갈시 사망
	for (int i = 0; i < m_pBuilding.size(); ++i) {
		if (m_pBuilding[i]->GetLife() <= 0.f) m_pBuilding.erase(m_pBuilding.begin() + i);
	}

	/*
	for (int i = 0; i < m_pObject.size(); ++i) {
		if (m_pObject[i]->GetLife() <= 0.f) m_pObject.erase(m_pObject.begin() + i);
	}
	*/

	for (auto &p : m_pBuilding)		p->Update(m_fTimeElapsed);
	for (auto &p : m_pObject)		p->Update(m_fTimeElapsed);
	for (auto &p : m_pArrow)		p->Update(m_fTimeElapsed);
	for (auto &p : m_pBullet)		p->Update(m_fTimeElapsed);


	Collision();
}

void CSceneMgr::Draw()
{
	for (auto &p : m_pBuilding)		p->Draw(m_gRenderer, m_textureID);
	for (auto &p : m_pObject)		p->Draw(m_gRenderer);
	for (auto &p : m_pArrow)		p->Draw(m_gRenderer);
	for (auto &p : m_pBullet)		p->Draw(m_gRenderer);
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


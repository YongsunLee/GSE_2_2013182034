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
	for (int i = 0; i < 3; ++i) {
		// ÆÀ 1 ºôµù
		CBuilding* building = new CBuilding(Vec3{ -130.f + ( i * 130.f), 300.f, 0 }, 100.f, Vec4{ 1,1,0,0 }, OBJECT_TYPE::OBJECT_BUILDING);
		building->SetLife(500.f);
		building->SetTeam(OBJECT_TYPE::TEAM_1);
		m_pTeam1Building.push_back(building);
	}

	for (int i = 0; i < 3; ++i) {
		//ÆÀ 2 ºôµù
		CBuilding* building = new CBuilding(Vec3{ -130.f + (i * 130.f), -300.f, 0 }, 100.f, Vec4{ 1,1,0,0 }, OBJECT_TYPE::OBJECT_BUILDING);
		building->SetLife(500.f);
		building->SetTeam(OBJECT_TYPE::TEAM_2);
		m_pTeam2Building.push_back(building);
	}

	// ÅØ½ºÃÄ ·Îµù
	m_textureID[0] = m_gRenderer->CreatePngTexture("./Resource/Round Shield.png");
	m_textureID[1] = m_gRenderer->CreatePngTexture("./Resource/Kite Shield.png");

}

void CSceneMgr::AddClickObject(float x, float y)
{
	// Ä³¸¯ÅÍ
	if (m_pObject.size() < MAX_OBJECT_COUNT && clickTimer > 2.f) {
		CRectangle* character = new CRectangle(Vec3{x, y, 0}, 10.f, Vec4{1,1,1,1}, OBJECT_TYPE::OBJECT_CHARACTER);
		character->SetLife(10.f);
		character->SetDir(Vec3{ 1,0,0 });
		character->SetSpeed(10.f);

		m_pObject.push_back(character);
		clickTimer = 0.f;
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
	for (int i = 0; i < m_pTeam1Building.size(); i++)
	{
		if (m_pTeam1Building[i] != NULL)
		{
			// Character
			for (int j = 0; j < m_pObject.size(); j++)
			{
				if (m_pObject[j] != NULL)
				{
					m_pTeam1Building[i]->SetOOBB();
					m_pObject[j]->SetOOBB();
					if (m_pTeam1Building[i]->Collision(m_pTeam1Building[i], m_pObject[j]))
					{
						m_pTeam1Building[i]->SetLife(m_pTeam1Building[i]->GetLife() - m_pObject[j]->GetLife());
						m_pObject[j]->SetLife(m_pObject[j]->GetLife() - m_pTeam1Building[i]->GetLife());
					}
				}
			}

			// Arrow
			for (int j = 0; j < m_pArrow.size(); j++)
			{
				if (m_pArrow[j] != NULL)
				{
					m_pTeam1Building[i]->SetOOBB();
					m_pArrow[j]->SetOOBB();
					if (m_pTeam1Building[i]->Collision(m_pTeam1Building[i], m_pArrow[j]))
					{
						collisionCount++;
						m_pTeam1Building[i]->SetLife(m_pTeam1Building[i]->GetLife() - m_pArrow[j]->GetLife());
						m_pArrow[j]->SetLife(m_pArrow[j]->GetLife() - m_pTeam1Building[i]->GetLife());
					}
				}
			}

			// bullet
			/*
			for (int j = 0; j < m_pBullet.size(); ++j) {
				m_pTeam1Building[i]->SetOOBB();
				m_pBullet[j]->SetOOBB();
				if (m_pTeam1Building[i]->Collision(m_pTeam1Building[i], m_pBullet[j]))
				{
					collisionCount++;
					m_pTeam1Building[i]->SetLife(m_pTeam1Building[i]->GetLife() - m_pBullet[j]->GetLife());
					m_pBullet[j]->SetLife(m_pBullet[j]->GetLife() - m_pTeam1Building[i]->GetLife());
				}
			}
			*/

		}
	}

	// Character
	for (int i = 0; i < m_pObject.size(); ++i)
	{
		if (m_pObject[i] != NULL)
		{
			// Arrow
			for (int j = 0; j < m_pArrow.size(); ++j)
			{
				if (m_pArrow[j] != NULL)
				{
					m_pObject[i]->SetOOBB();
					m_pArrow[j]->SetOOBB();
					if (m_pObject[i]->Collision(m_pObject[i], m_pArrow[j]))
					{
						m_pObject[i]->SetLife(m_pObject[i]->GetLife() - m_pArrow[j]->GetLife());
						m_pArrow[j]->SetLife(m_pArrow[j]->GetLife() - m_pObject[i]->GetLife());
					}
				}
			}
		}
	}

	// Enemy
	for (int i = 0; i < m_pEnemyObject.size(); ++i)
	{
		if (m_pEnemyObject[i] != NULL)
		{
			// Arrow
			for (int j = 0; j < m_pArrow.size(); ++j)
			{
				if (m_pArrow[j] != NULL)
				{
					m_pEnemyObject[i]->SetOOBB();
					m_pArrow[j]->SetOOBB();
					if (m_pEnemyObject[i]->Collision(m_pEnemyObject[i], m_pArrow[j]))
					{
						m_pEnemyObject[i]->SetLife(m_pEnemyObject[i]->GetLife() - m_pArrow[j]->GetLife());
						m_pArrow[j]->SetLife(m_pArrow[j]->GetLife() - m_pEnemyObject[i]->GetLife());
					}
				}
			}
		}
	}

	// Ã¼·Â < 0 »ç¸Á
	// ºôµù
	for (int i = 0; i < m_pTeam1Building.size();) {
		if (m_pTeam1Building[i]->GetLife() <= 0.f) m_pTeam1Building.erase(m_pTeam1Building.begin() + i);
		else ++i;
	}

	for (int i = 0; i < m_pTeam2Building.size();) {
		if (m_pTeam2Building[i]->GetLife() <= 0.f) m_pTeam2Building.erase(m_pTeam2Building.begin() + i);
		else ++i;
	}

	// Ä³¸¯ÅÍ
	for (int i = 0; i < m_pObject.size();) {
		if (m_pObject[i]->GetLife() <= 0.f) m_pObject.erase(m_pObject.begin() + i);
		else ++i;
	}
	for (int i = 0; i < m_pEnemyObject.size();) {
		if (m_pEnemyObject[i]->GetLife() <= 0.f) m_pEnemyObject.erase(m_pEnemyObject.begin() + i);
		else ++i;
	}

	// È­»ì
	for (int i = 0; i < m_pArrow.size();) {
		if (m_pArrow[i]->GetLife() <= 0.f) m_pArrow.erase(m_pArrow.begin() + i);
		else ++i;
	}

	// ÃÑ¾Ë
	for (int i = 0; i < m_pBullet.size();) {
		if (m_pBullet[i]->GetLife() <= 0.f) m_pBullet.erase(m_pBullet.begin() + i);
		else ++i;
	}
}

void CSceneMgr::Update()
{
	UpdateFPS();
	
	clickTimer += m_fTimeElapsed;

	for (auto &p : m_pTeam1Building)		p->Update(m_fTimeElapsed);
	for (auto &p : m_pTeam2Building)		p->Update(m_fTimeElapsed);
	for (auto &p : m_pObject)				p->Update(m_fTimeElapsed);
	for (auto &p : m_pEnemyObject)			p->Update(m_fTimeElapsed);
	for (auto &p : m_pArrow)				p->Update(m_fTimeElapsed);
	for (auto &p : m_pBullet)				p->Update(m_fTimeElapsed);

	ShotArrowNBullet();
	RespawnObject();

	Collision();
}

void CSceneMgr::Draw()
{
	for (auto &p : m_pTeam1Building)		p->Draw(m_gRenderer, m_textureID[0]);
	for (auto &p : m_pTeam2Building)		p->Draw(m_gRenderer, m_textureID[1]);
	for (auto &p : m_pObject)				p->Draw(m_gRenderer);
	for (auto &p : m_pEnemyObject)			p->Draw(m_gRenderer);
	for (auto &p : m_pArrow)				p->Draw(m_gRenderer);
	for (auto &p : m_pBullet)				p->Draw(m_gRenderer);
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

void CSceneMgr::ShotArrowNBullet()
{
	bulletTimer += m_fTimeElapsed;
	if (bulletTimer >= 1.f) {
		for (int i = 0; i < m_pTeam1Building.size(); ++i) {
			CRectangle* bullet = new CRectangle(m_pTeam1Building[i]->GetPosition(), 4.f, Vec4{ 1,0,0,1 }, OBJECT_TYPE::OBJECT_BULLET);
			bullet->SetDir(Vec3{ 1,1,1 });
			bullet->SetLife(10.f);
			bullet->SetSpeed(20.f);
			bullet->SetTeam(OBJECT_TYPE::TEAM_1);
			m_pBullet.push_back(bullet);
		}

		for (int i = 0; i < m_pTeam2Building.size(); ++i) {
			CRectangle* bullet = new CRectangle(m_pTeam2Building[i]->GetPosition(), 4.f, Vec4{ 0,0,1,1 }, OBJECT_TYPE::OBJECT_BULLET);
			bullet->SetDir(Vec3{ 1,1,1 });
			bullet->SetLife(10.f);
			bullet->SetSpeed(20.f);
			bullet->SetTeam(OBJECT_TYPE::TEAM_2);
			m_pBullet.push_back(bullet);
		}
		bulletTimer = 0.f;
	}

	arrowTimer += m_fTimeElapsed;
	if (arrowTimer >= 1.f) {
		for (int i = 0; i < m_pEnemyObject.size(); ++i) {
			CRectangle* arrow = new CRectangle(m_pEnemyObject[i]->GetPosition(), 2.f, Vec4{ 0.5f,0.2f,0.7f,1 }, OBJECT_TYPE::OBJECT_ARROW);
			arrow->SetDir(Vec3{ 1,1,0 });
			arrow->SetSpeed(10.f);
			arrow->SetLife(10.f);
			arrow->SetTeam(OBJECT_TYPE::TEAM_1);
			m_pArrow.push_back(arrow);
		}
		for (int i = 0; i < m_pObject.size(); ++i) {
			CRectangle* arrow = new CRectangle(m_pObject[i]->GetPosition(), 2.f, Vec4{ 1,1,0,1 }, OBJECT_TYPE::OBJECT_ARROW);
			arrow->SetDir(Vec3{ 1,1,0 });
			arrow->SetSpeed(10.f);
			arrow->SetLife(10.f);
			arrow->SetTeam(OBJECT_TYPE::TEAM_2);
			m_pArrow.push_back(arrow);
		}
		arrowTimer = 0.f;
	}
}

void CSceneMgr::RespawnObject()
{
	respawnTimer += m_fTimeElapsed;
	if (respawnTimer >= 1.f) {
		float xPos = rand() % 500 - 250;
		float yPos = rand() % 250;

		CRectangle* Enemy = new CRectangle(Vec3{xPos, yPos, 0}, 10, Vec4{1,0,0,1}, OBJECT_TYPE::OBJECT_CHARACTER);
		Enemy->SetLife(10.f);
		Enemy->SetSpeed(300.f);
		Enemy->SetTeam(OBJECT_TYPE::TEAM_1);
		m_pEnemyObject.push_back(Enemy);
		respawnTimer = 0.f;
	}

}

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
		CBuilding* building = new CBuilding(Vec3{ -130.f + ( i * 130.f), 280.f, 0 }, 100.f, Vec4{ 1,1,1,1 }, OBJECT_TYPE::OBJECT_BUILDING);
		building->SetLife(500.f);
		building->SetMaxHP();
		building->SetTeam(OBJECT_TYPE::TEAM_1);
		m_pTeam1Building.push_back(building);
	}

	for (int i = 0; i < 3; ++i) {
		//ÆÀ 2 ºôµù
		CBuilding* building = new CBuilding(Vec3{ -130.f + (i * 130.f), -300.f, 0 }, 100.f, Vec4{ 1,1,1,1 }, OBJECT_TYPE::OBJECT_BUILDING);
		building->SetLife(500.f);
		building->SetMaxHP();
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
		CRectangle* character = new CRectangle(Vec3{x, y, 0}, 30.f, Vec4{0,0,1,1}, OBJECT_TYPE::OBJECT_CHARACTER);
		character->SetLife(100.f);
		character->SetMaxLife();
		character->SetDir(Vec3{ 1,0,0 });
		character->SetSpeed(300.f * m_fTimeElapsed);
		character->SetTeam(OBJECT_TYPE::TEAM_2);
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
	// Àû ºôµù
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
						m_pTeam1Building[i]->SetLife(m_pTeam1Building[i]->GetLife() - m_pArrow[j]->GetLife());
						m_pArrow[j]->SetLife(m_pArrow[j]->GetLife() - m_pTeam1Building[i]->GetLife());
					}
				}
			}

			// bullet
			for (int j = 0; j < m_pBullet.size(); ++j) {
				m_pTeam1Building[i]->SetOOBB();
				m_pBullet[j]->SetOOBB();
				if (m_pTeam1Building[i]->Collision(m_pTeam1Building[i], m_pBullet[j]))
				{
					m_pTeam1Building[i]->SetLife(m_pTeam1Building[i]->GetLife() - m_pBullet[j]->GetLife());
					m_pBullet[j]->SetLife(m_pBullet[j]->GetLife() - m_pTeam1Building[i]->GetLife());
				}
			}
		}

	}

	// ÇÃ·¹ÀÌ¾î ºôµù
	for (int i = 0; i < m_pTeam2Building.size(); i++)
	{
		if (m_pTeam2Building[i] != NULL)
		{
			// Àû
			for (int j = 0; j < m_pEnemyObject.size(); j++)
			{
				if (m_pEnemyObject[j] != NULL)
				{
					m_pTeam2Building[i]->SetOOBB();
					m_pEnemyObject[j]->SetOOBB();
					if (m_pTeam2Building[i]->Collision(m_pTeam2Building[i], m_pEnemyObject[j]))
					{
						m_pTeam2Building[i]->SetLife(m_pTeam2Building[i]->GetLife() - m_pEnemyObject[j]->GetLife());
						m_pEnemyObject[j]->SetLife(m_pEnemyObject[j]->GetLife() - m_pTeam2Building[i]->GetLife());
					}
				}
			}

			// Arrow
			for (int j = 0; j < m_pArrow.size(); j++)
			{
				if (m_pArrow[j] != NULL)
				{
					m_pTeam2Building[i]->SetOOBB();
					m_pArrow[j]->SetOOBB();
					if (m_pTeam2Building[i]->Collision(m_pTeam2Building[i], m_pArrow[j]))
					{
						m_pTeam2Building[i]->SetLife(m_pTeam2Building[i]->GetLife() - m_pArrow[j]->GetLife());
						m_pArrow[j]->SetLife(m_pArrow[j]->GetLife() - m_pTeam2Building[i]->GetLife());
					}
				}
			}

			// bullet
			for (int j = 0; j < m_pBullet.size(); ++j) {
				m_pTeam2Building[i]->SetOOBB();
				m_pBullet[j]->SetOOBB();
				if (m_pTeam2Building[i]->Collision(m_pTeam2Building[i], m_pBullet[j]))
				{
					m_pTeam2Building[i]->SetLife(m_pTeam2Building[i]->GetLife() - m_pBullet[j]->GetLife());
					m_pBullet[j]->SetLife(m_pBullet[j]->GetLife() - m_pTeam2Building[i]->GetLife());
				}
			}
		}
	}

	// ÇÃ·¹ÀÌ¾î
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
			
			// bullet
			for (int j = 0; j < m_pBullet.size(); ++j) {
				m_pObject[i]->SetOOBB();
				m_pBullet[j]->SetOOBB();
				if (m_pObject[i]->Collision(m_pObject[i], m_pBullet[j]))
				{
					m_pObject[i]->SetLife(m_pObject[i]->GetLife() - m_pBullet[j]->GetLife());
					m_pBullet[j]->SetLife(m_pBullet[j]->GetLife() - m_pObject[i]->GetLife());
				}
			}
		}
	}

	// Àû
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

			// bullet
			for (int j = 0; j < m_pBullet.size(); ++j) {
				m_pEnemyObject[i]->SetOOBB();
				m_pBullet[j]->SetOOBB();
				if (m_pEnemyObject[i]->Collision(m_pEnemyObject[i], m_pBullet[j]))
				{
					m_pEnemyObject[i]->SetLife(m_pEnemyObject[i]->GetLife() - m_pBullet[j]->GetLife());
					m_pBullet[j]->SetLife(m_pBullet[j]->GetLife() - m_pEnemyObject[i]->GetLife());
				}
			}
		}
	}

	// Ã¼·Â < 0 »ç¸Á
	// ºôµù
	for(auto iter = m_pTeam1Building.begin(); iter != m_pTeam1Building.end();){
		if ((*iter)->GetLife() <= 0.f) 
			iter = m_pTeam1Building.erase(iter);
		else 
			++iter;
	}

	for (auto iter = m_pTeam2Building.begin(); iter != m_pTeam2Building.end();) {
		if ((*iter)->GetLife() <= 0.f)
			iter = m_pTeam2Building.erase(iter);
		else
			++iter;
	}

	// Ä³¸¯ÅÍ
	for (auto iter = m_pObject.begin(); iter != m_pObject.end();) {
		if ((*iter)->GetLife() <= 0.f)
			iter = m_pObject.erase(iter);
		else
			++iter;
	}
	for (auto iter = m_pEnemyObject.begin(); iter != m_pEnemyObject.end();) {
		if ((*iter)->GetLife() <= 0.f)
			iter = m_pEnemyObject.erase(iter);
		else
			++iter;
	}

	// È­»ì
	for (auto iter = m_pArrow.begin(); iter != m_pArrow.end();) {
		if ((*iter)->GetLife() <= 0.f)
			iter = m_pArrow.erase(iter);
		else if ((*iter)->GetPosition().x < -(WINDOWHEIGHT / 2.0f) || (*iter)->GetPosition().x >(WINDOWWIDTH / 2.0f)
			|| (*iter)->GetPosition().y < -(WINDOWHEIGHT / 2.0f) || (*iter)->GetPosition().y >(WINDOWHEIGHT) / 2.0f) {
			iter = m_pArrow.erase(iter);
		}
		else
			++iter;
	}

	// ÃÑ¾Ë
	for (auto iter = m_pBullet.begin(); iter != m_pBullet.end();) {
		if ((*iter)->GetLife() <= 0.f)
			iter = m_pBullet.erase(iter);
		else if ((*iter)->GetPosition().x < -(WINDOWHEIGHT / 2.0f) || (*iter)->GetPosition().x >(WINDOWWIDTH / 2.0f)
			|| (*iter)->GetPosition().y < -(WINDOWHEIGHT / 2.0f) || (*iter)->GetPosition().y >(WINDOWHEIGHT) / 2.0f) {
			iter = m_pBullet.erase(iter);
		}
		else
			++iter;
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
			bullet->SetDir(Vec3{ 0,-1,0 });
			bullet->SetLife(15.f);
			bullet->SetSpeed(600.f * m_fTimeElapsed);
			bullet->SetTeam(OBJECT_TYPE::TEAM_1);
			m_pBullet.push_back(bullet);
		}

		for (int i = 0; i < m_pTeam2Building.size(); ++i) {
			CRectangle* bullet = new CRectangle(m_pTeam2Building[i]->GetPosition(), 4.f, Vec4{ 0,0,1,1 }, OBJECT_TYPE::OBJECT_BULLET);
			bullet->SetDir(Vec3{ 0,1,0 });
			bullet->SetLife(15.f);
			bullet->SetSpeed(600.f * m_fTimeElapsed);
			bullet->SetTeam(OBJECT_TYPE::TEAM_2);
			m_pBullet.push_back(bullet);
		}
		bulletTimer = 0.f;
	}

	for (int i = 0; i < m_pEnemyObject.size(); ++i) {
		if (m_pEnemyObject[i]->GetArrowTimer() > 1.f) {
			CRectangle* arrow = new CRectangle(m_pEnemyObject[i]->GetPosition(), 
											   4.f, 
											   Vec4{ 0.5f,0.2f,0.7f,1 }, 
											   OBJECT_TYPE::OBJECT_ARROW);
			arrow->SetDir(Vec3{ 1,-1,0 });
			arrow->SetSpeed(100.f* m_fTimeElapsed);
			arrow->SetLife(10.f);
			arrow->SetTeam(m_pEnemyObject[i]->GetTeam());
			m_pArrow.push_back(arrow);
			m_pEnemyObject[i]->SetArrowTimer(0.0f);
		}
	}

	for (int i = 0; i < m_pObject.size(); ++i) {
		if (m_pObject[i]->GetArrowTimer() > 1.f) {
			CRectangle* arrow = new CRectangle(m_pObject[i]->GetPosition(),
											   4.f,
											   Vec4{1.f, 1.0f, 0.0f,1 },
											   OBJECT_TYPE::OBJECT_ARROW);
			arrow->SetDir(Vec3{ 1,1,0 });
			arrow->SetSpeed(100.f * m_fTimeElapsed);
			arrow->SetLife(10.f);
			arrow->SetTeam(m_pObject[i]->GetTeam());
			m_pArrow.push_back(arrow);
			m_pObject[i]->SetArrowTimer(0.0f);
		}
	}

}

void CSceneMgr::RespawnObject()
{
	respawnTimer += m_fTimeElapsed;
	if (respawnTimer >= 5.f) {
		float xPos = rand() % 500 - 250;
		float yPos = rand() % 250;

		CRectangle* Enemy = new CRectangle(Vec3{xPos, yPos, 0}, 30.f, Vec4{1,0,0,1}, OBJECT_TYPE::OBJECT_CHARACTER);
		Enemy->SetDir(Vec3{ 1, 0, 0 });
		Enemy->SetLife(100.f);
		Enemy->SetMaxLife();
		Enemy->SetSpeed(300.f * m_fTimeElapsed);
		Enemy->SetTeam(OBJECT_TYPE::TEAM_1);
		m_pEnemyObject.push_back(Enemy);
		respawnTimer = 0.f;
	}

}

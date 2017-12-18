#include "stdafx.h"
#include "SceneMgr.h"
#include "Renderer.h"
#include "GameObject.h"
#include "CRectangle.h"
#include "Sound.h"
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
		// 팀 1 빌딩
		CBuilding* building = new CBuilding(Vec3{ -130.f + ( i * 130.f), 280.f, 0 }, 100.f, Vec4{ 1,1,1,1 }, OBJECT_TYPE::OBJECT_BUILDING);
		building->SetLife(500.f);
		building->SetMaxHP();
		building->SetTeam(OBJECT_TYPE::TEAM_1);
		m_pTeam1Building.push_back(building);
	}

	for (int i = 0; i < 3; ++i) {
		//팀 2 빌딩
		CBuilding* building = new CBuilding(Vec3{ -130.f + (i * 130.f), -300.f, 0 }, 100.f, Vec4{ 1,1,1,1 }, OBJECT_TYPE::OBJECT_BUILDING);
		building->SetLife(500.f);
		building->SetMaxHP();
		building->SetTeam(OBJECT_TYPE::TEAM_2);
		m_pTeam2Building.push_back(building);
	}

	// 텍스처 로딩
	m_textureID[0] = m_gRenderer->CreatePngTexture("./Resource/Round Shield.png");
	m_textureID[1] = m_gRenderer->CreatePngTexture("./Resource/Kite Shield.png");
	m_textureID[2] = m_gRenderer->CreatePngTexture("./Resource/player.png");

	// 배경 텍스처 로딩
	m_BackGroundTextureID = m_gRenderer->CreatePngTexture("./Resource/Back Ground.png");
	
	// 파티클 텍스쳐 로딩
	m_ParticleTextureID = m_gRenderer->CreatePngTexture("./Resource/ceef_405_light01.png");
	m_ParticleClimateTextureID = m_gRenderer->CreatePngTexture("./Resource/rl_snowflake_1.png");

	// Sound
	m_pSound = new Sound();

	// SoundID (int)
	SoundBG = m_pSound->CreateSound("./Dependencies/SoundSamples/MF-W-90.XM");
	m_pSound->PlaySoundW(SoundBG, true, 0.2f);
}

void CSceneMgr::AddClickObject(float x, float y)
{
	// 캐릭터
	if (m_pObject.size() < MAX_OBJECT_COUNT && clickTimer > 2.f) {
		CRectangle* character = new CRectangle(Vec3{x, y, 0}, 30.f, Vec4{0,0,1,1}, OBJECT_TYPE::OBJECT_CHARACTER);
		character->SetLife(100.f);
		character->SetMaxLife();
		m_dir.x = rand() % 36 - 18;
		m_dir.y = rand() % 36 - 18;
		m_dir.z = 0;
		character->SetDir(m_dir.nomal());
		character->SetSpeed(300.f);
		character->SetTeam(OBJECT_TYPE::TEAM_2);
		m_pObject.push_back(character);
		clickTimer = 0.f;
	}
}

void CSceneMgr::Collision()
{
	// 적 빌딩
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
						m_Shake = true;
						SceneAnimationTimer = 0.f;
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

	// 플레이어 빌딩
	for (int i = 0; i < m_pTeam2Building.size(); i++)
	{
		if (m_pTeam2Building[i] != NULL)
		{
			// 적
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
						m_Shake = true;
						SceneAnimationTimer = 0.f;
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

	// 플레이어
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

	// 적
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

	// 체력 < 0 사망
	// 빌딩
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

	// 캐릭터
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

	// 화살
	for (auto iter = m_pArrow.begin(); iter != m_pArrow.end();) {
		if ((*iter)->GetLife() <= 0.f)
			iter = m_pArrow.erase(iter);
		else if ((*iter)->GetPosition().x < -(WINDOWWIDTH / 2.0f) || (*iter)->GetPosition().x > (WINDOWWIDTH / 2.0f)
			|| (*iter)->GetPosition().y < -(WINDOWHEIGHT / 2.0f) || (*iter)->GetPosition().y > (WINDOWHEIGHT) / 2.0f) {
			iter = m_pArrow.erase(iter);
		}
		else
			++iter;
	}

	// 총알
	for (auto iter = m_pBullet.begin(); iter != m_pBullet.end();) {
		if ((*iter)->GetLife() <= 0.f)
			iter = m_pBullet.erase(iter);
		else if ((*iter)->GetPosition().x < -(WINDOWWIDTH / 2.0f) || (*iter)->GetPosition().x >(WINDOWWIDTH / 2.0f)
			|| (*iter)->GetPosition().y < -(WINDOWHEIGHT / 2.0f) || (*iter)->GetPosition().y >(WINDOWHEIGHT) / 2.0f) {
			iter = m_pBullet.erase(iter);
		}
		else if ((*iter)->GetTimeInSec() >= 1.0f)
			iter = m_pBullet.erase(iter);
		else
			++iter;
	}
}

void CSceneMgr::Update()
{
	UpdateFPS();
	
	clickTimer += m_fTimeElapsed;
	ClimateTimer += m_fTimeElapsed;

	for (auto &p : m_pTeam1Building)		p->Update(m_fTimeElapsed);
	for (auto &p : m_pTeam2Building)		p->Update(m_fTimeElapsed);
	for (auto &p : m_pObject)				p->Update(m_fTimeElapsed);
	for (auto &p : m_pEnemyObject)			p->Update(m_fTimeElapsed);
	for (auto &p : m_pArrow)				p->Update(m_fTimeElapsed);
	for (auto &p : m_pBullet)				p->Update(m_fTimeElapsed);

	ShotArrowNBullet();
	RespawnObject();

	Collision();

	if (m_Shake) {
		m_ShakePos.x = (rand() % 36 - 18) - m_fTimeElapsed;
		m_ShakePos.y = (rand() % 36 - 18) - m_fTimeElapsed;
		m_ShakePos.z = 1;
		m_ShakePos = m_ShakePos.nomal();
		SceneAnimationTimer += m_fTimeElapsed;
		if (SceneAnimationTimer >= 2.f) {
			m_Shake = false;
		}
	}

	float trash = static_cast<int>(ClimateTimer / 4.f);
	trash = ClimateTimer - trash * 4.f;
	if (trash == 0) {
		EnviromentDir = 0.2f;
	}
}

void CSceneMgr::Draw()
{
	// 배경화면
	m_gRenderer->DrawTexturedRect(0.0f, 0.0f, 0.0f, 800.f, 1, 1, 1, 1, m_BackGroundTextureID, 0.6f);

	// Snow Particle
	m_gRenderer->DrawParticleClimate(0, 0, 0, 
									 1, 1, 1, 1, 1, 
									 EnviromentDir, -0.1,
									 m_ParticleClimateTextureID, 
									 ClimateTimer, 0.01f);

	for (auto &p : m_pTeam1Building)		p->Draw(m_gRenderer, m_textureID[0]);
	for (auto &p : m_pTeam2Building)		p->Draw(m_gRenderer, m_textureID[1]);
	for (auto &p : m_pObject)				p->Draw(m_gRenderer, m_textureID[2]);
	for (auto &p : m_pEnemyObject)			p->Draw(m_gRenderer, m_textureID[2]);
	for (auto &p : m_pArrow)				p->Draw(m_gRenderer);
	for (auto &p : m_pBullet)				p->Draw(m_gRenderer, m_ParticleTextureID);

	// 캐릭터가 빌딩에 충돌하면 화면 흔들기
	if (m_Shake) {
		m_gRenderer->SetSceneTransform(
			m_ShakePos.x,
			m_ShakePos.y,
			1, 1);
	}

	// Text Test 글씨 출력
	//m_gRenderer->DrawTextW(0.0f, 0.f, GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 1.0f, 1.0f, "Text Test");
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
			CRectangle* bullet = new CRectangle(m_pTeam1Building[i]->GetPosition(), 10.f, Vec4{ 1,0,0,1 }, OBJECT_TYPE::OBJECT_BULLET);
			m_dir.x = rand() % 36 - 18;
			m_dir.y = rand() % 36 - 18;
			m_dir.z = 0;
			bullet->SetDir(m_dir.nomal());
			bullet->SetLife(15.f);
			bullet->SetSpeed(600.f);
			bullet->SetTeam(OBJECT_TYPE::TEAM_1);
			m_pBullet.push_back(bullet);
		}

		for (int i = 0; i < m_pTeam2Building.size(); ++i) {
			CRectangle* bullet = new CRectangle(m_pTeam2Building[i]->GetPosition(), 10.f, Vec4{ 0,0,1,1 }, OBJECT_TYPE::OBJECT_BULLET);
			m_dir.y = rand() % 36 - 18;
			m_dir.x = rand() % 36 - 18;
			m_dir.z = 0;
			bullet->SetDir(m_dir.nomal());
			bullet->SetLife(15.f);
			bullet->SetSpeed(600.f);
			bullet->SetTeam(OBJECT_TYPE::TEAM_2);
			m_pBullet.push_back(bullet);
		}
		bulletTimer = 0.0f;
	}

	for (int i = 0; i < m_pEnemyObject.size(); ++i) {
		if (m_pEnemyObject[i]->GetArrowTimer() > 1.f) {
			CRectangle* arrow = new CRectangle(m_pEnemyObject[i]->GetPosition(), 
											   4.f, 
											   Vec4{ 0.5f,0.2f,0.7f,1 }, 
											   OBJECT_TYPE::OBJECT_ARROW);
			m_dir.x = rand() % 36 - 18;
			m_dir.y = rand() % 36 - 18;
			m_dir.z = 0;
			arrow->SetDir(m_dir.nomal());
			arrow->SetSpeed(100.f);
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
			m_dir.x = rand() % 36 - 18;
			m_dir.y = rand() % 36 - 18;
			m_dir.z = 0;
			arrow->SetDir(m_dir.nomal());
			arrow->SetSpeed(100.f);
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
	if (respawnTimer >= 2.f) {
		float xPos = rand() % 500 - 250;
		float yPos = rand() % 250;

		CRectangle* Enemy = new CRectangle(Vec3{xPos, yPos, 0}, 30.f, Vec4{1,0,0,1}, OBJECT_TYPE::OBJECT_CHARACTER);
		m_dir.x = rand() % 36 - 18;
		m_dir.y = rand() % 36 - 18;
		m_dir.z = 0;
		Enemy->SetDir(m_dir.nomal());
		Enemy->SetLife(100.f);
		Enemy->SetMaxLife();
		Enemy->SetSpeed(300.f);
		Enemy->SetTeam(OBJECT_TYPE::TEAM_1);
		m_pEnemyObject.push_back(Enemy);
		respawnTimer = 0.f;
	}

}

#pragma once

class Renderer;
class GameObject;
class Sound;

class CSceneMgr {
public:
	CSceneMgr();
	~CSceneMgr();

	void inIt();
	void AddClickObject(float x, float y);
	
	void DeleteObject(vector<GameObject*> cont, int index);

	void Collision();
	void Update();
	void Draw();

	void UpdateFPS();
	void ShotArrowNBullet();
	void RespawnObject();


private:
	Renderer				*m_gRenderer;

	vector<GameObject*>		m_pObject;
	vector<GameObject*>		m_pEnemyObject;
	vector<GameObject*>		m_pTeam1Building;
	vector<GameObject*>		m_pTeam2Building;
	vector<GameObject*>		m_pArrow;
	vector<GameObject*>		m_pBullet;

	Sound					*m_pSound;
	int						SoundBG;		// SoundID

	float					m_fTimeElapsed;
	unsigned int			m_textureID[3];
	unsigned int			m_BackGroundTextureID;
	unsigned int			m_ParticleTextureID;

	float					bulletTimer			= 0.f;
	float					arrowTimer			= 0.f;
	float					respawnTimer		= 0.f;
	float					clickTimer			= 0.f;
	
	Vec3					m_ShakePos;		
	float					SceneAnimationTimer	= 0.f;
	bool					m_Shake;

	Vec3					m_dir;
};
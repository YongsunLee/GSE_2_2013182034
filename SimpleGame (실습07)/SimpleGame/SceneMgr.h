#pragma once

class Renderer;
class GameObject;

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

private:
	Renderer*			m_gRenderer;

	vector<GameObject*>	m_pObject	;
	vector<GameObject*>	m_pBuilding ;
	vector<GameObject*>	m_pArrow	;
	vector<GameObject*> m_pBullet	;

	float				m_fTimeElapsed;
	unsigned int		m_textureID;
};
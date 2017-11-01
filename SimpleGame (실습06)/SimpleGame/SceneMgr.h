#pragma once

class Renderer;
class GameObject;

class CSceneMgr {
public:
	CSceneMgr();
	~CSceneMgr();

	void inIt();
	void AddClickObject(float x, float y);
	
	void Update();
	void Draw(Renderer *g_Renderer);

	void UpdateFPS();

private:
	GameObject*		m_pObject;
	int				m_nObject;

	GameObject*		m_pClickObject;
	int				m_nClickObject;

	float			m_fTimeElapsed;

};
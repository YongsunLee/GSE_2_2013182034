#pragma once

class Renderer;
class GameObject;

class CSceneMgr {
public:
	CSceneMgr();
	~CSceneMgr();

	void inIt();
	void Update();
	void Draw(Renderer *g_Renderer);

	void UpdateFPS();

private:
	GameObject*		m_pObject;
	int				m_nObject;

	float			m_fTimeElapsed;

};
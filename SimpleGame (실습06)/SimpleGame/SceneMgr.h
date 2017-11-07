#pragma once


class Renderer;
class GameObject;

class CSceneMgr {
public:
	CSceneMgr();
	~CSceneMgr();

	void inIt();
	void AddClickObject(float x, float y);
	
	void Collision();
	void Update();
	void Draw();

	void UpdateFPS();

private:
	Renderer*			m_gRenderer;

	vector<GameObject*>	m_pObject	;
	vector<GameObject*>	m_pBuilding ;
	vector<GameObject*>	m_pArrow	;

	float				m_fTimeElapsed;

};
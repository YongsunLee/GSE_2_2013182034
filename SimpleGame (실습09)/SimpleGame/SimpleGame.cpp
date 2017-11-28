/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "GameObject.h"
#include "CRectangle.h"
#include "SceneMgr.h"

bool gl_mLButton = false;
bool gl_mRButton = false;
CSceneMgr* g_SceneMgr;

enum MouseInputSide {
	LEFT = 0,
	RIGHT = 2
};

enum MouseInputType{
	BUTTONDOWN = 0,
	BUTTONUP = 1
};

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	glClearDepth(1.f);

	// GameObject Test
	g_SceneMgr->Draw();

	glutSwapBuffers();
}

// ��� ����
void Idle(void)
{
	g_SceneMgr->Update();
	RenderScene();
}

// MouseInputSide (0�̸� ���� 2�� ������)
// MouseInputType (0�̸� �ٿ� 1�̸� ��)
// x, y�� ���콺 ��ǥ
void MouseInput(int button, int state, int x, int y)
{
	// ���콺�� ��, �ٿ��� �ϳ��� UI ��� �����ؾ� �Ѵ�.
	// �ٿ� �޼����� ó���ϰ� �� �޼����� Ǯ���ִ� ��Ȳ�� �ʿ��ϴ�.

	// LButtonDown True
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		gl_mLButton = true;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (gl_mLButton)
		{
			float windowX = (float)(x - (float)WINDOWWIDTH / 2.0);
			float windowY = -(y - (float)WINDOWHEIGHT / 2.0);

			g_SceneMgr->AddClickObject(windowX, windowY);
		}
		gl_mLButton = false;
	}


	RenderScene();
}

// x, y�� Ű�� ������ ���� ���콺�� ��ǥ
// Ű���� ����
void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

// x, y�� Ű�� ������ ���� ���콺�� ��ǥ
// ����Ű, ����Ʈ, ��Ʈ��
void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	g_SceneMgr = new CSceneMgr();

	g_SceneMgr->inIt();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_SceneMgr;
	
    return 0;
}


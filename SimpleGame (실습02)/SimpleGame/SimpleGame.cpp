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

Renderer *g_Renderer = NULL;
GameObject gameObject(Vec3{ 10, 10, 0 }, 10.0f, Vec4{ 1,0,0,0 });

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

	// Renderer Test
	g_Renderer->DrawSolidRect(0, 0, 0, 10, 1, 0, 1, 1);

	// GameObject Test
	//gameObject.IsInitialized(Vec3{ 10, 10, 0 }, 10.0f, Vec4{1,0,0,0});
	gameObject.BuildObject(g_Renderer);
	

	glutSwapBuffers();
}

// ��� ����
void Idle(void)
{
	gameObject.Update();
	RenderScene();
}

// MouseInputSide (0�̸� ���� 2�� ������)
// MouseInputType (0�̸� �ٿ� 1�̸� ��)
// x, y�� ���콺 ��ǥ
void MouseInput(int button, int state, int x, int y)
{
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
	glutInitWindowSize(500, 500);
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

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}


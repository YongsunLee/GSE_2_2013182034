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

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	glutSwapBuffers();
}

// 계속 실행
void Idle(void)
{
	//std::cout << "In" << std::endl;
	RenderScene();
	//std::cout << "Out" << std::endl;
}

// x, y는 키가 눌렸을 때의 마우스의 좌표
// 키보드 전반
void KeyInput(unsigned char key, int x, int y)
{
	std::cout << "key :" << key << std::endl;
	RenderScene();
}

// x, y는 키가 눌렸을 때의 마우스의 좌표
// 방향키, 쉬프트, 컨트롤
void SpecialKeyInput(int key, int x, int y)
{
	std::cout << "Special key :" << key << std::endl;
	RenderScene();
}

// InputSide (0이면 왼쪽 2면 오른쪽)
// InputType (0이면 다운 1이면 업)
// x, y는 마우스 좌표
void MouseInput(int InputSide, int InputType, int x, int y)
{
	std::cout << " InputSide : " << InputSide << " InputType : " << InputType << " x : " << x << " y : " << y << std::endl;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);//optional
	glutInitWindowSize(500, 500); //optional
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

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMouseFunc(MouseInput);


	glutMainLoop();

    return 0;
}


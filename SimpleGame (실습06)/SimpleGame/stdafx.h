#pragma once

#pragma comment(lib,"winmm.lib")

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <random>
#include <chrono>
#include <vector>
using namespace std;

#include <Windows.h>

#define WINDOWWIDTH  500
#define WINDOWHEIGHT 500
#define MAX_OBJECT_COUNT 10

// vector (À§Ä¡)
struct Vec3 {
	float x;
	float y;
	float z;
};

// vector (Color)
struct Vec4 {
	float r;
	float g;
	float b;
	float a;
};

struct OOBB {
	float left;
	float bottom;
	float right;
	float top;
};

enum OBJECT_TYPE {
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW
};

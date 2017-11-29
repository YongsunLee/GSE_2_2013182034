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

#include "LoadPng.h"

#include <Windows.h>

#define WINDOWWIDTH  500
#define WINDOWHEIGHT 700
#define MAX_OBJECT_COUNT 10

// vector (À§Ä¡)
struct Vec3 {
	float x;
	float y;
	float z;

	Vec3 nomal(){
		float max = (pow(x,2) + pow(y,2) + pow(z,2));
		return Vec3{ x / max, y / max, z / max };
	}
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
	OBJECT_ARROW,
	TEAM_1,
	TEAM_2
};

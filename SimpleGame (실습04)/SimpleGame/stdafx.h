#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <random>
#include <chrono>
using namespace std;

#define WINDOWWIDTH  500
#define WINDOWHEIGHT 500



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
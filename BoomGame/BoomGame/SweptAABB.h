#pragma once
#pragma once
#include <algorithm>
#include <Windows.h>
#include "Box.h"

//
float sweptAABB(CBox box1, CBox box2, float &normalx, float &nomaly);

//
CBox getSweptBroadphaseBox(CBox box);

//
bool AABBCheck(CBox box1, CBox box2);

//
bool AABB(CBox box1, CBox box2, float &moveX, float &moveY, float &offsetX, float &offsetY);
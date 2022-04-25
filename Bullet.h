#pragma once
#include "WorldTransform.h"
#include"Vector3D.h"

class Bullet {
  public:
	WorldTransform pos;
	bool isActive;
	Vector3D front;
	float spd;
  public:
	Bullet();
	void Active(const Vector3D& frontVec, const WorldTransform& Pos);
	void Update();
};

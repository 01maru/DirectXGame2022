#pragma once
#include "WorldTransform.h"
#include "Input.h"
#include "Vector3D.h"
#include <DirectXMath.h>

class Player {
  public:
	enum PlayerId {
		Root,
		Front,
		Top,
		Left,
		Right,
		Bottom,
	};
	WorldTransform pos[6];
	float rotaA = 0.0f;
	Vector3D frontVec;				//	前方ベクトル

  private:
	void SetRotaRange(float& pos, float limit);
  public:
	Player();
	void Update(const Input& input);
};

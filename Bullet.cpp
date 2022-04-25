#include "Bullet.h"

Bullet::Bullet() : isActive(false), spd(5.0f) {}

void Bullet::Active(const Vector3D& frontVec, const WorldTransform& Pos) {
	isActive = true;
	front = frontVec;
	pos = Pos;
	front *= spd;
}

void Bullet::Update() {
	if (isActive) {
		Plus(pos.translation_, front);

		pos.UpdateMatrix();
	}
}


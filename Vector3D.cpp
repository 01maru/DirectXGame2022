#include "Vector3D.h"

Vector3D::Vector3D(){
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
}

Vector3D::Vector3D(DirectX::XMFLOAT3& pos) 
: pos(pos) {}

Vector3D::Vector3D(float x, float y, float z) {
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Vector3D::Set(DirectX::XMFLOAT3& pos) { this->pos = pos; }

float Vector3D::Lenght() const { return sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z); }

Vector3D& Vector3D::Normalize() {
	float len = Lenght();
	if (len != 0) {
		return *this /= len;
	}
	return *this;
}

float Vector3D::Dot(const Vector3D& v) const { return 0.0f; }

float Vector3D::Cross(const Vector3D& v) const { return 0.0f; }

Vector3D Vector3D::InverseVec() { return Vector3D(-pos.x, -pos.y, -pos.z); }

Vector3D& Vector3D::operator+=(const Vector3D& v) {
	pos.x += v.pos.x;
	pos.y += v.pos.y;
	pos.z += v.pos.z;
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& v) {
	pos.x -= v.pos.x;
	pos.y -= v.pos.y;
	pos.z -= v.pos.z;
	return *this;
}

Vector3D& Vector3D::operator*=(float s) {
	pos.x *= s;
	pos.y *= s;
	pos.z *= s;
	return *this;
}

Vector3D& Vector3D::operator/=(float s) {
	pos.x /= s;
	pos.y /= s;
	pos.z /= s;
	return *this;
}

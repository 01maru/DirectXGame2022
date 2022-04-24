#include "Vector3D.h"

Vector3D::Vector3D() {
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
}

Vector3D::Vector3D(DirectX::XMFLOAT3& pos) 
: pos(pos) {}

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

Vector3D Vector3D::operator+() const { return Vector3D(); }

Vector3D Vector3D::operator-() const { return Vector3D(); }

Vector3D& Vector3D::operator+=(const Vector3D& v) {
	// TODO: return ステートメントをここに挿入します
}

Vector3D& Vector3D::operator-=(const Vector3D& v) {
	// TODO: return ステートメントをここに挿入します
}

Vector3D& Vector3D::operator*=(float s) {
	// TODO: return ステートメントをここに挿入します
}

Vector3D& Vector3D::operator/=(float s) {
	// TODO: return ステートメントをここに挿入します
}

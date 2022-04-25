#pragma once
#include <DirectXMath.h>

class Vector3D {
  public:
	DirectX::XMFLOAT3 pos;

  public:
	Vector3D();
	Vector3D(DirectX::XMFLOAT3& pos);
	Vector3D(float x, float y, float z);
	void Set(DirectX::XMFLOAT3& pos);

	float Lenght() const;
	Vector3D& Normalize();
	float Dot(const Vector3D& v) const;
	float Cross(const Vector3D& v) const;
	Vector3D InverseVec();

	Vector3D& operator+=(const Vector3D& v);
	Vector3D& operator-=(const Vector3D& v);
	Vector3D& operator*=(float s);
	Vector3D& operator/=(float s);
};

void Plus(DirectX::XMFLOAT3& pos, Vector3D& v);
void Plus(DirectX::XMFLOAT3& pos, DirectX::XMFLOAT3& v);
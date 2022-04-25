#include "Player.h"

using namespace DirectX;

void Player::SetRotaRange(float& pos, float limit) {
	if (pos >= limit) {
		pos -= limit;
	}
	if (pos <= -limit) {
		pos += limit;
	}
}

Player::Player() {
	pos[PlayerId::Root].Initialize();

	pos[PlayerId::Front].translation_ = {0, 0, 2.0f};
	pos[PlayerId::Front].parent_ = &pos[PlayerId::Root];
	pos[PlayerId::Front].Initialize();

	pos[PlayerId::Bottom].translation_ = {0, -2.0f, 0};
	pos[PlayerId::Bottom].parent_ = &pos[PlayerId::Root];
	pos[PlayerId::Bottom].Initialize();

	pos[PlayerId::Left].translation_ = {-2.0f, 0, 0};
	pos[PlayerId::Left].parent_ = &pos[PlayerId::Root];
	pos[PlayerId::Left].Initialize();

	pos[PlayerId::Right].translation_ = {2.0f, 0, 0};
	pos[PlayerId::Right].parent_ = &pos[PlayerId::Root];
	pos[PlayerId::Right].Initialize();

	pos[PlayerId::Top].translation_ = {0, 2.0f, 0};
	pos[PlayerId::Top].parent_ = &pos[PlayerId::Root];
	pos[PlayerId::Top].Initialize();
}

void Player::Update(const Input& input) {
	//	回転
	XMFLOAT3 rota{0, 0, 0};

	const float kRotaSpeed = XM_PI / 64.0f;

	if (input.PushKey(DIK_LEFT)) {
		rota = {0, -kRotaSpeed, 0};

		//	カメラ更新
	} else if (input.PushKey(DIK_RIGHT)) {
		rota = {0, kRotaSpeed, 0};

		//	カメラ更新
	}

	//	範囲設定
	SetRotaRange(pos[PlayerId::Root].rotation_.x, XM_2PI);
	SetRotaRange(pos[PlayerId::Root].rotation_.y, XM_2PI);
	SetRotaRange(pos[PlayerId::Root].rotation_.z, XM_2PI);

	rotaA += rota.y;

	frontVec.pos.x = sin(rotaA);
	frontVec.pos.z = cos(rotaA);

	//	移動
	XMFLOAT3 move{0, 0, 0};
	const float kCharacterSpeed = 0.2f;

	if (input.PushKey(DIK_UP)) {
		move.x = kCharacterSpeed * sin(rotaA);
		move.z = kCharacterSpeed * cos(rotaA);
		
		//	カメラ更新
	} else if (input.PushKey(DIK_DOWN)) {
		move.x = -kCharacterSpeed * sin(rotaA);
		move.z = -kCharacterSpeed * cos(rotaA);

		//	カメラ更新
	}

	Plus(pos[PlayerId::Root].translation_, move);

	Plus(pos[PlayerId::Root].rotation_, rota);

	for (size_t i = 0; i < _countof(pos); i++) {
		pos[i].UpdateMatrix();
	}
}

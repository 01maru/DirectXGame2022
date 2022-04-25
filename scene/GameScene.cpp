#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	textureHandle_ = TextureManager::Load("mario.jpg");
	//	3Dモデル生成
	model_ = Model::Create();

	player[PlayerId::Root].Initialize();

	player[PlayerId::Front].translation_ = {0, 0, 2.0f};
	player[PlayerId::Front].parent_ = &player[PlayerId::Root];
	player[PlayerId::Front].Initialize();

	player[PlayerId::Bottom].translation_ = {0, -2.0f, 0};
	player[PlayerId::Bottom].parent_ = &player[PlayerId::Root];
	player[PlayerId::Bottom].Initialize();

	player[PlayerId::Left].translation_ = {-2.0f, 0, 0};
	player[PlayerId::Left].parent_ = &player[PlayerId::Root];
	player[PlayerId::Left].Initialize();

	player[PlayerId::Right].translation_ = {2.0f, 0, 0};
	player[PlayerId::Right].parent_ = &player[PlayerId::Root];
	player[PlayerId::Right].Initialize();

	player[PlayerId::Top].translation_ = {0, 2.0f, 0};
	player[PlayerId::Top].parent_ = &player[PlayerId::Root];
	player[PlayerId::Top].Initialize();

	viewProjection_.Initialize();
}

void GameScene::Update() {
	XMFLOAT3 rota{0, 0, 0};

	const float kRotaSpeed = XM_PI / 36.0f;

	if (input_->PushKey(DIK_LEFT)) {
		rota = {0, -kRotaSpeed, 0};
	} else if (input_->PushKey(DIK_RIGHT)) {
		rota = {0, kRotaSpeed, 0};
	}

	pFrontVec += rota;
	
	XMFLOAT3 move{0, 0, 0};
	//	速さ
	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_UP)) {
		move.x = kCharacterSpeed * sin(pFrontVec.pos.y);
		move.z = kCharacterSpeed * cos(pFrontVec.pos.y);
	} else if (input_->PushKey(DIK_DOWN)) {
		move.x = -kCharacterSpeed * sin(pFrontVec.pos.y);
		move.z = -kCharacterSpeed * cos(pFrontVec.pos.y);
	}

	player[PlayerId::Root].translation_.x += move.x;
	player[PlayerId::Root].translation_.y += move.y;
	player[PlayerId::Root].translation_.z += move.z;


	player[PlayerId::Root].rotation_.x += rota.x;
	player[PlayerId::Root].rotation_.y += rota.y;
	player[PlayerId::Root].rotation_.z += rota.z;

	if (
	  player[PlayerId::Root].rotation_.x >= XM_2PI ||
	  player[PlayerId::Root].rotation_.x <= -XM_2PI) {
		player[PlayerId::Root].rotation_.x = 0.0f;
	}
	if (
	  player[PlayerId::Root].rotation_.y >= XM_2PI ||
	  player[PlayerId::Root].rotation_.y <= -XM_2PI) {
		player[PlayerId::Root].rotation_.y = 0.0f;
	}
	if (
	  player[PlayerId::Root].rotation_.z >= XM_2PI ||
	  player[PlayerId::Root].rotation_.z <= -XM_2PI) {
		player[PlayerId::Root].rotation_.z = 0.0f;
	}



	for (size_t i = 0; i < _countof(player); i++) {
		player[i].UpdateMatrix();
	}
	

	//	debugText
	//	文字列
	debugText_->SetPos(50, 50);
	debugText_->Printf(
	  "rota:(%f,%f,%f)", player[PlayerId::Root].rotation_.x, player[PlayerId::Root].rotation_.y,
	  player[PlayerId::Root].rotation_.z);
	debugText_->SetPos(50, 70);
	debugText_->Printf(
	  "eye:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y,
	  viewProjection_.target.z);
	debugText_->SetPos(50, 90);
	debugText_->Printf(
	  "up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y,
	  viewProjection_.up.z);
	debugText_->SetPos(50, 110);
	debugText_->Printf(
	  "fovAngleY(Degree):%f", XMConvertToDegrees(viewProjection_.fovAngleY));
	debugText_->SetPos(50, 130);
	debugText_->Printf(
	  "nearZ:%f", viewProjection_.nearZ);
	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "nearZ:%f", viewProjection_.nearZ);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	//model_->Draw(worldTransform_[PartId::Root], viewProjection_, textureHandle_);
	//model_->Draw(worldTransform_[PartId::Spine], viewProjection_, textureHandle_);
	//model_->Draw(worldTransform_[PartId::Chest], viewProjection_, textureHandle_);
	//model_->Draw(worldTransform_[PartId::Head], viewProjection_, textureHandle_);
	//model_->Draw(worldTransform_[PartId::ArmL], viewProjection_, textureHandle_);
	//model_->Draw(worldTransform_[PartId::ArmR], viewProjection_, textureHandle_);
	//model_->Draw(worldTransform_[PartId::Hip], viewProjection_, textureHandle_);
	//model_->Draw(worldTransform_[PartId::LegL], viewProjection_, textureHandle_);
	//model_->Draw(worldTransform_[PartId::LegR], viewProjection_, textureHandle_);

	for (size_t i = 0; i < _countof(player); i++) {
		if (i != Root)
		model_->Draw(player[i], viewProjection_, textureHandle_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

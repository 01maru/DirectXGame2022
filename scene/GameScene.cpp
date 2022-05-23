#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <random>
#include "Easing.h"

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


	for (size_t i = 0; i < _countof(floor); i++) {
		for (size_t j = 0; j < _countof(floor[0]); j++) {
			floor[i][j].translation_ = {2.0f * i, -5.0f, 2.0f * j};
			floor[i][j].Initialize();
		}
	}

	cAngleF = EaseIn(XM_PI / 3.0f, XM_PI / 2.0f, lerp, 1);
	cDisPlayer = EaseIn(20.0f, 100.0f, lerp, 1);
	viewProjection_.eye.x = -cDisPlayer * sin(cDisPlayer * cos(cAngleF));
	viewProjection_.eye.z = -cDisPlayer * cos(cDisPlayer * cos(cAngleF));

	viewProjection_.eye.y = cDisPlayer * sin(cAngleF);
	viewProjection_.Initialize();
}

void GameScene::Update() {
	player.Update(*input_);

	const float kRotaSpeed = XM_PI / 64.0f;

	if (input_->PushKey(DIK_LEFT)) {
		if (cMoveT = 1.0f) {
			cMoveT = 0.0f;
		}
		cameraStart = viewProjection_.eye;
	} else if (input_->PushKey(DIK_RIGHT)) {
		if (cMoveT = 1.0f) {
			cMoveT = 0.0f;
		}
		cameraStart = viewProjection_.eye;
	}

	if (input_->PushKey(DIK_Z)) {
		lerp += 0.01f;
	} else if (input_->PushKey(DIK_X)) {
		lerp -= 0.01f;
	}
	
	if (lerp > 1.0f) {
		lerp = 1.0f;
	} else if (lerp < 0.0f) {
		lerp = 0.0f;
	}

	cAngleF = EaseIn(XM_PI / 3.0f, 0.0f, lerp, 3);
	cDisPlayer = EaseIn(20.0f, 100.0f, lerp, 3);

	if (input_->PushKey(DIK_UP)) {
		if (cMoveT = 1.0f) {
			cMoveT = 0.0f;
		}
		cameraStart = viewProjection_.eye;
	} else if (input_->PushKey(DIK_DOWN)) {
		if (cMoveT = 1.0f) {
			cMoveT = 0.0f;
		}
		cameraStart = viewProjection_.eye;
	}

	if (input_->TriggerKey(DIK_SPACE)) {
		for (size_t i = 0; i < _countof(player.bullet); i++) {
			player.bullet[i].Active(player.frontVec, player.pos[PlayerId::Root]);
		}
	}
	
	for (size_t i = 0; i < _countof(player.bullet); i++) {
		player.bullet[i].Update();
	}

	//	camera
	if (cMoveT < 1.0f) {
		cMoveT += 0.05f;
	}
	
	viewProjection_.target = player.pos[PlayerId::Root].translation_;
	viewProjection_.eye.x = viewProjection_.target.x - cDisPlayer * sin(player.rotaA);
	viewProjection_.eye.z = viewProjection_.target.z - cDisPlayer * cos(player.rotaA);
	viewProjection_.UpdateMatrix();

	//	debugText
	//	文字列
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
	debugText_->SetPos(50, 170);
	debugText_->Printf("CameraDistance:%f", cDisPlayer);
	debugText_->SetPos(50, 190);
	debugText_->Printf("CameraAngle:%f", cAngleF);
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

	for (size_t i = 0; i < _countof(floor); i++){
		for (size_t j = 0; j < _countof(floor[0]); j++) {
			model_->Draw(floor[i][j], viewProjection_, textureHandle_);
		}
	}
	for (size_t i = 0; i < _countof(player.pos); i++) {
		if (i != Root)
		model_->Draw(player.pos[i], viewProjection_, textureHandle_);
	}

	for (size_t i = 0; i < _countof(player.bullet); i++) {
		if (player.bullet[i].isActive) {
			model_->Draw(player.bullet[i].pos, viewProjection_, textureHandle_);
		}
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

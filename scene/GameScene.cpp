﻿#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

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

	for (size_t i = 0; i < _countof(worldTransform_); i++) {
		for (size_t j = 0; j < _countof(worldTransform_[0]); j++) {
			for (size_t z = 0; z < _countof(worldTransform_[0][0]); z++) {
				worldTransform_[i][j][z].scale_ = {5.0f, 5.0f, 5.0f};

				worldTransform_[i][j][z].rotation_ = {0.0f, 0.0f, 0.0f};
				worldTransform_[i][j][z].translation_ = {
				  j * 20.0f - 70.0f, 70.0f - i * 20.0f, 200.0f + z * 20};

				worldTransform_[i][j][z].Initialize();
			}
		}
	}

	viewProjection_.Initialize();
}

void GameScene::Update() {
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
	
	for (size_t i = 0; i < _countof(worldTransform_); i++) {
		for (size_t j = 0; j < _countof(worldTransform_[0]); j++) {
			for (size_t z = 0; z < _countof(worldTransform_[0][0]); z++) {
				model_->Draw(worldTransform_[i][j][z], viewProjection_, textureHandle_);
			}
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

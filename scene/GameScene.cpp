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

	//	乱数
	std::random_device seed_gen;			//	乱数シード生成器
	std::mt19937_64 engine(seed_gen());		//	メルセンヌ・ついスタ(疑似乱数列生成器)
	//	乱数範囲
	std::uniform_real_distribution<float> rotDist(0.0f, XM_2PI);	//	回転角用
	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);	//	座標用

	worldTransform_[0].translation_ = {0, 10.0f, 0};
	worldTransform_[1].translation_ = {-10.0f, -5.0f, 0};
	worldTransform_[2].translation_ = {10.0f, -5.0f, 0};

	for (size_t i = 0; i < _countof(worldTransform_); i++) {
		worldTransform_[i].scale_ = {3.0f, 3.0f, 3.0f};
		worldTransform_[i].rotation_ = {0, 0, 0};
		worldTransform_[i].Initialize();
	}
	
	viewProjection_.target = {0, 0, 0};								//	注視点
	viewProjection_.Initialize();
}

void GameScene::Update() {
	
	if (input_->TriggerKey(DIK_SPACE)) {
		worldTargetNum++;
		if (worldTargetNum >= _countof(worldTransform_)) {
			worldTargetNum = 0;
		}
		viewProjection_.target = worldTransform_[worldTargetNum].translation_;
	}

	viewProjection_.UpdateMatrix();

	//	debugText
	//	文字列
	debugText_->SetPos(50, 50);
	debugText_->Printf(
	  "eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	debugText_->SetPos(50, 70);
	debugText_->Printf(
	  "target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y,
	  viewProjection_.target.z);
	debugText_->SetPos(50, 90);
	debugText_->Printf(
	  "up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);
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
		model_->Draw(worldTransform_[i], viewProjection_, textureHandle_);
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

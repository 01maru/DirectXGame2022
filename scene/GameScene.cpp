#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete sprite_;
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	soundDataHandle_ = audio_->LoadWave("se_sad03.wav");
	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

	textureHandle_ = TextureManager::Load("mario.jpg");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	//	3Dモデル生成
	model_ = Model::Create();

	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	worldTransform_.rotation_ = {XM_PI / 4.0f, XM_PI / 4.0f, 0.0f};
	worldTransform_.translation_ = {10.0f, 10.0f, 10.0f};

	worldTransform_.Initialize();
	viewProjection_.Initialize();
}

void GameScene::Update() { 
	XMFLOAT2 position = sprite_->GetPosition();
	//	座標移動
	position.x += 2.0f;
	position.y += 1.0f;
	//	移動した座標をスプライトに反映
	sprite_->SetPosition(position);

	//	sound
	if (input_->TriggerKey(DIK_SPACE)) {
		audio_->StopWave(voiceHandle_);
	}

	
	//	debugText
	value_++;
	//	文字列
	std::string strDebug1 =
	  std::string("translation:(") + std::to_string(worldTransform_.translation_.x) +
	  std::to_string(worldTransform_.translation_.y) +
	  std::to_string(worldTransform_.translation_.z) + std::string(")");
	std::string strDebug2 =
	  std::string("rotation:(") + std::to_string(worldTransform_.rotation_.x) +
	  std::to_string(worldTransform_.rotation_.y) +
	  std::to_string(worldTransform_.rotation_.z) + std::string(")");
	std::string strDebug3 =
	  std::string("scale:(") + std::to_string(worldTransform_.scale_.x) +
	  std::to_string(worldTransform_.scale_.y) +
	  std::to_string(worldTransform_.scale_.z) + std::string(")");

	debugText_->Print(strDebug1, 50, 50, 1.0f);
	debugText_->Print(strDebug2, 50, 70, 1.0f);
	debugText_->Print(strDebug3, 50, 90, 1.0f);
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
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//sprite_->Draw();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

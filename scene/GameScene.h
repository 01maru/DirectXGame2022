#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>
#include "Vector3D.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	enum PlayerId {
		Root,
		Front,
		Top,
		Left,
		Right,
		Bottom,
	};
  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	uint32_t textureHandle_ = 0;

	//	3Dモデル
	Model* model_ = nullptr;
	
	//	ワールドトランスフォーム
	//WorldTransform worldTransform_[100];

	WorldTransform player[6];
	Vector3D pFrontVec;
	//	ビュープロジェクション
	ViewProjection viewProjection_;

	float vieewAngle = 0.0f;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};

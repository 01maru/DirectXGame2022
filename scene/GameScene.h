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
#include "Player.h"

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

	//	床
	WorldTransform floor[10][10];

	//	player
	Player player;

	//	ビュープロジェクション
	
	//	カメラ座標
	ViewProjection viewProjection_;
	float cDisPlayer = 20.0f;		//	カメラとobjの距離
	float cAngleF = 0.0f;
	float lerp = 0.0f;
	float cMoveT = 1.0f;			//	カメラ移動時間
	DirectX::XMFLOAT3 cameraStart;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};

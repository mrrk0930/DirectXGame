#pragma once
#include"KamataEngine.h"
#include "Player.h"
#include <vector>

//ゲームシーン
class GameScene
{

	public:
		
		//初期化
	    void Initialize();

		//更新
	    void Update();

		//描画
	    void Draw();

		// デストラクタ
	    ~GameScene();

	    // テクスチャハンドル
	    uint32_t textureHandle_ = 0;

		// 3Dモデル
	    KamataEngine::Model* model_ = nullptr;

		// カメラ
	    KamataEngine::Camera camera_;

		// 自キャラ
	    Player* player_ = nullptr;

		// ブロック用ワールドトランスフォームの配列バージョン
		std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

		//デバックカメラ有効
	    bool isDebugCameraActive_ = false;

		//デバックカメラ
	    KamataEngine::DebugCamera* debugcamera_ = nullptr;

};

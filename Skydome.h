#pragma once
#include "KamataEngine.h"

//天球
class Skydome 
{

	public:

		// 初期化
	    void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera);

		// 更新
	    void Update();

	    // 描画
	    void Draw();

		// デストラクタ
	    ~Skydome();

	private:

		//ワールド変換データ
	    KamataEngine::WorldTransform worldTransform_;

		//モデル
	    KamataEngine::Model* model_ = nullptr;

		// テクスチャ
	    uint32_t textureHandle_ = 0u;

	    // カメラ
	    KamataEngine::Camera* camera_ = nullptr;

};

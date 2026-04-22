#pragma once
#include "KamataEngine.h"

//プレイヤー
class Player 
{

	public:
	// 初期化
		///<param name="model">モデル</param>
		///<param name="textureHandle">テクスチャハンドル</param>
		///<param name="camera">カメラ</param>
	    void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera);

	// 更新
	void Update();

	// 描画
	void Draw();

	private:
        //ワールド変換データ
	    KamataEngine::WorldTransform worldTransform_;

		//モデル
	    KamataEngine::Model* model_ = nullptr;

		//テクスチャハンドル
	    uint32_t textureHandle_ = 0u;

		//カメラ
	    KamataEngine::Camera* camera_ = nullptr;

};
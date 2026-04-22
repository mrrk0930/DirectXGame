#include "Player.h"
#include "cassert"

using namespace KamataEngine;

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera) 
{

	// インゲームの初期化処理

	//NULLポインタチャック
	assert(model);
	
	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;

	//ワールド変換の初期化
	worldTransform_.Initialize();
}

void Player::Update() 
{

	// インゲームの更新処理

	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();


}

void Player::Draw() 
{

	//3Dモデルを描画
	model_->Draw(worldTransform_, *camera_, textureHandle_);

}


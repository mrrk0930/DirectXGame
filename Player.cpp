#include "Player.h"
#include "cassert"
#include "MathUtility.h"
#include "WorldMatrixF.h"

using namespace KamataEngine;

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera) {

	// インゲームの初期化処理

	// NULLポインタチャック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Player::Update() {

	// インゲームの更新処理

		// アフィン変換行列を計算してメンバ変数に代入
	UpdateWorldTransform(worldTransform_);
}

void Player::Draw() {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *camera_, textureHandle_);
}

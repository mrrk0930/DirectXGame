#include "GameScene.h"
#include "MathUtility.h"

using namespace KamataEngine;

void GameScene::Initialize() {

	// インゲームの初期化処理

	// ファイル名を指定してテクスチャ読み込む
	textureHandle_ = TextureManager::Load("cube/cube.jpg");

	// 3Dモデルの生成
	model_ = Model::Create();

	// カメラの初期化
	camera_.Initialize();

	// デバックカメラの生成
	debugcamera_ = new DebugCamera(1080, 720);

	// 自キャラの生成
	player_ = new Player();

	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_, &camera_);

	// 要素数
	const uint32_t kNumBlockVirtical = 10;
	const uint32_t kNumBlockHorizontal = 20;

	// ブロック一個分の横幅
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;

	// 要素数を変更する
	// 列数を設定（縦方向のブロック数）
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {

		// 一列の要素数を設定（横方向のブロック数）
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {

		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {

			// 交互に穴を開ける
			if ((i + j) % 2 == 0) {

				worldTransformBlocks_[i][j] = nullptr;
				continue;
			}

			worldTransformBlocks_[i][j] = new WorldTransform();
			worldTransformBlocks_[i][j]->Initialize();
			worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
			worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
		}
	}
}

void GameScene::Update() {

	// インゲームの更新処理

	// 自キャラの更新
	player_->Update();

	// デバックカメラの更新
	debugcamera_->Update();

#ifdef _DEBUG

	if (Input::GetInstance()->TriggerKey(DIK_K)) {

		// デバックカメラ有効フラグをトグル
		isDebugCameraActive_ = true;
	}

#endif

	// カメラの処理
	if (isDebugCameraActive_) {

		camera_.matView = debugcamera_->GetCamera().matView;
		camera_.matProjection = debugcamera_->GetCamera().matProjection;

		// ビュープロジェクション行列の転送
		camera_.TransferMatrix();

	} else {

		// ビュープロジェクション行列の更新と転送
		camera_.UpdateMatrix();
	}

	// ブロック更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			if (!worldTransformBlock)
				continue;

			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

			worldTransformBlock->TransferMatrix();
		}
	}
}
void GameScene::Draw() {

	// 3Dモデルの描画前処理
	Model::PreDraw();

	// 自キャラの描画
	player_->Draw();

	// ブロック描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			if (!worldTransformBlock)
				continue;

			model_->Draw(*worldTransformBlock, camera_, textureHandle_);
		}
	}

	// 3Dモデルの描画後処理
	Model::PostDraw();
}

GameScene::~GameScene() {

	// 3Dモデルデータの開放
	delete model_;
	model_ = nullptr;

	// 自キャラの開放
	delete player_;
	player_ = nullptr;

	// デバックカメラ
	delete debugcamera_;

	// ワールドトランスフォームの配列解放
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			delete worldTransformBlock;
		}
	}

	worldTransformBlocks_.clear();
}
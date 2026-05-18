#include "GameScene.h"
#include "MathUtility.h"

using namespace KamataEngine;

void GameScene::Initialize() {

	// インゲームの初期化処理

	// ファイル名を指定してテクスチャ読み込む
	blockTextureHandle_ = TextureManager::Load("block/block.png");
	playerTextureHandle_ = TextureManager::Load("player/player.png");

	// 3Dモデルの生成
	//model_ = Model::Create();

	// プレイヤーモデル生成
	modelPlayer_ = Model::CreateFromOBJ("player", true);

	// ブロックモデル生成
	modelBlock_ = Model::CreateFromOBJ("block", true);

	// 天球モデル生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	// カメラの初期化
	camera_.Initialize();

	// farZを変更
	camera_.farZ = 2000.0f;

	// 行列更新
	camera_.UpdateMatrix();

	// デバックカメラの生成
	debugcamera_ = new DebugCamera(1080, 720);

	// 自キャラの生成
	player_ = new Player();

	// 自キャラの初期化
	player_->Initialize(modelPlayer_, playerTextureHandle_, &camera_);

	// 天球生成
	skydome_ = new Skydome();

	// 天球初期化
	skydome_->Initialize(modelSkydome_, &camera_);

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

	// 天球更新
	skydome_->Update();

	// デバックカメラの更新
	debugcamera_->Update();

#ifdef _DEBUG

	if (Input::GetInstance()->TriggerKey(DIK_K)) {

		// デバックカメラ有効フラグをトグル
		isDebugCameraActive_ = !isDebugCameraActive_;
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

	// 天球描画
	skydome_->Draw();

	// 自キャラの描画
	player_->Draw();

	// ブロック描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			if (!worldTransformBlock)
				continue;

			modelBlock_->Draw(*worldTransformBlock, camera_, blockTextureHandle_);
		}
	}

	// 3Dモデルの描画後処理
	Model::PostDraw();
}

GameScene::~GameScene() {

	// 3Dモデルデータの開放
	//delete model_;
	//model_ = nullptr;

	// 3Dモデルデータの開放
	delete modelPlayer_;
	modelPlayer_ = nullptr;

	delete modelBlock_;
	modelBlock_ = nullptr;

	delete modelSkydome_;
	modelSkydome_ = nullptr;

	// 天球解放
	delete skydome_;
	skydome_ = nullptr;

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
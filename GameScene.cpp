#include"GameScene.h"

using namespace KamataEngine;

void GameScene::Initialize() 
{

	//インゲームの初期化処理

	// ファイル名を指定してテクスチャ読み込む
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// 3Dモデルの生成
	model_ = Model::Create();

	// カメラの初期化
	camera_.Initialize();

    // 自キャラの生成
	player_ = new Player();

	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_,&camera_);

}

void GameScene::Update()
{

	//インゲームの更新処理

	// 自キャラの更新
	player_->Update();

}

void GameScene::Draw() 
{

	// 3Dモデルの描画前処理
	Model::PreDraw();

	// 自キャラの描画
	player_->Draw();

	// 3Dモデルの描画後処理
	Model::PostDraw();

}

GameScene::~GameScene() 
{

	delete model_;
	model_ = nullptr;

	// 自キャラの開放
	delete player_;
	player_ = nullptr;

}
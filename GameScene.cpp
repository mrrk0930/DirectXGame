#include"GameScene.h"
#include "2d/ImGuiManager.h"

using namespace KamataEngine;

void GameScene::Initialize() 
{

	//インゲームの初期化処理

	//ファイル名を指定してテクスチャ読み込む
	//textureHandle_ = TextureManager::Load("uvChecker.png");

	textureHandle_ = TextureManager::Load("cube/cube.jpg");

	//サウンドデータの読み込み
	soundDateHandle_ = Audio::GetInstance()->LoadWave("fanfare.wav");

	//音声再生
	Audio::GetInstance()->PlayWave(soundDateHandle_);

	//音声再生
	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDateHandle_, true);

	//スプライトインスタンスの生成
	//sprite_ = Sprite::Create(textureHandle_, {100, 50});

	//3Dモデルの生成
	model_ = Model::Create();

	//デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//カメラの初期化
	camera_.Initialize();

	//ライン描画が参照するカメラを指定する（アドレス渡し）
	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());

}

void GameScene::Update()
{

	//インゲームの更新処理

	//スプライトの今の座標を取得
	//Vector2 position = sprite_->GetPosition();
	//座標を｛２，１｝移動
	//position.x += 2.0f;
	//position.y += 1.0f;
	//移動した座標をスプライトに反映
	//sprite_->SetPosition(position);

	//スペースキーを押した瞬間
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) 
	{
	
		//音声停止
		Audio::GetInstance()->StopWave(voiceHandle_);

	}

#ifdef  _DEBUG
	// デバックテキストの表示
	ImGui::Begin("Debug1");
	// float3入力ボックス
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	// float3スライダー
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	ImGui::Text("Kamata Tarou %d.%d.%d", 2050, 12, 31);
	ImGui::End();
	// デモウィンドウの表示を有効化
	ImGui::ShowDemoWindow();
#endif // DEBUG

	//デバックカメラの更新
	debugCamera_->Update();

}

void GameScene::Draw() 
{

	//スプライトの描画前処理
	Sprite::PreDraw();

	//ここにスプライトインスタンスの描画処理を記述する
	//sprite_->Draw();

	// スプライトの描画前処理
	Sprite::PostDraw();

	//3Dモデルの描画前処理
	Model::PreDraw();

	// 3Dモデル描画
	//model_->Draw(worldTransform_, camera_, textureHandle_);

	model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle_);

	// 3Dモデルの描画後処理
	Model::PostDraw();

	// ラインを描画する
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});

	

}

GameScene::~GameScene() 
{
	delete sprite_;
	sprite_ = nullptr;

	delete model_;
	model_ = nullptr;

	delete debugCamera_;
	debugCamera_ = nullptr;
	
}
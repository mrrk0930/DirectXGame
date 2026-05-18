#include "Skydome.h"


using namespace KamataEngine;

void Skydome::Initialize(Model* model, Camera* camera) {

	
	model_ = model;

	camera_ = camera;

	// ワールド変換初期化
	worldTransform_.Initialize();

	
}
void Skydome::Update() 
{

	worldTransform_.TransferMatrix();

}

void Skydome::Draw() 
{

	//3Dモデル描画
	model_->Draw(worldTransform_, *camera_);

}

Skydome::~Skydome() 
{

}
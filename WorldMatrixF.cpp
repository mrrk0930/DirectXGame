#include "MathUtility.h"
#include "WorldMatrixF.h"

using namespace KamataEngine;

// 行列を計算転送する
void UpdateWorldTransform(WorldTransform& worldTransform) {

	worldTransform.matWorld_ = MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);

	worldTransform.TransferMatrix();
}
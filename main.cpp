#include <Windows.h>
#include <KamataEngine.h>
using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) 
{
	
	//エンジンの初期化
	KamataEngine::Initialize(L"GC2B_05_ムロサキ_リク_AL3");

	//メインループ
	while (true) 
	{

		//エンジンの更新
		if (KamataEngine::Update()) 
		{
		
			break;
		
		}
	
	}

	//エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}

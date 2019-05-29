//------------------------//------------------------
// Contents(処理内容) SceneBase.hの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 08 / 13
// last updated (最終更新日) 2018 / 11 / 01
//------------------------//------------------------



// 多重インクルードの防止 =====================================================
#pragma once
#include "../../Utillity/DirectX11.h"
#include "../../../StepTimer.h"
// クラスの宣言 ===============================================================
class SceneManager;



// クラスの定義 ===============================================================
/// <summary>
/// シーンの基底クラス
/// </summary>
class SceneBase
{
	// データメンバの宣言 -------------------------------------------------
	protected:
		SceneManager* m_sceneManager;
		bool m_SceneFlag;

	// メンバ関数の宣言 ---------------------------------------------------
	// <コンストラクタ>
	public:
		SceneBase(SceneManager* sceneManager,bool SceneFlag);


	// <デストラクタ>
	public:
		virtual ~SceneBase();


	// <操作>
	public:
		// <初期化関数>
		virtual void Initialize() = 0;
		// <更新関数>
		virtual void Update(const DX::StepTimer& stepTimer) = 0;
		// <描画関数>
		virtual void Render() = 0;
		// <終了関数>
		virtual void Finalize() = 0;
};

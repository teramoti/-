//------------------------//------------------------
// Contents(処理内容) SceneManager.h
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 08 / 13
// last updated (最終更新日) 2018 / 11 / 01
//------------------------//------------------------

// 多重インクルードの防止 =====================================================
#pragma once
#include "../../Utillity/DirectX11.h"
#include "../../../StepTimer.h"
#include "../../Utillity/SingletonBase.h"
// クラスの宣言 ===============================================================
class SceneBase;



/// 定数の定義 ================================================================
/// <summary>
/// シーンID
/// </summary>
enum SceneId
{
	LOGO_SCENE,
	TITLE_SCENE,
	SELECT_SCENE,
	GAME_SCENE,
	RESULT_SCENE,

	NUM_SCENES
};



/// クラスの定義 ==============================================================
/// <summary>
/// シーンマネージャークラス
/// </summary>
class SceneManager:  public Utility::SingletonBase<SceneManager>
{
	// データメンバの宣言 -------------------------------------------------
	private:
		SceneBase* m_scenes[NUM_SCENES];    // 登録されているシーンのリスト

		SceneBase* m_activeScene;           // 活動中のシーン
		SceneBase* m_requestedScene;        // 要求されたシーン
	// メンバ関数の宣言 ---------------------------------------------------
	// <コンストラクタ>
	public:
		SceneManager();

	// <デストラクタ>
	public:
		~SceneManager();


	// <操作>
	public:
		//シーンのInitilize呼び出し関数
		void InitilizeActiveScene();
		//シーンのUpdate呼び出し関数
		void UpdateActiveScene(const DX::StepTimer step);
		//シーンのRederび出し関数
		void RenderActiveSceneRender();
		//シーンの設定用関数
		void SetScene(SceneId startSceneId);
		//シーンのFinalize呼び出し関数
		void FinalizeActiveScene();
		//シーンの変更用関数
		void ChangeScene(SceneBase* nextScene);

};

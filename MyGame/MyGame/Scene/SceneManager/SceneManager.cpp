//------------------------//------------------------
// SceneManager.cpp
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 08 / 13
// last updated (最終更新日) 2019 / 05 / 26
//------------------------//------------------------


// ヘッダファイルのインクルード ===============================================
#include "SceneManager.h"

#include "../Base/SceneBase.h"

#include "../TitleScene/TitleScene.h"
#include "../GameScene/Gamescene.h"
#include "../ResultScene/ResultScene.h"

// usingディレクティブ ========================================================


// メンバ関数の定義 ===========================================================
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="startSceneId">開始シーンのID</param>
SceneManager::SceneManager()
	: m_activeScene(nullptr)
	, m_requestedScene(nullptr)
{
	//何もしなくてよい
}


/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	if (m_activeScene != nullptr)
	{
		delete m_activeScene;
	}
	m_activeScene    = nullptr;
}
/// <summary>
/// 活動中のシーンの初期化処理
/// </summary>
void SceneManager::InitilizeActiveScene()
{

	if (m_activeScene != nullptr)
	{
		//initilizeを呼ぶ
		m_activeScene->Initialize();
	}
}

/// <summary>
/// 活動中のシーンの更新処理
/// </summary>
/// <param name="timer">時間情報</param>
void SceneManager::UpdateActiveScene(const DX::StepTimer stepTimer)
{
	if (m_requestedScene != nullptr)
	{
		//リクエストされているなら、シーン変更
		ChangeScene(m_activeScene);
	}

	if (m_activeScene != nullptr)
	{
		//nullじゃなければUpdateを呼ぶ
		m_activeScene->Update(stepTimer);
	}
}


/// <summary>
/// 活動中のシーンの描画処理
/// </summary>
void SceneManager::RenderActiveSceneRender()
{
	if (m_activeScene != nullptr)
	{
		//	Renderを呼ぶ
		m_activeScene->Render();
	}
}


/// <summary>
/// シーンの変更を要求
/// </summary>
/// <param name="sceneId">変更を要求するシーンのID</param>
/// <returns>要求が通った場合 true, 通らない場合 false</returns>
void SceneManager::SetScene(SceneId startSceneId)
{
	if(m_activeScene!=nullptr)
	{
		delete m_activeScene;
	}

	//シーンの追加があった入れる
	switch (startSceneId)
	{

	case TITLE_SCENE:
		m_activeScene = new TitleScene(this);
		break;

	case GAME_SCENE:
		m_activeScene = new GameScene(this);
		break;
	case RESULT_SCENE:
		m_activeScene = new ResultScene(this);
		break;

	default:
		m_activeScene = nullptr;
		break;
	}

	m_activeScene->Initialize();
}

void SceneManager::FinalizeActiveScene()
{
	// 活動中のシーンを終了させる
	if (m_activeScene != nullptr)
	{
		m_activeScene->Finalize();
		m_activeScene = nullptr;
	}


	// 要求されたシーンを活動中にする
	m_activeScene = m_requestedScene;
	m_requestedScene = nullptr;
}

/// <summary>
/// 活動シーンの変更
/// </summary>
void SceneManager::ChangeScene(SceneBase* nextScene)
{
	// 活動中のシーンを終了させる
	if (m_activeScene != nullptr)
	{
		m_activeScene->Finalize();
		m_activeScene = nullptr;
	}
	// 要求されたシーンを活動中にする
	m_activeScene    = nextScene;
}

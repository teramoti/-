//------------------------//------------------------
// SceneManager.cpp
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 08 / 13
// last updated (最終更新日) 2018 / 11 / 01
//------------------------//------------------------


// ヘッダファイルのインクルード ===============================================
#include "../../../pch.h"
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
SceneManager::SceneManager(ID3D11Device* device, ID3D11DeviceContext* context)
	: m_activeScene(nullptr)
	, m_requestedScene(nullptr)
	, m_device(device)
	,m_context(context)
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
void SceneManager::InitilizeActiveScene(int width, int height)
{

	if (m_activeScene != nullptr)
	{
		//initilizeを呼ぶ
		m_activeScene->Initialize(width,height,m_device,m_context);
	}
}

/// <summary>
/// 活動中のシーンの更新処理
/// </summary>
/// <param name="timer">時間情報</param>
void SceneManager::UpdateActiveScene( DX::StepTimer step)
{
	if (m_requestedScene != nullptr)
	{
		//リクエストされているなら、シーン変更
		ChangeScene();
	}

	if (m_activeScene != nullptr)
	{
		//nullじゃなければUpdateを呼ぶ
		m_activeScene->Update(step);
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
void SceneManager::SetScene(SceneId startSceneId, int width, int height)
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

	m_activeScene->Initialize(width,height,m_device,m_context);
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
void SceneManager::ChangeScene()
{
	// 活動中のシーンを終了させる
	if (m_activeScene != nullptr)
	{
		m_activeScene->Finalize();
	}

	// 要求されたシーンを活動中にする
	m_activeScene    = m_requestedScene;
	m_requestedScene = nullptr;
}

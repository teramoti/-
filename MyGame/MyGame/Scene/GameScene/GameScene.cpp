//------------------------//------------------------
// Contents(処理内容) GameScene.cppの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 13
// last updated (最終更新日) 2018 / 11 / 05
//------------------------//------------------------

//インクルードファイルの宣言
#include <d3d11.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include "Gamescene.h"
#include "../../GameSystem/GameSaveData.h"
#include "../../GameSystem/DrawManager.h"
#include "../../GameSystem/InputManager.h"
#include "../SceneManager/SceneManager.h"


#define MIN(a,b) ((a>b) ? (b):(a));
#define MAX(a,b) ((a>b) ? (a):(b));
//----------------------------------------------------------------------
//! @brief ゲームシーンクラスのコンストラクタ
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------

GameScene::GameScene(SceneManager* scenemaneger)
	: SceneBase(scenemaneger, m_SceneFlag), m_GameTimer(0),
	m_CouceCount(0),m_StageNum(0), m_GoalRank(0),
	m_startFlag(false), m_SceneFlag(false) , m_goalFlag(false)
{

}

//----------------------------------------------------------------------
//! @brief ゲームシーンのデストラクタ
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
GameScene::~GameScene()
{
	m_Camera.reset();
	m_player.reset();
	m_skyDome.reset();
	m_states.reset();

	m_time.reset();
	m_CheckPoint.reset();

	delete m_Count;
	delete m_GameTime;
}

//----------------------------------------------------------------------
//! @brief ゲームシーンの初期化処理
//!
//! @param windth,height,devive,context
//!
//! @return なし
//----------------------------------------------------------------------
void GameScene::Initialize()
{

	m_adx2le = MyLibrary::ADX2Le::GetInstance();
	// サウンドの読み込み
	m_adx2le->LoadAcb(L"GameScene.acb", L"GameScene.awb");
	//コースのステージメッシュの初期化
	m_stageMesh = std::make_unique<CollisionMesh>(m_directX.GetDevice().Get() , L"Resources/CircleCource.obj");

	if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	{
		// 効果音の再生
		m_criAtomExPlaybackId = m_adx2le->Play(0);
	}

	//Cameraクラスの初期化
	m_Camera = std::make_unique<TpsCamera>(m_directX.GetWidth(), m_directX.GetHeight());

	//Objectクラスの初期化
	MyLib::Object3D::InitielizeStatic(m_directX.GetDevice().Get(), m_directX.GetContext().Get(), m_Camera.get());

	//プレイヤーの生成
	m_player = std::make_unique<TestPlayer>();
	//Playerの初期化処理
	m_player->Initilize();

	//カメラのTargetの設定
	m_Camera->SetObject3D(m_player.get());

	//チェックポイントの作成
	m_CheckPoint = std::make_unique<CheckPoint>();
	//チェックポイントの初期化処理
	m_CheckPoint->Initilize();


	//コースクラスの作成
	m_cource = std::make_unique<Cource>();
	//コースクラスの初期化処理
	m_cource->Initilize();

	//スカイドームクラスの作成
	m_skyDome = std::make_unique<SkyDome>();
	//スカイドームクラスの初期化処理
	m_skyDome->Initilize();

	//時間クラスの作成
	m_time = std::make_unique<Time>();


	//カウントダウンクラスの作成
	m_Count = new CountDown();
	//カウントダウンクラスの初期化
	m_Count->Initilize();


	//ゲーム時間クラスの作成
	m_GameTime = new GameTime();
	//ゲーム時間クラスの初期化
	m_GameTime->Initilize();

//ゴール時の止める時間の初期化
	m_GoalNum = 0;
}

//----------------------------------------------------------------------
//! @brief ゲームシーンの更新処理
//!
//! @param steptimer
//!
//! @return なし
//----------------------------------------------------------------------

void GameScene::Update(DX::StepTimer& stepTimer)
{

	int startTime = (int)stepTimer.GetTotalSeconds();//ゲームの開始時間の取得
 	float elapsedTime = float(stepTimer.GetElapsedSeconds());
	//時間の情報
	m_GameTimer = m_time->GetTime();//タイムクラスの時間を取得
	counter--;//始まる前のＣｏｕｎｔを引く
	m_CheckPoint->Update();//チェックポイントの更新
	m_skyDome->Update();//スカイドームの更新

	if (counter < 0)
	{
		if (m_goalFlag == false)
		{
			m_time->Update(m_GameTimer);//時間の更新
			m_GameTime->SetTime(m_GameTimer);//ゲームの時間をＣｏｕｎｔダウンする
			m_startFlag = true;//始まるフラグをtrueにする

		}	

	}
	else
	{
		m_Count->SetTime(counter);
	}

	if (m_CheckPoint->GetFlag() == true)
	{
		m_time->SetFlag(false);
		m_GoalNum += 1;
		m_goalFlag = true;

	}
	//60秒たったら強制的にリザルトに行く処理
	if (m_GameTimer >= 6000)
	{
		m_time->SetFlag(false);

		m_GameTimer = 6000;//ゲーム時間を60秒にする。

		m_SceneFlag = true;

	}

	//リザルトにシーンを持っていく
	GameSaveData::GetInstance().SetGoal1Time(m_GameTimer);

	//GameSaveData::GetInstance().SetRank(m_GoalRank);

	m_cource->Update();//コースの更新処理
	if (m_GoalNum > 40)
	{
		m_SceneFlag = true;
	}
	if (m_SceneFlag == true)
	{
		//Resultをセットする
		m_adx2le->Stop();
		m_sceneManager->SetScene(RESULT_SCENE);//シーンをリザルトにする。
		return;
	}

	//カメラの更新	
	m_Camera->Update();

	m_player->Update(m_startFlag);//プレイヤーの更新
	HitManager();//当たり判定の更新用関数

}
//----------------------------------------------------------------------
//! @brief ゲームシーンの描画用関数
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void GameScene::Render()
{
	m_player->Render();//プレイヤーの描画
	m_skyDome->Render();//すかいどーむの描画
	m_cource->Render();//コースの描画
	SpriteRender();	//画像の描画	
	m_stageMesh->DrawCollision(m_directX.GetContext().Get(), m_Camera->GetView(), m_Camera->GetProj());//メッシュの描画
}
//----------------------------------------------------------------------
//! @brief ゲームシーンの終了処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------

void GameScene::Finalize()
{

}

//----------------------------------------------------------------------
//! @brief あたり判定をまとめるよう関数
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void GameScene::HitManager()
{
	StageCheckPoint();
	StageCollision();

}

//----------------------------------------------------------------------
//! @brief 画像の描画用関数
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void GameScene::SpriteRender()
{
	System::DrawManager::GetInstance().Begin();
	m_Count->Draw();//カウントを描画する
	m_GameTime->Draw(m_startFlag);
	if (m_goalFlag)
	{
		//ゴールの文字を出す

	}

	System::DrawManager::GetInstance().End();
}

//----------------------------------------------------------------------
//! @brief ステージのチェックポイント関数
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------

void GameScene::StageCheckPoint()
{
	if (m_CollisionManager->CollisionBox2Box(m_player->GetBox(), m_CheckPoint->GetBoxCheckPos1()) == true)
	{
		m_CheckPoint->Checkhit1(true);
	}
	if (m_CollisionManager->CollisionBox2Box(m_player->GetBox(), m_CheckPoint->GetBoxCheckPos2()) == true)
	{
		m_CheckPoint->Checkhit2(true);
	}
	if (m_CollisionManager->CollisionBox2Box(m_player->GetBox(), m_CheckPoint->GetBoxStartPos()) == true)
	{
		m_CheckPoint->Checkhit3(true);
	}

}
//----------------------------------------------------------------------
//! @brief ステージのあたり判定
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------

void GameScene::StageCollision()
{
	DirectX::SimpleMath::Vector3 playerVel = m_player->GetVel();
	DirectX::SimpleMath::Vector3 playerPos = m_player->GetTranslation();


	// ボールの真下に向かう線分
	DirectX::SimpleMath::Vector3 v[2] =
	{
		DirectX::SimpleMath::Vector3(playerPos.x, 100.0f, playerPos.z),
		DirectX::SimpleMath::Vector3(playerPos.x, -100.0f, playerPos.z),
		};

		//線分と床の交差判定を行う
		int id;
		DirectX::SimpleMath::Vector3 s;
		if (m_stageMesh->HitCheck_Segment(v[0], v[1], &id, &s))
		{
				playerPos.y = s.y + PLAYER_RISE;
				playerVel.y = 0.0f;
		}

	m_player->SetTranslation(playerPos);//プレイヤーの場所の更新
	m_player->SetVel(playerVel);//プレイヤーの速度を設定する。
}


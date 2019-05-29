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
	: SceneBase(scenemaneger, m_SceneFlag), m_gameTimer(0),
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
	m_camera.reset();
	m_player.reset();
	m_skyDome.reset();
	m_states.reset();

	m_time.reset();
	m_checkPoint.reset();

	delete m_count;
	delete m_gameTime;
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

	//m_adx2le = MyLibrary::ADX2Le::GetInstance();
	// サウンドの読み込み
	//m_adx2le->LoadAcb(L"GameScene.acb", L"GameScene.awb");
	//コースのステージメッシュの初期化
	m_stageMesh = std::make_unique<CollisionMesh>(m_directX.GetDevice().Get() , L"Resources/CircleCource.obj");

	//if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	//{
	//	// 効果音の再生
	//	m_criAtomExPlaybackId = m_adx2le->Play(0);
	//}

	//Cameraクラスの初期化
	m_camera = std::make_unique<TpsCamera>(m_directX.GetWidth(), m_directX.GetHeight());
	m_shadow = new Shadow();
	//m_shadow->Initialize();
	//プレイヤーの生成
	m_player = std::make_unique<Player>();
	//Playerの初期化処理
	m_player->Initilize(m_shadow);

	//カメラのTargetの設定
	m_camera->SetObject3D(m_player.get());

	//チェックポイントの作成
	m_checkPoint = std::make_unique<CheckPoint>();
	//チェックポイントの初期化処理
	m_checkPoint->Initilize();


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
	m_count = new CountDown();
	//カウントダウンクラスの初期化
	m_count->Initilize();

	//ゲーム時間クラスの作成
	m_gameTime = new GameTime();
	//ゲーム時間クラスの初期化
	m_gameTime->Initilize();


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

void GameScene::Update(const DX::StepTimer& stepTimer)
{

	//ゲームの開始時間の取得
	int startTime = (int)stepTimer.GetTotalSeconds();
	//時間の情報

	//タイムクラスの時間を取得
	m_gameTimer = m_time->GetTime();
	//初期化前のCountを引く
	counter--;
	//チェックポイントの更新
	m_checkPoint->Update();
	//スカイドームの更新
	m_skyDome->Update();

	if (counter < 0)
	{
		if (m_goalFlag == false)
		{
			//時間の更新
			m_time->Update(m_gameTimer);
			//ゲームの時間をＣｏｕｎｔダウンする
			m_gameTime->SetTime(m_gameTimer);
			//初期化フラグをtrueにする
			m_startFlag = true;
		}	
	}
	else
	{
		//タイマーの設定をする。
		m_count->SetTime(counter);
	}

	//プレイヤーがチェックポイントをすべて通ったのか
	if (m_checkPoint->GetFlag() == true)
	{
		m_time->SetFlag(false);
		m_GoalNum += 1;
		m_goalFlag = true;

	}
	//60秒たったら強制的にリザルトに行く処理
	if (m_gameTimer >= 6000)
	{
		m_time->SetFlag(false);

		//ゲーム時間を60秒にする
		m_gameTimer = 6000;

		m_SceneFlag = true;

	}

	//リザルトにシーンを持っていく
	GameSaveData::GetInstance().SetGoal1Time(m_gameTimer);

	//コースの更新処理
	m_cource->Update();
	
	if (m_GoalNum > 40)
	{
		m_SceneFlag = true;
	}
	if (m_SceneFlag == true)
	{
		//シーンをリザルトにする
		m_sceneManager->SetScene(RESULT_SCENE);
		return;
	}

	//カメラの更新	
	m_camera->Update();

	//プレイヤーの更新
	m_player->Update(m_startFlag);
	//当たり判定の更新用関数
	DetectCollisionManager();

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
	//プレイヤーの描画
	m_player->Render(m_camera->GetView(),m_camera->GetProj());
<<<<<<< HEAD
	m_shadow->Render(m_camera->GetView(), m_camera->GetProj(),m_player.get());
=======
>>>>>>> 44105518dbb6f25c151be9ebdc146f28eef5a8a7
	//スカイドームの描画
	m_skyDome->Render(m_camera->GetView(), m_camera->GetProj());
	//コースの描画
	m_cource->Render(m_camera->GetView(), m_camera->GetProj());
	//画像の描画
	SpriteRender();		
	//メッシュの描画
<<<<<<< HEAD
	m_stageMesh->DrawCollision(m_directX.GetContext().Get(), m_camera->GetView(), m_camera->GetProj());
=======
	//m_stageMesh->DrawCollision(m_directX.GetContext().Get(), m_camera->GetView(), m_camera->GetProj());
>>>>>>> 44105518dbb6f25c151be9ebdc146f28eef5a8a7
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
void GameScene::DetectCollisionManager()
{
	// ステージのチェックポイントにPlayerが当たっているか
	DetectCollisionPlayerToCheckPoint();
	// ステージのMeshにPlayerが当たっているか
	DetectCollisionPlayerToMesh();

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
	//カウントを描画する
	m_count->Draw();
	//ゴール時間の描画
	m_gameTime->Draw(m_startFlag);
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
void GameScene::DetectCollisionPlayerToCheckPoint()
{
	//ステージのチェックポイント1とPlayerがあったているのか
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxCheckPos1()) == true)
	{
		//1つ目のチェックポイントを通ったことにする
		m_checkPoint->Checkhit1(true);
	}
	//ステージのチェックポイント2とPlayerがあったているのか
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxCheckPos2()) == true)
	{
		//2つ目のチェックポイントを通ったことにする
		m_checkPoint->Checkhit2(true);
	}
	//ステージのチェックポイント3とPlayerがあったているのか
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxStartPos()) == true)
	{
		//3つ目のチェックポイントを通ったことにする
		m_checkPoint->Checkhit3(true);
	}

}
//----------------------------------------------------------------------
//! @brief ステージのあたり判定
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------

void GameScene::DetectCollisionPlayerToMesh()
{
	//プレイヤーの方向ベクトルの取得
	DirectX::SimpleMath::Vector3 playerVel = m_player->GetVelotity();
	//プレイヤーの位置の取得
	DirectX::SimpleMath::Vector3 playerPos = m_player->GetTranslation();





	// プレイヤーの真下に向かう線分
	DirectX::SimpleMath::Vector3 v[2] =
	{
		DirectX::SimpleMath::Vector3(playerPos.x, 100.0f, playerPos.z),
		DirectX::SimpleMath::Vector3(playerPos.x, -100.0f, playerPos.z),
	};

	// プレイヤーの外枠に向かう線分
	DirectX::SimpleMath::Vector3 feller[2] =
	{
		DirectX::SimpleMath::Vector3(playerPos.x, 100.0f, playerPos.z),
		DirectX::SimpleMath::Vector3(playerPos.x, -100.0f, playerPos.z),
	};


	//線分と床の交差判定を行う
	int id;
	DirectX::SimpleMath::Vector3 s;
	if (m_stageMesh->HitCheck_Segment(v[0], v[1], &id, &s))
	{
		//プレイヤーのポジションy軸をメッシュの判定分+プレイヤーの高さ分あげる
		playerPos.y = s.y + PLAYER_RISE;
		playerVel.y = 0.0f;
	}
	else
	{

	}

	//プレイヤーの場所の更新
	m_player->SetTranslation(playerPos);
	//プレイヤーの速度を設定する
	m_player->SetVel(playerVel);
}

void GameScene::UpdatePlayerFeller()
{
	/*
	//feeler pointing straight in front
	m_Feelers[0] = m_pVehicle->Pos() + m_dWallDetectionFeelerLength * m_pVehicle->Heading();

	//feeler to left
	Vector2D temp = m_pVehicle->Heading();
	Vec2DRotateAroundOrigin(temp, HalfPi * 3.5f);
	m_Feelers[1] = m_pVehicle->Pos() + m_dWallDetectionFeelerLength/2.0f * temp;

	//feeler to right
	temp = m_pVehicle->Heading();
	Vec2DRotateAroundOrigin(temp, HalfPi * 0.5f);
	m_Feelers[2] = m_pVehicle->Pos() + m_dWallDetectionFeelerLength/2.0f * temp;
	*/

	m_feelers.resize(3);
	m_feelers[0] = DirectX::SimpleMath::Vector3(m_player->GetTranslation().x + 10.0f * m_player->GetAngle(),
		m_player->GetTranslation().y + 10.0f * m_player->GetAngle(),
		m_player->GetTranslation().z + 10.0f * m_player->GetAngle());

	DirectX::SimpleMath::Vector3 temp;


	m_feelers[1] = DirectX::SimpleMath::Vector3(m_player->GetTranslation().x + 10.0f * m_player->GetAngle(),
		m_player->GetTranslation().y + 10.0f * m_player->GetAngle(),
		m_player->GetTranslation().z + 10.0f * m_player->GetAngle());



}


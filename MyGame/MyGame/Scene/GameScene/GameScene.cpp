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
#include<random>


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
	m_couceCount(0),m_stageNum(0),  m_playerHeight(0.0f),
	m_startFlag(false), m_sceneFlag(false) , m_goalFlag(false),m_isUpdateing(false)

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
	for (std::vector<Item*>::iterator itr = m_item.begin(); itr != m_item.end(); itr++)
	{
		delete (*itr);
	}
	delete m_itemManager;
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
	m_stageMesh = std::make_unique<CollisionMesh>(m_directX.GetDevice().Get() , L"Resources/Cource_01.obj");
	//m_stageMesh2 = std::make_unique<CollisionMesh>(m_directX.GetDevice().Get(), L"Resources/OutsidetheMyGameCourse_1.obj");
	//if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	//{
	//	// 効果音の再生
	//	m_criAtomExPlaybackId = m_adx2le->Play(0);
	//}

	m_itemManager = new ItemManager();
	m_itemManager->Initilize();

	//場所のランダム
	
	// 非決定的な乱数生成器を生成
	std::random_device rnd;
	 // メルセンヌ・ツイスタの32ビット版、引数は初期シード値	
	std::mt19937 mt(rnd());
	// [0, 99] 範囲の一様乱数
	std::uniform_int_distribution<> randx(-100,1050);
	std::uniform_int_distribution<> randz(-480, 600);

	m_item.resize(100);
	for (int i = 0; i < m_item.size(); i++)
	{
		m_item[i] = new Item(DirectX::SimpleMath::Vector3(randx(mt),-3.0f, randz(mt)));
	}

	for (std::vector<Item*>::iterator itr = m_item.begin(); itr != m_item.end(); itr++)
	{
		(*itr)->Initilize(*m_itemManager);
	}

	//Cameraクラスの初期化
	m_camera = std::make_unique<TpsCamera>(m_directX.GetWidth(), m_directX.GetHeight());
	m_shadow = new Shadow();
	//m_shadow->Initialize();
	//プレイヤーの生成
	m_player = std::make_unique<MyAirPlane>();
	//MyAirPlaneの初期化処理
	m_player->Initilize(m_shadow);

	//Enemyの生成
	m_enemy= std::make_unique<EnemyAirPlane>();
	//EnemyAirPlaneの初期化処理
	m_enemy->Initilize();	
	
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
	m_goalNum = 0;
	m_isUpdateing = false;

	m_collisionManager = new CollisionManager();

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
	m_isUpdateing = true;


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
			//ゲームの時間をCountダウンする
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
		m_goalNum += 1;
		m_goalFlag = true;

		//カメラワークを変える


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
	//m_cource->Update();
	
	if (m_goalNum > 40)
	{
		m_SceneFlag = true;
	}
	if (m_SceneFlag == true)
	{
		//シーンをリザルトにする
		m_sceneManager->SetScene(RESULT_SCENE);
		return;
	}
	//プレイヤーの更新
	m_player->Update(m_startFlag);
	
	//m_enemy->Update(stept);
	
	//カメラの更新	
	m_camera->Update();

	for (std::vector<Item*>::iterator itr = m_item.begin(); itr != m_item.end(); itr++)
	{
		(*itr)->Update();
	}
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
	if (!m_isUpdateing)
	{
		return;
	}

	//スカイドームの描画
	m_skyDome->Render(m_camera->GetView(), m_camera->GetProj());
	
	//コースの描画
	m_cource->Render(m_camera->GetView(), m_camera->GetProj());	
	
	//プレイヤーの描画	
	m_player->Render(m_camera->GetView(),m_camera->GetProj());
	//プレイヤーの影描画
	m_shadow->Render(m_camera.get()->GetView(), m_camera->GetProj(), m_player.get(), PLAYER_HEIGHT);
	//敵の描画
	//m_enemy->Render(m_camera->GetView(), m_camera->GetProj());
	//画像の描画
	SpriteRender();		
	m_checkPoint->Render(m_camera.get()->GetView(), m_camera->GetProj());
	//メッシュの描画
	m_stageMesh->DrawCollision(m_directX.GetContext().Get(), m_camera->GetView(), m_camera->GetProj());
	//コインの描画
	for (std::vector<Item*>::iterator itr = m_item.begin(); itr != m_item.end(); itr++)
	{
		(*itr)->Render(m_camera->GetView(), m_camera->GetProj());
	}

	//画像の描画
	SpriteRender();		

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
	// ステージのチェックポイントにMyAirPlaneが当たっているか
	DetectCollisionMyAirPlaneToCheckPoint();
	// ステージのMeshにMyAirPlaneが当たっているか
	DetectCollisionMyAirPlaneToMesh();
	// ステージとMyAirPlaneが当たっているか
	DetectCollisionMyAirPlaneToCource();
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
void GameScene::DetectCollisionMyAirPlaneToCheckPoint()
{
	//ステージのチェックポイント1とMyAirPlaneがあったているのか
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxCheckPos1()) == true)
	{
		int i = 0;
		i++;

		//1つ目のチェックポイントを通ったことにする
		m_checkPoint->Checkhit1(true);
	}
	//ステージのチェックポイント2とMyAirPlaneがあったているのか
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxCheckPos2()) == true)
	{
		//2つ目のチェックポイントを通ったことにする
		m_checkPoint->Checkhit2(true);
	}

	//ステージのチェックポイント3とMyAirPlaneがあったているのか
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxStartPos()) == true)
	{
		//3つ目のチェックポイントを通ったことにする
 		m_checkPoint->Checkhit3(true);
	}
}
void GameScene::DetectCollisionMyAirPlaneToCource()
{
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_cource->GetBox())==true)
	{
		m_player->SetScale(DirectX::SimpleMath::Vector3(3,3,3));
	}
	else
	{
		m_player->SetScale(DirectX::SimpleMath::Vector3(1,1,1));

	}
}
//----------------------------------------------------------------------
//! @brief ステージのあたり判定
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------

void GameScene::DetectCollisionMyAirPlaneToMesh()
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


	//線分と床の交差判定を行う
	int id;

	DirectX::SimpleMath::Vector3 s;

	if (m_stageMesh->HitCheck_Segment(v[0], v[1], &id, &s))
	{
		//プレイヤーのポジションy軸をメッシュの判定分+プレイヤーの高さ分あげる
		playerPos.y = s.y + PLAYER_HEIGHT;
		//プレイヤーの速度を0にする。s
		playerVel.y = 0.0f;
	}

	//プレイヤーの場所の更新
	m_player->SetTranslation(playerPos);
	//プレイヤーの速度を設定する
	m_player->SetVel(playerVel);
}


//void GameScene::DetectCollisionEnemyAirPlaneToMesh()
//{
//	//プレイヤーの方向ベクトルの取得
//	DirectX::SimpleMath::Vector3 playerVel = m_enemy->GetVelotity();
//	//プレイヤーの位置の取得
//	DirectX::SimpleMath::Vector3 playerPos = m_enemy->GetTranslation();
//
//	// プレイヤーの真下に向かう線分
//	DirectX::SimpleMath::Vector3 v[2] =
//	{
//		DirectX::SimpleMath::Vector3(playerPos.x, 100.0f, playerPos.z),
//		DirectX::SimpleMath::Vector3(playerPos.x, -100.0f, playerPos.z),
//	};
//
//
//	//線分と床の交差判定を行う
//	int id;
//
//	DirectX::SimpleMath::Vector3 s;
//
//	if (m_stageMesh->HitCheck_Segment(v[0], v[1], &id, &s))
//	{
//		//プレイヤーのポジションy軸をメッシュの判定分+プレイヤーの高さ分あげる
//		playerPos.y = s.y + PLAYER_HEIGHT;
//		//プレイヤーの速度を0にする。s
//		playerVel.y = 0.0f;
//	}
//
//	//プレイヤーの場所の更新
//	m_enemy->SetTranslation(playerPos);
//	//プレイヤーの速度を設定する
//	m_enemy->SetVel(playerVel);
//}

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
#include<random>

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
	m_enemy.reset();
	m_skyDome.reset();
	m_states.reset();
	m_stageMesh.reset();
	m_time.reset();
	m_checkPoint.reset();
	m_cource.reset();

	delete m_count;
	 m_gameTime.reset();
	delete m_itemManager;
	//delete m_iobserver;
	delete m_observer;
	delete m_subject;
	delete m_shadow;
	for(int i=0;i<20;i++) delete m_item[i];
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

	//if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	//{
	//	// 効果音の再生
	//	m_criAtomExPlaybackId = m_adx2le->Play(0);
	//}

	//アイテムマネージャークラスを作成
	m_itemManager = new ItemManager();
	//アイテムマネージャーの初期化処理
	m_itemManager->Initilize();

	//場所のランダム
	
	// 非決定的な乱数生成器を生成
	std::random_device rnd;

	 // メルセンヌ・ツイスタの32ビット版、引数は初期シード値	
	std::mt19937 mt(rnd());

	// x軸の一様乱数
	std::uniform_int_distribution<> randx(-100,1050);
	// z軸の一様乱数
	std::uniform_int_distribution<> randz(-480, 600);

	//アイテムの数を設定
	m_item.resize(20);

	int size = 0;
	 
	for (int i=0; i < (static_cast<int>(m_item.size())); i++)
	{
		//アイテムクラスの初期化
		m_item[i] = new Item();
	}



	int x1;
	int z1;

	int rangeX1=    0;

	int rangeZ1= -100;

	int rangeX2= -200;

	int rangeZ2= -200;

	m_itemPosVector.resize(20);

	//範囲を指定して乱数の作成
	for (int i = 0; i < 5; i++)
	{
		std::uniform_int_distribution<> randX1( rangeX2,rangeX1);//左
		std::uniform_int_distribution<> randZ1(rangeZ2+(i*100), rangeZ1 + (i * 100));//上

		x1 = randX1(mt);
		z1 = randZ1(mt);

		m_itemPosVector[i] = DirectX::SimpleMath::Vector3(static_cast<float>(x1), 3.0f, static_cast<float>( z1));
	
		rangeZ2 = randZ1.a();
		rangeZ1 = randZ1.b();
	}

	int i=0;
	//範囲指定して作る
	for (int i =5; i < 10; i++)
	{
		std::uniform_int_distribution<> randX1(rangeX2 + (i * 100), rangeX1 + (i * 100));//左
		std::uniform_int_distribution<> randZ1(rangeZ2, rangeZ1);//上

		x1 = randX1(mt);
		z1 = randZ1(mt);


		m_itemPosVector[i] = DirectX::SimpleMath::Vector3(static_cast<float>(x1), 3.0f, static_cast<float>(z1));

		rangeX2 = randX1.a();
		rangeX1 = randX1.b();

	}
	//int xO = 0;
	////範囲を指定して乱数の作成
	//for (int i = 10; i < 15; i++)
	//{
	//	std::uniform_int_distribution<> randX1(rangeX2, rangeX1);//左右
	//	std::uniform_int_distribution<> randZ1(rangeZ2  - (i * 100), rangeZ1 - (i * 100));//上下

	//	x1 = randX1(mt);
	//	z1 = randZ1(mt);
	//	rangeZ2 = randZ1.a();
	//	rangeZ1 = randZ1.b();

	//	m_itemPosVector[i] = DirectX::SimpleMath::Vector3(static_cast<float>(x1), 3.0f, static_cast<float>(z1));

	//}

	////範囲指定して作る
	//for (int i = 15; i < 20; i++)
	//{
	//	std::uniform_int_distribution<> randX1(rangeX2 - (i * 100), rangeX1 - (i * 100));//左
	//	std::uniform_int_distribution<> randZ1(rangeZ2, rangeZ1);//上

	//	x1 = randX1(mt);
	//	z1 = randZ1(mt);

	//	m_itemPosVector[i] = DirectX::SimpleMath::Vector3(static_cast<float>(x1), 3.0f, static_cast<float>(z1));

	//}
	int x=0;
	int z=0;

	//for (std::vector<Item*>::iterator itr = m_item.begin(); itr != m_item.end(); itr++)
	for(int i=0;i < 20;i++)
	{
		
		x = randx(mt);
		z = randz(mt);

		//ソートする
		
		//Itemクラスの初期化処理
		m_item[i]->Initilize(*m_itemManager, DirectX::SimpleMath::Vector3(static_cast<float>(m_itemPosVector[i].x), 3.0f, static_cast<float>(m_itemPosVector[i].z)));
		//numを1ずつ足す。
		size += 1;
	}
	

	//Cameraクラスの初期化
	m_camera = std::make_unique<TpsCamera>(m_directX.GetWidth(), m_directX.GetHeight());
	
	//Shadowクラスを作成する
	m_shadow = new Shadow();

	//プレイヤーの生成
	m_player = std::make_unique<MyAirPlane>();
	//MyAirPlaneの初期化処理
	m_player->Initilize(m_shadow);

	//Enemyの生成
	m_enemy= std::make_unique<EnemyAirPlane>();
	//EnemyAirPlaneの初期化処理
	m_enemy->Initilize(m_shadow);	
	
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
	m_gameTime = std::make_unique<GameTime>();
	//ゲーム時間クラスの初期化
	m_gameTime->Initilize();
	
	m_goal = new GoalObject();
	m_goal->Initilize();

	//ゴール時の止める時間の初期化
	m_goalNum = 0;
	m_isUpdateing = false;

	m_observer = new Observer(m_player.get());

	m_subject = new Subject();
	
	for (std::vector<Item*>::iterator itr = m_item.begin(); itr != m_item.end(); itr++)
	{
		//アッタチする。
		(*itr)->Attach(m_observer);
	}

	

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
	
	m_enemy->Update(stept);
	
	m_goal->Update();
	//カメラの更新	
	m_camera->Update();

	for (std::vector<Item*>::iterator itr = m_item.begin(); itr != m_item.end(); itr++)
	{
		(*itr)->Update();

		(*itr)->DetectCollision();
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
	//敵の描画
	m_enemy->Render(m_camera->GetView(), m_camera->GetProj());
	m_goal->Render(m_camera->GetView(), m_camera->GetProj());
	//画像の描画
	SpriteRender();	
	//メッシュの描画
	//m_stageMesh->DrawCollision(m_directX.GetContext().Get(), m_camera->GetView(), m_camera->GetProj());


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
	for (std::vector<Item*>::iterator itr = m_item.begin(); itr != m_item.end(); itr++)
	{

		delete (*itr);
	}

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
	// ステージとEnemyAirPlaneがあったているか
	DetectCollisionEnemyAirPlaneToMesh();
	//ステージとコインがあったているかの判定
	//DetectCollisionCoinToMesh();
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

	//コインの描画
	for (std::vector<Item*>::iterator itr = m_item.begin(); itr != m_item.end(); itr++)
	{
		(*itr)->Render(m_camera->GetView(), m_camera->GetProj());
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
	//if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxCheckPos1()) == true)
	//{
	//	int i = 0;
	//	i++;

	//	//1つ目のチェックポイントを通ったことにする
	//	m_checkPoint->Checkhit1(true);
	//}
	////ステージのチェックポイント2とMyAirPlaneがあったているのか
	//if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxCheckPos2()) == true)
	//{
	//	//2つ目のチェックポイントを通ったことにする
	//	m_checkPoint->Checkhit2(true);
	//}

	////ステージのチェックポイント3とMyAirPlaneがあったているのか
	//if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxStartPos()) == true)
	//{
	//	//3つ目のチェックポイントを通ったことにする
 //		m_checkPoint->Checkhit3(true);
	//}
}
void GameScene::DetectCollisionMyAirPlaneToCource()
{
	//自機とコースのあたり判定
	if (Collision::HitCheck_Box2Box(m_player->GetBox(), m_cource->GetBox()))
	{
		DirectX::SimpleMath::Vector3 pos = m_player->GetTranslation();

		DirectX::SimpleMath::Vector3 speed = m_player->GetVelotity();

		//あたり判定の処理
	}
}
//----------------------------------------------------------------------
//! @brief ステージのあたり判定
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
//
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


void GameScene::DetectCollisionEnemyAirPlaneToMesh()
{
	//プレイヤーの方向ベクトルの取得
	DirectX::SimpleMath::Vector3 playerVel = m_enemy->GetVelotity();
	//プレイヤーの位置の取得
	DirectX::SimpleMath::Vector3 playerPos = m_enemy->GetTranslation();

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
	m_enemy->SetTranslation(playerPos);
	//プレイヤーの速度を設定する
	m_enemy->SetVel(playerVel);
}

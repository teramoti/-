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

using namespace DirectX;
using namespace DirectX::SimpleMath;

GameScene::GameScene(SceneManager* scenemaneger)
	: SceneBase(scenemaneger, m_SceneFlag), m_GameTimer(0),
	m_CouceCount(0),m_StageNum(0), m_GoalRank(0),
	m_startFlag(false), m_SceneFlag(false) , m_goalFlag(false)
{

}

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

void GameScene::Initialize(int width, int height, ID3D11Device* device, ID3D11DeviceContext* context)
{

	m_adx2le = MyLibrary::ADX2Le::GetInstance();
	// サウンドの読み込み
	m_adx2le->LoadAcb(L"GameScene.acb", L"GameScene.awb");
	//コースのステージメッシュの初期化
	m_stageMesh = std::make_unique<CollisionMesh>(device, L"CircleCource.obj");
	//壁のステージメッシュの初期化
	m_stageMesh2 = std::make_unique<CollisionMesh>(device, L"CircleCourceOutSide.obj");


	if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	{
		// 効果音の再生
		m_criAtomExPlaybackId = m_adx2le->Play(0);
	}

	m_Camera = std::make_unique<TpsCamera>(width, height);//カメラの初期化
	MyLib::Object3D::InitielizeStatic(device, context, m_Camera.get());//Objectクラスの初期化

	m_device = device;
	m_context = context;

	//プレイヤーの生成
	m_player = std::make_unique<TestPlayer>();
	m_player->Initilize();

	//カメラの作成
	m_Camera->SetObject3D(m_player.get());

	m_CheckPoint = std::make_unique<CheckPoint>();	//チェックポイントの作成

	m_CheckPoint->Initilize();

	m_cource = std::make_unique<Cource>();//コースの作成
	m_cource->Initilize();

	m_skyDome = std::make_unique<SkyDome>();	//スカイドームクラスの作成

	m_skyDome->Initilize();

	m_time = std::make_unique<Time>();	//時間クラスの作成


	m_Count = new CountDown();//カウントダウン用クラスの初期化
	m_Count->Initilize();

	m_GameTime = new GameTime();//ゲーム時間クラスの初期化
	m_GameTime->Initilize();

	m_GoalNum = 0;//ゴール時の止める時間の初期化
}

void GameScene::Update(DX::StepTimer step)
{

	int startTime = (int)step.GetTotalSeconds();//
 	float elapsedTime = float(step.GetElapsedSeconds());
	//時間の情報
	m_GameTimer = m_time->GetTime();//タイムクラスの時間を取得
	counter--;//始まる前のＣｏｕｎｔを引く
	m_CheckPoint->Update();//チェックポイントの更新

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
		m_sceneManager->SetScene(RESULT_SCENE, 600, 800);//シーンをリザルトにする。
		return;
	}

	//カメラの更新	
	m_Camera->Update();

	m_player->Update(m_startFlag);//プレイヤーの更新
	HitManager();//当たり判定の更新用関数

	m_skyDome->Update();//スカイドームの更新
}
void GameScene::Render()
{
	m_player->Render();//プレイヤーの描画
	m_skyDome->Render();//すかいどーむの描画
	m_cource->Render();//コースの描画	SpriteRender();//画像の描画	
	SpriteRender();
	m_stageMesh->DrawCollision(m_context, m_Camera->GetView(), m_Camera->GetProj());//メッシュの描画
	m_stageMesh2->DrawCollision(m_context, m_Camera->GetView(), m_Camera->GetProj());//壁メッシュの描画

	// m_CheckPoint->Render();
}
void GameScene::Finalize()
{

}

void GameScene::HitManager()
{
	StageCheck();

}

void GameScene::SpriteRender()
{
	System::DrawManager::GetInstance().Begin();
	m_Count->Draw();
	m_GameTime->Draw(m_startFlag);
	if (m_goalFlag)
	{

	}

	System::DrawManager::GetInstance().End();
}

void GameScene::StageCheck()
{
	StageCheckPoint();
	StageCollision();
}

void GameScene::FileLoad()
{
}

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

void GameScene::StageCollision()
{
	// ボールを床の上に乗せる
	Vector3 playerrot = m_player->GetRotation();
	float playerVelY = m_player->GetVel().y;
	Vector3 playerPos = m_player->GetTranslation();


	// ボールの真下に向かう線分
	Vector3 v[2] =
	{
		Vector3(playerPos.x, 100.0f, playerPos.z),
			Vector3(playerPos.x, -100.0f, playerPos.z),
		};

		//線分と床の交差判定を行う
		int id;
		Vector3 s;
		if (m_stageMesh->HitCheck_Segment(v[0], v[1], &id, &s))
		{
			// 地面より低い位置の場合は補正する
			playerPos.y = MAX(s.y + 0.5f, playerPos.y);

			if (s.y + 0.5f > playerPos.y)
			{
				playerPos.y = s.y + 0.5f;
				playerVelY = 0.0f;

			}

		}



	m_player->SetTranslation(Vector3(playerPos.x, playerPos.y, playerPos.z));//プレイヤーの場所の更新
	m_player->SetVel(Vector3(m_player->GetVel().x, playerVelY, m_player->GetVel().z));//playerの速度を設定する。
}


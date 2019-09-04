//------------------------//------------------------
// Contents(処理内容) TitleScene.cppの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 13
// last updated (最終更新日) 2018 / 11 / 05
//------------------------//------------------------
#include <d3d11.h>


#include "TitleScene.h"

#include "../../../CheckMemory.h"

#include "../SceneManager/SceneManager.h"
#include "../../GameSystem/InputManager.h"
#include "../../GameSystem/DrawManager.h"

extern void ExitGame();



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scenemaneger"></param>
TitleScene::TitleScene(SceneManager* scenemaneger)
	: SceneBase(scenemaneger,m_SceneFlag=false),m_num(0),
	m_StartframeB(true),m_EndframeB(true)
	, m_transitionFrame(0)
{	
	//なにもしない
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	m_TitleLogo.reset();
	m_airPlane.reset();
	m_camera.reset();
	m_skyDome.reset();
	m_goalObj.reset();
	m_courceObj.reset();
	m_stageMesh.reset();
}

/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{
	//コースのステージメッシュの初期化
	m_stageMesh = std::make_unique<CollisionMesh>(m_directX11.GetDevice().Get(), L"Resources/Cource_01.obj");

	m_TitleLogo = std::make_unique<TitleLogo>();
	m_TitleLogo->Initilize();

	m_airPlane = std::make_unique<TitleAirPlane>();
	m_airPlane->Initilize();

	m_skyDome = std::make_unique<TitleSkyDome>();
	m_skyDome->Initilize();

	m_goalObj = std::make_unique<TitleGoalObject>();
	m_goalObj->Initilize();

	m_courceObj = std::make_unique<TitleCourceObject>();
	m_courceObj->Initilize();
	//m_adx2le = MyLibrary::ADX2Le::GetInstance();
	m_camera = std::make_unique<TitleTpsCamera>(800, 600);
	m_camera->SetObject3D(m_airPlane.get());


	//// サウンドの読み込み
	//m_adx2le->//LoadAcb(L"TitleScene.acb", L"TitleScene.awb");

	//if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	//{
	//	// 効果音の再生
	//	m_criAtomExPlaybackId = m_adx2le->Play(2);
	//}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="stepTimer"></param>
void TitleScene::Update(const DX::StepTimer& stepTimer)
{
	m_EndframeB = true;
	
	m_TitleLogo->Update();

	if (System::InputManager::GetInstance().GetKeyboardTracker().pressed.Space)
	{
		m_SceneFlag = true;

		// 効果音の再生
		//m_criAtomExPlaybackId = m_adx2le->Play(1);
	}
	//フラグがOnなら
	if (m_SceneFlag)
	{
		//カウントを足す
		m_transitionFrame++;
		//飛行機の移動
		m_airPlane->Update();
	}

	//カウントが60以上なら
	if (m_transitionFrame > 60)
	{	
		//m_adx2le->Stop();
		//シーンの移動
		m_sceneManager->SetScene(GAME_SCENE);
		return;

	}
	m_goalObj->Update();
	m_courceObj->Update();

	m_skyDome->Update();
	//カメラの更新	
	m_camera->Update();

	//プレイヤーの方向ベクトルの取得
	DirectX::SimpleMath::Vector3 playerVel = m_airPlane->GetVelotity();
	//プレイヤーの位置の取得
	DirectX::SimpleMath::Vector3 playerPos = m_airPlane->GetTranslation();

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
		playerPos.y = s.y + 0.6f;
		//プレイヤーの速度を0にする。s
		playerVel.y = 0.0f;
	}

	//プレイヤーの場所の更新
	m_airPlane->SetTranslation(playerPos);
	//プレイヤーの速度を設定する
	m_airPlane->SetVel(playerVel);


}
/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Render()
{		

	m_airPlane->Render(m_camera->GetView(),m_camera->GetProj());
	m_courceObj->Render(m_camera->GetView(), m_camera->GetProj());

	m_goalObj->Render(m_camera->GetView(), m_camera->GetProj());

	m_skyDome->Render(m_camera->GetView(), m_camera->GetProj());
	System::DrawManager::GetInstance().Begin();

	m_TitleLogo->Draw();


	System::DrawManager::GetInstance().End();


}

/// <summary>
/// 終了処理
/// </summary>
void TitleScene::Finalize()
{
	m_TitleLogo.reset();
	m_airPlane.reset();
	m_camera.reset();
	m_skyDome.reset();
	m_goalObj.reset();
	m_courceObj.reset();
	m_stageMesh.reset();
}

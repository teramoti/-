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
	m_StartFrame(0), m_EndFrame(0),
	m_StartframeB(true),m_EndframeB(true)
{	
	//なにもしない
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	delete m_Star;
	delete m_TitleLogo;
	delete m_GoGame;
	delete m_GoEnd;
	delete m_Aroow;
	delete m_BackGround;
	delete m_KeyDown;
	delete m_myAirPlane;
	delete m_camera;
}

/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{

	m_TitleLogo = new TitleLogo();
	m_TitleLogo->Initilize();

	m_GoGame = new TitleGoGame();
	m_GoGame->Initilize();

	m_GoEnd = new TitleGoEnd();
	m_GoEnd->Initilize();

	m_Aroow = new TitleAroow();
	m_Aroow->Initilize();

	m_BackGround = new TitleBackGround();
	m_BackGround->Initilize();

	m_KeyDown = new TitleKeyDown();
	m_KeyDown->Initilize();

	m_Star = new TitleStarEffect();
	m_Star->Initilize();

	m_myAirPlane = new MyAirPlane();
	m_myAirPlane->Initilize(nullptr);

	m_camera = new TpsCamera(800, 600);
	m_camera->SetObject3D(m_myAirPlane);
	//m_adx2le = MyLibrary::ADX2Le::GetInstance();

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
	m_Star->Update();
	m_StartFrame += 1;
	m_EndFrame = 0;
	m_EndframeB = true;

	if (m_StartFrame > 30)
	{
		m_StartframeB = !m_StartframeB;
		m_StartFrame = 0;
	}

	m_KeyDown->Update();
	m_TitleLogo->Update();

	if (m_EndFrame > 30)
	{
		m_EndframeB = !m_EndframeB;
		m_EndFrame = 0;
	}

	if (System::InputManager::GetInstance().GetKeyboardTracker().pressed.Space)
	{

		m_SceneFlag = true;
		//何もなしに初期化する.
		m_num = SERECT_ENUM::NONE;
		// 効果音の再生
		//m_criAtomExPlaybackId = m_adx2le->Play(1);
	}


	if (m_SceneFlag == true)
	{	
		//m_adx2le->Stop();

		m_sceneManager->SetScene(GAME_SCENE);
		return;

	}

	m_myAirPlane->Update(true);
}
/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Render()
{
	System::DrawManager::GetInstance().Begin();

	m_BackGround->Draw();
	m_Star->Draw();

	m_TitleLogo->Draw();
	//m_KeyDown->Draw();

	if (m_StartframeB == true)m_GoGame->Draw();

	System::DrawManager::GetInstance().End();
	//m_myAirPlane->Render(m_camera->GetView(),m_camera->GetProj());
}

/// <summary>
/// 終了処理
/// </summary>
void TitleScene::Finalize()
{
	delete m_TitleLogo;
	delete m_GoGame;
	delete m_GoEnd;

	delete m_Aroow;
	delete m_BackGround;

	delete m_KeyDown;
	delete m_Star;

	delete m_myAirPlane;
	delete m_camera;

}

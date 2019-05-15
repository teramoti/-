#include <d3d11.h>

#include "TitleScene.h"
#include "../SceneManager/SceneManager.h"
#include "../../GameSystem/InputManager.h"
#include "../../GameSystem/DrawManager.h"

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

TitleScene::TitleScene(SceneManager* scenemaneger)
	: SceneBase(scenemaneger,m_SceneFlag=false),m_num(0),
	m_StartFrame(0), m_EndFrame(0),
	m_StartframeB(true),m_EndframeB(true)
{	
	//‚È‚É‚à‚µ‚È‚¢
}

TitleScene::~TitleScene()
{
	delete m_Star;
	delete m_TitleLogo;
	delete m_GoGame;
	delete m_GoEnd;
	delete m_Aroow;
	delete m_BackGround;
	delete m_KeyDown;

}


void TitleScene::Initialize(int width, int height, ID3D11Device* device, ID3D11DeviceContext* context)
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

	m_adx2le = MyLibrary::ADX2Le::GetInstance();

	// ƒTƒEƒ“ƒh‚Ì“Ç‚Ýž‚Ý
	m_adx2le->LoadAcb(L"TitleScene.acb", L"TitleScene.awb");

	if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	{
		// Œø‰Ê‰¹‚ÌÄ¶
		m_criAtomExPlaybackId = m_adx2le->Play(2);
	}
}

void TitleScene::Update(DX::StepTimer step)
{
	m_Aroow->Update(m_num);
	m_Star->Update();
	switch (m_num)
	{
		case SERECT_ENUM::UP:
		{
			m_StartFrame += 1;
			m_EndFrame = 0;
			m_EndframeB = true;
			break;
		}

		case SERECT_ENUM::DOWN:
		{

			m_EndFrame += 1;
			m_StartFrame =0;
			m_StartframeB = true;
			break;
		}
	}

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
	if (System::InputManager::GetInstance().GetKeyboardTracker().pressed.Z)
	{
		switch (m_num)
		{
		case SERECT_ENUM::UP:
			{

				m_SceneFlag = true;
				m_num = SERECT_ENUM::NONE;//‰½‚à‚È‚µ‚É‰Šú‰»‚·‚é.
				// Œø‰Ê‰¹‚ÌÄ¶
				m_criAtomExPlaybackId = m_adx2le->Play(1);
				break;
			}
		
			case SERECT_ENUM::DOWN:
			{
				ExitGame();
				m_num = SERECT_ENUM::NONE;//‰½‚à‚È‚µ‚É‰Šú‰»‚·‚é.
				break;
			}
		}
	}


	if (m_SceneFlag == true)
	{	
		m_adx2le->Stop();

		m_sceneManager->SetScene(GAME_SCENE, 800, 600);
		return;

	}

}

void TitleScene::Render()
{
	System::DrawManager::GetInstance().Begin();

	m_BackGround->Draw();
	m_Star->Draw();

	m_TitleLogo->Draw();
	m_KeyDown->Draw();
	m_Aroow->Draw();

	if (m_StartframeB == true)m_GoGame->Draw();
	if (m_EndframeB == true)  m_GoEnd->Draw();

	System::DrawManager::GetInstance().End();
}

void TitleScene::Finalize()
{
	delete m_Star;
	delete m_TitleLogo;
	delete m_GoGame;
	delete m_GoEnd;
	delete m_Aroow;
	delete m_BackGround;
	delete m_KeyDown;
}

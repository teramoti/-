#include <d3d11.h>
#include "ResultScene.h"
#include <sstream>
#include "../../GameSystem/InputManager.h"
#include "../SceneManager/SceneManager.h"

extern void ExitGame();




ResultScene::ResultScene(SceneManager* scenemaneger): SceneBase(scenemaneger, m_SceneFlag)
{
	m_SceneFlag = false;
}

ResultScene::~ResultScene()
{
	if (m_score != nullptr)
	{
		delete m_score;
		m_score = nullptr;
	}
	if (m_space != nullptr)
	{
		delete m_space;
		m_space = nullptr;
	}
	if (m_wscore != nullptr)
	{
		delete m_wscore;
		m_wscore = nullptr;
	}
	if (m_backGorund != nullptr)
	{
		delete m_backGorund;
		m_backGorund = nullptr;
	}
	if (m_highTime != nullptr)
	{	
		delete m_highTime;
		m_highTime = nullptr;
	}
	if (m_rank != nullptr)
	{
		delete m_rank;
		m_rank = nullptr;
	}
}

void ResultScene::Initialize()
{
	m_score = new ResultTime();
	m_score->Initilize();
	m_space = new ResultKeyDown();
	m_space->Initilize();
	m_wscore = new ResultWordTime();
	m_wscore->Initilize();
	m_backGorund = new ResultBackGround();
	m_backGorund->Initilize();
	m_highTime = new ResultHighTime();
	m_highTime->Initilize();

	m_rank = new ResultRank();
	m_rank->Initilize();
	//m_adx2le = MyLibrary::ADX2Le::GetInstance();

	//// ƒTƒEƒ“ƒh‚Ì“Ç‚Ýž‚Ý
	//m_adx2le->//LoadAcb(L"ResultScene.acb", L"ResultScene.awb");
	//if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	//{
	//	// Œø‰Ê‰¹‚ÌÄ¶
	//	m_criAtomExPlaybackId = m_adx2le->Play(1);
	//}
}

void ResultScene::Update(const DX::StepTimer& step)
{
	m_score->Update(); 
	m_wscore->Update();
	m_space->Update();
	m_rank->Update();
	if (System::InputManager::GetInstance().GetKeyboardTracker().pressed.Z)
	{
		m_SceneFlag = true;
	}

		if (m_SceneFlag == true)
		{	
			m_sceneManager->SetScene(TITLE_SCENE);
		}
}

void ResultScene::Render()
{
	System::DrawManager::GetInstance().Begin();
	m_backGorund->Render();
	m_space->Draw();
	m_score->Draw();
	m_wscore->Draw();
	m_rank->Draw();
	m_highTime->Draw();
	System::DrawManager::GetInstance().End();
}

void ResultScene::Finalize()
{
	
}

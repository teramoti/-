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
	delete m_score;
	delete m_space;
	delete m_Wscore;
	delete m_BackGorund;
	delete m_HighTime;
	delete m_Rank;
}

void ResultScene::Initialize()
{
	m_score = new ResultTime();
	m_score->Initilize();
	m_space = new ResultKeyDown();
	m_space->Initilize();
	m_Wscore = new ResultWordTime();
	m_Wscore->Initilize();
	m_BackGorund = new ResultBackGorund();
	m_BackGorund->Initilize();
	m_HighTime = new ResultHighTime();
	m_HighTime->Initilize();

	m_Rank = new ResultRank();
	m_Rank->Initilize();
	//m_adx2le = MyLibrary::ADX2Le::GetInstance();

	//// ƒTƒEƒ“ƒh‚Ì“Ç‚Ýž‚Ý
	//m_adx2le->//LoadAcb(L"ResultScene.acb", L"ResultScene.awb");
	//if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	//{
	//	// Œø‰Ê‰¹‚ÌÄ¶
	//	m_criAtomExPlaybackId = m_adx2le->Play(1);
	//}
}

void ResultScene::Update(DX::StepTimer& step)
{
	m_score->Update(); 
	m_Wscore->Update();
	m_space->Update();
	m_Rank->Update();
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
	m_BackGorund->Render();
	m_space->Draw();
	m_score->Draw();
	m_Wscore->Draw();
	m_Rank->Draw();
	m_HighTime->Draw();
	System::DrawManager::GetInstance().End();
}

void ResultScene::Finalize()
{
	
}

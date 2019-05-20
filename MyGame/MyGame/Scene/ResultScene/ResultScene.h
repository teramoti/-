#pragma once
#include "../Base/SceneBase.h"
#include "../../StepTimer.h"
#include "../../GameSystem/GameSaveData.h"
#include "ResultTime.h"
#include "ResultKeyDown.h"
#include "ResultWordTime.h"
#include "ResultBackGorund.h"
#include "ResultHighTime.h"
#include "ResultRank.h"
#include "../../ADX2/ADX2Le.h"

class ResultScene : public SceneBase
{
public: 
	ResultScene(SceneManager* scenemaneger);
	~ResultScene();
public:
	// <�������֐�>
	virtual void Initialize();
	// <�X�V�֐�>
	virtual void Update(DX::StepTimer& stepTimer);
	// <�`��֐�>
	virtual void Render();
	// <�I���֐�>
	virtual void Finalize();


private:
	ResultTime* m_score;
	ResultKeyDown* m_space;
	ResultWordTime* m_Wscore;
	ResultBackGorund* m_BackGorund;
	ResultHighTime* m_HighTime;
	ResultRank* m_Rank;
	// �T�E���h
	MyLibrary::ADX2Le* m_adx2le;

	// ���y���L���p�ϐ�
	CriAtomExPlaybackId m_criAtomExPlaybackId;
};
#pragma once
#include "../Base/SceneBase.h"
#include "../../StepTimer.h"
#include "../../GameSystem/GameSaveData.h"
#include "ResultTime.h"
#include "ResultKeyDown.h"
#include "ResultWordTime.h"
#include "ResultBackGround.h"
#include "ResultHighTime.h"
#include "ResultRank.h"
//#include "../../ADX2/ADX2Le.h"

class ResultScene : public SceneBase
{
public: 
	ResultScene(SceneManager* scenemaneger);
	~ResultScene();
public:
	// <�������֐�>
	virtual void Initialize();
	// <�X�V�֐�>
	virtual void Update(const DX::StepTimer& stepTimer);
	// <�`��֐�>
	virtual void Render();
	// <�I���֐�>
	virtual void Finalize();


private:
	ResultTime* m_score;
	ResultKeyDown* m_space;
	ResultWordTime* m_wscore;
	ResultBackGround* m_backGorund;
	ResultHighTime* m_highTime;
	ResultRank* m_rank;
	// �T�E���h
	//MyLibrary::ADX2Le* m_adx2le;

	// ���y���L���p�ϐ�
	//CriAtomExPlaybackId m_criAtomExPlaybackId;
};
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
	// <初期化関数>
	virtual void Initialize();
	// <更新関数>
	virtual void Update(const DX::StepTimer& stepTimer);
	// <描画関数>
	virtual void Render();
	// <終了関数>
	virtual void Finalize();


private:
	ResultTime* m_score;
	ResultKeyDown* m_space;
	ResultWordTime* m_wscore;
	ResultBackGround* m_backGorund;
	ResultHighTime* m_highTime;
	ResultRank* m_rank;
	// サウンド
	//MyLibrary::ADX2Le* m_adx2le;

	// 音楽情報記憶用変数
	//CriAtomExPlaybackId m_criAtomExPlaybackId;
};
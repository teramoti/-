#pragma once
#include "../Base/SceneBase.h"
#include "TitleLogo.h"
#include "TitleGoGame.h"
#include "TitleGoEnd.h"
#include "TitleAroow.h"
#include "TitleBackGround.h"
#include "TitleKeyDown.h"
#include "TitleStarEffect.h"
#include "../..//ADX2/ADX2Le.h"

class TitleScene : public SceneBase
{
public: 
	enum SERECT_ENUM
	{
		UP,
		DOWN,
		NONE
	};

public: 
	TitleScene(SceneManager* scenemaneger);
	~TitleScene();
public:
	// <初期化関数>
	 void Initialize(int width, int height,ID3D11Device* device, ID3D11DeviceContext* context)override;
	// <更新関数>
	void Update(DX::StepTimer step)override;
	// <描画関数>
	void Render()override;
	// <終了関数>
	void Finalize()override;

private:
	//シーンに追加するクラス
	TitleLogo* m_TitleLogo;
	TitleGoGame* m_GoGame;
	TitleGoEnd* m_GoEnd;
	TitleAroow* m_Aroow;
	TitleBackGround* m_BackGround;
	TitleKeyDown* m_KeyDown;
	TitleStarEffect* m_Star;
private:
	//シーンに入る変数
	int m_num;
	int m_StartFrame;
	int m_EndFrame;
	//フレームの点滅bool値
	bool m_StartframeB;
	bool m_EndframeB;

	// サウンド
	MyLibrary::ADX2Le* m_adx2le;

	// 音楽情報記憶用変数
	CriAtomExPlaybackId m_criAtomExPlaybackId;
};
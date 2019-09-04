//------------------------//------------------------
// Contents(処理内容) TitleScene.hの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 13
// last updated (最終更新日) 2018 / 11 / 05
//------------------------//------------------------
#pragma once
#include "../Base/SceneBase.h"
#include "TitleLogo.h"
#include "TitleGoGame.h"
#include "TitleGoEnd.h"
#include "TitleAroow.h"
#include "TitleBackGround.h"
#include "TitleKeyDown.h"
#include "TitleTpsCamera.h"
#include "TitleAirPlane.h"
#include "TitleSkyDome.h"
#include "TtileGoal.h"
#include "TtileCource.h"

//
#include "../../Utillity/DirectX11.h"
#include "../../Collison/CollisionMesh.h"
//#include "../..//ADX2/ADX2Le.h"

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
	 void Initialize()override;
	// <更新関数>
	void Update(const DX::StepTimer& stepTimer)override;
	// <描画関数>
	void Render()override;
	// <終了関数>
	void Finalize()override;

private:
	//シーンに追加するクラス
	 std::unique_ptr<TitleLogo> m_TitleLogo;
	 std::unique_ptr<TitleBackGround> m_BackGround;
	 std::unique_ptr<TitleKeyDown> m_KeyDown;
	 std::unique_ptr<TitleTpsCamera> m_camera;
	 std::unique_ptr<TitleAirPlane> m_airPlane;
	 std::unique_ptr<TitleSkyDome> m_skyDome;
	 std::unique_ptr<TitleGoalObject> m_goalObj;
	 std::unique_ptr<TitleCourceObject> m_courceObj;

	std::unique_ptr<CollisionMesh> m_stageMesh;
private:

	DirectX11& m_directX11 = DirectX11::Get();
private:

	//シーンに入る変数
	int m_num;
	//シーンに移行用Frame
	int m_transitionFrame;
	//フレームの点滅bool値
	bool m_StartframeB;
	bool m_EndframeB;



	// サウンド
	//MyLibrary::ADX2Le* m_adx2le;

	// 音楽情報記憶用変数
	//CriAtomExPlaybackId m_criAtomExPlaybackId;
};
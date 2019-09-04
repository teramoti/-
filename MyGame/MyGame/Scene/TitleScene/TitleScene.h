//------------------------//------------------------
// Contents(�������e) TitleScene.h�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2018 / 07 / 13
// last updated (�ŏI�X�V��) 2018 / 11 / 05
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
	// <�������֐�>
	 void Initialize()override;
	// <�X�V�֐�>
	void Update(const DX::StepTimer& stepTimer)override;
	// <�`��֐�>
	void Render()override;
	// <�I���֐�>
	void Finalize()override;

private:
	//�V�[���ɒǉ�����N���X
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

	//�V�[���ɓ���ϐ�
	int m_num;
	//�V�[���Ɉڍs�pFrame
	int m_transitionFrame;
	//�t���[���̓_��bool�l
	bool m_StartframeB;
	bool m_EndframeB;



	// �T�E���h
	//MyLibrary::ADX2Le* m_adx2le;

	// ���y���L���p�ϐ�
	//CriAtomExPlaybackId m_criAtomExPlaybackId;
};
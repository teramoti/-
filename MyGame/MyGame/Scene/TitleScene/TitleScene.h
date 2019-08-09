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
	TitleLogo* m_TitleLogo;

	TitleGoGame* m_GoGame;

	TitleGoEnd* m_GoEnd;

	TitleAroow* m_Aroow;

	TitleBackGround* m_BackGround;

	TitleKeyDown* m_KeyDown;

	TitleTpsCamera* m_camera;

	TitleAirPlane* m_airPlane;

	TitleSkyDome* m_skyDome;
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
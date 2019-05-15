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
	// <�������֐�>
	 void Initialize(int width, int height,ID3D11Device* device, ID3D11DeviceContext* context)override;
	// <�X�V�֐�>
	void Update(DX::StepTimer step)override;
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
	TitleStarEffect* m_Star;
private:
	//�V�[���ɓ���ϐ�
	int m_num;
	int m_StartFrame;
	int m_EndFrame;
	//�t���[���̓_��bool�l
	bool m_StartframeB;
	bool m_EndframeB;

	// �T�E���h
	MyLibrary::ADX2Le* m_adx2le;

	// ���y���L���p�ϐ�
	CriAtomExPlaybackId m_criAtomExPlaybackId;
};
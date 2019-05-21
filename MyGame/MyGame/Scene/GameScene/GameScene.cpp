//------------------------//------------------------
// Contents(�������e) GameScene.cpp�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2018 / 07 / 13
// last updated (�ŏI�X�V��) 2018 / 11 / 05
//------------------------//------------------------

//�C���N���[�h�t�@�C���̐錾
#include <d3d11.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include "Gamescene.h"
#include "../../GameSystem/GameSaveData.h"
#include "../../GameSystem/DrawManager.h"
#include "../../GameSystem/InputManager.h"
#include "../SceneManager/SceneManager.h"


#define MIN(a,b) ((a>b) ? (b):(a));
#define MAX(a,b) ((a>b) ? (a):(b));
//----------------------------------------------------------------------
//! @brief �Q�[���V�[���N���X�̃R���X�g���N�^
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------

GameScene::GameScene(SceneManager* scenemaneger)
	: SceneBase(scenemaneger, m_SceneFlag), m_GameTimer(0),
	m_CouceCount(0),m_StageNum(0), m_GoalRank(0),
	m_startFlag(false), m_SceneFlag(false) , m_goalFlag(false)
{

}

//----------------------------------------------------------------------
//! @brief �Q�[���V�[���̃f�X�g���N�^
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
GameScene::~GameScene()
{
	m_Camera.reset();
	m_player.reset();
	m_skyDome.reset();
	m_states.reset();

	m_time.reset();
	m_CheckPoint.reset();

	delete m_Count;
	delete m_GameTime;
}

//----------------------------------------------------------------------
//! @brief �Q�[���V�[���̏���������
//!
//! @param windth,height,devive,context
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameScene::Initialize()
{

	m_adx2le = MyLibrary::ADX2Le::GetInstance();
	// �T�E���h�̓ǂݍ���
	m_adx2le->LoadAcb(L"GameScene.acb", L"GameScene.awb");
	//�R�[�X�̃X�e�[�W���b�V���̏�����
	m_stageMesh = std::make_unique<CollisionMesh>(m_directX.GetDevice().Get() , L"Resources/CircleCource.obj");

	if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	{
		// ���ʉ��̍Đ�
		m_criAtomExPlaybackId = m_adx2le->Play(0);
	}

	//Camera�N���X�̏�����
	m_Camera = std::make_unique<TpsCamera>(m_directX.GetWidth(), m_directX.GetHeight());

	//Object�N���X�̏�����
	MyLib::Object3D::InitielizeStatic(m_directX.GetDevice().Get(), m_directX.GetContext().Get(), m_Camera.get());

	//�v���C���[�̐���
	m_player = std::make_unique<TestPlayer>();
	//Player�̏���������
	m_player->Initilize();

	//�J������Target�̐ݒ�
	m_Camera->SetObject3D(m_player.get());

	//�`�F�b�N�|�C���g�̍쐬
	m_CheckPoint = std::make_unique<CheckPoint>();
	//�`�F�b�N�|�C���g�̏���������
	m_CheckPoint->Initilize();


	//�R�[�X�N���X�̍쐬
	m_cource = std::make_unique<Cource>();
	//�R�[�X�N���X�̏���������
	m_cource->Initilize();

	//�X�J�C�h�[���N���X�̍쐬
	m_skyDome = std::make_unique<SkyDome>();
	//�X�J�C�h�[���N���X�̏���������
	m_skyDome->Initilize();

	//���ԃN���X�̍쐬
	m_time = std::make_unique<Time>();


	//�J�E���g�_�E���N���X�̍쐬
	m_Count = new CountDown();
	//�J�E���g�_�E���N���X�̏�����
	m_Count->Initilize();


	//�Q�[�����ԃN���X�̍쐬
	m_GameTime = new GameTime();
	//�Q�[�����ԃN���X�̏�����
	m_GameTime->Initilize();

//�S�[�����̎~�߂鎞�Ԃ̏�����
	m_GoalNum = 0;
}

//----------------------------------------------------------------------
//! @brief �Q�[���V�[���̍X�V����
//!
//! @param steptimer
//!
//! @return �Ȃ�
//----------------------------------------------------------------------

void GameScene::Update(DX::StepTimer& stepTimer)
{

	int startTime = (int)stepTimer.GetTotalSeconds();//�Q�[���̊J�n���Ԃ̎擾
 	float elapsedTime = float(stepTimer.GetElapsedSeconds());
	//���Ԃ̏��
	m_GameTimer = m_time->GetTime();//�^�C���N���X�̎��Ԃ��擾
	counter--;//�n�܂�O�̂b��������������
	m_CheckPoint->Update();//�`�F�b�N�|�C���g�̍X�V
	m_skyDome->Update();//�X�J�C�h�[���̍X�V

	if (counter < 0)
	{
		if (m_goalFlag == false)
		{
			m_time->Update(m_GameTimer);//���Ԃ̍X�V
			m_GameTime->SetTime(m_GameTimer);//�Q�[���̎��Ԃ��b���������_�E������
			m_startFlag = true;//�n�܂�t���O��true�ɂ���

		}	

	}
	else
	{
		m_Count->SetTime(counter);
	}

	if (m_CheckPoint->GetFlag() == true)
	{
		m_time->SetFlag(false);
		m_GoalNum += 1;
		m_goalFlag = true;

	}
	//60�b�������狭���I�Ƀ��U���g�ɍs������
	if (m_GameTimer >= 6000)
	{
		m_time->SetFlag(false);

		m_GameTimer = 6000;//�Q�[�����Ԃ�60�b�ɂ���B

		m_SceneFlag = true;

	}

	//���U���g�ɃV�[���������Ă���
	GameSaveData::GetInstance().SetGoal1Time(m_GameTimer);

	//GameSaveData::GetInstance().SetRank(m_GoalRank);

	m_cource->Update();//�R�[�X�̍X�V����
	if (m_GoalNum > 40)
	{
		m_SceneFlag = true;
	}
	if (m_SceneFlag == true)
	{
		//Result���Z�b�g����
		m_adx2le->Stop();
		m_sceneManager->SetScene(RESULT_SCENE);//�V�[�������U���g�ɂ���B
		return;
	}

	//�J�����̍X�V	
	m_Camera->Update();

	m_player->Update(m_startFlag);//�v���C���[�̍X�V
	HitManager();//�����蔻��̍X�V�p�֐�

}
//----------------------------------------------------------------------
//! @brief �Q�[���V�[���̕`��p�֐�
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameScene::Render()
{
	m_player->Render();//�v���C���[�̕`��
	m_skyDome->Render();//�������ǁ[�ނ̕`��
	m_cource->Render();//�R�[�X�̕`��
	SpriteRender();	//�摜�̕`��	
	m_stageMesh->DrawCollision(m_directX.GetContext().Get(), m_Camera->GetView(), m_Camera->GetProj());//���b�V���̕`��
}
//----------------------------------------------------------------------
//! @brief �Q�[���V�[���̏I������
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------

void GameScene::Finalize()
{

}

//----------------------------------------------------------------------
//! @brief �����蔻����܂Ƃ߂�悤�֐�
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameScene::HitManager()
{
	StageCheckPoint();
	StageCollision();

}

//----------------------------------------------------------------------
//! @brief �摜�̕`��p�֐�
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameScene::SpriteRender()
{
	System::DrawManager::GetInstance().Begin();
	m_Count->Draw();//�J�E���g��`�悷��
	m_GameTime->Draw(m_startFlag);
	if (m_goalFlag)
	{
		//�S�[���̕������o��

	}

	System::DrawManager::GetInstance().End();
}

//----------------------------------------------------------------------
//! @brief �X�e�[�W�̃`�F�b�N�|�C���g�֐�
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------

void GameScene::StageCheckPoint()
{
	if (m_CollisionManager->CollisionBox2Box(m_player->GetBox(), m_CheckPoint->GetBoxCheckPos1()) == true)
	{
		m_CheckPoint->Checkhit1(true);
	}
	if (m_CollisionManager->CollisionBox2Box(m_player->GetBox(), m_CheckPoint->GetBoxCheckPos2()) == true)
	{
		m_CheckPoint->Checkhit2(true);
	}
	if (m_CollisionManager->CollisionBox2Box(m_player->GetBox(), m_CheckPoint->GetBoxStartPos()) == true)
	{
		m_CheckPoint->Checkhit3(true);
	}

}
//----------------------------------------------------------------------
//! @brief �X�e�[�W�̂����蔻��
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------

void GameScene::StageCollision()
{
	DirectX::SimpleMath::Vector3 playerVel = m_player->GetVel();
	DirectX::SimpleMath::Vector3 playerPos = m_player->GetTranslation();


	// �{�[���̐^���Ɍ���������
	DirectX::SimpleMath::Vector3 v[2] =
	{
		DirectX::SimpleMath::Vector3(playerPos.x, 100.0f, playerPos.z),
		DirectX::SimpleMath::Vector3(playerPos.x, -100.0f, playerPos.z),
		};

		//�����Ə��̌���������s��
		int id;
		DirectX::SimpleMath::Vector3 s;
		if (m_stageMesh->HitCheck_Segment(v[0], v[1], &id, &s))
		{
				playerPos.y = s.y + PLAYER_RISE;
				playerVel.y = 0.0f;
		}

	m_player->SetTranslation(playerPos);//�v���C���[�̏ꏊ�̍X�V
	m_player->SetVel(playerVel);//�v���C���[�̑��x��ݒ肷��B
}


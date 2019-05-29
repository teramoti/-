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
	: SceneBase(scenemaneger, m_SceneFlag), m_gameTimer(0),
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
	m_camera.reset();
	m_player.reset();
	m_skyDome.reset();
	m_states.reset();

	m_time.reset();
	m_checkPoint.reset();

	delete m_count;
	delete m_gameTime;
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

	//m_adx2le = MyLibrary::ADX2Le::GetInstance();
	// �T�E���h�̓ǂݍ���
	//m_adx2le->LoadAcb(L"GameScene.acb", L"GameScene.awb");
	//�R�[�X�̃X�e�[�W���b�V���̏�����
	m_stageMesh = std::make_unique<CollisionMesh>(m_directX.GetDevice().Get() , L"Resources/CircleCource.obj");

	//if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	//{
	//	// ���ʉ��̍Đ�
	//	m_criAtomExPlaybackId = m_adx2le->Play(0);
	//}

	//Camera�N���X�̏�����
	m_camera = std::make_unique<TpsCamera>(m_directX.GetWidth(), m_directX.GetHeight());
	m_shadow = new Shadow();
	//m_shadow->Initialize();
	//�v���C���[�̐���
	m_player = std::make_unique<Player>();
	//Player�̏���������
	m_player->Initilize(m_shadow);

	//�J������Target�̐ݒ�
	m_camera->SetObject3D(m_player.get());

	//�`�F�b�N�|�C���g�̍쐬
	m_checkPoint = std::make_unique<CheckPoint>();
	//�`�F�b�N�|�C���g�̏���������
	m_checkPoint->Initilize();


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
	m_count = new CountDown();
	//�J�E���g�_�E���N���X�̏�����
	m_count->Initilize();

	//�Q�[�����ԃN���X�̍쐬
	m_gameTime = new GameTime();
	//�Q�[�����ԃN���X�̏�����
	m_gameTime->Initilize();


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

void GameScene::Update(const DX::StepTimer& stepTimer)
{

	//�Q�[���̊J�n���Ԃ̎擾
	int startTime = (int)stepTimer.GetTotalSeconds();
	//���Ԃ̏��

	//�^�C���N���X�̎��Ԃ��擾
	m_gameTimer = m_time->GetTime();
	//�������O��Count������
	counter--;
	//�`�F�b�N�|�C���g�̍X�V
	m_checkPoint->Update();
	//�X�J�C�h�[���̍X�V
	m_skyDome->Update();

	if (counter < 0)
	{
		if (m_goalFlag == false)
		{
			//���Ԃ̍X�V
			m_time->Update(m_gameTimer);
			//�Q�[���̎��Ԃ��b���������_�E������
			m_gameTime->SetTime(m_gameTimer);
			//�������t���O��true�ɂ���
			m_startFlag = true;
		}	
	}
	else
	{
		//�^�C�}�[�̐ݒ������B
		m_count->SetTime(counter);
	}

	//�v���C���[���`�F�b�N�|�C���g�����ׂĒʂ����̂�
	if (m_checkPoint->GetFlag() == true)
	{
		m_time->SetFlag(false);
		m_GoalNum += 1;
		m_goalFlag = true;

	}
	//60�b�������狭���I�Ƀ��U���g�ɍs������
	if (m_gameTimer >= 6000)
	{
		m_time->SetFlag(false);

		//�Q�[�����Ԃ�60�b�ɂ���
		m_gameTimer = 6000;

		m_SceneFlag = true;

	}

	//���U���g�ɃV�[���������Ă���
	GameSaveData::GetInstance().SetGoal1Time(m_gameTimer);

	//�R�[�X�̍X�V����
	m_cource->Update();
	
	if (m_GoalNum > 40)
	{
		m_SceneFlag = true;
	}
	if (m_SceneFlag == true)
	{
		//�V�[�������U���g�ɂ���
		m_sceneManager->SetScene(RESULT_SCENE);
		return;
	}

	//�J�����̍X�V	
	m_camera->Update();

	//�v���C���[�̍X�V
	m_player->Update(m_startFlag);
	//�����蔻��̍X�V�p�֐�
	DetectCollisionManager();

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
	//�v���C���[�̕`��
	m_player->Render(m_camera->GetView(),m_camera->GetProj());
<<<<<<< HEAD
	m_shadow->Render(m_camera->GetView(), m_camera->GetProj(),m_player.get());
=======
>>>>>>> 44105518dbb6f25c151be9ebdc146f28eef5a8a7
	//�X�J�C�h�[���̕`��
	m_skyDome->Render(m_camera->GetView(), m_camera->GetProj());
	//�R�[�X�̕`��
	m_cource->Render(m_camera->GetView(), m_camera->GetProj());
	//�摜�̕`��
	SpriteRender();		
	//���b�V���̕`��
<<<<<<< HEAD
	m_stageMesh->DrawCollision(m_directX.GetContext().Get(), m_camera->GetView(), m_camera->GetProj());
=======
	//m_stageMesh->DrawCollision(m_directX.GetContext().Get(), m_camera->GetView(), m_camera->GetProj());
>>>>>>> 44105518dbb6f25c151be9ebdc146f28eef5a8a7
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
void GameScene::DetectCollisionManager()
{
	// �X�e�[�W�̃`�F�b�N�|�C���g��Player���������Ă��邩
	DetectCollisionPlayerToCheckPoint();
	// �X�e�[�W��Mesh��Player���������Ă��邩
	DetectCollisionPlayerToMesh();

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
	//�J�E���g��`�悷��
	m_count->Draw();
	//�S�[�����Ԃ̕`��
	m_gameTime->Draw(m_startFlag);
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
void GameScene::DetectCollisionPlayerToCheckPoint()
{
	//�X�e�[�W�̃`�F�b�N�|�C���g1��Player���������Ă���̂�
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxCheckPos1()) == true)
	{
		//1�ڂ̃`�F�b�N�|�C���g��ʂ������Ƃɂ���
		m_checkPoint->Checkhit1(true);
	}
	//�X�e�[�W�̃`�F�b�N�|�C���g2��Player���������Ă���̂�
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxCheckPos2()) == true)
	{
		//2�ڂ̃`�F�b�N�|�C���g��ʂ������Ƃɂ���
		m_checkPoint->Checkhit2(true);
	}
	//�X�e�[�W�̃`�F�b�N�|�C���g3��Player���������Ă���̂�
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxStartPos()) == true)
	{
		//3�ڂ̃`�F�b�N�|�C���g��ʂ������Ƃɂ���
		m_checkPoint->Checkhit3(true);
	}

}
//----------------------------------------------------------------------
//! @brief �X�e�[�W�̂����蔻��
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------

void GameScene::DetectCollisionPlayerToMesh()
{
	//�v���C���[�̕����x�N�g���̎擾
	DirectX::SimpleMath::Vector3 playerVel = m_player->GetVelotity();
	//�v���C���[�̈ʒu�̎擾
	DirectX::SimpleMath::Vector3 playerPos = m_player->GetTranslation();





	// �v���C���[�̐^���Ɍ���������
	DirectX::SimpleMath::Vector3 v[2] =
	{
		DirectX::SimpleMath::Vector3(playerPos.x, 100.0f, playerPos.z),
		DirectX::SimpleMath::Vector3(playerPos.x, -100.0f, playerPos.z),
	};

	// �v���C���[�̊O�g�Ɍ���������
	DirectX::SimpleMath::Vector3 feller[2] =
	{
		DirectX::SimpleMath::Vector3(playerPos.x, 100.0f, playerPos.z),
		DirectX::SimpleMath::Vector3(playerPos.x, -100.0f, playerPos.z),
	};


	//�����Ə��̌���������s��
	int id;
	DirectX::SimpleMath::Vector3 s;
	if (m_stageMesh->HitCheck_Segment(v[0], v[1], &id, &s))
	{
		//�v���C���[�̃|�W�V����y�������b�V���̔��蕪+�v���C���[�̍�����������
		playerPos.y = s.y + PLAYER_RISE;
		playerVel.y = 0.0f;
	}
	else
	{

	}

	//�v���C���[�̏ꏊ�̍X�V
	m_player->SetTranslation(playerPos);
	//�v���C���[�̑��x��ݒ肷��
	m_player->SetVel(playerVel);
}

void GameScene::UpdatePlayerFeller()
{
	/*
	//feeler pointing straight in front
	m_Feelers[0] = m_pVehicle->Pos() + m_dWallDetectionFeelerLength * m_pVehicle->Heading();

	//feeler to left
	Vector2D temp = m_pVehicle->Heading();
	Vec2DRotateAroundOrigin(temp, HalfPi * 3.5f);
	m_Feelers[1] = m_pVehicle->Pos() + m_dWallDetectionFeelerLength/2.0f * temp;

	//feeler to right
	temp = m_pVehicle->Heading();
	Vec2DRotateAroundOrigin(temp, HalfPi * 0.5f);
	m_Feelers[2] = m_pVehicle->Pos() + m_dWallDetectionFeelerLength/2.0f * temp;
	*/

	m_feelers.resize(3);
	m_feelers[0] = DirectX::SimpleMath::Vector3(m_player->GetTranslation().x + 10.0f * m_player->GetAngle(),
		m_player->GetTranslation().y + 10.0f * m_player->GetAngle(),
		m_player->GetTranslation().z + 10.0f * m_player->GetAngle());

	DirectX::SimpleMath::Vector3 temp;


	m_feelers[1] = DirectX::SimpleMath::Vector3(m_player->GetTranslation().x + 10.0f * m_player->GetAngle(),
		m_player->GetTranslation().y + 10.0f * m_player->GetAngle(),
		m_player->GetTranslation().z + 10.0f * m_player->GetAngle());



}


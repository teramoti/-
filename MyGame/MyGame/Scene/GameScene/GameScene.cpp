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
#include<random>


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
	m_couceCount(0),m_stageNum(0),  m_playerHeight(0.0f),
	m_startFlag(false), m_sceneFlag(false) , m_goalFlag(false),m_isUpdateing(false)

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
	for (std::vector<Item*>::iterator itr = m_item.begin(); itr != m_item.end(); itr++)
	{
		delete (*itr);
	}
	delete m_itemManager;
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
	m_stageMesh = std::make_unique<CollisionMesh>(m_directX.GetDevice().Get() , L"Resources/Cource_01.obj");
	//m_stageMesh2 = std::make_unique<CollisionMesh>(m_directX.GetDevice().Get(), L"Resources/OutsidetheMyGameCourse_1.obj");
	//if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	//{
	//	// ���ʉ��̍Đ�
	//	m_criAtomExPlaybackId = m_adx2le->Play(0);
	//}

	m_itemManager = new ItemManager();
	m_itemManager->Initilize();

	//�ꏊ�̃����_��
	
	// �񌈒�I�ȗ���������𐶐�
	std::random_device rnd;
	 // �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l	
	std::mt19937 mt(rnd());
	// [0, 99] �͈͂̈�l����
	std::uniform_int_distribution<> randx(-100,1050);
	std::uniform_int_distribution<> randz(-480, 600);

	m_item.resize(100);
	for (int i = 0; i < m_item.size(); i++)
	{
		m_item[i] = new Item(DirectX::SimpleMath::Vector3(randx(mt),-3.0f, randz(mt)));
	}

	for (std::vector<Item*>::iterator itr = m_item.begin(); itr != m_item.end(); itr++)
	{
		(*itr)->Initilize(*m_itemManager);
	}

	//Camera�N���X�̏�����
	m_camera = std::make_unique<TpsCamera>(m_directX.GetWidth(), m_directX.GetHeight());
	m_shadow = new Shadow();
	//m_shadow->Initialize();
	//�v���C���[�̐���
	m_player = std::make_unique<MyAirPlane>();
	//MyAirPlane�̏���������
	m_player->Initilize(m_shadow);

	//Enemy�̐���
	m_enemy= std::make_unique<EnemyAirPlane>();
	//EnemyAirPlane�̏���������
	m_enemy->Initilize();	
	
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
	m_goalNum = 0;
	m_isUpdateing = false;

	m_collisionManager = new CollisionManager();

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
	m_isUpdateing = true;


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
			//�Q�[���̎��Ԃ�Count�_�E������
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
		m_goalNum += 1;
		m_goalFlag = true;

		//�J�������[�N��ς���


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
	//m_cource->Update();
	
	if (m_goalNum > 40)
	{
		m_SceneFlag = true;
	}
	if (m_SceneFlag == true)
	{
		//�V�[�������U���g�ɂ���
		m_sceneManager->SetScene(RESULT_SCENE);
		return;
	}
	//�v���C���[�̍X�V
	m_player->Update(m_startFlag);
	
	//m_enemy->Update(stept);
	
	//�J�����̍X�V	
	m_camera->Update();

	for (std::vector<Item*>::iterator itr = m_item.begin(); itr != m_item.end(); itr++)
	{
		(*itr)->Update();
	}
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
	if (!m_isUpdateing)
	{
		return;
	}

	//�X�J�C�h�[���̕`��
	m_skyDome->Render(m_camera->GetView(), m_camera->GetProj());
	
	//�R�[�X�̕`��
	m_cource->Render(m_camera->GetView(), m_camera->GetProj());	
	
	//�v���C���[�̕`��	
	m_player->Render(m_camera->GetView(),m_camera->GetProj());
	//�v���C���[�̉e�`��
	m_shadow->Render(m_camera.get()->GetView(), m_camera->GetProj(), m_player.get(), PLAYER_HEIGHT);
	//�G�̕`��
	//m_enemy->Render(m_camera->GetView(), m_camera->GetProj());
	//�摜�̕`��
	SpriteRender();		
	m_checkPoint->Render(m_camera.get()->GetView(), m_camera->GetProj());
	//���b�V���̕`��
	m_stageMesh->DrawCollision(m_directX.GetContext().Get(), m_camera->GetView(), m_camera->GetProj());
	//�R�C���̕`��
	for (std::vector<Item*>::iterator itr = m_item.begin(); itr != m_item.end(); itr++)
	{
		(*itr)->Render(m_camera->GetView(), m_camera->GetProj());
	}

	//�摜�̕`��
	SpriteRender();		

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
	// �X�e�[�W�̃`�F�b�N�|�C���g��MyAirPlane���������Ă��邩
	DetectCollisionMyAirPlaneToCheckPoint();
	// �X�e�[�W��Mesh��MyAirPlane���������Ă��邩
	DetectCollisionMyAirPlaneToMesh();
	// �X�e�[�W��MyAirPlane���������Ă��邩
	DetectCollisionMyAirPlaneToCource();
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
void GameScene::DetectCollisionMyAirPlaneToCheckPoint()
{
	//�X�e�[�W�̃`�F�b�N�|�C���g1��MyAirPlane���������Ă���̂�
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxCheckPos1()) == true)
	{
		int i = 0;
		i++;

		//1�ڂ̃`�F�b�N�|�C���g��ʂ������Ƃɂ���
		m_checkPoint->Checkhit1(true);
	}
	//�X�e�[�W�̃`�F�b�N�|�C���g2��MyAirPlane���������Ă���̂�
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxCheckPos2()) == true)
	{
		//2�ڂ̃`�F�b�N�|�C���g��ʂ������Ƃɂ���
		m_checkPoint->Checkhit2(true);
	}

	//�X�e�[�W�̃`�F�b�N�|�C���g3��MyAirPlane���������Ă���̂�
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_checkPoint->GetBoxStartPos()) == true)
	{
		//3�ڂ̃`�F�b�N�|�C���g��ʂ������Ƃɂ���
 		m_checkPoint->Checkhit3(true);
	}
}
void GameScene::DetectCollisionMyAirPlaneToCource()
{
	if (m_collisionManager->CollisionBox2Box(m_player->GetBox(), m_cource->GetBox())==true)
	{
		m_player->SetScale(DirectX::SimpleMath::Vector3(3,3,3));
	}
	else
	{
		m_player->SetScale(DirectX::SimpleMath::Vector3(1,1,1));

	}
}
//----------------------------------------------------------------------
//! @brief �X�e�[�W�̂����蔻��
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------

void GameScene::DetectCollisionMyAirPlaneToMesh()
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


	//�����Ə��̌���������s��
	int id;

	DirectX::SimpleMath::Vector3 s;

	if (m_stageMesh->HitCheck_Segment(v[0], v[1], &id, &s))
	{
		//�v���C���[�̃|�W�V����y�������b�V���̔��蕪+�v���C���[�̍�����������
		playerPos.y = s.y + PLAYER_HEIGHT;
		//�v���C���[�̑��x��0�ɂ���Bs
		playerVel.y = 0.0f;
	}

	//�v���C���[�̏ꏊ�̍X�V
	m_player->SetTranslation(playerPos);
	//�v���C���[�̑��x��ݒ肷��
	m_player->SetVel(playerVel);
}


//void GameScene::DetectCollisionEnemyAirPlaneToMesh()
//{
//	//�v���C���[�̕����x�N�g���̎擾
//	DirectX::SimpleMath::Vector3 playerVel = m_enemy->GetVelotity();
//	//�v���C���[�̈ʒu�̎擾
//	DirectX::SimpleMath::Vector3 playerPos = m_enemy->GetTranslation();
//
//	// �v���C���[�̐^���Ɍ���������
//	DirectX::SimpleMath::Vector3 v[2] =
//	{
//		DirectX::SimpleMath::Vector3(playerPos.x, 100.0f, playerPos.z),
//		DirectX::SimpleMath::Vector3(playerPos.x, -100.0f, playerPos.z),
//	};
//
//
//	//�����Ə��̌���������s��
//	int id;
//
//	DirectX::SimpleMath::Vector3 s;
//
//	if (m_stageMesh->HitCheck_Segment(v[0], v[1], &id, &s))
//	{
//		//�v���C���[�̃|�W�V����y�������b�V���̔��蕪+�v���C���[�̍�����������
//		playerPos.y = s.y + PLAYER_HEIGHT;
//		//�v���C���[�̑��x��0�ɂ���Bs
//		playerVel.y = 0.0f;
//	}
//
//	//�v���C���[�̏ꏊ�̍X�V
//	m_enemy->SetTranslation(playerPos);
//	//�v���C���[�̑��x��ݒ肷��
//	m_enemy->SetVel(playerVel);
//}

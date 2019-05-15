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

using namespace DirectX;
using namespace DirectX::SimpleMath;

GameScene::GameScene(SceneManager* scenemaneger)
	: SceneBase(scenemaneger, m_SceneFlag), m_GameTimer(0),
	m_CouceCount(0),m_StageNum(0), m_GoalRank(0),
	m_startFlag(false), m_SceneFlag(false) , m_goalFlag(false)
{

}

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

void GameScene::Initialize(int width, int height, ID3D11Device* device, ID3D11DeviceContext* context)
{

	m_adx2le = MyLibrary::ADX2Le::GetInstance();
	// �T�E���h�̓ǂݍ���
	m_adx2le->LoadAcb(L"GameScene.acb", L"GameScene.awb");
	//�R�[�X�̃X�e�[�W���b�V���̏�����
	m_stageMesh = std::make_unique<CollisionMesh>(device, L"CircleCource.obj");
	//�ǂ̃X�e�[�W���b�V���̏�����
	m_stageMesh2 = std::make_unique<CollisionMesh>(device, L"CircleCourceOutSide.obj");


	if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	{
		// ���ʉ��̍Đ�
		m_criAtomExPlaybackId = m_adx2le->Play(0);
	}

	m_Camera = std::make_unique<TpsCamera>(width, height);//�J�����̏�����
	MyLib::Object3D::InitielizeStatic(device, context, m_Camera.get());//Object�N���X�̏�����

	m_device = device;
	m_context = context;

	//�v���C���[�̐���
	m_player = std::make_unique<TestPlayer>();
	m_player->Initilize();

	//�J�����̍쐬
	m_Camera->SetObject3D(m_player.get());

	m_CheckPoint = std::make_unique<CheckPoint>();	//�`�F�b�N�|�C���g�̍쐬

	m_CheckPoint->Initilize();

	m_cource = std::make_unique<Cource>();//�R�[�X�̍쐬
	m_cource->Initilize();

	m_skyDome = std::make_unique<SkyDome>();	//�X�J�C�h�[���N���X�̍쐬

	m_skyDome->Initilize();

	m_time = std::make_unique<Time>();	//���ԃN���X�̍쐬


	m_Count = new CountDown();//�J�E���g�_�E���p�N���X�̏�����
	m_Count->Initilize();

	m_GameTime = new GameTime();//�Q�[�����ԃN���X�̏�����
	m_GameTime->Initilize();

	m_GoalNum = 0;//�S�[�����̎~�߂鎞�Ԃ̏�����
}

void GameScene::Update(DX::StepTimer step)
{

	int startTime = (int)step.GetTotalSeconds();//
 	float elapsedTime = float(step.GetElapsedSeconds());
	//���Ԃ̏��
	m_GameTimer = m_time->GetTime();//�^�C���N���X�̎��Ԃ��擾
	counter--;//�n�܂�O�̂b��������������
	m_CheckPoint->Update();//�`�F�b�N�|�C���g�̍X�V

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
		m_sceneManager->SetScene(RESULT_SCENE, 600, 800);//�V�[�������U���g�ɂ���B
		return;
	}

	//�J�����̍X�V	
	m_Camera->Update();

	m_player->Update(m_startFlag);//�v���C���[�̍X�V
	HitManager();//�����蔻��̍X�V�p�֐�

	m_skyDome->Update();//�X�J�C�h�[���̍X�V
}
void GameScene::Render()
{
	m_player->Render();//�v���C���[�̕`��
	m_skyDome->Render();//�������ǁ[�ނ̕`��
	m_cource->Render();//�R�[�X�̕`��	SpriteRender();//�摜�̕`��	
	SpriteRender();
	m_stageMesh->DrawCollision(m_context, m_Camera->GetView(), m_Camera->GetProj());//���b�V���̕`��
	m_stageMesh2->DrawCollision(m_context, m_Camera->GetView(), m_Camera->GetProj());//�ǃ��b�V���̕`��

	// m_CheckPoint->Render();
}
void GameScene::Finalize()
{

}

void GameScene::HitManager()
{
	StageCheck();

}

void GameScene::SpriteRender()
{
	System::DrawManager::GetInstance().Begin();
	m_Count->Draw();
	m_GameTime->Draw(m_startFlag);
	if (m_goalFlag)
	{

	}

	System::DrawManager::GetInstance().End();
}

void GameScene::StageCheck()
{
	StageCheckPoint();
	StageCollision();
}

void GameScene::FileLoad()
{
}

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

void GameScene::StageCollision()
{
	// �{�[�������̏�ɏ悹��
	Vector3 playerrot = m_player->GetRotation();
	float playerVelY = m_player->GetVel().y;
	Vector3 playerPos = m_player->GetTranslation();


	// �{�[���̐^���Ɍ���������
	Vector3 v[2] =
	{
		Vector3(playerPos.x, 100.0f, playerPos.z),
			Vector3(playerPos.x, -100.0f, playerPos.z),
		};

		//�����Ə��̌���������s��
		int id;
		Vector3 s;
		if (m_stageMesh->HitCheck_Segment(v[0], v[1], &id, &s))
		{
			// �n�ʂ��Ⴂ�ʒu�̏ꍇ�͕␳����
			playerPos.y = MAX(s.y + 0.5f, playerPos.y);

			if (s.y + 0.5f > playerPos.y)
			{
				playerPos.y = s.y + 0.5f;
				playerVelY = 0.0f;

			}

		}



	m_player->SetTranslation(Vector3(playerPos.x, playerPos.y, playerPos.z));//�v���C���[�̏ꏊ�̍X�V
	m_player->SetVel(Vector3(m_player->GetVel().x, playerVelY, m_player->GetVel().z));//player�̑��x��ݒ肷��B
}


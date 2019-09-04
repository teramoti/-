//------------------------//------------------------
// Contents(�������e) TitleScene.cpp�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2018 / 07 / 13
// last updated (�ŏI�X�V��) 2018 / 11 / 05
//------------------------//------------------------
#include <d3d11.h>


#include "TitleScene.h"

#include "../../../CheckMemory.h"

#include "../SceneManager/SceneManager.h"
#include "../../GameSystem/InputManager.h"
#include "../../GameSystem/DrawManager.h"

extern void ExitGame();



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scenemaneger"></param>
TitleScene::TitleScene(SceneManager* scenemaneger)
	: SceneBase(scenemaneger,m_SceneFlag=false),m_num(0),
	m_StartframeB(true),m_EndframeB(true)
	, m_transitionFrame(0)
{	
	//�Ȃɂ����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
	m_TitleLogo.reset();
	m_airPlane.reset();
	m_camera.reset();
	m_skyDome.reset();
	m_goalObj.reset();
	m_courceObj.reset();
	m_stageMesh.reset();
}

/// <summary>
/// ����������
/// </summary>
void TitleScene::Initialize()
{
	//�R�[�X�̃X�e�[�W���b�V���̏�����
	m_stageMesh = std::make_unique<CollisionMesh>(m_directX11.GetDevice().Get(), L"Resources/Cource_01.obj");

	m_TitleLogo = std::make_unique<TitleLogo>();
	m_TitleLogo->Initilize();

	m_airPlane = std::make_unique<TitleAirPlane>();
	m_airPlane->Initilize();

	m_skyDome = std::make_unique<TitleSkyDome>();
	m_skyDome->Initilize();

	m_goalObj = std::make_unique<TitleGoalObject>();
	m_goalObj->Initilize();

	m_courceObj = std::make_unique<TitleCourceObject>();
	m_courceObj->Initilize();
	//m_adx2le = MyLibrary::ADX2Le::GetInstance();
	m_camera = std::make_unique<TitleTpsCamera>(800, 600);
	m_camera->SetObject3D(m_airPlane.get());


	//// �T�E���h�̓ǂݍ���
	//m_adx2le->//LoadAcb(L"TitleScene.acb", L"TitleScene.awb");

	//if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
	//{
	//	// ���ʉ��̍Đ�
	//	m_criAtomExPlaybackId = m_adx2le->Play(2);
	//}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="stepTimer"></param>
void TitleScene::Update(const DX::StepTimer& stepTimer)
{
	m_EndframeB = true;
	
	m_TitleLogo->Update();

	if (System::InputManager::GetInstance().GetKeyboardTracker().pressed.Space)
	{
		m_SceneFlag = true;

		// ���ʉ��̍Đ�
		//m_criAtomExPlaybackId = m_adx2le->Play(1);
	}
	//�t���O��On�Ȃ�
	if (m_SceneFlag)
	{
		//�J�E���g�𑫂�
		m_transitionFrame++;
		//��s�@�̈ړ�
		m_airPlane->Update();
	}

	//�J�E���g��60�ȏ�Ȃ�
	if (m_transitionFrame > 60)
	{	
		//m_adx2le->Stop();
		//�V�[���̈ړ�
		m_sceneManager->SetScene(GAME_SCENE);
		return;

	}
	m_goalObj->Update();
	m_courceObj->Update();

	m_skyDome->Update();
	//�J�����̍X�V	
	m_camera->Update();

	//�v���C���[�̕����x�N�g���̎擾
	DirectX::SimpleMath::Vector3 playerVel = m_airPlane->GetVelotity();
	//�v���C���[�̈ʒu�̎擾
	DirectX::SimpleMath::Vector3 playerPos = m_airPlane->GetTranslation();

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
		playerPos.y = s.y + 0.6f;
		//�v���C���[�̑��x��0�ɂ���Bs
		playerVel.y = 0.0f;
	}

	//�v���C���[�̏ꏊ�̍X�V
	m_airPlane->SetTranslation(playerPos);
	//�v���C���[�̑��x��ݒ肷��
	m_airPlane->SetVel(playerVel);


}
/// <summary>
/// �`�揈��
/// </summary>
void TitleScene::Render()
{		

	m_airPlane->Render(m_camera->GetView(),m_camera->GetProj());
	m_courceObj->Render(m_camera->GetView(), m_camera->GetProj());

	m_goalObj->Render(m_camera->GetView(), m_camera->GetProj());

	m_skyDome->Render(m_camera->GetView(), m_camera->GetProj());
	System::DrawManager::GetInstance().Begin();

	m_TitleLogo->Draw();


	System::DrawManager::GetInstance().End();


}

/// <summary>
/// �I������
/// </summary>
void TitleScene::Finalize()
{
	m_TitleLogo.reset();
	m_airPlane.reset();
	m_camera.reset();
	m_skyDome.reset();
	m_goalObj.reset();
	m_courceObj.reset();
	m_stageMesh.reset();
}

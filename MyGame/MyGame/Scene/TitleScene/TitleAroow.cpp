
//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  TitlLogo(�^�C�g����)��Cpp
//���e	:	�@TitlLogo(�^�C�g����)�̃^�X�N
//--------------------------------------------

#include <d3d11.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include "../../GameSystem/InputManager.h"
#include "TitleAroow.h"




/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleAroow::TitleAroow() : m_data()
{
	//�������Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleAroow::~TitleAroow()
{
}
/// <summary>
/// �J�n����
/// </summary>
void TitleAroow::Initilize()
{
	// �e�N�X�`���̃��[�h
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\Arrow.png");
	m_Pos = DirectX::SimpleMath::Vector2(150, 300);
	m_data.SetPos(m_Pos);
	m_data.SetOrigin(45, 45);
	m_data.SetRect(0,0,90,90);
	m_num = 0;
	//m_adx2le = MyLibrary::ADX2Le::GetInstance();

	// �T�E���h�̓ǂݍ���
	//m_adx2le->//LoadAcb(L"TitleScene.acb", L"TitleScene.awb");

}

void TitleAroow::Update(int& num)
{	
	//m_adx2le->Stop(0);

	if (System::InputManager::GetInstance().GetKeyboardTracker().pressed.Up)
	{
		m_Pos.y = 300;
		m_num = 0;
		//if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
		//{
		//	// ���ʉ��̍Đ�
		//	m_criAtomExPlaybackId = m_adx2le->Play(0);
		//}
	}
	if (System::InputManager::GetInstance().GetKeyboardTracker().pressed.Down)
	{	
		m_Pos.y = 400;
		m_num = 1;
		//if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
		//{
		//	// ���ʉ��̍Đ�
		//	m_criAtomExPlaybackId = m_adx2le->Play(0);

		//}
	}
	num = m_num ;

	m_data.SetPos(m_Pos);
}

void TitleAroow::Draw()
{
	System::DrawManager::GetInstance().Draw(m_data);

}
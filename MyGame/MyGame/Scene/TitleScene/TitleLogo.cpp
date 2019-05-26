//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  TitlLogo(�^�C�g����)��Cpp
//���e	:	�@TitlLogo(�^�C�g����)�̃^�X�N
//--------------------------------------------

#include "TitleLogo.h"




/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleLogo::TitleLogo() : m_data(), m_Pos(1000,150), m_Size(0.5,0.5)
{
	//�������Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleLogo::~TitleLogo()
{
	//�������Ȃ�
}
/// <summary>
/// �J�n����
/// </summary>
void TitleLogo::Initilize()
{	
	// �e�N�X�`���̃��[�h
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\TitleLogo.png");

	m_data.SetPos(m_Pos);
	m_data.SetRect(0,0,600,120);
	m_data.SetScale(m_Size);
	m_data.SetOrigin(static_cast<float>(m_data.GetRect().right), static_cast<float>(m_data.GetRect().bottom));
}

void TitleLogo::Update()
{

	m_Pos.x -= 3.0f;

	if (m_Pos.x < 800)
	{
		m_Pos.x = 800;

	}
	m_Size.x += 0.05f;
	m_Size.y += 0.05f;

	if (m_Size.x >1.2)
	{
		m_Size.x = 1.2;
		m_Size.y = 1.2;
	}

	m_data.SetScale(m_Size);
	m_data.SetPos(m_Pos);
}

void TitleLogo::Draw()
{
	System::DrawManager::GetInstance().Draw(m_data);
}
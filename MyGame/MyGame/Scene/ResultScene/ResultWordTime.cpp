//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/27
//���g	:	  ResultWordTime(���U���g�̕���)��Cpp
//���e	:	�@ResultWordTime(���U���g�̕���)�̃^�X�N
//--------------------------------------------

#include "ResultWordTime.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultWordTime::ResultWordTime()
{
	//�������Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultWordTime::~ResultWordTime()
{
	//�������Ȃ�
}

/// <summary>
/// �J�n����
/// </summary>
void ResultWordTime::Initilize()
{
	m_drawData.SetPos(0.0f,90.0f);
	m_drawData.SetRect(0.0f, 0.0f, 200.0f, 90.0f);
	m_drawData.SetOrigin(0.0f, 0.0f);

	System::DrawManager::GetInstance().LoadTexture(m_drawData, L"Resources\\Textures\\Time.png");
}

/// <summary>
/// �X�V����
/// </summary>
void ResultWordTime::Update()
{
}

/// <summary>
/// �`�揈��
/// </summary>
void ResultWordTime::Draw()
{
	System::DrawManager::GetInstance().Draw(m_drawData);
}

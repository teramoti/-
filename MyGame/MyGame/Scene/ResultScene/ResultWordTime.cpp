//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/27
//���g	:	  ResultWordTime(���U���g�̕���)��Cpp
//���e	:	�@ResultWordTime(���U���g�̕���)�̃^�X�N
//--------------------------------------------

#include "../../GameSystem/GameSabe.h"

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
	m_DrawData.SetPos(0,90);
	m_DrawData.SetRect(0, 0, 200, 90);
	m_DrawData.SetOrigin(0, 0);
	System::DrawManager::GetInstance().LoadTexture(m_DrawData, L"Resources\\Textures\\Time.png");
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
	System::DrawManager::GetInstance().Draw(m_DrawData);
}

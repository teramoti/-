//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/27
//���g	:	  ResultScore(���U���g�̃X�R�A�\��)��Cpp
//���e	:	�@ResultScore(���U���g�̃X�R�A�\��)�̃^�X�N
//--------------------------------------------


#include "ResultKeyDown.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultKeyDown::ResultKeyDown() :  m_frame(0), m_Frash(false)
{

}
/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultKeyDown::~ResultKeyDown()
{

}

/// <summary>
/// ������
/// </summary>
void ResultKeyDown::Initilize()
{
	// �e�N�X�`���̃��[�h
	System::DrawManager::GetInstance().LoadTexture(m_DrawData, L"Resources\\Textures\\Zkey.png");

	m_DrawData.SetPos(400, 400);
	m_DrawData.SetRect(0, 0, 150,90);
	m_DrawData.SetOrigin(0, 0);
	m_DrawData.SetScale(DirectX::SimpleMath::Vector2(2, 2));

}
/// <summary>
/// �X�V
/// </summary>

void ResultKeyDown::Update()
{
	m_frame++;

	if (m_frame > 60)
	{
		m_frame = 0;
		m_Frash = !m_Frash;
	}
}

/// <summary>
/// �`��
/// </summary>
void ResultKeyDown::Draw()
{
	if (m_Frash == true)
	{
		System::DrawManager::GetInstance().Draw(m_DrawData);
	}
}

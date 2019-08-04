//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/27
//���g	:	  ResultTime(���U���g�̕���)��Cpp
//���e	:	�@ResultTime(���U���g�̕���)�̃^�X�N
//--------------------------------------------

#include "ResultTime.h"
#include "../../GameSystem/GameSaveData.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultTime::ResultTime() : m_score(0)
{
	//�������Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultTime::~ResultTime()
{
	//�������Ȃ�
	
	m_Comma;
}

/// <summary>
/// �J�n����
/// </summary>
void ResultTime::Initilize()
{

	m_num = GameSaveData::GetInstance().GetStage();
	switch (m_num)
	{
	case 1:
		//�X�R�A�̐ݒ�
		m_score = GameSaveData::GetInstance().GetGoal1Time();
	default:
		break;
	}



	//�e�N�X�`���̓ǂݍ���
	for (int i = 0; i < 4; i++)
	{
		System::DrawManager::GetInstance().LoadTexture(m_DrawData[i], L"Resources\\Textures\\Number.png");
	}

	m_Comma = new ResultTimeComma();
	m_Comma->SetPos(DirectX::SimpleMath::Vector2(310, 200));

	m_Comma->Initilize();
}

/// <summary>
/// �X�V����
/// </summary>
void ResultTime::Update()
{


}

/// <summary>
/// �`�揈��
/// </summary>
void ResultTime::Draw()
{
	m_rect[0] = { 0 + (((int)m_score / 1000 % 10) * 50),0,50 + (((int)m_score / 1000 % 10) * 50),50 };
	m_rect[1] = { 0 + (((int)m_score / 100 % 10) * 50),0,50 + (((int)m_score / 100 % 10) * 50),50 };
	m_rect[2] = { 0 + (((int)m_score / 10 % 10) * 50),0,50 + (((int)m_score / 10 % 10) * 50),50 };
	m_rect[3] = { 0 + (((int)m_score % 10) * 50),0,50 + (((int)m_score % 10) * 50),50 };

	for (int i = 0; i < 4; i++)
	{
		m_DrawData[i].SetPos(200.0f + (i * 60), 200.0f);
		m_DrawData[i].SetRect(m_rect[i].left, m_rect[i].top, m_rect[i].right, m_rect[i].bottom);
		m_DrawData[i].SetOrigin(0, 0);
		System::DrawManager::GetInstance().Draw(m_DrawData[i]);
	}
	m_Comma->Draw();
}

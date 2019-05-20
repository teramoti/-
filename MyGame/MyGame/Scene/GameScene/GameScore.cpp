//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/27
//���g	:	  GameScore(���U���g�̃X�R�A�\��)��Cpp
//���e	:	�@GameScore(���U���g�̃X�R�A�\��)�̃^�X�N
//--------------------------------------------

//#include "../../pch.h"
#include "GameScore.h"
#include "../../GameSystem/GameSabe.h"

using namespace MyGame;

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameScore::GameScore()
{
	m_score = 0;
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScore::~GameScore()
{
	//�������Ȃ�
}


/// <summary>
/// ������
/// </summary>
void GameScore::Initilize()
{
	//�e�N�X�`���̓ǂݍ���
	for (int i = 0; i < 5; i++)
	{
		//�X�R�A�̏ꏊ�̃Z�b�g
		m_DrawData[i].SetPos(400.0f - (i * 96), 530.0f);
		//�e�N�X�`���̓ǂݍ���
		System::DrawManager::GetInstance().LoadTexture(m_DrawData[i], L"Resources\\GameScene\\Number.png");
	}
	//�X�R�A�̐ݒ�
	m_score = System::GameSabe::GetInstance().GetData();
}


/// <summary>
/// �X�V
/// </summary>
void GameScore::Update()
{
	//���
	int n = this->m_score;
	//�����̗�\��
	for (int i = 0; i < 5; i++)
	{
		int number;
		number = n % 10;
		n = n / 10;
		int leftX = 0 + (64 * (number % 4));
		int topY = 0 + (64 * (number / 4));
		//�؂���̐ݒ�
		m_DrawData[i].SetRect(leftX, topY, leftX + 64, topY + 64);
	}

}

/// <summary>
/// �`��
/// </summary>
void GameScore::Draw()
{
	for (int i = 0; i < 5; i++)
	{
		//�`��
		System::DrawManager::GetInstance().Draw(m_DrawData[i]);
	}
}

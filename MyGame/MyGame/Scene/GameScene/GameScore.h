//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/27
//���g	:	  GameScore(���U���g�̃X�R�A�\��)�̃w�b�_�[
//���e	:	�@GameScore(���U���g�̃X�R�A�\��)�̃^�X�N
//--------------------------------------------

#pragma once

#include "../../GameSystem/DrawManager.h"
namespace MyGame
{
	class GameScore 
	{

	public:

		//�Q�[���X�R�A�̃R���X�g���N�^
		GameScore();
		//�Q�[���X�R�A�̃f�X�g���N�^
		~GameScore();
	public:
		//����������
		void Initilize();
		//�X�V����
		void Update();
		//�`�揈��
		void Draw();

		int SetScore(int score)
		{
			m_score = score;
		}
		//�^�C�g�����S�̃|�W�V����
		DirectX::SimpleMath::Vector2 m_Pos;
		//�`��p�̕ϐ�
		System::DrawData m_DrawData[5];
		//�X�R�A�󂯎��
		int m_score;
	};
}
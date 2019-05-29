//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/27
//���g	:	 ResultRank(���U���g�̃X�R�A�\��)�̃w�b�_�[
//���e	:	ResultRank(���U���g�̃X�R�A�\��)�̃^�X�N
//--------------------------------------------

#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <CommonStates.h>

#include "../../GameSystem/DrawManager.h"

class ResultRank
{

public:

	//���U���g�X�R�A�̃R���X�g���N�^
	ResultRank();
	//���U���g�X�R�A�̃f�X�g���N�^
	~ResultRank();

public:
	//����������
	void Initilize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

	//�^�C�g�����S�̃|�W�V����
	DirectX::SimpleMath::Vector2 m_Pos;
	//�`��p�̕ϐ�
	System::DrawData m_DrawData;
	//�X�R�A�󂯎��
	int m_num;

};

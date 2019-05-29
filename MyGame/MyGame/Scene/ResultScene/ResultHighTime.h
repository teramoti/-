//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/27
//���g	:	  ResultTime(���U���g�̕���)�̃w�b�_�[
//���e	:	�@ResultTime(���U���g�̕���)�̃^�X�N
//--------------------------------------------

#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <CommonStates.h>
#include "../../GameSystem/DrawManager.h"
#include "ResultTimeComma.h"
#include "ResultRecord.h"

class ResultHighTime
{
public:

	//���U���g�����̃R���X�g���N�^
	ResultHighTime();
	//���U���g�����̃f�X�g���N�^
	~ResultHighTime();

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
	System::DrawData m_DrawData[4];
	//�X�R�A�󂯎��
	float m_score;
	RECT m_rect[4];
	ResultTimeComma* m_Comma;
	ResultRecord* m_Record;
	int m_num;
};


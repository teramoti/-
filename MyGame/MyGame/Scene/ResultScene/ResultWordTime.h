//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/27
//���g	:	  ResultTime(���U���g�̕���)�̃w�b�_�[
//���e	:	�@ResultTime(���U���g�̕���)�̃^�X�N
//--------------------------------------------

#pragma once


#include "../../GameSystem/DrawManager.h"

class ResultWordTime
{
public:

	//���U���g�����̃R���X�g���N�^
	ResultWordTime();
	//���U���g�����̃f�X�g���N�^
	~ResultWordTime();

public:
	//�n�܂鏈��
	void Initilize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

	//�^�C�g�����S�̃|�W�V����
	DirectX::SimpleMath::Vector2 m_Pos;
	//�`��p�̕ϐ�
	System::DrawData m_drawData;
};

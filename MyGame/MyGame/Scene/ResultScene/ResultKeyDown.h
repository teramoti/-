//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/27
//���g	:	 ResultKeyDown(���U���g�̃X�R�A�\��)�̃w�b�_�[
//���e	:	ResultKeyDown(���U���g�̃X�R�A�\��)�̃^�X�N
//--------------------------------------------

#pragma once
#include "../../GameSystem/DrawManager.h"

class ResultKeyDown
{

public:

	//���U���g�X�R�A�̃R���X�g���N�^
	ResultKeyDown();
	//���U���g�X�R�A�̃f�X�g���N�^
	~ResultKeyDown();

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
	int m_frame;
	bool m_Frash;
};

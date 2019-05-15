//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/27
//���g	:	TitletKeyDown(���U���g�̃X�R�A�\��)�̃w�b�_�[
//���e	:	TitletKeyDown(���U���g�̃X�R�A�\��)�̃^�X�N
//--------------------------------------------

#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../GameSystem/DrawManager.h"

class TitleKeyDown
{

public:

	//���U���g�X�R�A�̃R���X�g���N�^
	TitleKeyDown();
	//���U���g�X�R�A�̃f�X�g���N�^
	~TitleKeyDown();

public:
	//�n�܂鏈��
	void Initilize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

private:
	//�^�C�g�����S�̃|�W�V����
	DirectX::SimpleMath::Vector2 m_Pos;
	//�`��p�̕ϐ�
	System::DrawData m_data;
	//�X�R�A�󂯎��
	int m_frame;
	bool m_Frash;


};

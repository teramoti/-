//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  TitleBackGround(�^�C�g����)�̃w�b�_�[
//���e	:	�@TitleBackGround(�^�C�g����)�̃^�X�N�Ǘ�
//--------------------------------------------

#pragma once

#include "../../GameSystem/DrawManager.h"
class TitleBackGround
{
public:

	//�^�C�g�����̃R���X�g���N�^
	TitleBackGround();
	//�^�C�g�����̃f�X�g���N�^
	~TitleBackGround();

public:
	//�n�܂鏈��
	void Initilize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

private:
	DirectX::SimpleMath::Vector2 m_Pos;
	System::DrawData m_data;
};

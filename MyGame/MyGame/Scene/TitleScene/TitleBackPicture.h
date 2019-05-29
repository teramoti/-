//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  TitleBackPicture(�^�C�g����)�̃w�b�_�[
//���e	:	�@TitleBackPicture(�^�C�g����)�̃^�X�N�Ǘ�
//--------------------------------------------

#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../GameSystem/DrawManager.h"
class TitleBackPicture
{
public:

	//�^�C�g�����̃R���X�g���N�^
	TitleBackPicture();
	//�^�C�g�����̃f�X�g���N�^
	~TitleBackPicture();

public:
	//����������
	void Initilize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

private:

	//�^�C�g�����S�̃|�W�V����
	DirectX::SimpleMath::Vector2 m_Pos;
	System::DrawData m_data[2];
};

//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  TitleLogo(�^�C�g����)�̃w�b�_�[
//���e	:	�@TitleLogo(�^�C�g����)�̃^�X�N�Ǘ�
//--------------------------------------------

#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../GameSystem/DrawManager.h"
class TitleGoGame
{
public:

	//�^�C�g�����̃R���X�g���N�^
	TitleGoGame();
	//�^�C�g�����̃f�X�g���N�^
	~TitleGoGame();

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
	System::DrawData m_data;
};

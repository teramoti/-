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
class TitleLogo
{
public:

	//�^�C�g�����̃R���X�g���N�^
	TitleLogo();
	//�^�C�g�����̃f�X�g���N�^
	~TitleLogo();

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
	DirectX::SimpleMath::Vector2 m_Size;
	System::DrawData m_data;
};

//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/27
//���g	:	  ResultTime(���U���g�̕���)�̃w�b�_�[
//���e	:	�@ResultTime(���U���g�̕���)�̃^�X�N
//--------------------------------------------

#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include "../../GameSystem/DrawManager.h"

class TimeComma
{
public:

	//���U���g�����̃R���X�g���N�^
	TimeComma();
	//���U���g�����̃f�X�g���N�^
	~TimeComma();

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
	System::DrawData m_DrawData;
	RECT m_rect;
};

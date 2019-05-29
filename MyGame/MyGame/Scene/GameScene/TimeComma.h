//------------------------//------------------------
// Contents(�������e) TimeComma.cpp�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2018 / 07 / 13
// last updated (�ŏI�X�V��) 2018 / 11 / 05
//------------------------//------------------------
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

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
#include "TimeComma.h"

class GameTime
{
public:

	//���U���g�����̃R���X�g���N�^
	GameTime();
	//���U���g�����̃f�X�g���N�^
	~GameTime();

public:
	//����������
	void Initilize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw(bool Flag);

	void SetTime(float score)
	{
		m_score= score;
	}
	void SetTime(int time)
	{
		m_time = time;
	}
private:
	//�^�C�g�����S�̃|�W�V����
	DirectX::SimpleMath::Vector2 m_Pos;
	//�`��p�̕ϐ�
	System::DrawData m_DrawData[4];
	//�X�R�A�󂯎��
	float m_score;
	int m_time;

	RECT m_rect[5];
	TimeComma* m_comma;
};

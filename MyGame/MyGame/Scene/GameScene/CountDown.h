//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	 CountDown�̃w�b�_�[
//���e	:	CountDown�̃^�X�N�Ǘ�
//--------------------------------------------

#pragma once
#include "../../GameSystem/DrawManager.h"
#include"GameReadyWord.h"
class CountDown
{
public:

	//�^�C�g�����̃R���X�g���N�^
	CountDown();
	//�^�C�g�����̃f�X�g���N�^
	~CountDown();

public:
	//����������
	void Initilize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

	void SetTime(float& count)
	{
	 m_Count= count;
	}
private:

	//�^�C�g�����S�̃|�W�V����
	DirectX::SimpleMath::Vector2 m_Pos;
	System::DrawData m_data;
	float m_Count;

	RECT m_rect;

	GameReadyWord* m_ready;
};

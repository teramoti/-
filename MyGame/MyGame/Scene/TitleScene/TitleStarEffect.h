//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  TitleStarEffect(�^�C�g����)�̃w�b�_�[
//���e	:	�@TitleStarEffect(�^�C�g����)�̃^�X�N�Ǘ�
//--------------------------------------------

#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../GameSystem/DrawManager.h"
class TitleStarEffect
{
public:

	//�^�C�g�����̃R���X�g���N�^
	TitleStarEffect();
	//�^�C�g�����̃f�X�g���N�^
	~TitleStarEffect();
public:
	//����������
	void Initilize();
	//�X�V����
	void Update();

	//�`�揈��
	void Draw();
	void Move();
private:

	//�^�C�g�����S�̃|�W�V����
	DirectX::SimpleMath::Vector2 m_Pos;
	DirectX::SimpleMath::Vector2 m_Speed;
	System::DrawData m_data;
};

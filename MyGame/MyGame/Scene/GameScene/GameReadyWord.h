//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  GameReadyWord(�^�C�g����)�̃w�b�_�[
//���e	:	�@GameReadyWord(�^�C�g����)�̃^�X�N�Ǘ�
//--------------------------------------------

#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../GameSystem/DrawManager.h"
class GameReadyWord
{
public:

	//�^�C�g�����̃R���X�g���N�^
	GameReadyWord();
	//�^�C�g�����̃f�X�g���N�^
	~GameReadyWord();

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

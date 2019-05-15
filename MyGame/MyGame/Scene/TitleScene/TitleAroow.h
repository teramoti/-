//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  TitleBackGround(�^�C�g����)�̃w�b�_�[
//���e	:	�@TitleBackGround(�^�C�g����)�̃^�X�N�Ǘ�
//--------------------------------------------

#pragma once
#include "../../GameSystem/DrawManager.h"
//#include "../..//ADX2/ADX2Le.h"

class TitleAroow
{
public:
	enum SERECT_ENUM
	{
		UP,
		DOWN,
		NONE

	};

public:

	
	//�^�C�g�����̃R���X�g���N�^
	TitleAroow();
	//�^�C�g�����̃f�X�g���N�^
	~TitleAroow();

public:
	//�n�܂鏈��
	void Initilize();
	//�X�V����
	void Update(int& num);
	//�`�揈��
	void Draw();

private:

	//�^�C�g�����S�̃|�W�V����
	DirectX::SimpleMath::Vector2 m_Pos;
	System::DrawData m_data;

	int m_num;

	// �T�E���h
	//MyLibrary::ADX2Le* m_adx2le;

	// ���y���L���p�ϐ�
	//CriAtomExPlaybackId m_criAtomExPlaybackId;
};

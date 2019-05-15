//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  TitlLogo(�^�C�g����)��Cpp
//���e	:	�@TitlLogo(�^�C�g����)�̃^�X�N
//--------------------------------------------
#include <d3d11.h>
#include <SimpleMath.h>
#include "TitleBackGround.h"
using namespace DirectX;

using namespace DirectX::SimpleMath;
/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleBackGround::TitleBackGround() : m_data() , m_Pos(Vector2(0,0))
{
	//�������Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleBackGround::~TitleBackGround()
{

}
/// <summary>
/// �J�n����
/// </summary>
void TitleBackGround::Initilize()
{
	// �e�N�X�`���̃��[�h
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\TitleBack.png");

	m_data.SetPos(0, 0);
	m_data.SetRect(0, 0, 800,600);
	m_data.SetScale(5, 5);
	m_data.SetOrigin(400,300);
}

void TitleBackGround::Update()
{
	
}

void TitleBackGround::Draw()
{
	System::DrawManager::GetInstance().Draw(m_data);

}
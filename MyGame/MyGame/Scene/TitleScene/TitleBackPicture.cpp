//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  TitlLogo(�^�C�g����)��Cpp
//���e	:	�@TitlLogo(�^�C�g����)�̃^�X�N
//--------------------------------------------
#include "TitleBackPicture.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;
/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleBackPicture::TitleBackPicture()  :m_data() , m_Pos(0,0)
{
	//�������Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleBackPicture::~TitleBackPicture()
{
	//�������Ȃ�
}
/// <summary>
/// �J�n����
/// </summary>
void TitleBackPicture::Initilize()
{
	for (int i = 0; i < 2; i++)
	{
		// �e�N�X�`���̃��[�h
		System::DrawManager::GetInstance().LoadTexture(m_data[i], L"Resources\\Textures\\Base.png");
		m_data[i].SetRect(0, 30, 500, 170);
		m_data[i].SetOrigin(0, 0);
	}
	m_Pos = Vector2(350, 250);

	m_data[0].SetPos(m_Pos);
	m_Pos = Vector2(400, 550);

	m_data[1].SetPos(m_Pos);
}

void TitleBackPicture::Update()
{
	
}

void TitleBackPicture::Draw()
{
	for (int i = 0; i < 2; i++)
	{
		System::DrawManager::GetInstance().Draw(m_data[i]);
	}

}
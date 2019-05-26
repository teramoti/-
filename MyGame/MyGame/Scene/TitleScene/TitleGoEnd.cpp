//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  TitlLogo(�^�C�g����)��Cpp
//���e	:	�@TitlLogo(�^�C�g����)�̃^�X�N
//--------------------------------------------
#include "../../GameSystem/DrawManager.h"
#include "TitleGoEnd.h"




/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleGoEnd::TitleGoEnd()  :m_data() , m_Pos(0,0)
{
	//�������Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleGoEnd::~TitleGoEnd()
{
	//�������Ȃ�
}
/// <summary>
/// �J�n����
/// </summary>
void TitleGoEnd::Initilize()
{	
	// �e�N�X�`���̃��[�h
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\GoEnd.png");
	m_Pos = DirectX::SimpleMath::Vector2(300, 350);
	m_data.SetPos(m_Pos);
	m_data.SetRect(0, 0, 200,90);
	m_data.SetOrigin(0, 0);
}

void TitleGoEnd::Update()
{
	
}

void TitleGoEnd::Draw()
{
	System::DrawManager::GetInstance().Draw(m_data);

}
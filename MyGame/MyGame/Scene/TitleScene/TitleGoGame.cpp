//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  TitlLogo(�^�C�g����)��Cpp
//���e	:	�@TitlLogo(�^�C�g����)�̃^�X�N
//--------------------------------------------
#include "TitleGoGame.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;
/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleGoGame::TitleGoGame()  :m_data() , m_Pos(0,0)
{
	//�������Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleGoGame::~TitleGoGame()
{
	//�������Ȃ�
}
/// <summary>
/// �J�n����
/// </summary>
void TitleGoGame::Initilize()
{// �e�N�X�`���̃��[�h
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\GoGame.png");
	m_data.SetRect(0, 0, 200, 90);
	m_Pos = Vector2(300, 250);
	m_data.SetPos(m_Pos);
	m_data.SetOrigin(0, 0);
	
}

void TitleGoGame::Update()
{
	
}

void TitleGoGame::Draw()
{
 	System::DrawManager::GetInstance().Draw(m_data);

}
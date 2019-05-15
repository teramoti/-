//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  TitlLogo(�^�C�g����)��Cpp
//���e	:	�@TitlLogo(�^�C�g����)�̃^�X�N
//--------------------------------------------
#include "TitleStarEffect.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;
/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleStarEffect::TitleStarEffect() :m_Pos(-64,-64), m_Speed(5,5)  ,m_data()
{
	//�������Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleStarEffect::~TitleStarEffect()
{
	//�������Ȃ�
}
/// <summary>
/// �J�n����
/// </summary>
void TitleStarEffect::Initilize()
{
	// �e�N�X�`���̃��[�h									 
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\Star.png");
	m_data.SetRect(0, 0, 64,64);
	m_data.SetPos(m_Pos.x,m_Pos.y);
	m_data.SetOrigin(0, 0);
}

void TitleStarEffect::Update()
{
	Move();
	if (m_Pos.y > 664)
	{	
		m_Pos.y = -64;
		
	}
	if (m_Pos.x > 864)
	{
		m_Pos.x = -64;
	}

}

void TitleStarEffect::Draw()
{
	System::DrawManager::GetInstance().Draw(m_data);

}

void TitleStarEffect::Move()
{
	m_Pos += m_Speed;

	m_data.SetPos(m_Pos);
}

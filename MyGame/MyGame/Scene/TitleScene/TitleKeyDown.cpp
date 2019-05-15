//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/27
//���g	:	  ResultScore(���U���g�̃X�R�A�\��)��Cpp
//���e	:	�@ResultScore(���U���g�̃X�R�A�\��)�̃^�X�N
//--------------------------------------------


#include "TitleKeyDown.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleKeyDown::TitleKeyDown() :  m_frame(0), m_Frash(false), m_Pos(200, 500) , m_data()
{

}
/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleKeyDown::~TitleKeyDown()
{

}

/// <summary>
/// ������
/// </summary>
void TitleKeyDown::Initilize()
{
	// �e�N�X�`���̃��[�h
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\Space.png");
	m_Pos=Vector2(500, 450);
	m_data.SetPos(m_Pos);
	m_data.SetRect(0, 0, 150,90);
	m_data.SetOrigin(0, 0);
	m_data.SetScale(Vector2(2,2));

	
}
/// <summary>
/// �X�V
/// </summary>

void TitleKeyDown::Update()
{
	m_frame++;

	if (m_frame > 60)
	{
		m_frame = 0;
		m_Frash = !m_Frash;
	}
}

/// <summary>
/// �`��
/// </summary>
void TitleKeyDown::Draw()
{
	if (m_Frash == true)
	{
		System::DrawManager::GetInstance().Draw(m_data);
	}
}

//---------------------------------------------
//�쐬��	: ���{ �[�u
//�ŏI�X�V��: 2018 06/13
//���g	:	  TitlLogo(�^�C�g����)��Cpp
//���e	:	�@TitlLogo(�^�C�g����)�̃^�X�N
//--------------------------------------------


#include "GameReadyWord.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;
/// <summary>
/// �R���X�g���N�^
/// </summary>
GameReadyWord::GameReadyWord() : m_data() , m_Pos(Vector2(400, 200))
{
	//�������Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameReadyWord::~GameReadyWord()
{

}
/// <summary>
/// �J�n����
/// </summary>
void GameReadyWord::Initilize()
{
	// �e�N�X�`���̃��[�h
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\Ready.png");

	m_data.SetPos(m_Pos);
	m_data.SetScale(Vector2(2, 2));
	m_data.SetRect(0, 0, 150,60);
	m_data.SetOrigin(static_cast<float>(m_data.GetRect().right), static_cast<float>(m_data.GetRect().bottom));
}

void GameReadyWord::Update()
{
	
}

void GameReadyWord::Draw()
{
	System::DrawManager::GetInstance().Draw(m_data);

}
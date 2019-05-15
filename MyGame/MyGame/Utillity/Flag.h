//------------------------//------------------------
// Contents(�������e) Flag.h�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2018 / 07 / 05
// last updated (�ŏI�X�V��) 2018 / 07 / 05
//------------------------//------------------------

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

//----------------------------------------------------------------------
//!
//! @brief �t���O�N���X
//!
//----------------------------------------------------------------------
namespace Utility
{
	class Flag
	{
	public:
		// �R���X�g���N�^
		Flag()
			: m_Flag(0)
		{

		}

		// �t���O�𗧂Ă鏈��
		void On(unsigned int flag)
		{
			m_Flag |= flag;
		}

		// �t���O�𕚂��鏈��
		void Off(unsigned int flag)
		{
			m_Flag &= ~flag;
		}
		
		// �t���O�������Ă邩�m�F����
		bool Is(unsigned int flag)
		{
			return (m_Flag & flag) != 0;
		}

	private:
		// �t���O�ϐ�
		unsigned int m_Flag;
	};
}
//------------------------//------------------------
// Contents(�������e) Singleton.h�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2018 / 07 / 07
// last updated (�ŏI�X�V��) 2018 / 07 / 07
//------------------------//------------------------
#pragma once

namespace Utility
{
	//�V���O���g�������邽��
	template<class T> class SingletonBase
	{
	protected:

		SingletonBase() {}
		virtual ~SingletonBase() {}

	public:

		// �C���X�^���X�Ăяo��
		static inline T& GetInstance()
		{
			static T ins;
			return ins;
		}

	private:

		void operator=(const SingletonBase& obj) {}

		SingletonBase(const SingletonBase &obj) {}
	};
}
//------------------------//------------------------
// Contents(処理内容) Singleton.hの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 07
// last updated (最終更新日) 2018 / 07 / 07
//------------------------//------------------------

#pragma once
#ifndef  SINGLETON_DEFINED
#define  SINGLETON_DEFINED


namespace Utility
{
	//シングルトン化するため
	template<class T> class SingletonBase
	{
	protected:

		SingletonBase() {}
		virtual ~SingletonBase() {}

	public:

		// インスタンス呼び出し
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
#endif  //SINGLETON_DEFINED
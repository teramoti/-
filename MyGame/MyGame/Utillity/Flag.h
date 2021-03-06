//------------------------//------------------------
// Contents(処理内容) Flag.hの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 05
// last updated (最終更新日) 2018 / 07 / 05
//------------------------//------------------------

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef  FLAG_DEFINED
#define  FLAG_DEFINED

//----------------------------------------------------------------------
//!
//! @brief フラグクラス
//!
//----------------------------------------------------------------------
namespace Utility
{
	class Flag
	{
	public:
		// コンストラクタ
		Flag()
			: m_Flag(0)
		{

		}

		// フラグを立てる処理
		void On(unsigned int flag)
		{
			m_Flag |= flag;
		}

		// フラグを伏せる処理
		void Off(unsigned int flag)
		{
			m_Flag &= ~flag;
		}
		
		// フラグが立ってるか確認処理
		bool Is(unsigned int flag)
		{
			return (m_Flag & flag) != 0;
		}

	private:
		// フラグ変数
		unsigned int m_Flag;
	};
}
#endif  //FLAG_DEFINED

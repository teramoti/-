#pragma once

#include <list>

#include "../Utillity/SingletonBase.h"


#include "WICTextureLoader.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"

#include  "../Utillity/Flag.h"

namespace System
{
	typedef ID3D11ShaderResourceView* DxTexture;

	// 描画データをまとめたクラス
	struct DrawData
	{
	private:

		enum eDrawManagerFlag
		{
			NOT_TEXTURE_DELETE = (1<<0)
		};

		// フラグ
		Utility::Flag m_Flag;

		// テクスチャ
		DxTexture m_Texture;

		// 座標
		DirectX::SimpleMath::Vector2 m_Pos;

		// 角度
		float m_Rot;

		// 切り取り情報
		RECT m_Rect;

		// 中心点
		DirectX::XMFLOAT2 m_Origin;

		// スケール
		DirectX::XMFLOAT2 m_Scale;

	public:

		// コンストラクタ
		DrawData()
			: m_Texture(NULL)
			, m_Pos()
			, m_Rot(0.0f)
			, m_Rect()
			, m_Origin()
			, m_Scale(1.0f, 1.0f)
		{
		}

		// デストラクタ
		~DrawData()
		{
			if (m_Texture == NULL)
			{
				return;
			}

			// フラグによる削除制限
			if (m_Flag.Is(eDrawManagerFlag::NOT_TEXTURE_DELETE))
			{
				return;
			}

			m_Texture->Release();
		}

	public: // getter

		DxTexture* GetTexture() { return &m_Texture; }

		DirectX::SimpleMath::Vector2 GetPos() { return m_Pos; }

		float GetRot() { return m_Rot; }

		RECT GetRect() { return m_Rect; }
		const RECT* GetRectPtn() { return &m_Rect; }

		DirectX::XMFLOAT2 GetOrigin() { return m_Origin; }

		DirectX::XMFLOAT2 GetScale() { return  m_Scale; }

	public: // setter

		void SetTexture(DxTexture pTexture) {
			m_Texture = pTexture;
			m_Flag.On(eDrawManagerFlag::NOT_TEXTURE_DELETE);
		}

		void SetPos(float x, float y) { m_Pos.x = x; m_Pos.y = y; }

		void SetPos(DirectX::SimpleMath::Vector2 pos) { m_Pos = pos; }

		void SetRot(float r) { m_Rot = r; }

		void SetRect(LONG left, LONG top, LONG right, LONG bottom) {
			m_Rect.left = left;
			m_Rect.top = top;
			m_Rect.right = right;
			m_Rect.bottom = bottom;
		}
		void SetRect(LONG right, LONG bottom) { SetRect(0, 0, right, bottom); }

		void SetOrigin(float x, float y) { m_Origin.x = x; m_Origin.y = y; }
		void SetOrigin(DirectX::SimpleMath::Vector2 origin) { m_Origin = origin; }

		void SetScale(float x, float y) { m_Scale.x = x; m_Scale.y = y; }
		void SetScale(DirectX::SimpleMath::Vector2 scale) { m_Scale = scale; }
	};


	class DrawManager : public Utility::SingletonBase<DrawManager>
	{

	public:

		friend class Utility::SingletonBase<DrawManager>;

	protected:

		DrawManager() {};
		~DrawManager() {};

	public:

		// 初期化処理
		void Initialize(ID3D11Device* pDevise, ID3D11DeviceContext* pContext);

		// 描画
		void Draw(DrawData& data);

		// 描画前後処理
		void Begin();
		void End();

		// テクスチャ読み込み
		bool LoadTexture(DrawData& data, wchar_t* pFileName);
		bool LoadTexture(DxTexture& pTexture, wchar_t* pFileName);

		DirectX::SpriteBatch* GetSprite()
		{
			return mSpriteBatch.get();
		}

		// デバイスの設定
		void SetDevise(ID3D11Device* pDevise)
		{
			mpDevice = pDevise;
		}

		// デバイスの取得
		ID3D11Device* GetDevise()
		{
			return mpDevice;
		}

		// スプライトフォントの作成
		//m_font = std::make_unique<SpriteFont>(device, L"SegoeUI_18.spritefont");


	private:

		ID3D11Device* mpDevice;

		// スプライトバッチ
		std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
	};
}
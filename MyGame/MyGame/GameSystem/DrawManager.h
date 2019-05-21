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

	// �`��f�[�^���܂Ƃ߂��N���X
	struct DrawData
	{
	private:

		enum eDrawManagerFlag
		{
			NOT_TEXTURE_DELETE = (1<<0)
		};

		// �t���O
		Utility::Flag m_Flag;

		// �e�N�X�`��
		DxTexture m_Texture;

		// ���W
		DirectX::SimpleMath::Vector2 m_Pos;

		// �p�x
		float m_Rot;

		// �؂�����
		RECT m_Rect;

		// ���S�_
		DirectX::XMFLOAT2 m_Origin;

		// �X�P�[��
		DirectX::XMFLOAT2 m_Scale;

	public:

		// �R���X�g���N�^
		DrawData()
			: m_Texture(NULL)
			, m_Pos()
			, m_Rot(0.0f)
			, m_Rect()
			, m_Origin()
			, m_Scale(1.0f, 1.0f)
		{
		}

		// �f�X�g���N�^
		~DrawData()
		{
			if (m_Texture == NULL)
			{
				return;
			}

			// �t���O�ɂ��폜����
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

		// ����������
		void Initialize(ID3D11Device* pDevise, ID3D11DeviceContext* pContext);

		// �`��
		void Draw(DrawData& data);

		// �`��O�㏈��
		void Begin();
		void End();

		// �e�N�X�`���ǂݍ���
		bool LoadTexture(DrawData& data, wchar_t* pFileName);
		bool LoadTexture(DxTexture& pTexture, wchar_t* pFileName);

		DirectX::SpriteBatch* GetSprite()
		{
			return mSpriteBatch.get();
		}

		// �f�o�C�X�̐ݒ�
		void SetDevise(ID3D11Device* pDevise)
		{
			mpDevice = pDevise;
		}

		// �f�o�C�X�̎擾
		ID3D11Device* GetDevise()
		{
			return mpDevice;
		}

		// �X�v���C�g�t�H���g�̍쐬
		//m_font = std::make_unique<SpriteFont>(device, L"SegoeUI_18.spritefont");


	private:

		ID3D11Device* mpDevice;

		// �X�v���C�g�o�b�`
		std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
	};
}
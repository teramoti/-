#include "ItemManager.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

void ItemManager::Initilize()
{
	// �X�v���C�g�o�b�`�̍쐬
	m_sprites = std::make_unique < DirectX::SpriteBatch > (m_directX11.GetContext().Get());

	// �e�N�X�`���̃��[�h
	DirectX::CreateWICTextureFromFile(m_directX11.GetDevice().Get(), L"Resources\\Textures\\coin.png", nullptr, m_texture.GetAddressOf());
}

void ItemManager::Finalize()
{
}

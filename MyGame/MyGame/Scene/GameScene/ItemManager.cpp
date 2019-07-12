#include "ItemManager.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

void ItemManager::Initilize()
{
	// スプライトバッチの作成
	m_sprites = std::make_unique < DirectX::SpriteBatch > (m_directX11.GetContext().Get());

	// テクスチャのロード
	DirectX::CreateWICTextureFromFile(m_directX11.GetDevice().Get(), L"Resources\\Textures\\coin.png", nullptr, m_texture.GetAddressOf());
}

void ItemManager::Finalize()
{
}

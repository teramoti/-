//ItemManagerクラス
#include <d3d11.h>
#include <SimpleMath.h>
#include <wrl.h>
#include <wrl/client.h>

#include <SpriteBatch.h>
#include <WICTextureLoader.h>

#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>


#include <memory.h>

#include "../../Utillity/DirectX11.h"
#include "../../Utillity/dx.h"

#ifndef ITEM_MANAGER_DEFINED
#define ITEM_MANAGER_DEFINED

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	void Initilize();
	void Finalize();

	ID3D11ShaderResourceView* GetTexture()
	{
		return m_texture.Get();
	}
private:

	DirectX11& m_directX11 = DirectX11::Get();
	
	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;
	// テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};

#endif // ITEM_DEFINED

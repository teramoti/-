//Item�N���X

#ifndef ITEM_DEFINED
#define ITEM_DEFINED

#include <d3d11.h>
#include <SimpleMath.h>
#include <wrl.h>
#include <wrl/client.h>

#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <memory.h>

#include "../../Utillity/DirectX11.h"
#include "../../Utillity/dx.h"

#include "ItemManager.h"

class ItemManager;

class Item
{
public:
	Item(DirectX::SimpleMath::Vector3 pos);
	~Item();

	void Initilize(ItemManager& itemManager);
	void Update();
	void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& projection);
private:
	// �G�t�F�N�g
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	DirectX11& m_directX11 = DirectX11::Get();

	DirectX::SimpleMath::Vector3 m_pos;

	float m_angle;
	DirectX::SimpleMath::Matrix m_world;
	ItemManager* m_itemManager;
};

#endif // ITEM_DEFINED

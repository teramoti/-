//Itemクラス

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
#include "../../Utillity/Observer.h"
class ItemManager;

class Item
{
public:
	Item();
	~Item();

	void Initilize(ItemManager& itemManager, DirectX::SimpleMath::Vector3 pos);
	void Update();
	void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& projection);

	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_pos;
	}

	void SetPos(DirectX::SimpleMath::Vector3 pos)
	{
		m_pos = pos;
	}
	//監視者をいれる
	void Attach(Observer* observer)
	{
		m_list.push_back(observer);
	}

	void Detach(Observer* observer)
	{
		m_list.erase(std::remove(m_list.begin(), m_list.end(), observer), m_list.end());
	}

	void DetectCollision();

private:
	// エフェクト
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	DirectX11& m_directX11 = DirectX11::Get();

	DirectX::SimpleMath::Vector3 m_pos;

	float m_angle;
	DirectX::SimpleMath::Matrix m_world;
	ItemManager* m_itemManager;
	std::vector<Observer*> m_list;
};

#endif // ITEM_DEFINED

#include "Item.h"
#include <random>


Item::Item() : m_pos(DirectX::SimpleMath::Vector3::Zero), m_angle(0.0f) ,m_batchEffect(nullptr)
{
}

Item::~Item()
{
	m_batchEffect.reset();
	m_batch.reset();
	m_inputLayout.Reset();
	//delete m_itemManager;
}

void Item::Initilize(ItemManager& itemManager, DirectX::SimpleMath::Vector3 pos)
{


	m_itemManager = &itemManager;
	// エフェクトの作成
	m_batchEffect = std::make_unique<DirectX::AlphaTestEffect>(m_directX11.GetDevice().Get());
	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_batchEffect->SetReferenceAlpha(255);
	// 入力レイアウト生成
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	m_directX11.GetDevice().Get()->CreateInputLayout(DirectX::VertexPositionTexture::InputElements, 
		DirectX::VertexPositionTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());
	// プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>((m_directX11.GetContext().Get()));	


	int i = 0;
	m_pos = pos;
}

void Item::Update()
{	
	//コインのモデルを回転させる処理
	m_angle += 0.05f;
	
	m_pos = GetPos();
	//ワールドを算出する
	m_world = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle)* DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);


}

void Item::Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& projection)
{
	if (m_batchEffect == nullptr) return;

	// 頂点情報（ここは自分で設定してください。）
	DirectX::VertexPositionTexture vertex[4] =
	{
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 0.0f),  DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(-1.0f, 1.0f, 0.0f), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(-1.0f, -1.0f, 0.0f),DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(1.0f,-1.0f, 0.0f),  DirectX::SimpleMath::Vector2(0.0f, 1.0f)),
	};
	// テクスチャサンプラーの設定（クランプテクスチャアドレッシングモード）
	ID3D11SamplerState* samplers[1] = { m_directX11.Get().GetStates()->LinearClamp() };
	m_directX11.GetContext().Get()->PSSetSamplers(0, 1, samplers);
	// 不透明に設定
	m_directX11.GetContext().Get()->OMSetBlendState(m_directX11.Get().GetStates()->Opaque(), nullptr, 0xFFFFFFFF);
	// 深度バッファに書き込み参照する
	m_directX11.GetContext().Get()->OMSetDepthStencilState(m_directX11.Get().GetStates()->DepthDefault(), 0);
	// カリングは左周り
	m_directX11.GetContext().Get()->RSSetState(m_directX11.Get().GetStates()->CullCounterClockwise());
	// 不透明のみ描画する設定
 	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_batchEffect->SetReferenceAlpha(255);
	m_batchEffect->SetWorld(m_world);
	m_batchEffect->SetView(view);
	m_batchEffect->SetProjection(projection);
	m_batchEffect->SetTexture(m_itemManager->GetTexture());
	m_batchEffect->Apply(m_directX11.GetContext().Get());
	m_directX11.GetContext().Get()->IASetInputLayout(m_inputLayout.Get());
	// 不透明部分を描画
	m_batch->Begin();
	m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_batch->End();
	// 不透明以外の半透明部分を描画する設定
	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_batchEffect->Apply(m_directX11.GetContext().Get());
	// 半透明で描画
	m_directX11.GetContext().Get()->OMSetBlendState(m_directX11.Get().GetStates()->NonPremultiplied(), nullptr, 0xFFFFFFFF);
	// 深度バッファに書き込まないが参照だけする
	m_directX11.GetContext().Get()->OMSetDepthStencilState(m_directX11.Get().GetStates()->DepthRead(), 0);
	// 半透明部分を描画
	m_batch->Begin();
	m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_batch->End();

}

void Item::DetectCollision()
{
	//Notify();
}
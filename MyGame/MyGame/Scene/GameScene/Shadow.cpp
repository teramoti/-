#include "../../../pch.h"
#include "Shadow.h"
#include "../../GameSystem/Object.h"
#include "../../GameSystem/DrawManager.h"
#include "../../../DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
Shadow::Shadow() : m_active(true)
{
}

void Shadow::Initialize(DirectX::Model * model, ID3D11Device* device)
{
	m_model = model;
	m_device = device;
	// ブレンドステート作成（減算合成）
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.AlphaToCoverageEnable = FALSE;
	bd.IndependentBlendEnable = FALSE;
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	m_device->CreateBlendState(&bd, m_blendState.GetAddressOf());


}

void Shadow::Render()
{
	if (!m_model) return;
	// 親の真下に影を表示する
	MyLib::Object3D* object = new MyLib::Object3D();
	const Vector3& pos = object->GetTranslation();

	Matrix world = Matrix::CreateTranslation(Vector3(pos.x, 0.0f, pos.z));
	//m_model->Draw(game->GetContext(), *game->GetStates()
	//	, world
	//	, m_gameWindow->GetViewMatrix()
	//	, m_gameWindow->GetProjectionMatrix()
	//	, false, [&]()
	//{
	//	// ブレンドを減算合成にし深度バッファは使用せず描画する
	//	game->GetContext()->OMSetBlendState(m_blendState.Get(), nullptr, 0xffffffff);
	//	game->GetContext()->OMSetDepthStencilState(game->GetStates()->DepthNone(), 0);
	//});

}

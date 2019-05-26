//#include "../../.."
#include "Shadow.h"
#include "../../GameSystem/Object.h"
#include "../../GameSystem/DrawManager.h"

//
//
Shadow::Shadow() : m_active(true)
{
}

void Shadow::Initialize()
{

	//m_model = DirectX::Model::CreateFromCMO(m_directX11.GetDevice(), L"",);
	// �u�����h�X�e�[�g�쐬�i���Z�����j
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
	
	m_directX11.GetDevice().Get()->CreateBlendState(&bd, m_blendState.GetAddressOf());


}

void Shadow::Render()
{
	if (!m_model) return;
	// �e�̐^���ɉe��\������
	MyLib::Object3D* object = new MyLib::Object3D();
	const DirectX::SimpleMath::Vector3& pos = object->GetTranslation();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(pos.x, 0.0f, pos.z));
	m_model->Draw(m_directX11.GetContext().Get()
	, *m_directX11.GetStates()
		, world
		, m_camera->GetView()
		, m_camera->GetProj()
		, false, [&]()
	{
		// �u�����h�����Z�����ɂ��[�x�o�b�t�@�͎g�p�����`�悷��
		m_directX11.GetContext().Get()->OMSetBlendState(m_blendState.Get(), nullptr, 0xffffffff);
		m_directX11.GetContext().Get()->OMSetDepthStencilState(m_directX11.Get().GetStates()->DepthNone(), 0);
	});

}

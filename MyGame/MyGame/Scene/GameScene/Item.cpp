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
	// �G�t�F�N�g�̍쐬
	m_batchEffect = std::make_unique<DirectX::AlphaTestEffect>(m_directX11.GetDevice().Get());
	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_batchEffect->SetReferenceAlpha(255);
	// ���̓��C�A�E�g����
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	m_directX11.GetDevice().Get()->CreateInputLayout(DirectX::VertexPositionTexture::InputElements, 
		DirectX::VertexPositionTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());
	// �v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>((m_directX11.GetContext().Get()));	


	int i = 0;
	m_pos = pos;
}

void Item::Update()
{	
	//�R�C���̃��f������]�����鏈��
	m_angle += 0.05f;
	
	m_pos = GetPos();
	//���[���h���Z�o����
	m_world = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle)* DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);


}

void Item::Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& projection)
{
	if (m_batchEffect == nullptr) return;

	// ���_���i�����͎����Őݒ肵�Ă��������B�j
	DirectX::VertexPositionTexture vertex[4] =
	{
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 0.0f),  DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(-1.0f, 1.0f, 0.0f), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(-1.0f, -1.0f, 0.0f),DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(1.0f,-1.0f, 0.0f),  DirectX::SimpleMath::Vector2(0.0f, 1.0f)),
	};
	// �e�N�X�`���T���v���[�̐ݒ�i�N�����v�e�N�X�`���A�h���b�V���O���[�h�j
	ID3D11SamplerState* samplers[1] = { m_directX11.Get().GetStates()->LinearClamp() };
	m_directX11.GetContext().Get()->PSSetSamplers(0, 1, samplers);
	// �s�����ɐݒ�
	m_directX11.GetContext().Get()->OMSetBlendState(m_directX11.Get().GetStates()->Opaque(), nullptr, 0xFFFFFFFF);
	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	m_directX11.GetContext().Get()->OMSetDepthStencilState(m_directX11.Get().GetStates()->DepthDefault(), 0);
	// �J�����O�͍�����
	m_directX11.GetContext().Get()->RSSetState(m_directX11.Get().GetStates()->CullCounterClockwise());
	// �s�����̂ݕ`�悷��ݒ�
 	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_batchEffect->SetReferenceAlpha(255);
	m_batchEffect->SetWorld(m_world);
	m_batchEffect->SetView(view);
	m_batchEffect->SetProjection(projection);
	m_batchEffect->SetTexture(m_itemManager->GetTexture());
	m_batchEffect->Apply(m_directX11.GetContext().Get());
	m_directX11.GetContext().Get()->IASetInputLayout(m_inputLayout.Get());
	// �s����������`��
	m_batch->Begin();
	m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_batch->End();
	// �s�����ȊO�̔�����������`�悷��ݒ�
	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_batchEffect->Apply(m_directX11.GetContext().Get());
	// �������ŕ`��
	m_directX11.GetContext().Get()->OMSetBlendState(m_directX11.Get().GetStates()->NonPremultiplied(), nullptr, 0xFFFFFFFF);
	// �[�x�o�b�t�@�ɏ������܂Ȃ����Q�Ƃ�������
	m_directX11.GetContext().Get()->OMSetDepthStencilState(m_directX11.Get().GetStates()->DepthRead(), 0);
	// ������������`��
	m_batch->Begin();
	m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_batch->End();

}

void Item::DetectCollision()
{
	//Notify();
}
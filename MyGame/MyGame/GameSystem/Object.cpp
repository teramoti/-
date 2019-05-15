#include "Object.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLib;
//
Microsoft::WRL::ComPtr<ID3D11Device>			MyLib::Object3D::m_Device;
Microsoft::WRL::ComPtr<ID3D11DeviceContext>		MyLib::Object3D::m_Context;

std::unique_ptr<DirectX::CommonStates>			MyLib::Object3D::m_States;
std::unique_ptr<DirectX::EffectFactory>			MyLib::Object3D::m_Factory;

Camera* MyLib::Object3D::ccamera;

void MyLib::Object3D::InitielizeStatic(Microsoft::WRL::ComPtr<ID3D11Device> _device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context, Camera* _camera)
{
	m_Device = _device;
	m_Context = _context;

	m_States = std::make_unique<CommonStates>(m_Device.Get());
	m_Factory = std::make_unique<EffectFactory>(m_Device.Get());

	ccamera = _camera;

	m_Factory->SetDirectory(L"Resources\\Model");
}

MyLib::Object3D::Object3D()
{
	m_Scale = Vector3(1, 1, 1);
	m_Parent = nullptr;
}

MyLib::Object3D::~Object3D()
{

}

void MyLib::Object3D::Load(const wchar_t * fileName)
{
	m_ModelData = Model::CreateFromCMO(m_Device.Get(), fileName, *m_Factory);
}

void MyLib::Object3D::Update()
{
	Matrix scalemat = Matrix::CreateScale(m_Scale);
	Matrix rotmat;

	Matrix rmat;
	rmat = Matrix::CreateFromQuaternion(m_rot);
	rotmat = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);

	Matrix transmat = Matrix::CreateTranslation(m_Translation);

	m_World = scalemat * rmat * transmat;

	if (m_Parent)
	{
		m_World *= m_Parent->m_World;
	}
}

void MyLib::Object3D::Draw()
{
	if (m_ModelData != nullptr)
	{
		m_ModelData->Draw(m_Context.Get(), *m_States, m_World, ccamera->GetView(), ccamera->GetProj());
	}
}

void MyLib::Object3D::ReUpdate()
{
	Matrix scalemat = Matrix::CreateScale(m_Scale);
	Matrix rotmat;

	rotmat = Matrix::CreateFromYawPitchRoll(m_Rotation.x, m_Rotation.y, m_Rotation.z);

	Matrix transmat = Matrix::CreateTranslation(m_Translation);

	m_World = scalemat * rotmat * transmat;

	if (m_Parent)
	{
		m_World *= m_Parent->m_World;
	}
}


void MyLib::Object3D::SetLight()
{
	auto SetLight = [&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			lights->SetAmbientLightColor(Vector3(0.1f, 0.1f, 0.1f));
			// �A���r�G���g�F��ݒ肷�� 
			lights->SetLightEnabled(0, true);
			// �P�Ԃ̃��C�gON 
			lights->SetLightEnabled(1, true);
			// �Q�Ԃ̃��C�gOFF 
			lights->SetLightEnabled(2, true);
			// �R�Ԃ̃��C�gOFF 
			lights->SetLightDiffuseColor(0, Colors::White);
			lights->SetLightDiffuseColor(1, Colors::White);
			lights->SetLightDiffuseColor(2, Colors::White);
			// ���C�g�̐F 
			Vector3 light_dir(-1, 1, 0);
			// ���C�g�̕����x�N�g�� 
			light_dir.Normalize();
			// ���C�g�̕����x�N�g���𐳋K������
			lights->SetLightDirection(0, light_dir);
			lights->SetLightDirection(1, Vector3(0, 1, -1));
			lights->SetLightDirection(2, Vector3(1, 1, 1));
			// �P�Ԃ̃��C�g�̕�����ݒ肷�� 
			lights->SetPerPixelLighting(true);
			//�s�N�Z���V�F�[�_�[�Ń��C�g�̌v�Z������
		}
	};
	m_ModelData->UpdateEffects(SetLight);
}


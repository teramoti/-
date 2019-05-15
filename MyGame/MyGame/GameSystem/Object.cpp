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
			// アンビエント色を設定する 
			lights->SetLightEnabled(0, true);
			// １番のライトON 
			lights->SetLightEnabled(1, true);
			// ２番のライトOFF 
			lights->SetLightEnabled(2, true);
			// ３番のライトOFF 
			lights->SetLightDiffuseColor(0, Colors::White);
			lights->SetLightDiffuseColor(1, Colors::White);
			lights->SetLightDiffuseColor(2, Colors::White);
			// ライトの色 
			Vector3 light_dir(-1, 1, 0);
			// ライトの方向ベクトル 
			light_dir.Normalize();
			// ライトの方向ベクトルを正規化する
			lights->SetLightDirection(0, light_dir);
			lights->SetLightDirection(1, Vector3(0, 1, -1));
			lights->SetLightDirection(2, Vector3(1, 1, 1));
			// １番のライトの方向を設定する 
			lights->SetPerPixelLighting(true);
			//ピクセルシェーダーでライトの計算をする
		}
	};
	m_ModelData->UpdateEffects(SetLight);
}


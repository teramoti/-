#include "../../../pch.h"
#include "Cource.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

Cource::Cource()
{
}

Cource::~Cource()
{
}

void Cource::Initilize()
{
	Load(L"Resources/Model/CircleCource.cmo");
	m_Translation = Vector3(0, -1, 0);
}

void Cource::Update()
{
	Object3D::Update();
}

void Cource::Render()
{
	Object3D::Draw();
}


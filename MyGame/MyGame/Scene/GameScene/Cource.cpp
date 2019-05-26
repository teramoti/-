//#include "../../../pch.h"
#include "Cource.h"



Cource::Cource()
{
}

Cource::~Cource()
{
}

void Cource::Initilize()
{
	//Load(L"Resources/Model/CircleCource.cmo");
	m_translation = DirectX::SimpleMath::Vector3(0, -1, 0);
}

void Cource::Update()
{
	Object3D::Update();
}

void Cource::Render()
{
	Object3D::Draw();
}


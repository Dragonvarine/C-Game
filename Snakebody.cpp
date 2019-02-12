#include "Snakebody.h"



Snakebody::Snakebody()
{
	m_Bodylist[0];

}

Snakebody::Snakebody(const Snakebody &)
{
}


Snakebody::~Snakebody()
{
}

bool Snakebody::Initialize(ID3D11Device * device, HWND hwnd, InputClass * input, ModelClass & outModel)
{
	bool result;

	m_Input = input;

	for (int i = 0; i < m_Bodylist.Length; i++) {
		m_Bodylist[i] = new ModelClass;
		if (!m_Bodylist[i])
		{
			return false;
		}
	}

	// Initialize the model object.
	result = m_Bodylist[0]->Initialize(device, "../Engine/data/cube.txt", L"../Engine/data/red.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the player model object.", L"Error", MB_OK);
		return false;
	}

	scale = D3DXVECTOR3(-3.5f, -1.5f, 0.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return true;
}

void Snakebody::Shutdown()
{
}

bool Snakebody::Frame()
{
	

	return false;
}

ModelClass * Snakebody::GetModel()
{
	return nullptr;
}

D3DXMATRIX Snakebody::GetWorldMatrix()
{
	return D3DXMATRIX();
}

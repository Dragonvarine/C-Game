#include "gridclass.h"

gridclass::gridclass()
{
	m_Grid = 0;
}

gridclass::gridclass(const gridclass &)
{
}

gridclass::~gridclass()
{
}

bool gridclass::Initialize(ID3D11Device * device, HWND hwnd)
{
	bool result;

	int x = 10;
	int y = 10;
	m_Grid = new ModelClass[x * y];
	gridPosition = new D3DXMATRIX[x * y];
	for (int i = 0; i < x; i++)
	{

		for (int j = 0; j < y; j++) 
		{
			result = m_Grid[(i * 10) + j].Initialize(device, "../Engine/data/cube.txt", L"../Engine/data/blue.dds");
			D3DXMatrixTranslation(&gridPosition[(i * 10) + j], i*5, j*5, 100);
			if (!result) 
			{
				MessageBox(hwnd, L"Could not initialize the player model object.", L"Error", MB_OK);
				return false;
			}
		}
	}

	return true;
}

void gridclass::Shutdown()
{
	if (m_Grid)
	{
		delete m_Grid;
		m_Grid = 0;
	}
}

bool gridclass::Frame()
{
	return true;
}

ModelClass * gridclass::GetModel()
{
	return m_Grid;
}

D3DXMATRIX * gridclass::GetWorldMatrix()
{
	return gridPosition;
}

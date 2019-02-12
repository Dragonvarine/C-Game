#include "snakemain.h"

snakemain::snakemain()
{
	m_Tail = 0;
}

snakemain::snakemain(const snakemain &)
{
}

snakemain::~snakemain()
{
}

bool snakemain::Initialize(ID3D11Device * device, HWND hwnd, gridclass* grid, SnakeHead* Shead)
{
	bool result;
	m_Grid = grid;
	snakeAmount = food;
	m_Shead = Shead;
	headIndex = m_Shead->indexPos;
	m_Tail = new ModelClass[100];
	tailPositions = new D3DXMATRIX[100];

	D3DXMatrixTranslation(&awayPosition, 1000.0f, 1000.0f, 1000.0f);

	for (int i = 0; i < 100; i++) 
	{

		result = m_Tail[i].Initialize(device, "../Engine/data/cube.txt", L"../Engine/data/green.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the player model object.", L"Error", MB_OK);
			return false;
		}
	}
	
	

	for (int i = 99; i > 0; i--)
	{
		if (i > snakeAmount)
		{
			tailPositions[i] = awayPosition;
		}
		else
		{
			tailPositions[i] = m_Grid->gridPosition[headIndex - i];
		}
	}

	return true;
}

void snakemain::Shutdown()
{
	
	if (m_Tail)
	{
		delete m_Tail;
		m_Tail = 0;
	}
	
}

bool snakemain::Frame(gridclass* grid, SnakeHead* head)
{
	

	for (int i = 99; i > 0; i--)
	{
		if (i > snakeAmount)
		{
			tailPositions[i] = awayPosition;
		}
		else
		{
			D3DMATRIX test1 = tailPositions[i];
			D3DMATRIX test2 = tailPositions[i - 1];

			tailPositions[i] = tailPositions[i - 1];
		}
	}

	tailPositions[0] = grid->gridPosition[head->indexPos];

	return true;
}

ModelClass * snakemain::GetModel()
{
	return m_Tail;
}

//This is the position of the models - needs to be an array
D3DXMATRIX * snakemain::GetWorldMatrix()
{
	return tailPositions;
}

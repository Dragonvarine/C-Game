#include "food.h"


Food::Food()
{
	m_Food = 0;
	m_Grid = 0;

}

Food::Food(const Food &)
{
}

Food::~Food()
{
}

bool Food::Initialize(ID3D11Device * device, HWND hwnd, gridclass * grid, SnakeHead* head, snakemain* tail)
{
	bool result;
	//foodIndex = rand() % 100 + 1;
	m_Food = new ModelClass;
	m_Grid = grid;
	m_Head = head;
	m_Tail = tail;
	
	
	result = m_Food->Initialize(device, "../Engine/data/cube.txt", L"../Engine/data/green.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the food object.", L"Error", MB_OK);
		return false;
	}

	foodPosition = new D3DXMATRIX;
	foodPosition = &m_Grid->gridPosition[foodIndex];


	return true;
}

void Food::Shutdown()
{
	if (m_Food > 0)
	{
		delete m_Food;
		m_Food = 0;
	}
}

bool Food::Frame()
{
	if (foodIndex == m_Head->indexPos)
	{
		m_Tail->food++;
		Shutdown();
	}

	return true;
}

ModelClass * Food::GetModel()
{
	return m_Food;
}

D3DXMATRIX * Food::GetWorldMatrix()
{
	return foodPosition;
}

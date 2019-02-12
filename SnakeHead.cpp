#include "SnakeHead.h"

SnakeHead::SnakeHead()
{
	m_Head = 0;
	m_Input = 0;

}

SnakeHead::SnakeHead(const SnakeHead &)
{
}

SnakeHead::~SnakeHead()
{
}

bool SnakeHead::Initialize(ID3D11Device * device, HWND hwnd, InputClass * input, gridclass* grid)
{
	bool result;

	m_Input = input;
	m_Grid = grid;
	indexPos = 55;
	whatIsDirection = 3;
	headPosition = &m_Grid->gridPosition[indexPos];
	m_Head = new ModelClass;
	result = m_Head->Initialize(device, "../Engine/data/cube.txt", L"../Engine/data/red.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the player model object.", L"Error", MB_OK);
		return false;
	}

	headPosition = new D3DXMATRIX;
	

	return true;
}

void SnakeHead::Shutdown()
{
	if (m_Head)
	{
		delete m_Head;
		m_Head = 0;
	}
}


bool SnakeHead::Frame()
{


	//This checks if the player should die
	if (indexPos % 10 == 0)
	{
		if (whatIsDirection == 4)
		{
			return false;
		}
	}

	if (indexPos % 10 == 9)
	{
		if (whatIsDirection == 3)
		{
			return false;
		}
	}

	if (indexPos - 10 <= -1)
	{
		if (whatIsDirection == 1)
		{
			return false;
		}
	}

	if (indexPos + 10 >= 101)
	{
		if (whatIsDirection == 2)
		{
			return false;
		}
	}
	
	if (indexPos <= -1) 
	{
		return false;
	}

	if (indexPos >= 101)
	{
		return false;
	}

	//This changes position

	if (whatIsDirection == 1) 
	{
		indexPos = indexPos - 10;
		//whatIsDirection = 1;
		//This is left.
	}

	if (whatIsDirection == 2) 
	{
		indexPos = indexPos + 10;
		//whatIsDirection = 2;
		//This is right.
	}

	if (whatIsDirection == 3) 
	{
		indexPos = indexPos + 1;
		//whatIsDirection = 3;
		//This is up.
	}

	if (whatIsDirection == 4) 
	{
		indexPos = indexPos - 1;
		//whatIsDirection = 4;
		//This is down.
	}

	headPosition = &m_Grid->gridPosition[indexPos];

	return true;
}

bool SnakeHead::Input()
{

	if (m_Input->IsLeftPressed()) {
	
		whatIsDirection = 1;
	}

	if (m_Input->IsRightPressed()) {
		
		whatIsDirection = 2;
	}

	if (m_Input->IsUpPressed()) {

		whatIsDirection = 3;
	}

	if (m_Input->IsDownPressed()) {
	
		whatIsDirection = 4;
	}

	return false;
}

ModelClass * SnakeHead::GetModel()
{
	return m_Head;
}

D3DXMATRIX * SnakeHead::GetWorldMatrix()
{
	return headPosition;
}

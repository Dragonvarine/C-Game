////////////////////////////////////////////////////////////////////////////////
// Filename: SnakeHead.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SNAKEHEAD_H_
#define _SNAKEHEAD_H_


//////////////
// INCLUDES //
//////////////


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "modelclass.h"
#include "inputclass.h"
#include "gridclass.h"




////////////////////////////////////////////////////////////////////////////////
// Class name: SnakeHead
////////////////////////////////////////////////////////////////////////////////
class SnakeHead
{
private:


public:
	SnakeHead();
	SnakeHead(const SnakeHead&);
	~SnakeHead();



	bool Initialize(ID3D11Device* device, HWND hwnd, InputClass* input, gridclass* grid);
	void Shutdown();
	bool Frame();
	bool Input();

public:

	ModelClass* GetModel();
	D3DXMATRIX* GetWorldMatrix();
	int indexPos = 55;
	int whatIsDirection = 0;

private:

	ModelClass* m_Head;
	InputClass* m_Input;
	gridclass* m_Grid;

private:

	D3DXVECTOR3 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 position;
	D3DXVECTOR3 forwardVector;
	D3DXVECTOR3 sideVector;
	D3DXMATRIX* headPosition;

	float speed = 1.0f;
};

#endif

////////////////////////////////////////////////////////////////////////////////
// Filename: snakemain.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SNAKEMAIN_H_
#define _SNAKEMAIN_H_


//////////////
// INCLUDES //
//////////////


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "modelclass.h"
#include "inputclass.h"
#include "snakehead.h"
#include "gridclass.h"




////////////////////////////////////////////////////////////////////////////////
// Class name: snakemain
////////////////////////////////////////////////////////////////////////////////
class snakemain
{
private:

	SnakeHead* m_Shead;

public:
	snakemain();
	snakemain(const snakemain&);
	~snakemain();

	bool Initialize(ID3D11Device* device, HWND hwnd, gridclass* grid, SnakeHead* Shead);
	void Shutdown();
	bool Frame(gridclass* grid, SnakeHead* head);


public:

	int headIndex = 0;
	int food = 5;
	ModelClass* GetModel();
	D3DXMATRIX* GetWorldMatrix();

private:
	ModelClass* m_Tail;
	InputClass* m_Input;
	D3DXMATRIX* tailPositions;
	gridclass* m_Grid;

	D3DXMATRIX awayPosition;



	

private:

	
	int snakeAmount = 0;
};

#endif

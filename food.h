////////////////////////////////////////////////////////////////////////////////
// Filename: food.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FOOD_H_
#define _FOOD_H_


//////////////
// INCLUDES //
//////////////


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "modelclass.h"
#include "gridclass.h"
#include "snakemain.h"
#include "SnakeHead.h"
#include <cstdlib>


////////////////////////////////////////////////////////////////////////////////
// Class name: Food
////////////////////////////////////////////////////////////////////////////////
class Food
{
private:

	snakemain* m_Tail;
	SnakeHead* m_Head;

public:
	Food();
	Food(const Food&);
	~Food();

	bool Initialize(ID3D11Device* device, HWND hwnd, gridclass* grid, SnakeHead* head, snakemain* tail);
	void Shutdown();
	bool Frame();

	int foodIndex = rand() % 100 + 1;

public:

	ModelClass* GetModel();
	D3DXMATRIX* GetWorldMatrix();

private:

	ModelClass* m_Food;
	gridclass* m_Grid;

private:
	D3DXMATRIX* foodPosition;
};

#endif

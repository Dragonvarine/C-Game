////////////////////////////////////////////////////////////////////////////////
// Filename: playerclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _PLAYERCLASS_H_
#define _PLAYERCLASS_H_


//////////////
// INCLUDES //
//////////////


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "modelclass.h"
#include "inputclass.h"



////////////////////////////////////////////////////////////////////////////////
// Class name: PlayerClass
////////////////////////////////////////////////////////////////////////////////
class PlayerClass
{
private:


public:
	PlayerClass();
	PlayerClass(const PlayerClass&);
	~PlayerClass();

	bool Initialize(ID3D11Device* device, HWND hwnd, InputClass* input, ModelClass& outModel);
	void Shutdown();
	bool Frame();


public:

	ModelClass* GetModel();
	D3DXMATRIX GetWorldMatrix();

private:

	ModelClass* m_Model;
	InputClass* m_Input;

private:

	D3DXVECTOR3 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 position;
	D3DXVECTOR3 forwardVector;

	float speed = 1.0f;
};

#endif
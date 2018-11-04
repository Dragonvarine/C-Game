#include "playerclass.h"

PlayerClass::PlayerClass()
{
	m_Model[100];
	m_Input = 0;
	int m_Bodyamount[100];
}

PlayerClass::PlayerClass(const PlayerClass &)
{
}

PlayerClass::~PlayerClass()
{
}

bool PlayerClass::Initialize(ID3D11Device* device, HWND hwnd, InputClass* input, ModelClass& outModel)
{
	bool result;

	m_Input = input;

	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	for (int i = 0; i < 100; i++) {
		result = m_Model->Initialize(device, "../Engine/data/cube.txt", L"../Engine/data/blue.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the player model object.", L"Error", MB_OK);
			return false;
		}
	}


	scale = D3DXVECTOR3(-3.5f, -1.5f, 0.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	forwardVector = D3DXVECTOR3(0.0f, 0.0, 1.0f);


	return true;
}

void PlayerClass::Shutdown()
{
	if (m_Model)
	{
		delete m_Model;
		m_Model = 0;
	}
}

bool PlayerClass::Frame()
{
	if (m_Input->IsLeftPressed()) {
		//Turn left
	}

	if (m_Input->IsRightPressed()) {
		//Turn right
	}

	if (m_Input->IsUpPressed()) {
		position += forwardVector * speed;
	}

	if (m_Input->IsDownPressed()) {
		position += forwardVector * speed;
	}
	return true;
}

ModelClass* PlayerClass::GetModel()
{
	return m_Model;
}

D3DXMATRIX PlayerClass::GetWorldMatrix()
{
	D3DXMATRIX worldMatrix;
	D3DXQUATERNION qRotation;

	D3DXQuaternionRotationYawPitchRoll(&qRotation, rotation.x, rotation.y, rotation.z);
	D3DXMatrixTransformation(&worldMatrix, NULL, NULL, &scale, NULL, &qRotation, &position);
	return worldMatrix;
}

////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "applicationclass.h"


ApplicationClass::ApplicationClass()
{
	m_Input = 0;
	m_Direct3D = 0;
	m_Camera = 0;
	//m_Terrain = 0;
	m_Timer = 0;
	m_Position = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_FontShader = 0;
	m_Text = 0;
	//m_TerrainShader = 0;
	m_Light = 0;
	m_LightShader = 0;
	m_Player = 0;
	m_Snakeplayer = 0;
	m_Snakehead = 0;
	m_Grid = 0;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	float cameraX, cameraY, cameraZ;
	D3DXMATRIX baseViewMatrix;
	char videoCard[128];
	int videoMemory;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if(!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize DirectX 11.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, 0.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Set the initial position of the camera.
	cameraX = 25.0f;
	cameraY = 25.0f;
	cameraZ = 25.0f;

	m_Camera->SetPosition(cameraX, cameraY, cameraZ);

	/* Create the terrain object.
	m_Terrain = new TerrainClass;
	if(!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(m_Direct3D->GetDevice(), "../Engine/data/heightmap01.bmp", L"../Engine/data/dirt01.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}*/



	// Create the timer object.
	m_Timer = new TimerClass;
	if(!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if(!m_Position)
	{
		return false;
	}

	// Set the initial position of the viewer to the same as the initial camera position.
	m_Position->SetPosition(cameraX, cameraY, cameraZ);

	// Create the fps object.
	m_Fps = new FpsClass;
	if(!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the cpu object.
	m_Cpu = new CpuClass;
	if(!m_Cpu)
	{
		return false;
	}

	// Initialize the cpu object.
	m_Cpu->Initialize();

	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if(!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the text object.
	m_Text = new TextClass;
	if(!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Retrieve the video card information.
	m_Direct3D->GetVideoCardInfo(videoCard, videoMemory);

	// Set the video card information in the text object.
	result = m_Text->SetVideoCardInfo(videoCard, videoMemory, m_Direct3D->GetDeviceContext());
	if(!result)
	{
		MessageBox(hwnd, L"Could not set video card info in the text object.", L"Error", MB_OK);
		return false;
	}

	/* Create the terrain shader object.
	m_TerrainShader = new TerrainShaderClass;
	if(!m_TerrainShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}*/

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	/*m_Player = new PlayerClass;
	if (!m_Player)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_Player->Initialize(m_Direct3D->GetDevice(), hwnd, m_Input, *m_RenderList[0]);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the player object.", L"Error", MB_OK);
		return false;
	}*/

	m_Grid = new gridclass;

	result = m_Grid->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the grid object.", L"Error", MB_OK);
		return false;
	}

	m_Snakehead = new SnakeHead;
	if (!m_Snakehead)
	{
		return false;
	}

	result = m_Snakehead->Initialize(m_Direct3D->GetDevice(), hwnd, m_Input, m_Grid);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the player object.", L"Error", MB_OK);
		return false;
	}

	//Create snake object.
	m_Snakeplayer = new snakemain;
	if (!m_Snakeplayer)
	{
		return false;
	}

	//Initialize test.
	result = m_Snakeplayer->Initialize(m_Direct3D->GetDevice(), hwnd, m_Grid, m_Snakehead);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the player object.", L"Error", MB_OK);
		return false;
	}

	m_Food = new Food;
	if (!m_Food)
	{
		return false;
	}


	result = m_Food->Initialize(m_Direct3D->GetDevice(), hwnd, m_Grid, m_Snakehead, m_Snakeplayer);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the food object.", L"Error", MB_OK);
		return false;
	}



	// Initialize the light object.
	m_Light->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDiffuseColor(0.2f, 0.2f, 0.2f, 1.0f);
	m_Light->SetDirection(-0.5f, -0.5f, 0.0f);


	return true;
}



void ApplicationClass::Shutdown()
{
	if (m_Food)
	{
		delete m_Food;
		m_Food = 0;
	}

	if (m_Grid)
	{
		delete m_Grid;
		m_Grid = 0;
	}

	// Release the snake model.
	if (m_Snakeplayer)
	{
		delete m_Snakeplayer;
		m_Snakeplayer = 0;
	}

	// Release the snake head.
	if (m_Snakehead)
	{
		delete m_Snakehead;
		m_Snakehead = 0;
	}

	// Release the model object.
	if (m_Player)
	{
		delete m_Player;
		m_Player = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	/* Release the terrain shader object.
	if(m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}*/

	// Release the text object.
	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the font shader object.
	if(m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the cpu object.
	if(m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	// Release the fps object.
	if(m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the timer object.
	if(m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	/* Release the terrain object.
	if(m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}*/

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the Direct3D object.
	if(m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool ApplicationClass::Frame()
{
	bool result;



	// Read the user input.
	result = m_Input->Frame();
	if(!result)
	{
		return false;
	}
	
	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Update the system stats.
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	tCounter += m_Timer->GetTime();
	if (tCounter > 1000)
	{
		result = m_Snakeplayer->Frame(m_Grid, m_Snakehead);
		if (!result)
		{
			return false;
		}


		result = m_Snakehead->Frame();
		if (!result)
		{
			return false;
		}

		tCounter = 0;
	}

	result = m_Food->Frame();
	if (!result)
	{
		return false;
	}

	if (!m_Food)
	{
		Food::Food();
	}

	// Update the FPS value in the text object.
	result = m_Text->SetFps(m_Fps->GetFps(), m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}
	
	// Update the CPU usage value in the text object.
	result = m_Text->SetCpu(m_Cpu->GetCpuPercentage(), m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	/*result = m_Player->Frame();
	if (!result) 
	{
		return false;
	}*/

	// Render the graphics.
	result = RenderGraphics();
	if(!result)
	{
		return false;
	}

	m_Snakehead->Input();
	

	return result;
}

bool ApplicationClass::RenderGraphics()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;


	// Clear the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	// Render the terrain buffers.
	//m_Terrain->Render(m_Direct3D->GetDeviceContext());

	// Render the terrain using the terrain shader.
	//result = m_TerrainShader->Render(m_Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
									// m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), m_Terrain->GetTexture());
	//if(!result)
	//{
		//return false;
	//}



	m_Snakehead->GetModel()->Render(m_Direct3D->GetDeviceContext());
	result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Snakehead->GetModel()->GetIndexCount(), *m_Snakehead->GetWorldMatrix(), viewMatrix, projectionMatrix, m_Snakehead->GetModel()->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor());
	if (!result)
	{
		return false;
	}

	for (int i = 0; i < m_Snakeplayer->food; i++) {

		m_Snakeplayer->GetModel()[i].Render(m_Direct3D->GetDeviceContext());

		result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Snakeplayer->GetModel()[i].GetIndexCount(), m_Snakeplayer->GetWorldMatrix()[i], viewMatrix, projectionMatrix, m_Snakeplayer->GetModel()->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor());
		if (!result)
		{
			return false;
		}
	}

	for (int i = 0; i < 100; i++)
	{
		m_Grid->GetModel()[i].Render(m_Direct3D->GetDeviceContext());
		ModelClass* temp = &m_Grid->GetModel()[i];

		result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), temp->GetIndexCount(), m_Grid->GetWorldMatrix()[i], viewMatrix, projectionMatrix, m_Grid->GetModel()->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor());
		if (!result)
		{
			return false;
		}
	}

	m_Food->GetModel()->Render(m_Direct3D->GetDeviceContext());
	result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Food->GetModel()->GetIndexCount(), *m_Food->GetWorldMatrix(), viewMatrix, projectionMatrix, m_Food->GetModel()->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor());
	if (!result)
	{
		return false;
	}

	// Render the buffers.
	/*m_Player->GetModel()->Render(m_Direct3D->GetDeviceContext());

	// Render the terrain using the terrain shader.
	result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Player->GetModel()->GetIndexCount(), m_Player->GetWorldMatrix(), viewMatrix, projectionMatrix, m_Player->GetModel()->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor());
	if (!result)
	{
		return false;
	}*/

	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();
		
	// Turn on the alpha blending before rendering the text.
	m_Direct3D->TurnOnAlphaBlending();

	m_Text->SetFps(m_Snakehead->indexPos, m_Direct3D->GetDeviceContext());

	// Render the text user interface elements.
	result = m_Text->Render(m_Direct3D->GetDeviceContext(), m_FontShader, worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_Direct3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_Direct3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}
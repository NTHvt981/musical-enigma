#include "IGame.h"

namespace rgf
{
std::shared_ptr<IGame> IGame::m_instance = NULL;

IGame::IGame(HWND hWnd, HINSTANCE hInstance)
{
	this->m_hWnd = hWnd;
	this->m_hInstance = hInstance;
}

void IGame::Render()
{
	auto graphic = IGraphic::GetInstance();
	LPDIRECT3DDEVICE9 d3ddev = graphic->GetDirect3DDevice();
	LPD3DXSPRITE spriteHandler = graphic->GetSpriteHandler();
	LPDIRECT3DSURFACE9 backBuffer = graphic->GetBackBuffer();

	if (d3ddev->BeginScene() == D3D_OK)
	{
		// Clear the whole window with a color
		d3ddev->ColorFill( backBuffer, NULL, BACKGROUND_COLOR );
		spriteHandler->Begin( D3DXSPRITE_ALPHABLEND );

		// Draw here
		this->DuringRender();

		spriteHandler->End();
		d3ddev->EndScene();
	}

	// Display back buffer content to the screen
	d3ddev->Present( NULL, NULL, NULL, NULL );
}

void IGame::CleanResources()
{
}

std::shared_ptr<IGame> IGame::GetInstance()
{
	if (IGame::m_instance == NULL)
	{
		throw("Instance of game is null when GetInstance");
	}
	return IGame::m_instance;
}

void IGame::InitInstance(std::shared_ptr<IGame> game)
{
	IGame::m_instance = game;
}

void IGame::Init()
{
	IGraphic::GetInstance()->Init( m_hWnd );
#pragma region reset the window true width and height
	LPRECT rect = new RECT{};
	auto result = GetClientRect( m_hWnd, rect );
	m_info.m_windowClientWidth = rect->right;
	m_info.m_windowClientHeight = rect->bottom;
#pragma endregion

	//CInput::GetInstance()->Init( hInstance, hWnd );
	//Sound::DirectSound_Init( hWnd );

	/// <summary>
	/// Setup camera
	/// </summary>
	//CCamera* camera = new CCamera( CAMERA_WIDTH * CAMERA_SCALE, CAMERA_HEIGHT * CAMERA_SCALE, CAMERA_SCALE );
	//CCamera::SetInstance( *camera );

	//mapGrid = DivideGrids(GAME_WIDTH, GAME_HEIGHT, GRID_WIDTH, GRID_HEIGHT);
	//grid_count_width = mapGrid[0].size();
	//grid_count_height = mapGrid.size();

	//manager.Init();
}

void IGame::Run()
{
	//Load resource to the game
	LoadResources();

	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount64();
	DWORD tickPerFrame = 1000 / m_info.m_frameRate;

	try
	{
		while (!done)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) done = 1;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			DWORD now = GetTickCount64();

			// dt: the time between (beginning of last frame) and now
			// this frame: the frame we are about to render
			DWORD dt = now - frameStart;

			//Heart of the game
			if (dt >= tickPerFrame)
			{
				frameStart = now;

				Update(dt / 10);
				Render();
			}
			//else
			//	Sleep(tickPerFrame - dt);
		}
	}
	catch (const std::exception& ex)
	{
		rgf::DebugOut(L"[ERROR] Exception in Run method in Game %s\n", ex.what());
		return;
	}

	//Clean the resources
	CleanResources();
}

unsigned int IGame::GetFrameRate()
{
	return m_info.m_frameRate;
}

void IGame::SetFrameRate( unsigned int fps )
{
	m_info.m_frameRate = fps;
}

IGameInfo IGame::GetGameInfo()
{
	return m_info;
}

void IGame::UpdateGameInfo( const IGameInfo i_gameInfo )
{
	m_info = i_gameInfo;
}

HWND CreateGameWindow( HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight )
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof( WNDCLASSEX );

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
#pragma region Recalculate the width and height (add the task bar)
	LPRECT rect = new RECT{};
	rect->right = ScreenWidth;
	rect->bottom = ScreenHeight;
	auto result = AdjustWindowRect( rect, wc.style, true );
	ScreenWidth = rect->right - rect->left;
	ScreenHeight = rect->bottom - rect->top;
#pragma endregion

	//Try this to see how the debug function prints out file and line 
	//wc.hInstance = (HINSTANCE)-100; 

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage( hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE );;
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx( &wc );

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			WINDOW_TITLE,
			WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,	//window style (unresizable)
			// WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,	//window style (resizable)
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL );

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		MessageBox( hWnd, L"Error create window handle", L"Error", MB_OK );
		return 0;
	}

	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );

	return hWnd;
}

LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
		//if the player close the window
	case WM_DESTROY:
		//tell window to kill this program
		PostQuitMessage( 0 );
		break;
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}
}	//namespace rgf
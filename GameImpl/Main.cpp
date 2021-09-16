#include "Main.h"
#include "CGame.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd = rgf::CreateGameWindow(hInstance, 
									   nCmdShow, 
									   WINDOW_WIDTH, 
									   WINDOW_HEIGHT);
	std::shared_ptr<CGame> game(new CGame(hwnd, hInstance));
	rgf::IGame::InitInstance(game);
	rgf::IGame::GetInstance()->Init();
	rgf::IGame::GetInstance()->Run();

	return 0;
}

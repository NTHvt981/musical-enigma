#pragma once
#include <memory>
#include <windows.h>

#include "utils/Debug.h"
#include "entity/IEntity.h"
#include "RgfConstants.h"
#include "IGameInfo.h"
#include "lifecycle/ILifeCycle.h"

namespace rgf
{
/// <summary>
/// [singleton] Heart of the game, init and run in main file
/// </summary>
class IGame: public ILifeCycle
{
public:
	IGame( HWND hWnd, HINSTANCE hInstance );
	static std::shared_ptr<IGame> GetInstance();
	static void InitInstance(std::shared_ptr<IGame> game);
	void Init() override;
	/// <summary>
	/// load resource -> (update/render) loop
	/// </summary>
	void Run();
	unsigned int GetFrameRate();
	void SetFrameRate( unsigned int fps );
	IGameInfo GetGameInfo();
	void UpdateGameInfo( const IGameInfo i_gameInfo );

protected:
	HWND m_hWnd = NULL;									// Window handle
	HINSTANCE m_hInstance = NULL;
	static std::shared_ptr<IGame> m_instance;
	IGameInfo m_info;

	virtual void LoadResources() = 0;
	virtual void LoadTextures() = 0;
	virtual void LoadSprites() = 0;

	virtual void Update(DWORD dt) = 0;
	void Render() override;
	virtual void DuringRender() = 0;

	void CleanResources();
};

HWND CreateGameWindow( HINSTANCE hInstance, int nCmdShow, int i_ScreenWidth, int i_ScreenHeight );
LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
}	//namespace rgf


#include "CGame.h"

CGame::CGame( HWND hWnd, HINSTANCE hInstance ): IGame( hWnd, hInstance )
{
}

void CGame::DuringRender()
{
	m_redBlock->Render();
	m_yellowBlock->Render();
	m_blueBlock->Render();
	m_greenBlock->Render();
}

void CGame::Update( DWORD dt )
{
	m_redBlock->Update( dt );
	m_yellowBlock->Update( dt );
	m_blueBlock->Update( dt );
	m_greenBlock->Update( dt );
}

void CGame::LoadResources()
{
	LoadTextures();
	LoadSprites();

	m_redBlock = std::make_shared<CBlock>( CBlock( ID_RED_BLOCK, m_info, 
											  rgf::IEntityLib::GetInstance()->GetNewId()) );
	m_yellowBlock = std::make_shared<CBlock>( CBlock( ID_YELLOW_BLOCK, m_info,
										   rgf::IEntityLib::GetInstance()->GetNewId() ) );
	m_blueBlock = std::make_shared<CBlock>( CBlock( ID_BLUE_BLOCK, m_info,
										   rgf::IEntityLib::GetInstance()->GetNewId() ) );
	m_greenBlock = std::make_shared<CBlock>( CBlock( ID_GREEN_BLOCK, m_info,
										   rgf::IEntityLib::GetInstance()->GetNewId() ) );
	m_redBlock->Init();
	m_blueBlock->Init();
	m_yellowBlock->Init();
	m_greenBlock->Init();

	m_blueBlock->SetPosition( rgf::Vector( 300, 0 ) );
	m_yellowBlock->SetPosition( rgf::Vector( 0, 400 ) );
	m_greenBlock->SetPosition( rgf::Vector( 600, 200 ) );

	m_blueBlock->SetVelocity( rgf::Vector( 3, 5 ) );
	m_redBlock->SetVelocity( rgf::Vector( 5, 5 ) );
	m_yellowBlock->SetVelocity( rgf::Vector( 8, 2 ) );
	m_greenBlock->SetVelocity( rgf::Vector( 3, 7 ) );
}

void CGame::LoadTextures()
{
	auto lib = rgf::ITextureLib::GetInstance();
	lib->Add( FOUR_COLOR_BLOCK_TEXTURE_ID, FOUR_COLOR_BLOCK_TEXTURE_PATH );
}

void CGame::LoadSprites()
{
	auto texLib = rgf::ITextureLib::GetInstance();
	auto spriteLib = rgf::ISpriteLib::GetInstance();

	auto blockTex = texLib->Get( FOUR_COLOR_BLOCK_TEXTURE_ID );

	spriteLib->Add( ID_RED_BLOCK, 0, 0, 63, 63, blockTex );
	spriteLib->Add( ID_YELLOW_BLOCK, 64, 0, 63+64, 63, blockTex );
	spriteLib->Add( ID_GREEN_BLOCK, 0, 64, 63, 63+64, blockTex );
	spriteLib->Add( ID_BLUE_BLOCK, 64, 64, 63+64, 63+64, blockTex );
}

void CGame::Destroy()
{
}

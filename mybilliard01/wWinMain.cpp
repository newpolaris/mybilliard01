//--------------------------------------------------------------------------------------
// File: SimpleSample.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "StdAfx.h"
#include "my_app.h"



//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    //_CrtSetBreakAlloc( 26837 );
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    SetDllDirectory( ConstString::dllDirectoryForColladaDOM().c_str() );

    RenderEventListenerImp * renderEvent = new RenderEventListenerImp( L"..\\asset\\1ball1box.triangles.dae", L"..\\asset\\1ball1box.physx.xml" );

    RenderWin32DX9 * render = new RenderWin32DX9Imp();
    render->addRenderEventListener( renderEvent );


    InputListenerImp * inputListener = new InputListenerImp( renderEvent );

    ApplicationWin32 * app = new ApplicationWin32Imp();
    app->setRender( render );
    app->addKeyboardListener( inputListener );
    app->addMouseListener( inputListener );
    app->addWin32MessageListener( inputListener );
    app->setScreenWidth( 640 );
    app->setScreenHeight( 480 );
    app->setWindowedMode( true );
    app->setScreenTitle( ConstString::windowTitle() );
    app->start();

    delete app;
    delete inputListener;
    delete render;
    delete renderEvent;

    return 0;
}









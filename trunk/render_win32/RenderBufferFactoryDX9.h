#pragma once
namespace my_render_win32_dx9 {


INTERFACE_ RenderBufferFactoryDX9
    : EXTENDS_INTERFACE_( RenderBufferFactory )
    , EXTENDS_INTERFACE_( RenderEventListener )
{
public:
};


}
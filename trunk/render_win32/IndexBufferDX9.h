#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE IndexBufferDX9 : EXTENDS_INTERFACE_STATIC_( IndexBuffer ) {

    virtual size_t getSizeInByte() = 0;
    virtual size_t getNumberOfByteForEach() = 0; // 2 or 4

    virtual void setIndexBufferDX9( LPDIRECT3DINDEXBUFFER9 ) = 0;
    virtual LPDIRECT3DINDEXBUFFER9 getIndexBufferDX9() = 0;

    virtual void writeOntoDevice( DWORD lockingFlags ) = 0;
    virtual void releaseIndexBufferDX9() = 0;
};


}

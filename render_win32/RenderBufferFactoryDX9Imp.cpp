#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


RenderBufferFactoryDX9Imp::RenderBufferFactoryDX9Imp( LPDIRECT3DDEVICE9 d3dDevice )
: d3dDevice_( d3dDevice )
, bNeedToUpdate_( false )
{    
    if( NULL == d3dDevice ) throw exception();
}  

void RenderBufferFactoryDX9Imp::acquireEffectPool() {
    LPD3DXEFFECTPOOL d3dEffectPool;
    D3DXCreateEffectPool( & d3dEffectPool );
    d3dEffectPool_ = ID3DXEffectPoolPtr( d3dEffectPool, ComReleaser< ID3DXEffectPool >() );
}
void RenderBufferFactoryDX9Imp::releaseEffectPool() {
    d3dEffectPool_.reset();
}

void RenderBufferFactoryDX9Imp::pushBackToReadyQueue( int resourceType, ReleasableResourceDX9Ptr newResource ) {
    resources_[ resourceType ][ EREADY_QUEUE ].push_back( newResource );
    bNeedToUpdate_ = true;
}
void RenderBufferFactoryDX9Imp::pushBackToActiveQueue( int resourceType, ReleasableResourceDX9Ptr newResource) {
    resources_[ resourceType ][ EACTIVE_QUEUE ].push_back( newResource );
}

Surface * RenderBufferFactoryDX9Imp::getBackBuffer( size_t whichBackBuffer ) {
    IDirect3DSurface9 * newDXSurface;
    const HRESULT hr = getD3D9Device()->GetBackBuffer( 0, whichBackBuffer, D3DBACKBUFFER_TYPE_MONO, &newDXSurface );
    if( FAILED( hr ) ) {
        DXUT_ERR( L"RenderWin32DX9Imp::getBackBuffer", hr );
        return NULL;
    }

    SurfaceDX9Ptr newSurface = SurfaceDX9Ptr( new SurfaceDX9Imp( newDXSurface ) );
    pushBackToActiveQueue( E_SURFACES, newSurface );
    return newSurface.get();
}

bool RenderBufferFactoryDX9Imp::destroy( ReleasableResourceDX9 * victim )
{
    for( size_t i = 0; i < SIZE_OF_RESOURCETYPES; ++i ) {
        for( size_t j = 0; j < SIZE_OF_QUEUE; ++j ) {
            if( remove_only_one_pointer< ReleasableResources >( resources_[ ( SIZE_OF_RESOURCETYPES - 1 ) - i ][ j ], victim ) )
                return true;
        }    
    }
    return false;
}

void RenderBufferFactoryDX9Imp::destroyAll() {
    for( size_t i = 0; i < SIZE_OF_RESOURCETYPES; ++i ) {
        for( size_t j = 0; j < SIZE_OF_QUEUE; ++j ) {
            resources_[ ( SIZE_OF_RESOURCETYPES - 1 ) - i ][ j ].clear();
        }    
    }
}

bool RenderBufferFactoryDX9Imp::destroyEffectShader( EffectShader * victim ) {
    return destroy( dynamic_cast< ReleasableResourceDX9 * >( victim ) ); 
}

bool RenderBufferFactoryDX9Imp::destroyVertexBuffer( VertexBuffer * victim ) {
    return destroy( dynamic_cast< ReleasableResourceDX9 * >( victim ) ); 
}

bool RenderBufferFactoryDX9Imp::destroySurface( Surface * victim ) {
    return destroy( dynamic_cast< ReleasableResourceDX9 * >( victim ) ); 
}

bool RenderBufferFactoryDX9Imp::destroyTexture( Texture * victim ) {
    return destroy( dynamic_cast< ReleasableResourceDX9 * >( victim ) ); 
}

void RenderBufferFactoryDX9Imp::init() {
    if( NULL == d3dEffectPool_ ) acquireEffectPool();
}

void RenderBufferFactoryDX9Imp::displayReset( RenderBufferFactory *, int x, int y, int width, int height ) {
    acquireResources();
}

void RenderBufferFactoryDX9Imp::update( RenderBufferFactory *, float elapsedTime ) {
    acquireResources();
}

void RenderBufferFactoryDX9Imp::displayLost() {
    releaseResourceByType( E_EFFECT_SHADERS );
    releaseResourceByType( E_TEXTURE );
    releaseResourceByType( E_SURFACES );
    releaseResourceByType( E_DYNAMIC_VERTICES );
    releaseResourceByType( E_STATIC_VERTICES );
 }

void RenderBufferFactoryDX9Imp::destroy() {
    destroyAll();
    releaseEffectPool();
}

void RenderBufferFactoryDX9Imp::acquireResources()
{
    if( false == bNeedToUpdate_ ) return;
    bNeedToUpdate_ = false;

    if( NULL == d3dEffectPool_ ) acquireEffectPool();
    for( size_t i = 0; i < SIZE_OF_RESOURCETYPES; ++i )
        acquireResourcesByType( i );
}

void RenderBufferFactoryDX9Imp::acquireResourcesByType( int resourceType ) {
    MY_FOR_EACH( ReleasableResources, iter, resources_[ resourceType ][ EREADY_QUEUE ] ) {
        const bool bRst = (*iter)->acquireResource();
        assert( bRst );
    }

    resources_[ resourceType ][ EACTIVE_QUEUE ].splice( resources_[ resourceType ][ EACTIVE_QUEUE ].end(), resources_[ resourceType ][ EREADY_QUEUE ] );
}

void RenderBufferFactoryDX9Imp::releaseResourceByType( int resourceType )
{
    MY_FOR_EACH( ReleasableResources, iter, resources_[ resourceType ][ EACTIVE_QUEUE ] )
        (*iter)->releaseResource();

    resources_[ resourceType ][ EREADY_QUEUE ].splice( resources_[ resourceType ][ EREADY_QUEUE ].end(), resources_[ resourceType ][ EACTIVE_QUEUE ] );
    bNeedToUpdate_ = true;
}


LPDIRECT3DDEVICE9 RenderBufferFactoryDX9Imp::getD3D9Device() {
    return d3dDevice_;
}


}
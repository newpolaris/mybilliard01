#pragma once
namespace my_render {


MY_INTERFACE Scene {
    virtual ~Scene() {}

    virtual void setColladaFactoryBeforeLoad( ColladaFactory * factory ) PURE;
    virtual void setRenderFactory( RenderBufferFactory * renderFactory ) PURE;

    virtual bool load( wstring filename ) PURE;

    virtual void update( float elapsedTime ) PURE;
    virtual void display( Render * ) PURE;

    virtual vector< wstring > getVisualSceneIDs() PURE;
    virtual wstring getDefaultVisualSceneID() PURE;
    virtual bool hasDefaultVisualSceneID() PURE;

    virtual wstring getCurrentVisualSceneID() PURE;
    virtual bool setCurrentVisualScene( wstring sceneID ) PURE;

    virtual Node * getVisualScene( wstring id ) PURE;
    virtual Node * getNode( wstring nodeID ) PURE;
    virtual Geometry * getGeometryByID( wstring id ) PURE;
    virtual Geometry * getGeometryByName( wstring name ) PURE;

};

}
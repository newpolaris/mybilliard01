#pragma once
namespace my_render {


MY_INTERFACE Scene {
    virtual ~Scene() {}

    virtual bool load( wstring filename, Factory * factory ) = 0;

    virtual void update() = 0;
    virtual void render( Render * ) = 0;

    virtual vector< wstring > getVisualSceneIDs() = 0;
    virtual wstring getDefaultVisualSceneID() = 0;

    virtual wstring getCurrentVisualSceneID() = 0;
    virtual bool setCurrentVisualScene( wstring sceneID ) = 0;

};

}
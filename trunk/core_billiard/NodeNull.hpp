#pragma once
namespace my_render {


NULL_OBJECT( Node ), public BaseNull {

    virtual Node * getParent() OVERRIDE { return NULL; }
    virtual Node * getNextSibling() OVERRIDE { return NULL; }
    virtual Node * getFirstChild() OVERRIDE { return NULL; }
    virtual size_t getNbChild() OVERRIDE { return 0; }
    virtual wstring getSID() OVERRIDE { return L""; }

    virtual bool hasParent() OVERRIDE { return false; }
    virtual bool hasNextSibling() OVERRIDE { return false; }
    virtual bool hasFirstChild() OVERRIDE { return false; }

    virtual void update( float elapsedTime ) OVERRIDE {}
    virtual void display( Render * render ) OVERRIDE {}

};


}
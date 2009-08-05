#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TestProject1
{
    class MyUserNotify: public NXU_userNotify
    {
    public:
        virtual void NXU_errorMessage(bool isError, const char *str) {
            throw exception();
        }
    } userNotify;

	[TestClass]
	public ref class MyPhysXTest
	{
	public: 
        [ClassInitialize()]
        static void MyClassInitialize(TestContext^ testContext)
        {};

        [ClassCleanup()]
        static void MyClassCleanup()
        {};

        [TestInitialize()]
        void MyTestInitialize()
        {};

        [TestCleanup()]
        void MyTestCleanup()
        {};

        [TestMethod]
        void Constructor()
        {
            MyPhysX phys;
		};

        [TestMethod]
        void LoadColladaFile()
        {
            const wstring filename = ConstString::colladaPhysXFilename();

            MyPhysX phys;
            const bool bLoad = phys.loadColladaFile( filename, &userNotify );
            Assert::IsTrue( bLoad );
            Assert::AreEqual( 2, phys.countActors() );

            {
                NxActor * const actor0 = phys.getActor( 0 );
                Assert::IsTrue( actor0 != NULL );
                Assert::AreEqual( gcnew String( L"Sphere01" ),
                    gcnew String( convertString< string, wstring >( actor0->getName() ).c_str() )
                );
            }

            {
                NxActor * const actor1 = phys.getActor( 1 );
                Assert::IsTrue( actor1 != NULL );
                Assert::AreEqual( gcnew String( L"Box01" ),
                    gcnew String( convertString< string, wstring >( actor1->getName() ).c_str() )
                );
            }
    };
    };
}

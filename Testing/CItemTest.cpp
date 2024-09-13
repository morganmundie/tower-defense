#include "pch.h"
#include "CppUnitTest.h"

#include "Item.h"
#include "TowersGame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

/// Grass item filename 
const std::wstring GrassFileName = L"grass1.png";

namespace Testing
{
    /**
    *  CItem mock derived object
    */
    class CItemMock : public CItem
    {
    public:
        /**  Constructor
         * @param city TowersGame this Item is a member of */
        CItemMock(CTowersGame* city) : CItem(city)
        {
        }

        ///  Default constructor (disabled)
        CItemMock() = delete;

        ///  Copy constructor (disabled)
        CItemMock(const CItemMock&) = delete;

        ~CItemMock() {}

        /** Accept a visitor
        * @param visitor The visitor we accept */
        virtual void Accept(CItemVisitor* visitor) override { }

        virtual void RenderEntities(Gdiplus::Graphics* graphics) {};
        
    };

	TEST_CLASS(CItemTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
        TEST_METHOD(TestConstructor)
        {
            CTowersGame game;
            CItemMock item(&game);
        }

        /**  Tests for the GetAdjacent function
        */
        TEST_METHOD(TestCItemAdjacenct)
        {
            CTowersGame game;
            int grid = CTowersGame::GridSpacing;

            // Add a center item to test
            auto center = make_shared<CItemMock>(&game);
            center->SetLocation(grid * 10, grid * 17);
            game.Add(center);

            // Upper left
            auto ul = make_shared<CItemMock>(&game);
            ul->SetLocation(grid * 8, grid * 16);
            game.Add(ul);
            game.SortTiles();

            Assert::IsTrue(center->GetAdjacent(-1, -1) == ul, L"Upper left test");
            Assert::IsTrue(center->GetAdjacent(1, -1) == nullptr, L"Upper right null test");

            // Upper right
            auto ur = make_shared<CItemMock>(&game);
            ur->SetLocation(grid * 12, grid * 16);
            game.Add(ur);

            // Lower left
            auto ll = make_shared<CItemMock>(&game);
            ll->SetLocation(grid * 8, grid * 18);
            game.Add(ll);

            // Lower right
            auto lr = make_shared<CItemMock>(&game);
            lr->SetLocation(grid * 12, grid * 18);
            game.Add(lr);

            game.SortTiles();

            Assert::IsTrue(center->GetAdjacent(1, -1) == ur, L"Upper right test");
            Assert::IsTrue(center->GetAdjacent(-1, 1) == ll, L"Lower left test");
            Assert::IsTrue(center->GetAdjacent(1, 1) == lr, L"Lower right test");
        }


        TEST_METHOD(TestCItemSetLocation)
        {
            CTowersGame game;
            CItemMock item(&game);

            Assert::AreEqual(double(0), item.GetX());
            Assert::AreEqual(double(0), item.GetY());

            item.SetLocation(17, 23);
            Assert::AreEqual(double(17), item.GetX());
            Assert::AreEqual(double(23), item.GetY());

        }

        /* 
        * Test for CItem::HitTest
        */
        TEST_METHOD(TestCItemHitTest)
        {
            // Create a item to test
            CTowersGame game;
            CItemMock item(&game);

            // Set image to grass
            item.SetImage(GrassFileName);

            // Give it a location
            // Always make the numbers different, in case they are mixed up
            item.SetLocation(100, 200);

            // Center of the item should be a true
            Assert::IsTrue(item.HitTest(100, 200));

            // Left of the item
            Assert::IsFalse(item.HitTest(60, 200));

            // Right of the item
            Assert::IsFalse(item.HitTest(200, 200));

            // Above the item
            Assert::IsFalse(item.HitTest(100, 0));

            // Below the item
            Assert::IsFalse(item.HitTest(100, 300));

            // Should be a true, within tile
            Assert::IsTrue(item.HitTest(70, 230));

        }

	};
}
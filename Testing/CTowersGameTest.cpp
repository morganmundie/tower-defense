#include "pch.h"
#include "CppUnitTest.h"

#include "TowersGame.h"
#include "Tower.h"
#include "Tower8.h"
#include "Tile.h"
#include "TileHouse.h"
#include "TileOpen.h"
#include "ItemVisitor.h"
#include "CanMoveVisitor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CTowersGameTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
        TEST_METHOD(TestCTowersGameConstructor)
        {
            CTowersGame city;
        }

        /**  Tests for the GetAdjacent function
         */
        TEST_METHOD(TestCTowersGameAdjacent)
        {
            CTowersGame city;
            int grid = CTowersGame::GridSpacing;
            
            // Add a center tile to test
            auto center = make_shared<CTileHouse>(&city);
            center->SetLocation(grid * 10, grid * 17);
            city.Add(center);

            // Upper left
            auto ul = make_shared<CTileHouse>(&city);
            ul->SetLocation(grid * 8, grid * 16);
            city.Add(ul);
            city.SortTiles();

            Assert::IsTrue(city.GetAdjacent(center, -1, -1) == ul, L"Upper left test");
            Assert::IsTrue(city.GetAdjacent(center, 1, -1) == nullptr, L"Upper right null test");

            // Upper right
            auto ur = make_shared<CTileHouse>(&city);
            ur->SetLocation(grid * 12, grid * 16);
            city.Add(ur);

            // Lower left
            auto ll = make_shared<CTileHouse>(&city);
            ll->SetLocation(grid * 8, grid * 18);
            city.Add(ll);

            // Lower right
            auto lr = make_shared<CTileHouse>(&city);
            lr->SetLocation(grid * 12, grid * 18);
            city.Add(lr);

            city.SortTiles();

            Assert::IsTrue(city.GetAdjacent(center, 1, -1) == ur, L"Upper right test");
            Assert::IsTrue(city.GetAdjacent(center, -1, 1) == ll, L"Lower left test");
            Assert::IsTrue(city.GetAdjacent(center, 1, 1) == lr, L"Lower right test");
        }

        TEST_METHOD(TestCTowersGameHitTest)
        {
            CTowersGame game;

            Assert::IsTrue(game.HitTest(100, 200) == nullptr,
                L"Testing empty game");

            shared_ptr<CTileHouse> item1 = make_shared<CTileHouse>(&game);
            item1->SetLocation(100, 200);
            game.Add(item1);

            Assert::IsTrue(game.HitTest(100, 200) == item1,
                L"Testing item at 100, 200");

            Assert::IsTrue(game.HitTest(10, 10) == nullptr,
                L"Testing no image");

            shared_ptr<CTileHouse> item2 = make_shared<CTileHouse>(&game);
            item2->SetLocation(100, 200);
            game.Add(item2);

            Assert::IsTrue(game.HitTest(100, 200) == item2,
                L"Testing when two item at 100, 200");
        }

        /**  Tests for the Iterator
         */
        TEST_METHOD(TestCTowersGameIterator)
        {
            // Construct a game object
            CTowersGame game;
                
            
            // Add some items
            auto item1 = make_shared<CTileHouse>(&game);
            auto item2 = make_shared<CTileHouse>(&game);
            auto item3 = make_shared<CTileHouse>(&game);


            
            game.Add(item1);
            game.Add(item2);
            game.Add(item3);

            // Does begin point to the first item?
            auto iter1 = game.begin();
            auto iter2 = game.end();

            Assert::IsTrue(item1 == *iter1, L"First item correct");

            ++iter1;
            Assert::IsTrue(item2 == *iter1, L"Second item correct");

            ++iter1;
            Assert::IsTrue(item3 == *iter1, L"Third item correct");

            ++iter1;
            Assert::IsFalse(iter1 != iter2);  
        }

        TEST_METHOD(TestCCanMoveVisitor)
        {
            // construct game
            CTowersGame game;


            // make items to test
            auto tower1 = make_shared<CTower8>(&game);
            auto nontower1 = make_shared<CTileHouse>(&game);
            auto open1 = make_shared<CTileOpen>(&game);

            game.Add(tower1);
            game.Add(nontower1);

            // the visitor
            CCanMoveVisitor nonTowerVisitor;
            nontower1->Accept(&nonTowerVisitor);

            Assert::IsFalse(nonTowerVisitor.GetIsTower());
            Assert::IsFalse(nonTowerVisitor.GetIsOpen());

            // the visitor
            CCanMoveVisitor towerVisitor;
            tower1->Accept(&towerVisitor);

            Assert::IsTrue(towerVisitor.GetIsTower());

            // the visitor
            CCanMoveVisitor openVisitor;
            open1->Accept(&openVisitor);

            Assert::IsFalse(openVisitor.GetIsTower());
            Assert::IsTrue(openVisitor.GetIsOpen());

        }

	};
}
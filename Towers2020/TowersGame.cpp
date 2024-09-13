/**
 * \file TowersGame.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <map>
#include <utility>
#include "TowersGame.h"
#include "TileTrees.h"
#include "TileHouse.h"
#include "TileOpen.h"
#include "TileCastle.h"
#include "TileRoad.h"
#include "Item.h"
#include "DiagTimer.h"
#include "ScoreCounter.h"
#include "ConfigureRoad.h"
#include "CanMoveVisitor.h"
#include "Balloon.h"
#include "GoButton.h"
#include "FindBalloon.h"
#include "RoadCollector.h"
using namespace std;
using namespace Gdiplus;
using namespace xmlnode;

/// Game area width in virtual pixels
const static int Width = 1224;

/// Game area height in virtual pixels
const static int Height = 1024;

/// Constructor
CTowersGame::CTowersGame()
{
}

/// Destructor
CTowersGame::~CTowersGame()
{
}

/**  Add a item to the game
 * @param item New item to add
 */
void CTowersGame::Add(shared_ptr<CItem> item)
{
	mItems.push_back(item);
}

/**
 *   Test an x,y click location to see if it clicked
 *   on some item in the game.
 *   This function relies on CItem's implementation.
 *
 * @param x X location
 * @param y Y location
 * @returns Pointer to item we clicked on or nullptr if none.
 */
shared_ptr<CItem> CTowersGame::HitTest(double x, double y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}

/**  Move an item to the front of the list of items.
 *
 * Removes item from the list and adds it to the end so it
 * will display last.
 * @param item The item to move
 */
void CTowersGame::MoveToFront(shared_ptr<CItem> item)
{
    auto loc = find(::begin(mItems), ::end(mItems), item);
    if (loc != ::end(mItems))
    {
        mItems.erase(loc);
    }

    mItems.push_back(item);
}

/**
 * Draw the game area
 * @param graphics The GDI+ graphics context to draw on
 * @param width Width of the client window
 * @param height Height of the client window
 */
void CTowersGame::OnDraw(Graphics* graphics, int width, int height)
{
    // Fill the background with black
    SolidBrush brush(Color::Black);
    graphics->FillRectangle(&brush, 0, 0, width, height);


    // automatic scaling
    mDrawWidth = width;
    mDrawHeight = height;

    graphics->TranslateTransform(mXOffset, mYOffset);
    graphics->ScaleTransform(mScale, mScale);


    // Draw the score
    
    FontFamily fontFamily(L"Arial");
    Gdiplus::Font stringFont(&fontFamily, 30);
    Gdiplus::Font counterFont(&fontFamily, 40);


    SolidBrush yellow(Color(255, 255, 0));
    graphics->DrawString(L"Score", -1,
        &stringFont, PointF(1090, 500), &yellow);

    // Draw the entire collection of top-level items (not including entities)

    for (auto item : mItems)
    {
        item->Draw(graphics);
    }

    wstring scoreValue = to_wstring(mGameScore);

    graphics->DrawString(scoreValue.c_str(), -1,
        &counterFont, PointF(1125, 550), &yellow);

    // Renders entities above the top-level items
    for (auto item : mItems)
    {
        item->RenderEntities(graphics);
    }

    if (mDrawLevelLabel)
    {
        wstring levelName = L"Level " + to_wstring(mCurrentLevel) + L" Begin";

        FontFamily fontFamily(L"Arial");
        Gdiplus::Font font(&fontFamily, 56);

        SolidBrush brown(Color(140, 70, 70));
        graphics->DrawString(levelName.c_str(), -1,
            &font, PointF(240, 456), &brown);
    }
    else if (mDrawEndLabel)
    {
        wstring levelComplete = L"Level Complete!";

        FontFamily fontFamily(L"Arial");
        Gdiplus::Font font(&fontFamily, 56);

        SolidBrush brown(Color(140, 70, 70));
        graphics->DrawString(levelComplete.c_str(), -1,
            &font, PointF(240, 456), &brown);
    }
}

/** 
 * Handle updates for animation
 * @param elapsed The time since last update 
 */
void CTowersGame::Update(double elapsed)
{
    //
    // Automatic Scaling
    //
    float scaleX = float(mDrawWidth) / float(Width);
    float scaleY = float(mDrawHeight) / float(Height);
    mScale = min(scaleX, scaleY);

    // Ensure it is centered horizontally
    mXOffset = (float)((mDrawWidth - Width * mScale) / 2);

    // Ensure it is centered vertically
    mYOffset = (float)((mDrawHeight - Height * mScale) / 2);


   // CFindBalloon baloonVisitor;

    for (auto item : mItems)
    {
        item->Update(elapsed);
        //item->Accept(&baloonVisitor);
        //baloonVisitor.FindBalloon(); // Iterate through a CTileRoad object's collection
    }

    // Used to determine if a level is over

    if (mNumBalloons == 0 && !mDrawLevelLabel && !mDrawEndLabel)
    {
        LevelComplete();
        mNumBalloons = 30;
    }

    if (mDrawLevelLabel || mDrawEndLabel)
    { 
        GetLevelTime();  //Get Level time since current load
    }

    if (mCreateNewButton) 
    {
        auto button = make_shared<CGoButton>(this);
        button->SetLocation(1150, 923);
        Add(button);
        mCreateNewButton = false;
    }


}

/**
 * Ensure the items are in the correct drawing order.
 *
 * This draws bottom to top so the items can overlapp.
 * Also builds the adjacency support since this is called whenever
 * the game is reorganized.
 */
void CTowersGame::SortTiles()
{
    // sort using a lambda expression 
    sort(::begin(mItems), ::end(mItems),
        [](const shared_ptr<CItem>& a, const shared_ptr<CItem>& b) {
            if (a->GetY() < b->GetY())
                return true;

            if (a->GetY() > b->GetY())
                return false;

            return a->GetX() > b->GetX();
        });

    BuildAdjacencies();
}

/**
 *  Get any adjacent tile.
 *
 * @param item Tile to test
 * @param dx Left/right determination, -1=left, 1=right
 * @param dy Up/Down determination, -1=up, 1=down
 * @returns Adjacent tile or nullptr if none.
 */
shared_ptr<CItem> CTowersGame::GetAdjacent(std::shared_ptr<CItem> item, int dx, int dy)
{
    return GetAdjacent(item.get(), dx, dy);
}

/**
 *  Get any adjacent tile.
 *
 * @param item Tile to test
 * @param dx Left/right determination, -1=left, 1=right
 * @param dy Up/Down determination, -1=up, 1=down
 * @returns Adjacent tile or nullptr if none.
 */
shared_ptr<CItem> CTowersGame::GetAdjacent(CItem* item, int dx, int dy)
{
    int atX = (item->GetX() + 16) / GridSpacing + dx;
    int atY = (item->GetY() - 32) / GridSpacing + dy;

    auto adj = mAdjacency.find(pair<int, int>(atX, atY));
    if (adj != mAdjacency.end())
    {
        // We found it
        return adj->second;
    }


    // If nothing found
    return nullptr; 
}

/**  Load the city from a .city XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the city from.
 */
void CTowersGame::Load(const wstring& filename)
{
    mNumBalloons = 30; // 30 balloons at start of level


    // We surround with a try/catch to handle errors
    try
    {
        // Open the document to read
        shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

        // Once we know it is open, clear the existing data
        Clear();

        //
        // Traverse the children of the root
        // node of the XML document in memory!!!!
        //
        for (auto node : root->GetChildren())
        {
            // root -> (Declarations node)
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"declarations")
            {
                for (auto node2 : node->GetChildren())
                {
                    // root -> (Items node) -> Declarations
                    XmlDeclarations(node2);
                }

            }
            // root -> (Items node)
            else if (node->GetType() == NODE_ELEMENT && node->GetName() == L"items")
            {
                for (auto node2 : node->GetChildren())
                {
                    // root -> (Items node) -> Items
                    XmlItem(node2);
                }
            }
        }

        //
        // All loaded, ensure all sorted
        //
        SortTiles();

    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }

    // file name as string
    const std::string s(filename.begin(), filename.end());

    mCurrentLevel = stoi(s.substr(12, 1)); // Get level num
    mLevelStartTime = time(NULL); //gets current time
    mDrawLevelLabel = true; // Draw Label on load
}

/** 
 * Loads in individual item objects specified by the  
 * Items section of the xml document.
 * @param node The node from the Item section that we are loading 
 */
void CTowersGame::XmlItem(const shared_ptr<CXmlNode>& node)
{
    // A pointer for the item we are loading
    shared_ptr<CItem> item;

    // We have an item. What type?
    wstring name = node->GetName();

    if (name == L"road") // Road tiles
    {
        item = make_shared<CTileRoad>(this);
    }
    else if (name == L"open") // Grass tiles
    {
        item = make_shared<CTileOpen>(this);
    }
    else if (name == L"house") // Pad tiles
    {
        item = make_shared<CTileHouse>(this);
    }
    else if (name == L"trees") // House tiles
    {
        item = make_shared<CTileTrees>(this);
    }

    name = node->GetAttributeValue(L"id", L"");

    // If mDeclarations has not been made, then declarations were not included, or
    // some formatting error has occurred.
    if (mDeclarations.size() != 0)
    {

    }

    if (item != nullptr)
    {
        item->XmlLoad(node);
        Add(item);
    }
}

/**
 * Stores blueprints of individual objects specified by the
 * Declarations section of the xml document.
 * @param node The node from the Item section that we are loading
 */
void CTowersGame::XmlDeclarations(const shared_ptr<CXmlNode>& node)
{
    map<wstring, wstring> attributes;

    // If new attributes are in the xml node, then add them here
    attributes[L"name"] = node->GetName();
    attributes[L"id"] = node->GetAttributeValue(L"id", L"");
    attributes[L"image"] = node->GetAttributeValue(L"image", L"");
    attributes[L"type"] = node->GetAttributeValue(L"type", L"");

    // A seperate container for the information about the visited node*   \n

    mDeclarations.push_back(attributes);
}

/**	
 * Changes the state of the go button. Deletes the button afterwards. 
 * @param item The Go button
 */
void CTowersGame::PressGoButton(shared_ptr<CItem> item)
{
    mGameStarted = true;
    DeleteItem(item); // Deletes the go button

    StartLevel(0); // TODO
}

/** 
 * Starts a loaded level by finding the starter tile and ordering balloons to spawn.
 * @param difficulty The difficulty of the level. Not depenant on the level number. 
 */
void CTowersGame::StartLevel(int difficulty)
{
    CConfigureRoad roadVisitor;

    // Finds the start tile 

    for (auto item : mItems)
    {
        item->Accept(&roadVisitor);
        if (roadVisitor.IsStartTile() && roadVisitor.IsRoad())
        {
            mRoadStart = item;
            if (roadVisitor.GetRoad() != nullptr) 
            {
                roadVisitor.SetStarterRoad();
            }
            
            //roadVisitor.TestRoad();
        }
    }
    
    if (difficulty == 0)
    {
        //roadVisitor.TestRoad();
    }
}

/** 
 * Clear the item data.
 * Deletes all known items in the game. 
 */
void CTowersGame::Clear()
{
    mItems.clear();
    mDeclarations.clear();
    mGameStarted = false;
    mDrawNewLevelItems = true;
    mBalloonsInGame = false;
}

/** 
 * Gets a specific attribute from an item value
 * @returns The value of the attribute at the speicifc item value. Null if none.
 * @param id The itemID as declared in the XML Declarations section
 * @param attribute The attribute that needs to be looked up 
 */
wstring CTowersGame::GetDeclarationAttribute(const wstring id, const wstring& attribute)
{
    // If there has been no declarations, then return null
    if (mDeclarations.size() != 0) 
    {
        // Iterate through declarations and figure out what the default image is supposed to be
        for (auto declared : mDeclarations)
        {
            if (declared.find(L"id") != declared.end() && declared.at(L"id") == id)
            {
                // Found the id that matches the object's id. Return it with an attribute of the id
                if (declared.find(attribute) != declared.end())
                {
                    return declared.at(attribute);
                }
            }
        }
    }
    return L"";
}

/**
 * Accepts a CItem visitor to perform operations
 * @param visitor The visitor being accepted
 */
void CTowersGame::Accept(CItemVisitor* visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Deletes an item from the collection
 * @param item The item being deleted
 */
void CTowersGame::DeleteItem(shared_ptr<CItem> item)
{
    auto it = find(mItems.begin(), mItems.end(), item);
    int index = distance(mItems.begin(), it);
    mItems.erase(mItems.begin() + index);
}

/**
 *  Build support for fast adjacency testing.
 *
 * This builds a map of the grid locations of every tile, so we can 
 * just look them up.
 */
void CTowersGame::BuildAdjacencies()
{
    double oX, oY;
    mAdjacency.clear();
    for (auto item : mItems)
    {
        oX = ((double)item->GetX()+16) / 64;
        oY = ((double)item->GetY()-32) / 64;
        mAdjacency[pair<int, int>(oX, oY)] = item;
    } 
}

/**
 *  Gets time since current load level
 */
void CTowersGame::GetLevelTime()
{
    time_t timer;

    timer = time(NULL); //gets current time

    if (mDrawLevelLabel)
    {
        if (difftime(timer, mLevelStartTime) >= 2)
        {
            mCreateNewButton = true;
            mDrawLevelLabel = false;
        }
    }

    if (mDrawEndLabel)
    {
        if (difftime(timer, mLevelEndTime) >= 2)
        {
            mDrawEndLabel = false;

            if (mCurrentLevel < 3)
            {
                wstring levelToLoad = L"levels/level" + to_wstring(mCurrentLevel + 1) + L".xml";
                Load(levelToLoad);
            }
            else if (mCurrentLevel == 3)
            {
                // Message box to restart game
                int restart = MessageBox(NULL, L"Would you like to restart?", L"Restart", MB_YESNO | MB_ICONQUESTION);

                if (restart == IDYES)
                {
                    Load(L"levels/level1.xml");
                    mGameScore = 0;
                }
                else
                {

                }
            }
            
        }
    }
    
}

/** 
 * Called when level is complete 
 */
void CTowersGame::LevelComplete()
{
    // Set end time to cur time
    mLevelEndTime = time(NULL); //gets current time

    mDrawEndLabel = true;

}

/** Checks for a collision between balloon and entity
 * @param x The x value to compare to 
 * @param y The y value to compare to
 * @param towerRadius The radius of the tower
 * @param dartTower is true if tower is dart
 * @returns int value for number of collisions
 */
int CTowersGame::CollisionCheck(int x, int y, int towerRadius, bool dartTower)
{
    int hitsOccurred = 0;

    std::vector<CTileRoad*> Roads;
    CRoadCollector visitor;
    for (auto item : mItems) {
        double dX = 0, dY = 0, distance = 0;

        dX = (x - double(item->GetX()));
        dY = (y - double(item->GetY()));

        distance = sqrt(dX * dX + dY * dY);
        if (distance < 200) {
            item->Accept(&visitor);
        }
    
    }
    Roads = visitor.GetRoads();
    
    CConfigureRoad visitor2;
    for (auto item : Roads)
    {
        item->Accept(&visitor2);


        if (visitor2.IsRoad())
        {
                hitsOccurred += visitor2.HitTestRoad(x, y, towerRadius, dartTower);
        }
    }

  return hitsOccurred;
}
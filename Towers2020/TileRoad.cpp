/**
 * \file TileRoad.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "TileRoad.h"
#include "ConfigureRoad.h"

#include <algorithm>
#include <memory>
#include <utility>

using namespace std;

/// Indicates when a balloon's mT will be subtracted
bool mCleanup = false; 

/** 
 * Constructor
 * @param item The Towers game 
 */
CTileRoad::CTileRoad(CTowersGame* item) : CTile(item)
{
	
}

/// Destructor
CTileRoad::~CTileRoad()
{
}

/**
 * @brief Load the attributes for an item node.
 * @param node The Xml node we are loading the item from
 */
void CTileRoad::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    // For storing any roadTile-specific attributes

    CTile::XmlLoad(node);

    mType = GetDeclarationAttribute(GetItemId(), L"type");
    
    if (node->GetAttributeValue(L"start", L"") == L"true")
    {
        mStartTile = true;
        mStartDirection = true;
    }
    else if (node->GetAttributeValue(L"start", L"") == L"false")
    {
        mStartTile = true;
        mStartDirection = false;
    }

}

/**
 * Place the balloon on the North/West tile, where
 * forward motion is assumed to be from a North entrance
 * to a West exit.
 * @param balloon The balloon we are placing.
 */
void CTileRoad::PlaceBalloonNW(std::shared_ptr<CBalloon> balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the tile in each dimension
    auto y = GetY() + GetHeight() / 2;
    auto x = GetX() + GetWidth() / 2;

    if (balloon->IsReverse())
    {
        t = 1 - t;
    }

    if (t < 0.5)
    {
        // First half of path
        // Moving vertically down
        y = GetY() + t * GetHeight();
    }
    else
    {
        // Second half of path
        // Moving horizontally left
        x = GetX() + (1 - t) * GetWidth();
    }

    balloon->SetLocation(x, y);
}

/**
 * Place the balloon on the South/East tile, where
 * forward motion is assumed to be from a South entrance
 * to an East exit.
 * @param balloon The balloon we are placing.
 */
void CTileRoad::PlaceBalloonSE(std::shared_ptr<CBalloon> balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    int y = GetY() + GetHeight() / 2;
    int x = GetX() + GetWidth() / 2;

    if (balloon->IsReverse())
    {
        t = 1 - t;
    }

    if (t < 0.5)
    {
        // First half of path
        // Moving vertically up
        y = GetY() - (t - 1) * GetHeight();
    }
    else
    {
        // Second half of path
        // Moving horizontally right
        x = GetX() + t * GetWidth();
    }

    balloon->SetLocation(x, y);
}

/**
 * Place the balloon on the South/West tile, where
 * forward motion is assumed to be from a West entrance
 * to a South exit.
 * @param balloon The balloon we are placing.
 */ 
void CTileRoad::PlaceBalloonSW(std::shared_ptr<CBalloon> balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY() + GetHeight() / 2;
    auto x = GetX() + GetWidth() / 2;

    if (balloon->IsReverse())
    {
        t = 1 - t;
    }

    if (t < 0.5)
    {
        // First half of path
        // Moving vertically up
        y = GetY() - (t - 1) * GetHeight();
    }
    else
    {
        // Second half of path
        // Moving horizonally left
        x = GetX() + (1 - t) * GetWidth();
    }

    balloon->SetLocation(x, y);
}

/**
 * Place the balloon on the North/South tile, where
 * forward motion is assumed to be from a North entrance
 * to a South exit.
 * @param balloon The balloon we are placing.
 */
void CTileRoad::PlaceBalloonNS(std::shared_ptr<CBalloon> balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY() + GetHeight() / 2;
    auto x = GetX() + GetWidth() / 2;

    if (balloon->IsReverse())
    {
        t = 1 - t;
    }

    // Full path
    // Moving vertically down
    y = GetY() + t * GetHeight();

    balloon->SetLocation(x, y);
}

/**
 * Place the balloon on the North/East tile, where
 * forward motion is assumed to be from a North entrance
 * to an East exit.
 * @param balloon The balloon we are placing.
 */
void CTileRoad::PlaceBalloonNE(std::shared_ptr<CBalloon> balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    if (balloon->IsReverse())
    {
        t = 1 - t;
    }

    // Initially set to the center of the file in each dimension
    auto y = GetY() + GetHeight() / 2;
    auto x = GetX() + GetWidth() / 2;

    if (t < 0.5)
    {
        // First half of path
        // Moving vertically down
        y = GetY() + t * GetHeight();
    }
    else
    {
        // Second half of path
        // Moving horizontally right
        x = GetX() + t * GetWidth();
    }

    balloon->SetLocation(x, y);
}

/**
 * Place the balloon on the East/West tile, where
 * forward motion is assumed to be from an East entrance
 * to a West exit.
 * @param balloon The balloon we are placing.
 */
void CTileRoad::PlaceBalloonEW(std::shared_ptr<CBalloon> balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    if (balloon->IsReverse())
    {
        t = 1 - t;
    }

    // Initially set to the center of the file in each dimension
    auto y = GetY() + GetHeight() / 2;
    auto x = GetX() + GetWidth() / 2;

    // Second half of path
    // Moving horizontally left
    x = GetX() + (1 - t) * GetWidth();

    balloon->SetLocation(x, y);
}

/**
 * Generates a Ballon entity at the request of the level.
 * @param offsetX The X offset relative to the start of the level.
 * @param offsetY The Y offset relative to the start of the level.
 */
void CTileRoad::GenerateBalloon(double offsetX, double offsetY)
{
    auto balloon = make_shared<CBalloon>(GetGame());
    balloon->setXOffset(offsetX);
    balloon->setYOffset(offsetY);
    balloon->SetLocation(GetX() + (int)balloon->GetXOffset(), GetY() + (int)balloon->GetYOffset());

    // If the starting tile is reversed, then reverse the balloon upon load
    if (mStartDirection == false)
    {
        balloon->Backwards();
    }
    mBalloons.push_back(balloon);
}

/**
 * Code for updating the position of the balloon goes here after each tile
 * @param elapsed The elapsed time
 */
void CTileRoad::Update(double elapsed)
{
    if (GetGame()->GetGoButtonPressed() && mStarterRoad) {
        mTimeToGenerate -= elapsed;

        if (mTimeToGenerate < 0 && mNumToGenerate > 0)
        {
            mTimeToGenerate = 0.5;

            GenerateBalloon(-64, -64);

            mNumToGenerate -= 1;
        }
    }
    

    // Adds new balloons to the collection
    for (auto balloon : mBalloonsToTransfer)
    {
        shared_ptr<CBalloon> bal = move(balloon);

        bal->SetIsDeleted(false);

        mBalloons.push_back(bal);
    }
    mBalloonsToTransfer.clear();

    // Deletes balloons removed from the collection
    for (auto balloon : mBalloonsToDelete)
    {
        auto it = find(mBalloons.begin(), mBalloons.end(), balloon);
        int index = distance(mBalloons.begin(), it);
        mBalloons.erase(mBalloons.begin() + index);
    }
    mBalloonsToDelete.clear();

    for (auto balloon : mBalloons)
    {
        // A transferred balloon will have mT subtracted by 1
        if (balloon->HasTransferred())
        {
            balloon->SetT(balloon->GetT() - 1);
            balloon->SetHasTransferred(false);
        }

        auto t = balloon->GetT();

        if (t >= 1)
        {
            balloon->SetHasTransferred(true);
            DetermineTileProgression(balloon);
        }
        else
        {
            PlaceBalloon(balloon);
        }

        balloon->Update(elapsed);
    }
}

/** 
 * Uses a PlaceBalloonXX method to determine the placement of an updating balloon.
 * @param balloon The balloon needing to be moved 
 */
void CTileRoad::PlaceBalloon(std::shared_ptr<CBalloon> balloon)
{
    if (mType == L"EW")
        PlaceBalloonEW(balloon);
    else if (mType == L"NE")
        PlaceBalloonNE(balloon);
    else if (mType == L"NS")
        PlaceBalloonNS(balloon);
    else if (mType == L"NW")
        PlaceBalloonNW(balloon);
    else if (mType == L"SE")
        PlaceBalloonSE(balloon);
    else if (mType == L"SW")
        PlaceBalloonSW(balloon);
}

/**
 * Determines the next road tile a balloon will follow after its time on a tile expires. 
 * Schedules balloons for deletion and addition to other lists. 
 * @param balloon The balloon needing to be deleted/traded out of the collection
 */
void CTileRoad::DetermineTileProgression(std::shared_ptr<CBalloon> balloon)
{
    // We must determine the type of the tile this balloon currently is on
    // and if it is going backwards

    // Save the next adjacent tile to the current one
    shared_ptr<CItem> temp;

    // Variables to record which direction the adjacent tile is leading
    int dx = -99, dy = -99;
    bool reverse = balloon->IsReverse();

    // If the balloon has ended on the North end
    if (mType == L"NS" && reverse ||
        mType == L"NW" && reverse ||
        mType == L"NE" && reverse)
    {
        dx = 0;
        dy = -1;
        temp = GetAdjacent(dx, dy); // Up
    }
    // If the balloon has ended on the South end
    else if (mType == L"NS" && !reverse ||
             mType == L"SE" && reverse  ||
             mType == L"SW" && reverse)
    {
        dx = 0;
        dy = 1;
        temp = GetAdjacent(dx, dy); // Down
    }
    // If the balloon has ended on the West end
    else if (mType == L"EW" && !reverse ||
             mType == L"NW" && !reverse ||
             mType == L"SW" && !reverse)
    {
        dx = -1;
        dy = 0;
        temp = GetAdjacent(dx, dy); // Left
    }
    // If the balloon has ended on the East end
    else if (mType == L"EW" && reverse ||
             mType == L"NE" && !reverse  ||
             mType == L"SE" && !reverse)
    {
        dx = 1;
        dy = 0;
        temp = GetAdjacent(dx, dy); // Right
    }

    CConfigureRoad visitor;

    // End of path if temp is null (no adjacency)
    if (temp == nullptr)
    {


        // Balloons delete themselves at the end of the path

        ScheduleDelete(balloon);
        if (balloon->GetRendering())
        {
            GetGame()->AddToGameScore(-1);
            GetGame()->DecrementBalloonCount();
        }
        
        return;
    }

    temp->Accept(&visitor);

    wstring type = visitor.GetRoadType();


    // The balloon is being transferred to a Northern (Southern-accepting) tile. Figure out which:
    if (dx == 0 && dy == -1)
    {
        // Balloon is transfering North to an "NS"-type tile
        if (type == L"NS")
        {
            balloon->Backwards(); // Indicate the balloon is now moving backwards
        }
        // Balloon is transfering North to an "SE"-type tile
        else if (type == L"SE")
        {
            balloon->Forwards(); // Indicate the balloon is now moving forwards
        }
        // Balloon is transfering North to an "SW"-type tile
        else if (type == L"SW")
        {
            balloon->Forwards();
        }
    }
    // The balloon is being transferred to a Southern (Northern-accepting) tile. Figure out which:
    else if (dx == 0 && dy == 1)
    {
        if (type == L"NE")
        {
            balloon->Forwards();
        }
        else if (type == L"NS")
        {
            balloon->Forwards();
        }
        else if (type == L"NW")
        {
            balloon->Forwards();
        }
    }
    // The balloon is being transferred to a Western (Eastern-accepting) tile. Figure out which:
    else if (dx == -1 && dy == 0)
    {
        if (type == L"EW")
        {
            balloon->Forwards();
        }
        else if (type == L"NE")
        {
            balloon->Backwards();
        }
        else if (type == L"SE")
        {
            balloon->Backwards();
        }
    }
    // The balloon is being transferred to a Eastern (Western-accepting) tile. Figure out which:
    else if (dx == 1 && dy == 0)
    {
        if (type == L"EW")
        {
            balloon->Backwards();
        }
        else if (type == L"NW")
        {
            balloon->Backwards();
        }
        else if (type == L"SW")
        {
            balloon->Backwards();
        }
    }

    // Schedule a delete to this Tlle's balloon.
    // Schedule a transfer of this Tile's balloon to another Tile's collection.

    ScheduleDelete(balloon);
    visitor.GetRoad()->ScheduleTransfer(balloon);
}

/**
 * A list balloons queued for removal by DetermineTileProgression() 
 * @param balloon The balloon needing to be deleted/traded out of the collection
 */
void CTileRoad::ScheduleDelete(std::shared_ptr<CBalloon> balloon)
{
    // Make sure we are not deleting the balloon twice by accident
    if (!balloon->IsBeingDeleted())
    {
        shared_ptr<CBalloon> bal = move(balloon);
        bal->SetIsDeleted(true); // Pop the balloon (temporarily)

        mBalloonsToDelete.push_back(bal);

    }

}

/**
 * A list balloons queued to be added to the road tile by DetermineTileProgression() 
 * @param balloon The balloon needing to be added to the collection
 */
void CTileRoad::ScheduleTransfer(std::shared_ptr<CBalloon> balloon)
{
    // Add a new externally created balloon into this tile's collection
    shared_ptr<CBalloon> bal = move(balloon);
    mBalloonsToTransfer.push_back(bal);
}

/** 
 * Draw this item
 * @param graphics The graphics context to draw on 
 */
void CTileRoad::Draw(Gdiplus::Graphics* graphics)
{
    CItem::Draw(graphics);
}

/** 
 * Draw all entities in an item.  
 * Does not draw the item itself.
 * @param graphics The graphics context to draw on 
 */
void CTileRoad::RenderEntities(Gdiplus::Graphics* graphics)
{
    
    for (auto balloon : mBalloons)
    {
        if (balloon->GetRendering())
        {
            balloon->Draw(graphics, balloon->GetXOffset(), balloon->GetYOffset());
        }
    }
}

/**
 * Hit test all balloons on a tile road
 * @param x The x value of the balloon
 * @param y The y value of the balloon
 * @param towerRadius The radius to check for a hit
 * @param dartTower True if a dart tower
 * @return int value of collisions
 */
int CTileRoad::HitTestAllBalloons(int x, int y, double towerRadius, bool dartTower)
{
    std::vector<std::shared_ptr<CBalloon>> toDelete;
    bool numHit = 0;

    for (auto balloon : mBalloons)
    {
        if (balloon->GetRendering())
        {

            double dX = 0, dY = 0, distance = 0;

            dX = (x - double(balloon->GetX()));
            dY = (y - double(balloon->GetY()));

            distance = sqrt(dX * dX + dY * dY);

            if (!dartTower && distance <= towerRadius + 24)
            {
                toDelete.push_back(balloon);

                numHit++;
            }
            else if (dartTower && distance <= towerRadius + 30)
            {
                dX = abs(dX);   // the X in the first quadrant
                dY = abs(dY);   // the Y in the first quadrant

                if (dX < 30)
                {
                    toDelete.push_back(balloon);
                    numHit++;
                }
                else if (dY < 30)
                {
                    toDelete.push_back(balloon);
                    numHit++;
                }
                else if (abs(dX - dY) < 30)
                {
                    toDelete.push_back(balloon);
                    numHit++;
                }
            }
        }
    }

    for (auto balloon : toDelete)
    {
        //ScheduleDelete(balloon);
        if (balloon->GetRendering())
        {
            balloon->SetRendering(false);
            GetGame()->DecrementBalloonCount();
        }
    }

    return numHit;
}

/** 
 * Accepts all the potential balloons in a tile 
 * @param visitor The visitor pass through 
 */
void CTileRoad::AcceptAllBalloons(CItemVisitor* visitor)
{
    for (auto balloon : mBalloons)
    {
        balloon->Accept(visitor);
    }
}

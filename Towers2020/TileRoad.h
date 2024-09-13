/**
 * \file TileRoad.h
 *
 * \author Jacob Frank
 * \author 
 * 
 *  Declares the Road tile and its behvior
 */

#pragma once
#include "Tile.h"
#include "XmlNode.h"
#include "Balloon.h"
#include "TowersGame.h"

 /**
  *  Implements a simple tile with tiles we can manipulate
  */
class CTileRoad : public CTile
{
public:

    CTileRoad(CTowersGame* game);

    ///  Default constructor (disabled)
    CTileRoad() = delete;

    ///  Copy constructor (disabled)
    CTileRoad(const CTileRoad&) = delete;
    
    ~CTileRoad();

    //virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** 
     * Accept a visitor
     * @param visitor The visitor we accept 
     */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTileRoad(this); }

    virtual void Update(double elapsed) override;

    /** 
     * Gets the road tile type
     * @returns a tile type in string literal form, Ex: L"NS" 
     */
    std::wstring GetType() { return mType; };

    /**
     * Gets if this road is a starter
     * @returns a tile type in string literal form, Ex: L"NS" 
     */
    bool IsStartTile() { return mStartTile; };

    virtual void Draw(Gdiplus::Graphics* graphics);

    virtual void RenderEntities(Gdiplus::Graphics* graphics);

    int HitTestAllBalloons(int x, int y, double towerRadius, bool dartTower);

    void AcceptAllBalloons(CItemVisitor* visitor);

    void GenerateBalloon(double offsetX, double offsetY);

    void PlaceBalloon(std::shared_ptr<CBalloon> balloon);

    void CTileRoad::ScheduleDelete(std::shared_ptr<CBalloon> balloon);

    void CTileRoad::ScheduleTransfer(std::shared_ptr<CBalloon> balloon);

    /**
     * Sets whether this tile is the starter tile for the level 
     * @param isStarter true = Is a starter road : false = Is not a starter road
     */
    void CTileRoad::SetStarterRoad(bool isStarter) { mStarterRoad = isStarter; }


private:

    void CTileRoad::DetermineTileProgression(std::shared_ptr<CBalloon> balloon);

    void PlaceBalloonNW(std::shared_ptr<CBalloon> balloon);

    void PlaceBalloonSE(std::shared_ptr<CBalloon> balloon);

    void PlaceBalloonSW(std::shared_ptr<CBalloon> balloon);

    void PlaceBalloonEW(std::shared_ptr<CBalloon> balloon);

    void PlaceBalloonNS(std::shared_ptr<CBalloon> balloon);

    void PlaceBalloonNE(std::shared_ptr<CBalloon> balloon);

    /// Indicates if this tile will be the spawner of balloons
    bool mStartTile = false; 

    /**
     * Determines what direction the balloons will spawn from the start tile. 
     * True = Normal direction. False = Inverse direction 
     */
    bool mStartDirection = false;

    /// List of balloons
    std::vector<std::shared_ptr<CBalloon>> mBalloons;    

    /// List of balloons to delete
    std::vector<std::shared_ptr<CBalloon>> mBalloonsToDelete; 

    /// List of balloons to trasnfer to a new tile
    std::vector<std::shared_ptr<CBalloon>> mBalloonsToTransfer; 

    /// The type of road object it is
    std::wstring mType = L"NS"; 

    /// Time to generate next balloon
    double mTimeToGenerate = 0;

    /// Total number of balloons to generate
    int mNumToGenerate = 30;

    /// Bool to determine starter road
    bool mStarterRoad = false;

};


/**
 * \file CanMoveVisitor.h
 * 
 * \author Morgan Mundell
 * \author Rohit Vadlamudi
 * \author Jacob Frank
 * 
 * 
 * A visitor class which visits towers to 
 * check if they are allowed to be dragged / moved.
 * 
 */

#pragma once
#include "ItemVisitor.h"
#include "TileRoad.h"

/// Can visit most items to detect many different things
class CCanMoveVisitor : public CItemVisitor
{
public:

    /** 
     * Get's the status of the tower.
     * \return Boolean to indicate whether it is tower or not 
     */
    bool GetIsTower() const { return mIsTower; }

    /** 
     * Get's the status of the open tile. Determine if open.
     * \return Boolean to indicate whether it is an open tile or not 
     */
    bool GetIsOpen() const { return mIsOpen; }

    /** 
     * Get's the status of the tile. Determine if tile.
     * \return Boolean to indicate whether it is a tile or not 
     */
    bool GetIsTile() const { return mIsTile; }

    /** 
     * Get's the status of the tile. Determine if entity.
     * \return Boolean to indicate whether it is an entity or not 
     */
    bool GetIsEntity() const { return mIsEntity;  }

    /** 
     * Get's the status of the item. Determine if balloon.
     * \return Boolean to indicate whether it is a balloon or not 
     */
    bool GetIsBalloon() const { return mIsBalloon; }

    /** 
     * Used for the BombTower to determine if the explosion has occured
     * \return Boolean to indicate if the bomb has blown up. 
     */
    bool GetIsBlownUp() const { return mIsBlownUp; }

    /** 
     * Get's the visited item's tower ID, if it has one
     * \return The ID for the tower 
     */
    int GetKey() const { return mKey;  }
    
    /** 
     * Get's the radius of the ring from the ring tower.
     * \return The radius of the ring 
     */
    int GetRingRadius() const { return mRingRadius; }

    /** 
     * Determine if the TowerRing ring is attacking.
     * \return Boolean to indicate if TowerRing is attacking 
     */
    bool GetRingAttacking() const { return mRingAttacking; }

    void PlaceTower();

    void LiftTower();

    std::wstring GetRoadType();

    /** 
     * Gets the road tile which was accepted
     * @returns A road tile 
     */
    CTileRoad* GetRoad() { return mRoad; };

    /**
     * Test function. Generates one balloon.
     */
    void TestRoad() { mRoad->SetStarterRoad(true); }

    bool IsRoad();

    void VisitTower8(CTower8* tower8)  override;

    void VisitTowerBomb(CTowerBomb* bomb) override;

    void VisitTowerRings(CTowerRings* ring) override;

    void VisitTowerAirship(CTowerAirship* airship) override;

    void VisitTileOpen(CTileOpen* open) override;

    void VisitEntity(CEntity* entity) override;

    void VisitBalloon(CBalloon* balloon) override;

    void VisitTileRoad(CTileRoad* road) override;
    
private:
    /// Used to represent a visited tower object
    CTower* mTower = nullptr;

    /// Used to represent the type of tower object the visitor has
    int mKey = 0; 

    /// Boolean to check if it is an open tile or not
    bool mIsOpen = false; 

    /// Boolean to check if it is a tower or not
    bool mIsTower = false; 

    /// Boolean to check if it is a tile or not
    bool mIsTile = false; 

    /// The Type of road this RoadTile is (if it is one)
    std::wstring mType; 

    /// Boolean to check if is an entity or not
    bool mIsEntity = false; 

    /// Boolean to check if it a balloon or not 
    bool mIsBalloon = false; 

    /// Boolean to check if it a road or not 
    bool mIsRoad = false; 

    /// Pointer to a found road object
    CTileRoad* mRoad = nullptr; 

    /// True if the visitor found the starter road tile
    bool mFoundStarter = false; 

    /// Boolean to check if TowerBomb blew up
    bool mIsBlownUp = false; 

    /// Integer to store the TowerRing ring radius
    int mRingRadius = 0; 

    /// Boolean to check if TowerRing is attacking
    bool mRingAttacking = false; 
};
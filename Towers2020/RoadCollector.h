#pragma once
/**
 * \file RoadCollector.h
 *
 * \author Dimitri Snell
 * \
 *
 *  Class that collects all TileRoads into a vector
 */
#include "ItemVisitor.h"
#include "TileRoad.h"
#include <string>

/** Visitor for getting the road tiles in the set */
class CRoadCollector : public CItemVisitor
{
public:
    /** Getter for getting the set of tile roads
     * @return The number of road in the tile
     */
    std::vector<CTileRoad*> GetRoads() { return mTileRoads; }

    /** Visits TileRoad and adds TileRoads to vector
     * @param road Road tile object to visit 
     */
    void CRoadCollector::VisitTileRoad(CTileRoad* road)
    {
        mTileRoads.push_back(road);
    }
private:

    std::vector<CTileRoad*> mTileRoads; ///< keeps track of all TileRoads in the set
};


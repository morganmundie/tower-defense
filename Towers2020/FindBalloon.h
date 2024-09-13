#pragma once
#include "ItemVisitor.h"
#include "TileRoad.h"
#include "Balloon.h"

/// Visits a balloon
class CFindBalloon : public CItemVisitor
{
public:

	/** 
	 * Imdicates if a balloon has been visited
	 * @returns The number of bombs recorded. 
	 */
	bool FoundBalloon() { return mFoundBalloon; }

	void FindBalloon();

	void CFindBalloon::VisitTileRoad(CTileRoad* road) override;

	void CFindBalloon::VisitBalloon(CBalloon* balloon) override;

private:
	/// The road object
	CTileRoad* mRoad = nullptr;

	/// The number of bombs visited
	bool mFoundBalloon = false; 
};

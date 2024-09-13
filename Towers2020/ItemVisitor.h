/**
 * \file ItemVisitor.h
 *
 * \author Dimitri Snell
 *
 * Tile visitor base class.
 */

#pragma once

//forward reference to all item types

class CTileCastle;
class CTileOpen;
class CTileHouse;
class CTileRoad;
class CTileTrees;
class CTower8;
class CTowerBomb;
class CTowerRings;
class CTileOpen;
class CGoButton;
class CDiagTimer;
class CBalloon;
class CEntity;
class CTower;
class CTowerAirship;

/** Tile visitor base class */
class CItemVisitor
{
public:
	/** 
 	 * For all objects that inherit CItem
	 */
	virtual ~CItemVisitor() {}

	/** 
	 * Visit a CTilecastle object
	 * @param castle Castle tile we are visiting 
	 */
	virtual void VisitTileCastle(CTileCastle* castle) {}

	/** 
	 * Visit a CTileOpen object
	 * @param grass Open tile we are visiting 
	 */
	virtual void VisitTileOpen(CTileOpen* grass) {}

	/**
	 * Visit a CTileHouse object
	 * @param tileHouse House tile we are visiting 
	 */
	virtual void VisitTileHouse(CTileHouse* tileHouse) {}

	/** 
	 * Visit a CTileRoad object
	 * @param road Road tile we are visiting 
	 */
	virtual void VisitTileRoad(CTileRoad* road) {}

	/** 
	 * Visit a CTileTree object
	 * @param trees Tree tile we are visiting 
	 */
	virtual void VisitTileTrees(CTileTrees* trees) {}

	/** 
	 * Visit a CTower8 object
	 * @param tower8 Tower8 we are visiting 
	 */
	virtual void VisitTower8(CTower8* tower8) {}

	/** 
	 * Visit a CTowerBomb object
	 * @param bomb Bomb tower we are visiting 
 	 */
	virtual void VisitTowerBomb(CTowerBomb* bomb){}

	/** 
	 * Visit a CTowerRing object
	 * @param ring Ring tower we are visiting 
	 */
	virtual void VisitTowerRings(CTowerRings* ring) {}

	/** 
	 * Visit a CGoButton object
	 * @param button Button we are visiting 
	 */
	virtual void VisitDiagGoButton(CGoButton* button) {}

	/** 
	 * Visit a CDiagTimer object
	 * @param timer Time dialogue we are visiting 
	 */
	virtual void VisitDiagTimer(CDiagTimer* timer) {}

	/** 
	 * Visit a CBalloon object
	 * @param balloon Balloon we are visiting 
	 */
	virtual void VisitBalloon(CBalloon* balloon) {}

	/** 
	 * Visit a CEntity object
	 * @param entity The Entity we are visiting
	 */
	virtual void VisitEntity(CEntity* entity) {}

	/** 
	 * Visit a CTowerAirship object
	 * @param airship The tower airship we are visiting
	 */
	virtual void VisitTowerAirship(CTowerAirship* airship) {}

	/** 
	 * Visit a CTower object
	 * @param tower The tower we are visiting
	 */
	virtual void VisitTower(CTower* tower) {}
};


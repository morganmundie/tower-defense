/**
 * \file TowerAirship.h
 *
 * \author Morgan Mundell
 * \author
 *
 *  Class that holds TowerAirship
 */

#pragma once
#include "Tower.h"
#include"TowersGame.h"
#include "Dart.h"
#include "Airship.h"

 /**
  *  Implements a simple tower we can manipulate
  */
class CTowerAirship : public CTower
{

public:

	CTowerAirship(CTowersGame* game);

	///  Default constructor (disabled)
	CTowerAirship() = delete;

	///  Copy constructor (disabled)
	CTowerAirship(const CTowerAirship&) = delete;

	~CTowerAirship();

	/** 
	 * Accept a visitor
	 * @param visitor The visitor we accept 
	 */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerAirship(this); }

	void GenerateAirship();

	virtual void Attack() override;

	virtual void Update(double elapsed) override;

	virtual void Draw(Gdiplus::Graphics* graphics);

	virtual void RenderEntities(Gdiplus::Graphics* graphics);

	void GenerateDart(double offsetX, double offsetY, double radians);

	void GenerateAllDarts();

private:
	/// Dart entities owned by the tower
	std::vector<std::shared_ptr<CDart>> mDarts;  

	/// The airship collection
	std::shared_ptr<CAirship> mAirship;

	/// Double for time to fire
	double mTimeTofire = 7;  

	/// Indicates to draw airship
	bool mAirshipDraw = false;  

	/// Indicates to draw darts
	bool mDrawDarts = false;  

};


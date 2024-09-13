/**
 * \file Tower8.h
 *
 * \author
 * \author
 *
 *  Class that holds tower8
 */

#pragma once
#include "Tower.h"
#include "TowersGame.h"
#include "Dart.h"

 /**
  *  Implements a simple tower we can manipulate
  */
class CTower8 : public CTower
{

public:

    CTower8(CTowersGame* game);

    ///  Default constructor (disabled)
    CTower8() = delete;
    
    ///  Copy constructor (disabled)
    CTower8(const CTower8&) = delete;

	~CTower8();

	/** 
	 * Accept a visitor
	 * @param visitor The visitor we accept 
     */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTower8(this); }

    void GenerateDart(double offsetX, double offsetY, double radians);

    void GenerateAllDarts();

    virtual void Attack() override;

    virtual void Update(double elapsed) override;

    virtual void Draw(Gdiplus::Graphics* graphics);

    virtual void RenderEntities(Gdiplus::Graphics* graphics);

private:
    /// Dart entities owned by the tower
	std::vector<std::shared_ptr<CDart>> mDarts;

    /// The time until the tower fires
	double mTimeTofire = 5;


};


/**
 * \file TowersGame.h
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * 
 *  Class that implements the game and holds the collection of all game items
 */

#pragma once

#include <memory>
#include <vector>
#include <map>
#include <utility>
#include <time.h>

#include "XmlNode.h"
#include "Item.h"

 /**
  *  Implements the actual game
  */
class CTowersGame
{
public:

	CTowersGame();

	virtual ~CTowersGame();

	/// The spacing between grid locations
	static const int GridSpacing = 64;

	void Add(std::shared_ptr<CItem> item);

	std::shared_ptr<CItem> HitTest(double x, double y);

	void MoveToFront(std::shared_ptr<CItem> item);

	void OnDraw(Gdiplus::Graphics* graphics, int width, int height);

	void Update(double elapsed);

	void SortTiles();

	std::shared_ptr<CItem> GetAdjacent(std::shared_ptr<CItem> item, int dx, int dy);

	std::shared_ptr<CItem> GetAdjacent(CItem* item, int dx, int dy);

	// void Save(const std::wstring& filename); Save function not required

	void Load(const std::wstring& filename);

	// Getters

	/** 
	 * Getter used for getting the current scale of the application 
	 * \return The current scale 
	 */
	double GetmScale() const { return mScale; }

	/** 
	 * Getter used for getting the current horizontal offset of the application
	 * \return The current horizontal offset 
	 */
	double GetmXOffset() const { return mXOffset; }

	/** 
	 * Getter used for getting the current vertical offset of the application
	 * \return The current vertical offset 
	 */
	double GetmYOffset() const { return mYOffset; }

	/** 
	 * Getter used for getting the current pressed status of the button
	 * \return The status of the button pressed 
	 */
	bool GetGoButtonPressed() const { return mGameStarted;  }

	/** 
	 * Getter used for determining the items to draw initially
	 * \return A booleaan indicating if new items need to be drawn at level load 
	 */
	bool GetNewLevelItems() const { return mDrawNewLevelItems;  }

	/** 
	 * Getter used for determining level label status
	 * \return A boolean indicating whether level status 
	 */
	bool GetLevelLabelStatus() const { return mDrawLevelLabel; }

	// Setters

	/**	
	 * Used to set the object which determines if the palette objects will be drawn again
	 * @param items True if items need to be loaded again, false if not 
	 */
	void SetNewLevelItems(bool items) { mDrawNewLevelItems = items; }

	void PressGoButton(std::shared_ptr<CItem> item);

	void Clear();

	/**
	 * Sets the game score
	 * @param score The current game score
	 */
	void SetScore(int score) { mScore += score;  }

	std::wstring GetDeclarationAttribute(const std::wstring id, const std::wstring& attribute);

	void Accept(CItemVisitor* visitor);

	void DeleteItem(std::shared_ptr<CItem> item);

	void GetLevelTime();

	void CTowersGame::StartLevel(int difficulty);

	void LevelComplete();

	int CollisionCheck(int x, int y, int towerRadius, bool dartTower);

	/**
	 * Called when balloon is hit or leaves screen
	 */
	void DecrementBalloonCount() { mNumBalloons += -1; }

	/**
	 * Called when balloon is hit to add score
	 * @param scoreToAdd The score from the tower
	 */
	void AddToGameScore(int scoreToAdd) { mGameScore += scoreToAdd; }

	/** 
	 * Iterator that iterates over the item tiles 
	 */
	class Iter
	{
	public:
		/** Constructor
		 * @param city The city we are iterating over
		 * @param pos The position 
		 */
		Iter(CTowersGame* city, size_t pos) : mGame(city), mPos(pos) {}

		/** Test for end of the iterator
		 * @param other The other position
		 * @returns True if we this position equals not equal to the other position 
		 */
		bool operator!=(const Iter& other) const
		{
			return mPos != other.mPos;
		}

		/** Get value at current position
		 * @returns Value at mPos in the collection 
		 */
		std::shared_ptr<CItem> operator *() const { return mGame->mItems[mPos]; }

		/** Increment the iterator
		 * @returns Reference to this iterator 
		 */
		const Iter& operator++()
		{
			mPos++;
			return *this;
		}

	private:
		CTowersGame* mGame; ///< City we are iterating over
		int mPos; ///< Position in the collection
	};

	/** Get an iterator for the beginning of the collection
	 * @returns Iter object at position 0 */
	Iter begin() { return Iter(this, 0); }

	/** Get an iterator for the end of the collection
	 * @returns Iter object at position past the end */
	Iter end() { return Iter(this, mItems.size()); }

private:

	void XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node);

	void XmlDeclarations(const std::shared_ptr<xmlnode::CXmlNode>& node);

	void BuildAdjacencies();

	/// Variable used for getting the scale
	double mScale = 0; 

	/// Variable used for ensuring it is centered horizontally
	double mXOffset = 0; 

	/// Variable used for ensuring it is centered vertically
	double mYOffset = 0; 

	/// Represents if the "GO" button for the level has been pressed
	bool mGameStarted = false;

	/// Used to only create the palette objects when needed to
	bool mDrawNewLevelItems = true;

	/// Used as a trigger to draw the "Level [X] Start" on level load
	bool mDrawLevelLabel = false;

	/// Used as a trigger to draw the "Level completed" 
	bool mDrawEndLabel = false;

	/// Used to record the current level number
	int mCurrentLevel = 0;

	/// Total score of the game
	int mScore = 0;

	/// Used to record the current time when the level began
	time_t mLevelStartTime = 0;

	/// Used to record the current time when the level ends
	time_t mLevelEndTime = 0;

	/// All of the items that make up our city
	std::vector<std::shared_ptr<CItem> > mItems;

	/// Used to indicate when a new GO button needs to be drawn
	bool mCreateNewButton = false;

	/// Used to indicate when there were balloons in the game
	bool mBalloonsInGame = false;

	/// Total game score to display
	int mGameScore = 0;

	/** 
	 * A vector containing XML item declarations
	 * vector index : map of each XML node
	 * map keys : the attribute names
	 * map values : the attribute values 
	 */
	std::vector<std::map<std::wstring, std::wstring>> mDeclarations;

	/// Adjacency lookup support
	std::map<std::pair<int, int>, std::shared_ptr<CItem> > mAdjacency;

	/// Pointer to the TileRoad which serves as the beginning of the path
	std::shared_ptr<CItem> mRoadStart;

	/// Number of balloons on screen
	int mNumBalloons = 30;

	/// Width of OnDraw function
	int mDrawWidth;

	/// Height of OnDraw function
	int mDrawHeight;
};


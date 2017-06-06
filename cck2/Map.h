//***************************************************************************80
#pragma once

#include <string>
#include <memory>
#include "Observer.h"
#include <ostream>
#include <fstream>

struct MapImpl;
struct Coordinate;
class Display;

class Map : public Observer {
public:
	Map(Display * const display);

	~Map();
	
	virtual bool addressTileChange(
		const Coordinate & tile,
		const char newDesign) override;

	void readLevel(const std::string & mapTxtFile);
	void placePlayer(const Coordinate playerStart);

private:
	void notifyVisibleArea(void);
	void updateVisibleArea(void);
	bool validMove(const Coordinate & newOrigin);
	bool addressMovementChange(const Coordinate & tile);

	std::unique_ptr<MapImpl> mapImpl;
	void printVisibleArea(void) const;
	friend std::ostream & operator<<(std::ostream & out, const Map & map);
};


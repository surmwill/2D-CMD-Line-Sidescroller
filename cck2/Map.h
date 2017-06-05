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
	Map(
		const std::string & mapTxtFile, 
		Display * const display,
		const Coordinate playerStart);

	~Map();
	
	virtual bool addressTileChange(
		const Coordinate & tile,
		const char newDesign) override;

private:
	void notifyVisibleArea(void);
	void updateVisibleArea(void);
	bool validMove(const Coordinate & newOrigin);

	std::unique_ptr<MapImpl> mapImpl;
	void printVisibleArea(void) const;
	friend std::ostream & operator<<(std::ostream & out, const Map & map);
};


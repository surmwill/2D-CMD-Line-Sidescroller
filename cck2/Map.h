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
	Map(const std::string & mapTxtFile, Display * const display);
	~Map();
	
	virtual void addressTileChange(
		const Coordinate & tile,
		const char newDesign) override;

	void notifyVisibleArea(void);
	void updateVisibleArea(void);

private:
	std::unique_ptr<MapImpl> mapImpl;
	void printVisibleArea(void) const;
	friend std::ostream & operator<<(std::ostream & out, const Map & map);
};


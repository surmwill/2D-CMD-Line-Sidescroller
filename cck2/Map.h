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
		Coordinate & tile,
		const char newDesign) override;

private:
	void notifyVisibleArea(void);
	void updateVisibleArea(void);
	void updateVisionOrigin(Coordinate & newOrigin);

	std::unique_ptr<MapImpl> mapImpl;
	void printVisibleArea(void) const;
	friend std::ostream & operator<<(std::ostream & out, const Map & map);
};


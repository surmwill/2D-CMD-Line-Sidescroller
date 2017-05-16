//***************************************************************************80
#pragma once

#include <string>
#include <memory>
#include "Observer.h"
#include <ostream>

struct MapImpl;
struct Coordinate;

class Map : public Observer {
public:
	Map(const std::string & mapTxtFile);
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


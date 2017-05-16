//***************************************************************************80
#pragma once

#include <string>
#include <memory>
#include "Observer.h"
#include "Subject.h"
#include <ostream>

struct MapImpl;
struct Coordinate;

class Map : public Observer, public Subject {
public:
	Map(const std::string & mapTxtFile, Observer * const display);
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


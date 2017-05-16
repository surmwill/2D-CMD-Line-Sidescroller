#pragma once
#include <memory>

class Observer;

class Level
{
public:
	virtual ~Level() = default;

protected:

	Level() = default;
	std::shared_ptr <Observer> map; 
};


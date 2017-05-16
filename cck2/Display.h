#pragma once
#include <memory>

struct DisplayImpl;

class Display
{
	std::unique_ptr <DisplayImpl> displayImpl;

public:
	Display();
	~Display();
	void refresh(void);
};


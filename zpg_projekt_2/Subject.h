#pragma once
#include "Observer.h"
class Subject
{
	void virtual Notify() = 0;

	void virtual Attach(Observer* observer) = 0;

	void virtual Detach(Observer* observer) = 0;
};


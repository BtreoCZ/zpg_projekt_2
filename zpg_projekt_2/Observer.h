#pragma once
#include "Subject.h"

class Subject;
class Observer
{
public:
	void virtual Update(Subject *subject) = 0;
};


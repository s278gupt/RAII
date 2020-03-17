#ifndef _SUBJECT_H
#define _SUBJECT_H
#include <vector>

class Observer;
class CellInfo;

class Subject{
	protected:
		std::vector<Observer*> observers;
	public:
	void attach(Observer* ob);
	void notifyObservers();
	virtual CellInfo getInfo() const = 0;
};

#endif

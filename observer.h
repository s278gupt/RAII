#ifndef _OBSERVER_H
#define _OBSERVER_H

class Subject;

class Observer{
	public:
		virtual void notify(Subject& whoNotified) = 0;
		virtual ~Observer() = 0;
};

#endif

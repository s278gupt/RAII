#include <vector>
#include "subject.h"
#include "observer.h"
using namespace std;

void Subject::attach(Observer* ob) {
	if (ob != nullptr){
		observers.emplace_back(ob);
	}
}

void Subject::notifyObservers() {
	for (auto& ob: observers) {
		ob->notify(*this);
	}
}

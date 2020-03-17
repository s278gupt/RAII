#include <string>
#include "exception.h"
using namespace std;

InvalidMove::InvalidMove(string s): s{s} {}

string InvalidMove::getErrorMessage() { return s; }

#include "cell.h"
using namespace std;

Cell::Cell(int r, int c): r{r}, c{c} {}

int Cell::getRow() const { return r; }

int Cell::getCol() const { return c; }

Cell::~Cell(){}

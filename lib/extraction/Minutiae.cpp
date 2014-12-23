#include "Minutiae.h"

Minutiae::Minutiae(int x, int y, Type t)
         : locX(x), locY(y), type(t)
{
    Minutiae::markedForErasing = false;
}

Minutiae::~Minutiae()
{
    //dtor
}

int Minutiae::getLocX()
{
    return locX;
}

int Minutiae::getLocY()
{
    return locY;
}

Minutiae::Type Minutiae::getType()
{
    return type;
}

void Minutiae::setMarkTrue()
{
    Minutiae::markedForErasing = true;
}

bool Minutiae::getMark()
{
    return Minutiae::markedForErasing;
}

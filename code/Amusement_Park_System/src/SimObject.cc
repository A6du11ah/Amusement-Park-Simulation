#include "SimObject.h"

using namespace std;

SimObject::SimObject()
{
    //ctor
}

void
SimObject::signal (int msg)
{
    cout << "signal" << endl;
}

void
SimObject::respond (int obj, int msg)
{
    cout << "respond" << endl;
}

void
SimObject::displayReports ()
{
    cout << "display" << endl;
}

SimObject::~SimObject()
{
    //dtor
}

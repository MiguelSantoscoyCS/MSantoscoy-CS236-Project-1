#include "Jobs.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;
//________Class Function Definitions________

//default construcor
Jobs::Jobs()
{
  weight = 0;
  startTime= 0;
  endTime = 0;
  name = "null";
}

Jobs::Jobs(int n, int m, int k, string j)
{
  weight = n;
  startTime = m;
  endTime = k;
  name= j;
}

int Jobs::getStartTime()
{
  return startTime;
}

int Jobs::getEndTime()
{
  return endTime;
}

string Jobs::getName()
{
  return name;
}

int Jobs::getWeight()
{
  return weight;
}


void Jobs::printDet()
{
  cout << name << setw(15) << startTime << setw(15) << endTime << setw(15) << weight << endl;
}
#ifndef JOBS_H
#define JOBS_H

#include <string>

using namespace std;

class Jobs{
public:
Jobs ();
Jobs (int n, int m, int k, string j);
int getStartTime();
int getEndTime();
string getName();
int getWeight();
void printDet(); //print job Details

void findProfit();

private:
string name;
int weight;
int startTime;
int endTime;

};

#endif
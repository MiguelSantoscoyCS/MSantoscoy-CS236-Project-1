#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

class Jobs{
public:
Jobs ();
Jobs (int n, int m, int k, string j);

//get class Details
int getStartTime();
int getEndTime();
void getName();
int getWeight();

void printDet(); //print job Details

private:
string name;
int weight;
int startTime;
int endTime;

};

// __________ Function Protos__________

void createJobs(Jobs *n);

void sortJobs(Jobs *n, Jobs **jbPtr);

bool weightTimeComp(Jobs *a, Jobs *b);
//_____________________________________

int const  MAX_JOBS=6;
  
int main() {
 cout << "We will create 6 jobs and then sort them by finish time." << endl;
Jobs *job =  new Jobs[6];

createJobs(job);


  sort(job, job + MAX_JOBS,
  [](Jobs  & a, Jobs  & b) -> bool
  { if ( a.getEndTime() < b.getEndTime())
  {return a.getEndTime() < b.getEndTime();}
   else if (a.getEndTime() == b.getEndTime())
     return a.getWeight() < b.getWeight();
  } );

  for (int i = 0; i < MAX_JOBS; i++)
    {
      job[i].printDet();
    }
  return 0;
}

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

void Jobs::getName()
{
  cout << name << endl;
}

int Jobs::getWeight()
{
  return weight;
}

void Jobs::printDet()
{
  cout << "Job Name: " << name
 <<"\nStart Time: " << startTime << "\nEnd Time: " << endTime << " \nWeight: " << weight << "\n" << endl;
}
//_________Function Defintions__________

//function to create jobs
void createJobs(Jobs *job)
{
  cout<< " The start time may be between 0 and 24. Enter the START time, END time, and WEIGHT of the jobs separated by a space." << endl;
  for(int i = 0; i < MAX_JOBS; i++)
    {
      cout<< "Enter the details for Job " << i+1 << ": ";
      int weight, startTime, endTime;
      string name= "Job " +to_string(i +1);
      cin >>startTime >> endTime >> weight;

      //while loop to check for valid input
      while (startTime < 0 || startTime > 24 || endTime < 0 || endTime > 24 || startTime > endTime)
        {
          if (startTime < 0 || startTime > 24)
          {
            cout << "Invalid START time! Please enter a start time between 0 and 24." << endl;
          cin >> startTime;
          }
          else if (endTime > 24 || endTime < 0)
          {
            cout << "Invalid END time! Please enter an END time between 0 and 24." << endl;
            
            cin>> endTime;
          }
          else if (startTime > endTime)
          
          {
            cout << "Invalid START/END times! Please enter an END time that is greater than the START time." << "\nPlease enter a START time: ";
            cin >> startTime;

              cout << "Please enter an END time: ";
            cin>> endTime;
            
          }
            
          } //end while loop
      
          job[i] = Jobs(weight, startTime, endTime, name);
        }
      
  
      
    }

bool weightTimeComp(Jobs& a, Jobs& b)
{
    if (a.getEndTime() < b.getEndTime()) return true;
    if (a.getEndTime() == b.getEndTime()) return a.getWeight() < b.getWeight();

    return false;
};


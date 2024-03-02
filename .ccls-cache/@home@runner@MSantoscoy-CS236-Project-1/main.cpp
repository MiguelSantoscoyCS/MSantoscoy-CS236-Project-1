#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iomanip>

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

// __________ Function Protos__________

void createJobs(Jobs *n);

void findOptimal(Jobs *n, Jobs *Optimal, int & jbsOpt);

void findProfit(Jobs *n, int & jbsOpt);

//void printDet(Jobs* n);
//_____________________________________

int const  MAX_JOBS=6;

/*
Things to still fix before submission:
1. Check the logic for the optimal jobs. They must be non overlapping, current logic does not make the distinction for non-overlapping jobs
2. Make sure you split up the implementation files
  */
int main() {
 cout << "We will create "<< MAX_JOBS<< " jobs and then sort them by finish time." << endl;

int optimalCount = 0;

Jobs *job =  new Jobs[MAX_JOBS]; //array to store all jobs
Jobs *jobOpt = new Jobs[MAX_JOBS]; //array to store optimal jobs

createJobs(job);

//sort jobs by finish time
  sort(job, job + MAX_JOBS,
  [](Jobs  & a, Jobs  & b) -> bool
  { return a.getEndTime() < b.getEndTime(); } );


  cout<< "\nDetails of job entered (ordered by END time): \n"<< "Job Name " << setw(15)
     <<"Start Time " << setw(15) << "End Time " << setw(15) << "Weight "  << endl;



  for (int i = 0; i < MAX_JOBS; i++)
    {
      job[i].printDet();
    }

  findOptimal(job, jobOpt, optimalCount);

  cout<< "\nThere are "<< optimalCount << " jobs in the optimal schedule.\n" <<"The optimal schedule is: "<< "\nJob Name " << setw(15)
     <<"Start Time " << setw(15) << "End Time " << setw(15) << " Weight "  << endl;
  for (int i = 0; i < optimalCount; i++)
  {
    jobOpt[i].printDet();
  }


  findProfit(jobOpt, optimalCount);\

  //Deallocating memory
  delete[] job;
  delete[] jobOpt;

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

//_________Function Defintions__________

//function to take input and create jobs
void createJobs(Jobs *job)
{
  cout<< "The start time may be between 0 and 24. Enter the START time, END time, and WEIGHT of the jobs separated by a space." << endl;
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

        } // endWhile

      job[i]= Jobs(weight, startTime, endTime, name);
    }

}

//function to find optimal job schedule
void findOptimal(Jobs *job, Jobs *Optimal, int & jbs)
{
  //Assign first element to optimal jobs
  Optimal[jbs] = job[0];
  jbs++;

  //loop to run through all available jobs
  for(int i =1; i < MAX_JOBS; i++)
  {
    //If next job is not overlapping with the last job in the optimal schedule, add it to the optimal schedule
      if(Optimal[jbs].getEndTime() <= job[i].getStartTime())
      {
        Optimal[jbs] = job[i];
        jbs++;
      }
      // If next job is overlapping with the last job in the optimal schedule, check if it is better than the last job in the optimal schedule
    if (Optimal[jbs].getStartTime() >= job[i].getStartTime())
        {
          //Find total time for current optimal job
        int jobTimeOpt= Optimal[jbs].getEndTime()- Optimal[jbs].getStartTime();

          //find total time for new job
          int jobTimeTemp= job[i].getEndTime()- job[i].getStartTime();

          //if new job is better than the last job in the optimal schedule, replace the last job in the optimal schedule with
          if (jobTimeOpt < jobTimeTemp && Optimal[jbs].getWeight() <= job[i].getWeight())
          {
            Optimal[jbs] = job[i];
          } // end if

        } //end if
  }//end for
  
}

//Calculate max profit
void findProfit(Jobs *job, int & jbsOpt)
{
  int profit = 0;
  for(int i = 0; i < jbsOpt; i++)
    {
      profit += job[i].getWeight();
    }
  cout << "\nThe profit is: " << profit << endl;
  
};

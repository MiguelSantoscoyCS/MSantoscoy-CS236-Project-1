#include "Jobs.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;


// __________ Function Protos__________

void createJobs(Jobs *n);

void findOptimal(Jobs *n, Jobs *Optimal, int & jbsOpt);

void findProfit(Jobs *n, int & jbsOpt);

//_____________________________________

//const to set limit of jobs
int const  MAX_JOBS=6;

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

  cout<< "\nThere are "<< optimalCount + 1 << " jobs in the optimal schedule.\n" <<"The optimal schedule is: "<< "\nJob Name " << setw(15)
     <<"Start Time " << setw(15) << "End Time " << setw(15) << " Weight "  << endl;
  for (int i = 0; i < optimalCount + 1; i++)
  {
    jobOpt[i].printDet();
  }


  findProfit(jobOpt, optimalCount);\

  //Deallocating memory
  delete[] job;
  delete[] jobOpt;

  return 0;
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
          //start time out of range
          if (startTime < 0 || startTime > 24)
          {
            cout << "Invalid START time! Please enter a start time between 0 and 24 for "<< name << "." << endl;
          cin >> startTime;
          }
            //end time out of range
          else if (endTime > 24 || endTime < 0)
          {
            cout << "Invalid END time! Please enter an END time between 0 and 24 for "<< name << "." << endl;
            cin>> endTime;
          }
            //start time after end time
          else if (startTime > endTime)

          {
            cout << "Invalid START/END times! Please enter an END time that is greater than the START time." << "\nPlease enter a START time for "<< name << "." << endl;
            cin >> startTime;

              cout << "Please enter an END time for "<< name << "." << endl;
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

  //loop to run through all available jobs
  for(int i =0; i < MAX_JOBS; i++)
  {
    //If next job is not overlapping with the last job in the optimal schedule, add it to the optimal schedule
      if(Optimal[jbs].getEndTime() <= job[i].getStartTime())
      {
        jbs++;
        Optimal[jbs] = job[i];
      }
      // If next job is overlapping with the last job in the optimal schedule, check if it is better than the last job in the optimal schedule
    if (Optimal[jbs].getStartTime() == job[i].getStartTime())
        {
          //Find total time for current optimal job
        int jobTimeOpt= Optimal[jbs].getEndTime()- Optimal[jbs].getStartTime();

          //find total time for new job
          int jobTimeTemp= job[i].getEndTime()- job[i].getStartTime();

          //if new job is better than the last job in the optimal schedule, replace the last job in the optimal schedule with new job
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
  for(int i = 0; i < jbsOpt + 1; i++)
    {
      profit += job[i].getWeight();
    }
  cout << "\nThe profit is: " << profit << endl;
  
};

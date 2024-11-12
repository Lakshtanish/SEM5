#include<iostream>
#include<vector>
using namespace std;
class Processes
{
	public:
		int process;
		int arrivalTime;
		int burstTime;
		int completionTime;
		int turnaroundTime;
		int waitingTime;		
};
void CalculateCompletionTime(Processes process[],int n,int quantum)
{
	int remainingTime[n];
	for(int i=0;i<n;i++)
	{
		remainingTime[i] = process[i].burstTime;
	}
	int currentTime = 0;
	bool allDone = false;
	int i=0;
	while(!allDone)
	{
		allDone = true;
		for(int i=0;i<n;i++)
		{
			if(remainingTime[i]>0)
			{
				allDone = false;
				if(remainingTime[i] > quantum)
				{
					currentTime = currentTime + quantum;
					remainingTime[i] = remainingTime[i] - quantum;
				}
				else
				{
					currentTime = currentTime + remainingTime[i];
					process[i].completionTime = currentTime;
					remainingTime[i] = 0;
				}
			}
		}
		
	}
}
void CalculateTurnaroundTime(Processes process[],int n)
{
	for(int i=0;i<n;i++)
	{
		process[i].turnaroundTime = process[i].completionTime - process[i].arrivalTime;
	}
}

void CalculateWaitingTime(Processes process[],int n)
{
	for(int i=0;i<n;i++)
	{
		process[i].waitingTime = process[i].turnaroundTime - process[i].burstTime;
	}
}

void PrintTable(Processes process[],int n)
{
	cout << "Process\tArrival time\tBurst time\tCompletion Time\t\tTurn around time\tWaiting time" << endl;
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    double avgtat = 0,avgwt = 0;
    for(int i=0;i<n;i++)
    {
    	avgtat += process[i].turnaroundTime;
    	avgwt += process[i].waitingTime;
    	cout<<"P"<<process[i].process<<"\t\t"<<process[i].arrivalTime<<"ms\t\t"<<process[i].burstTime<<"\t\t"<<process[i].completionTime<<"\t\t\t"<<process[i].turnaroundTime<<"ms\t\t\t"<<process[i].waitingTime;
		cout<<endl;
	}
	cout<<"\nAverage Turn around Time :"<<avgtat;
	cout<<"\nAverage Waiting Time :"<<avgwt;
}
int main()
{
	int n,quantum;
	cout << "********Round Robin Scheduling (Preemptive)********" << endl;
	cout<<"\nEnter number of processes :";
	cin>>n;
	cout<<"\nEnter time quantum :";
	cin>>quantum;
	Processes process[n];
	for(int i=0;i<n;i++)
	{
		process[i].process = i+1;
		cout<<"\nEnter arrival time for process "<<i+1<<" :";
		cin>>process[i].arrivalTime;
		cout<<"\nEnter burst time for process "<<i+1<<" :";
		cin>>process[i].burstTime;		
	}
	CalculateCompletionTime(process,n,quantum);
	CalculateTurnaroundTime(process,n);
	CalculateWaitingTime(process,n);
	cout << "********Round Robin Scheduling (Preemptive)********" << endl;
	PrintTable(process,n);
	
	return 0;
}


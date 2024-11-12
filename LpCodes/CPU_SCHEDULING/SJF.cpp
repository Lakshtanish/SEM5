#include<iostream>
#include<vector>
using namespace std;

int main()
{
	int n, temp;
	float avgtat = 0, avgwt = 0;
	cout << "********Shortest Job First Scheduling(Preemptive)********" << endl;
	cout << "\nEnter number of processes :";
	cin >> n;
	vector<int> process(n), arrivalTime(n), burstTime(n), completionTime(n), TAT(n), waitingTime(n), visit(n), remburstTime(n);
	int start = 0, total = 0;
	
	for (int i = 0; i < n; i++)
	{
		process[i] = (i + 1);
		cout << "\nEnter arrival time for process " << i + 1 << " :";
		cin >> arrivalTime[i];
		cout << "\nEnter burst time for process " << i + 1 << " :";
		cin >> burstTime[i];
		remburstTime[i] = burstTime[i]; 
		visit[i] = 0;  
		cout << endl;
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (arrivalTime[i] > arrivalTime[j])
			{
				swap(process[i], process[j]);
				swap(arrivalTime[i], arrivalTime[j]);
				swap(burstTime[i], burstTime[j]);
				swap(remburstTime[i], remburstTime[j]);
			}
		}
	}
	
	while (total < n)
	{
		int min = 99, c = n; 
		for (int i = 0; i < n; i++)
		{
			if ((arrivalTime[i] <= start) && (visit[i] == 0) && (remburstTime[i] < min))
			{
				min = remburstTime[i];
				c = i;
			}
		}

		if (c == n) //If no process is ready increment start
			start++; 
		else
		{
			remburstTime[c]--; 
			start++; 
			
			if (remburstTime[c] == 0) 
			{
				completionTime[c] = start;
				visit[c] = 1; 
				total++; 
			}
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		TAT[i] = completionTime[i] - arrivalTime[i]; 
		waitingTime[i] = TAT[i] - burstTime[i]; 
		avgtat += TAT[i];
		avgwt += waitingTime[i]; 
	}
	
	cout << "********Shortest Job First Scheduling(Preemptive)********" << endl;
	cout << "\nProcesses\tArrival Time\tBurst Time\tCompletion Time\t\tTurn Around Time\tWaiting Time";
	cout << "\n-----------------------------------------------------------------------------------------------------------";
	for (int i = 0; i < n; i++)
	{
		cout << "\nP" << process[i] << "\t\t" << arrivalTime[i] << "ms\t\t" << burstTime[i] << "ms\t\t" << completionTime[i] << "ms\t\t\t" << TAT[i] << "ms\t\t\t" << waitingTime[i] << "ms";
	}
	
	avgtat /= n;
	avgwt /= n;
	
	cout << "\nAverage turn around time is :" << avgtat;
	cout << "\nAverage waiting time is :" << avgwt;
	return 0;
}


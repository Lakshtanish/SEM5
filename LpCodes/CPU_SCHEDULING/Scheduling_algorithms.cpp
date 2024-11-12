#include <iostream>
#include <vector>
#include <algorithm>
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
    int priority; // Only for priority scheduling
};

void CalculateTurnaroundTime(Processes process[], int n) 
{
    for (int i = 0; i < n; i++) 
	{
        process[i].turnaroundTime = process[i].completionTime - process[i].arrivalTime;
    }
}

void CalculateWaitingTime(Processes process[], int n) 
{
    for (int i = 0; i < n; i++) 
	{
        process[i].waitingTime = process[i].turnaroundTime - process[i].burstTime;
    }
}

void PrintTable(Processes process[], int n) 
{
    double avgTAT = 0, avgWT = 0;
    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time";
    cout << "\n-----------------------------------------------------------------------------------";

    for (int i = 0; i < n; i++) 
	{
        avgTAT += process[i].turnaroundTime;
        avgWT += process[i].waitingTime;
        cout << "\nP" << process[i].process << "\t" << process[i].arrivalTime << "\t\t" << process[i].burstTime << "\t\t"
             << process[i].completionTime << "\t\t" << process[i].turnaroundTime << "\t\t" << process[i].waitingTime;
    }

    avgWT /= n;
    avgTAT /= n;
    cout << "\n\nAverage Waiting Time: " << avgWT;
    cout << "\nAverage Turnaround Time: " << avgTAT << endl;
}

// Function for Round Robin Scheduling
void CalculateCompletionTimeRR(Processes process[], int n, int quantum) {
    vector<int> remainingTime(n)
    for (int i = 0; i < n; i++) 
	{
        remainingTime[i] = process[i].burstTime;
    }
    int currentTime = 0;
    bool allDone = false;
    while (!allDone) 
	{
        allDone = true;
        for (int i = 0; i < n; i++) 
		{
            if (remainingTime[i] > 0) 
			{
                allDone = false;
                if (remainingTime[i] > quantum) 
				{
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                } else 
				{
                    currentTime += remainingTime[i];
                    process[i].completionTime = currentTime;
                    remainingTime[i] = 0;
                }
            }
        }
    }
}

// Function for Priority Scheduling (Non-Preemptive)
void CalculateCompletionTimePriority(Processes process[], int n) 
{
    int tLap = 0;
    for (int i = 0; i < n; i++) 
	{
        int minIndex = i;
        for (int j = i + 1; j < n; j++) 
		{
            if (process[j].arrivalTime <= tLap && process[j].priority < process[minIndex].priority) 
			{
                minIndex = j;
            }
        }
        tLap += process[i].burstTime;
        process[i].completionTime = tLap;
        process[i].priority = 9999;
    }
}

// Function for First Come First Serve (FCFS) Scheduling
void CalculateCompletionTimeFCFS(Processes process[], int n) 
{
    for (int i = 0; i < n; i++) 
	{
        if (i == 0) 
		{
            process[i].completionTime = process[i].arrivalTime + process[i].burstTime;
        } 
		else 
		{
            if (process[i].arrivalTime > process[i - 1].completionTime) 
			{
                process[i].completionTime = process[i].arrivalTime + process[i].burstTime;
            } 
			else 
			{
                process[i].completionTime = process[i - 1].completionTime + process[i].burstTime;
            }
        }
    }
}

// Function for Shortest Job First (Preemptive)
void CalculateCompletionTimeSJF(Processes process[], int n) 
{
    vector<int> remburstTime(n);
    vector<int> visit(n, 0);
    int start = 0, total = 0;

    for (int i = 0; i < n; i++) 
	{
        remburstTime[i] = process[i].burstTime;
    }

    while (total < n) 
	{
        int minBurst = 9999, c = n;
        for (int i = 0; i < n; i++) 
		{
            if (process[i].arrivalTime <= start && visit[i] == 0 && remburstTime[i] < minBurst) 
			{
                minBurst = remburstTime[i];
                c = i;
            }
        }

        if (c == n) 
		{
            start++;
        }
		else 
		{
            remburstTime[c]--;
            start++;
            if (remburstTime[c] == 0) 
			{
                process[c].completionTime = start;
                visit[c] = 1;
                total++;
            }
        }
    }
}

// Main Function with Menu-Driven Interface
int main() 
{
    int n, choice, quantum;
    
    cout << "******** CPU Scheduling Algorithms ********" << endl;
    cout << "Enter number of processes: ";
    cin >> n;
    Processes process[n];

    for (int i = 0; i < n; i++) {
        process[i].process = i + 1;
        cout << "\nEnter arrival time for process " << i + 1 << ": ";
        cin >> process[i].arrivalTime;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> process[i].burstTime;
    }

    do {
        cout << "\n\n1. Round Robin Scheduling";
        cout << "\n2. Priority Scheduling (Non-Preemptive)";
        cout << "\n3. First Come First Serve Scheduling";
        cout << "\n4. Shortest Job First Scheduling (Preemptive)";
        cout << "\n5. Exit";
        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nEnter time quantum for Round Robin: ";
            cin >> quantum;
            CalculateCompletionTimeRR(process, n, quantum);
            CalculateTurnaroundTime(process, n);
            CalculateWaitingTime(process, n);
            PrintTable(process, n);
            break;
        case 2:
            for (int i = 0; i < n; i++) {
                cout << "Enter priority for process " << i + 1 << ": ";
                cin >> process[i].priority;
            }
            CalculateCompletionTimePriority(process, n);
            CalculateTurnaroundTime(process, n);
            CalculateWaitingTime(process, n);
            PrintTable(process, n);
            break;
        case 3:
            CalculateCompletionTimeFCFS(process, n);
            CalculateTurnaroundTime(process, n);
            CalculateWaitingTime(process, n);
            PrintTable(process, n);
            break;
        case 4:
            CalculateCompletionTimeSJF(process, n);
            CalculateTurnaroundTime(process, n);
            CalculateWaitingTime(process, n);
            PrintTable(process, n);
            break;
        case 5:
            cout << "Exiting...";
            break;
        default:
            cout << "Invalid choice! Try again.";
        }
    } while (choice != 5);

    return 0;
}


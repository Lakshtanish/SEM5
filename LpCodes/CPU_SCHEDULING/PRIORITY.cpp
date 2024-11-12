#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Processes {
public:
    int process;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int priority;
};

void CalculateCompletionTime(Processes process[], int n) {
    int minArrival = 9999;
    int totalTime = 0, tLap;
    int minIndex = 0, currentIndex = 0;

    // Sort by arrival time and priority
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (process[i].arrivalTime > process[j].arrivalTime) {
                swap(process[i], process[j]);
            } else if (process[i].arrivalTime == process[j].arrivalTime && process[j].priority > process[i].priority) {
                swap(process[i], process[j]);
            }
        }
    }

    // Find total burst time
    for (int i = 0; i < n; i++) {
        totalTime += process[i].burstTime;
        if (process[i].arrivalTime < minArrival) {
            minArrival = process[i].arrivalTime;
            minIndex = i;
            currentIndex = i;
        }
    }

    tLap = minArrival;

    while (tLap < totalTime) {
        for (int i = 0; i < n; i++) {
            if (process[i].arrivalTime <= tLap) {
                if (process[i].priority < process[minIndex].priority) {
                    minIndex = i;
                    currentIndex = i;
                }
            }
        }
        tLap += process[currentIndex].burstTime;
        process[currentIndex].completionTime = tLap;
        process[currentIndex].priority = 9999; // mark as completed
    }
}

void CalculateTurnaroundTime(Processes process[], int n) {
    for (int i = 0; i < n; i++) {
        process[i].turnaroundTime = process[i].completionTime - process[i].arrivalTime;
    }
}

void CalculateWaitingTime(Processes process[], int n) {
    for (int i = 0; i < n; i++) {
        process[i].waitingTime = process[i].turnaroundTime - process[i].burstTime;
    }
}

void PrintTable(Processes process[], int n) {
    double avgTAT = 0, avgWT = 0;
    cout << "********Priority Scheduling (Non-Preemptive)********" << endl;
    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time";
    cout << "\n-----------------------------------------------------------------------------------";

    for (int i = 0; i < n; i++) {
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

int main() {
    int n;
    cout << "********Priority Scheduling (Non-Preemptive)********" << endl;
    cout << "\nEnter number of processes: ";
    cin >> n;

    Processes process[n];
    
    for (int i = 0; i < n; i++) {
        process[i].process = i + 1;
        cout << "\nEnter arrival time for process " << i + 1 << ": ";
        cin >> process[i].arrivalTime;
        cout << "\nEnter burst time for process " << i + 1 << ": ";
        cin >> process[i].burstTime;
        cout << "\nEnter priority for process " << i + 1 << ": ";
        cin >> process[i].priority;
    }

    CalculateCompletionTime(process, n);
    CalculateTurnaroundTime(process, n);
    CalculateWaitingTime(process, n);
    PrintTable(process, n);

    return 0;
}


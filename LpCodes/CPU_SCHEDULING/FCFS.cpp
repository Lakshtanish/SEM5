#include <iostream>
#include <vector>
using namespace std;

int main() 
{
    int n, temp;
    float avgtat = 0, avgwt = 0;
    cout << "********First Come First Serve Scheduling********" << endl;
    cout << "Enter number of Processes: ";
    cin >> n;

    vector<int> process(n), arrivalTime(n), burstTime(n), completionTime(n), TAT(n), waitingTime(n);

    for (int i = 0; i < n; i++) {
        process[i] = (i + 1);
        cout << "\nEnter Arrival time for process " << (i + 1) << ": ";
        cin >> arrivalTime[i];
        cout << "Enter Burst time for process " << (i + 1) << ": ";
        cin >> burstTime[i];
    }

    // Sorting based on Arrival Time
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrivalTime[i] > arrivalTime[j]) {
                // Swap process number
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;

                // Swap arrival time
                temp = arrivalTime[i];
                arrivalTime[i] = arrivalTime[j];
                arrivalTime[j] = temp;

                // Swap burst time
                temp = burstTime[i];
                burstTime[i] = burstTime[j];
                burstTime[j] = temp;
            }
        }
    }

    // Calculate completion time
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            completionTime[i] = arrivalTime[i] + burstTime[i];
        } else {
            if (arrivalTime[i] > completionTime[i - 1]) {
                completionTime[i] = arrivalTime[i] + burstTime[i];
            } else {
                completionTime[i] = completionTime[i - 1] + burstTime[i];
            }
        }
    }

    // Output header
    cout << "********First Come First Serve Scheduling********" << endl;
    cout << "Processor\tArrival time\tBurst time\tCompletion Time\t\tTurn around time\tWaiting time" << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl;

    // Calculate TAT and Waiting Time and print the details
    for (int i = 0; i < n; i++) {
        TAT[i] = completionTime[i] - arrivalTime[i];  // Turn Around Time
        waitingTime[i] = TAT[i] - burstTime[i];       // Waiting Time

        avgtat += TAT[i];
        avgwt += waitingTime[i];

        // Print process details
        cout << "P" << process[i] << "\t\t" << arrivalTime[i] << "ms\t\t" << burstTime[i] << "ms\t\t" << completionTime[i]
             << "ms\t\t\t" << TAT[i] << "ms\t\t\t" << waitingTime[i] << "ms" << endl;
    }

    // Average times
    cout << "Average Turn around time of Processes: " << (avgtat / n) << "ms" << endl;
    cout << "Average waiting time of Processes: " << (avgwt / n) << "ms" << endl;

    return 0;
}

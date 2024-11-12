#include <iostream>
#include <vector>
using namespace std;

int main() {
    int noofpages, capacity, ptr = 0, hit = 0, fault = 0;
    bool isFull = false;
    double hitRatio, faultRatio;
    cout << "Enter the number of pages you want to enter: ";
    cin >> noofpages;
    vector<int> pages(noofpages);
    for (int i = 0; i < noofpages; i++) {
        cin >> pages[i];
    }
    cout << "Enter the capacity of frame: ";
    cin >> capacity;
    vector<int> frame(capacity, -1);
    vector<vector<int>> table(noofpages, vector<int>(capacity, -1));
    cout << "----------------------------------------------------------------------\n";
    for (int i = 0; i < noofpages; i++) {
        int search = -1;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                search = j;
                hit++;
                cout << "   H";
                break;
            }
        }
        if (search == -1) {
            if (isFull) {
                vector<int> index(capacity, 0);
                vector<bool> index_flag(capacity, false);
                for (int j = i + 1; j < noofpages; j++) {
                    for (int k = 0; k < capacity; k++) {
                        if (pages[j] == frame[k] && !index_flag[k]) {
                            index[k] = j;
                            index_flag[k] = true;
                            break;
                        }
                    }
                }
                int max = index[0];
                ptr = 0;
                if (max == 0) max = 200;
                for (int j = 0; j < capacity; j++) {
                    if (index[j] == 0) index[j] = 200;
                    if (index[j] > max) {
                        max = index[j];
                        ptr = j;
                    }
                }
            }
            frame[ptr] = pages[i];
            fault++;
            cout << "   F";
            if (!isFull) {
                ptr++;
                if (ptr == capacity) {
                    ptr = 0;
                    isFull = true;
                }
            }
        }
        for (int j = 0; j < capacity; j++) {
            table[i][j] = frame[j];
        }
    }
    cout << "\n----------------------------------------------------------------------\n";
    for (int i = 0; i < capacity; i++) {
        for (int j = 0; j < noofpages; j++) {
            cout << " " << table[j][i] << " ";
        }
        cout << endl;
    }
    cout << "----------------------------------------------------------------------\n";
    hitRatio = ((double)hit / noofpages) * 100;
    faultRatio = ((double)fault / noofpages) * 100;
    cout << "Page Fault: " << fault << "\nPage Hit: " << hit << endl;
    cout << "Hit Ratio:" << hitRatio << " \nFault Ratio:" << faultRatio << endl;
    return 0;
}

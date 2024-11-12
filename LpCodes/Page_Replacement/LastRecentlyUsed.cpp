#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int noofpages, capacity, hit = 0, fault = 0, index = 0;
    bool isFull = false;
    double hitRatio, faultRatio;

    cout << "Enter the number of pages you want to enter: ";
    cin >> noofpages;

    vector<int> pages(noofpages);
    cout << "Enter page numbers: ";
    for (int i = 0; i < noofpages; i++) {
        cin >> pages[i];
    }

    cout << "Enter the capacity of frame: ";
    cin >> capacity;

    vector<int> frame(capacity, -1);
    vector<int> arr; // Used for keeping track of page order
    vector<vector<int>> table(noofpages, vector<int>(capacity, -1));

    cout << "----------------------------------------------------------------------" << endl;
    for (int i = 0; i < noofpages; i++) {
        // Remove the page from arr if it exists and add it back
        auto it = find(arr.begin(), arr.end(), pages[i]);
        if (it != arr.end()) {
            arr.erase(it);
        }
        arr.push_back(pages[i]);

        int search = -1;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                search = j;
                hit++;
                cout << "  H"; // Hit
                break;
            }
        }

        if (search == -1) {
            if (isFull) {
                int min_loc = noofpages;
                for (int j = 0; j < capacity; j++) {
                    // Find the least recently used page in the frame
                    auto temp_it = find(arr.begin(), arr.end(), frame[j]);
                    if (temp_it != arr.end()) {
                        int temp = distance(arr.begin(), temp_it);
                        if (temp < min_loc) {
                            min_loc = temp;
                            index = j; // Update the index to replace
                        }
                    }
                }
            }

            // Replace the frame index with the new page
            frame[index] = pages[i];
            fault++;
            cout << "  F"; // Fault
            index++;
            if (index == capacity) {
                index = 0;
                isFull = true; // Mark as full after the first complete pass
            }
        }
        // Copy current frame state to table
        copy(frame.begin(), frame.end(), table[i].begin());
    }

    cout << "\n----------------------------------------------------------------------" << endl;
    for (int i = 0; i < capacity; i++) {
        for (int j = 0; j < noofpages; j++) {
            cout << (table[j][i] == -1 ? "  - " : " " + to_string(table[j][i]) + " ");
        }
        cout << endl;
    }

    cout << "----------------------------------------------------------------------" << endl;
    hitRatio = ((double)hit / noofpages) * 100;
    faultRatio = ((double)fault / noofpages) * 100;
    cout << "Page Fault: " << fault << "\nPage Hit: " << hit << endl;
    printf("Hit Ratio: %.2f \nFault Ratio: %.2f\n", hitRatio, faultRatio);

    return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

class MemoryAllocation 
{
private:
    int *blockSize;
    int m;
    int *processSize;
    int n;
    int *originalBlockSize;

public:
    MemoryAllocation(int m, int n)
    {
        this->m = m;
        this->n = n;
        blockSize = new int[m];
        processSize = new int[n];
        originalBlockSize = new int[m];
    }

    ~MemoryAllocation()
    {
        delete[] blockSize;
        delete[] processSize;
        delete[] originalBlockSize;
    }

    void inputSizes()
    {
        for (int i = 0; i < m; i++)
        {
            cout << "Enter block size " << i + 1 << ": ";
            cin >> blockSize[i];
            originalBlockSize[i] = blockSize[i];
        }
        cout << "\n";
        for (int i = 0; i < n; i++)
        {
            cout << "Enter process size " << i + 1 << ": ";
            cin >> processSize[i];
        }
    }

    void resetBlockSize()
    {
        for (int i = 0; i < m; i++)
        {
            blockSize[i] = originalBlockSize[i];
        }
    }

    void bestFit()
    {
        resetBlockSize();
        vector<int> allocation(n, -1);
        vector<int> remblockSize(n, -1);

        for (int i = 0; i < n; i++)
        {
            int bestIdx = -1;
            for (int j = 0; j < m; j++)
            {
                if (blockSize[j] >= processSize[i])
                {
                    if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j])
                    {
                        bestIdx = j;
                    }
                }
            }
            if (bestIdx != -1)
            {
                allocation[i] = bestIdx;
                blockSize[bestIdx] -= processSize[i];
                remblockSize[i] = blockSize[bestIdx];
            }
        }

        cout << "\nBest Fit Allocation:\nProcess No.\tProcess Size\tBlock No.\tRemaining Block Size\n";
        for (int i = 0; i < n; i++)
        {
            cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
            if (allocation[i] != -1)
                cout << allocation[i] + 1 << "\t\t" << remblockSize[i] << endl;
            else
                cout << "Not Allocated\n";
        }
    }

    void firstFit()
    {
        resetBlockSize();
        vector<int> allocation(n, -1);
        vector<int> remblockSize(n, -1);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (blockSize[j] >= processSize[i])
                {
                    allocation[i] = j;
                    blockSize[j] -= processSize[i];
                    remblockSize[i] = blockSize[j];
                    break;
                }
            }
        }

        cout << "\nFirst Fit Allocation:\nProcess No.\tProcess Size\tBlock No.\tRemaining Block Size\n";
        for (int i = 0; i < n; i++)
        {
            cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
            if (allocation[i] != -1)
                cout << allocation[i] + 1 << "\t\t" << remblockSize[i] << endl;
            else
                cout << "Not Allocated\n";
        }
    }

    void nextFit()
    {
        resetBlockSize();
        vector<int> allocation(n, -1);
        vector<int> remblockSize(n, -1);
        int j = 0;

        for (int i = 0; i < n; i++)
        {
            int count = 0;
            while (count < m)
            {
                if (blockSize[j] >= processSize[i])
                {
                    allocation[i] = j;
                    blockSize[j] -= processSize[i];
                    remblockSize[i] = blockSize[j];
                    break;
                }
                j = (j + 1) % m;
                count++;
            }
        }

        cout << "\nNext Fit Allocation:\nProcess No.\tProcess Size\tBlock No.\tRemaining Block Size\n";
        for (int i = 0; i < n; i++)
        {
            cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
            if (allocation[i] != -1)
                cout << allocation[i] + 1 << "\t\t" << remblockSize[i] << endl;
            else
                cout << "Not Allocated\n";
        }
    }

    void worstFit()
    {
        resetBlockSize();
        vector<int> allocation(n, -1);
        vector<int> remblockSize(n, -1);

        for (int i = 0; i < n; i++)
        {
            int wstIdx = -1;
            for (int j = 0; j < m; j++)
            {
                if (blockSize[j] >= processSize[i])
                {
                    if (wstIdx == -1 || blockSize[wstIdx] < blockSize[j])
                        wstIdx = j;
                }
            }
            if (wstIdx != -1)
            {
                allocation[i] = wstIdx;
                blockSize[wstIdx] -= processSize[i];
                remblockSize[i] = blockSize[wstIdx];
            }
        }

        cout << "\nWorst Fit Allocation:\nProcess No.\tProcess Size\tBlock No.\tRemaining Block Size\n";
        for (int i = 0; i < n; i++)
        {
            cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
            if (allocation[i] != -1)
                cout << allocation[i] + 1 << "\t\t" << remblockSize[i] << endl;
            else
                cout << "Not Allocated\n";
        }
    }
};

int main()
{
    int m, n, choice;
    cout << "Enter the number of blocks: ";
    cin >> m;
    cout << "Enter the number of processes: ";
    cin >> n;

    MemoryAllocation memory(m, n);

    memory.inputSizes();

    while (true)
    {
        cout << "\nChoose the allocation strategy:\n";
        cout << "1. Best Fit\n2. First Fit\n3. Next Fit\n4. Worst Fit\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            memory.bestFit();
        }
        else if (choice == 2)
        {
            memory.firstFit();
        }
        else if (choice == 3)
        {
            memory.nextFit();
        }
        else if (choice == 4)
        {
            memory.worstFit();
        }
        else if (choice == 5)
        {
            cout << "Exiting program.\n";
            break;
        }
        else
        {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}



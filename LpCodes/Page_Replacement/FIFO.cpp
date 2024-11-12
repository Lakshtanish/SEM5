#include<iostream>
#include<vector>
using namespace std;
int main()
{
	int noofpages,capacity;
	int hit=0,fault=0,index=0;
	double faultRatio,hitRatio;
	cout<<"\n************ FIRST IN FIRST OUT **************";
	cout<<"\nEnter number of pages :";
	cin>>noofpages;
	cout<<"\nEnter page numbers :";
	vector<int> pages(noofpages);
	for(int i=0;i<noofpages;i++)
	{
		cin>>pages[i];
	}
	cout<<"\nEnter capacity of frame :";
	cin>>capacity;
	vector<int> frame(noofpages,-1);
	vector<vector<int> > table(noofpages,vector<int>(capacity,-1));
	cout<<"\n-------------------------------------------------------------------------------------"<<endl;
	
	for(int i=0;i<noofpages;i++)
	{
		int search = -1;
		
		for(int j=0;j<capacity;j++)
		{
			if(frame[j] == pages[i])
			{
				search = j;
				hit++;
				cout<<"  H";
				break;
			}
		}
		
		if(search == -1)
		{
			frame[index] = pages[i];
			fault++;
			cout<<"  F";
			index = (index+1)%capacity;
		}
		
		for(int j=0;j<capacity;j++)
		{
			table[i][j] = frame[j];
		}
		
	}
	cout << "\n----------------------------------------------------------------------\n";
	for (int i = 0; i < capacity; i++) 
	{
	    for (int j = 0; j < noofpages; j++) 
		{
	        cout << table[j][i] << " "; 
	    }
	    cout << endl;
	}
	cout << "----------------------------------------------------------------------" << endl;
	faultRatio = ((double)fault/noofpages)*100;
	hitRatio = ((double)hit/noofpages)*100;
	cout << "Page Fault: " << fault << "\nPage Hit: " << hit << endl;
	cout << "Hit Ratio: " << hitRatio << "% \n";
	cout << "Fault Ratio: " << faultRatio << "%" << endl;
	return 0;
}


#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

using namespace std;

class Pass_02 {
    ifstream sy, li, fin;
    ofstream fout;
    vector<pair<string, int>> symtable;
    vector<pair<string, int>> littable;

public:
    void input() {
        sy.open("symb2.txt");
        li.open("lit1.txt");
        fin.open("output2.txt");
        fout.open("machine1.txt");
    }

    void generate() {
        string line = "", word = "";

        // Load Symbol Table
        while (getline(sy, line)) {
            stringstream ss(line);
            string label;
            int address;
            ss >> label >> word >> address; // Read the symbol number, symbol name (ignore), and address
            symtable.push_back({word, address});
        }

        // Load Literal Table
        while (getline(li, line)) {
            stringstream ss(line);
            string label;
            int address;
            ss >> label >> address;
            littable.push_back({label, address});
        }

        // for(auto &i: symtable)
        // {
        //     cout<<" "<<i.first<<" "<<i.second<<endl;
        // }        

        // Generate Machine Code from Intermediate Code
        while (getline(fin, line)) 
        {
            stringstream ss(line);
            string location, opcode, operand;
            ss >> location >> opcode; // Read the location and opcode
            if (opcode == "(IS,")
            {
                string code;
                ss >> code;
                //cout<<"\ncode = "<<code;
                string instruction = code.substr(0, code.size() - 1); // Remove the closing parenthesis
                fout << location << " " << instruction << " "; // Write location and opcode to file

                while (ss >> word) 
                {
                    if (word == "(S,") 
                    {
                        ss >> operand;
                        int symIndex = stoi(operand.substr(0, operand.size() - 1)) - 1;
                        fout << symtable[symIndex].second << " "; // Write symbol address
                        //cout<<"op:"<<operand<<" "<<symtable[symIndex].second<<endl;
                    } 
                    else if (word == "(L,") 
                    {
                        ss >> operand;
                        int litIndex = stoi(operand.substr(0, operand.size() - 1)) - 1;
                        //cout<<"li:"<<operand<<" "<<littable[litIndex].second<<endl;
                        fout << littable[litIndex].second << " "; // Write literal address
                    } 
                    else if (word.find("(C,") != string::npos) 
                    {
                        fout << word.substr(0, word.size() - 1) << " "; // Write constant
                    } 
                    else 
                    {
                        fout << word << " "; // Write register codes or anything else
                    }
                }
            } 
            else if (opcode == "(DL,") 
            {
                string directive;
                ss >> directive;
                if (directive == "01)") 
                {
                    ss >> word;
                    ss>>word;
                    fout << location << " 00 00 " << word.substr(0, word.size() - 1); // Write DC with constant
                } 
                else if (directive == "02)") 
                { 
                    fout << location << " No machine code"; 
                }
            }
            else
            {
                fout<<" No machine code";
            }
            fout << "\n"; // New line after each machine instruction
        }
    }

    void show() {
        cout << "\n===========Symbol table ==============" << endl;
        for (auto x : symtable) {
            cout << x.first << " " << x.second << "\n";
        }
        cout << "\n===========Literal table ===============" << endl;
        for (auto x : littable) {
            cout << x.first << " " << x.second << "\n";
        }
    }

    ~Pass_02() 
    {
        sy.close();
        li.close();
        fin.close();
        fout.close();
    }
};

int main() {
    Pass_02 obj;
    obj.input();
    obj.generate();
    obj.show();
    return 0;
}
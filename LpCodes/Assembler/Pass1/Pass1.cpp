#include<iostream>
#include<vector>
#include<map>
#include<sstream>
#include<fstream>

using namespace std;

class Pass1
{
    public:
    map<string,pair<string,string>>opcode;
    map<string,pair<int,string>>symtab;
    vector<pair<string,int>>littab;
    vector<string>pooltab;
    int litindex;
    int LC = -1;

    void initializeOpcode()
    {
        opcode = 
        {
            {"STOP",{"IS","00"}},
            {"ADD",{"IS","01"}},
            {"SUB",{"IS","02"}},
            {"MULT",{"IS","03"}},
            {"MOVER",{"IS","04"}},
            {"MOVEM",{"IS","05"}},
            {"COMP",{"IS","06"}},
            {"BC",{"IS","07"}},
            {"DIV",{"IS","08"}},
            {"READ",{"IS","09"}},
            {"PRINT",{"IS","10"}},
            {"START",{"AD","01"}},
            {"END",{"AD","02"}},
            {"ORIGIN",{"AD","03"}},
            {"EQU",{"AD","04"}},
            {"LTORG",{"AD","05"}},
            {"DC",{"DL","01"}},
            {"DS",{"DL","02"}},
            {"AREG",{"1",""}},
            {"BREG",{"2",""}},
            {"CREG",{"3",""}},
            {"DREG",{"4",""}},
            {"LT",{"1",""}},
            {"LE",{"2",""}},
            {"EQ",{"3",""}},
            {"GT",{"4",""}},
            {"GE",{"5",""}},
            {"ANY",{"6",""}},
        };
    }

    void execute()
    {
        initializeOpcode();
        litindex = 0;
        LC = -1;
        symtab.clear();
        littab.clear();
        pooltab.clear();
        string line,word;
        ifstream fin("input1.txt");
        ofstream fout("output2.txt");

        while(getline(fin,line))
        {
            stringstream st(line);
            st>>word;
            string label = "";
            if(opcode.count(word) == 0)
            {
                if(symtab.count(word) == 0)
                {
                    symtab[word] = {LC,to_string(symtab.size() + 1)};
                }
                else
                {
                    symtab[word].first = LC; 
                }
                label = word;
                st>>word;
            }

            string operation = word;
            if(operation == "START")
            {
                fout<<"("<<opcode[word].first<<", "<<opcode[word].second<<") ";
                st>>word;
                fout<<" (C, "<<word<<")";
                LC = stoi(word);
            }
            else if(operation == "END")
            {
                fout<<"( "<<opcode[word].first<<","<<opcode[word].second<<") ";
                fout<<endl;
                pooltab.push_back("#"+ to_string(litindex));
                for(;litindex<littab.size();litindex++)
                {
                    fout<<LC;
                    fout<<"("<<opcode["DC"].first<<","<<opcode[word].second<<")";
                    littab[litindex].second = LC;
                    string literal = littab[litindex].first;
                    string sublit = literal.substr(4,literal.length()-7);
                    fout<<"(C,"<<sublit<<")";
                    fout<<endl;
                    LC++;
                }
            }
            else if(operation == "LTORG")
            {
                //fout<<" ( "<<opcode[word].first<<","<<opcode[word].second<<" ) ";
                fout<<endl;
                pooltab.push_back("#" + to_string(litindex + 1));
                for(;litindex<littab.size();litindex++)
                {
                    fout<<LC;
                    fout<<" ("<<opcode["DC"].first<<", "<<opcode["DC"].second<<") ";
                    littab[litindex].second = LC;
                    string literal = littab[litindex].first;
                    string sublit = literal.substr(4,literal.length() - 7);
                    fout<<" (C, "<<sublit<< ")";
                    fout<<endl;
                    LC++;
                }
            }
            else if(operation == "EQU")
            {
                fout<<" ";
                fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";
                st>>word;
                int plusminusindex = 0;
                for(int i=0;i<word.length();i++)
                {
                    if(word[i] == '+' || word[i] == '-')
                    {   
                        plusminusindex = i;
                        break;
                    }
                }
                string beforeindex;
                string afterindex = "0";
                char plusminus = '0';
                if(plusminusindex != 0)
                {
                    plusminus = word[plusminusindex];
                    beforeindex =word.substr(0,plusminusindex);
                    afterindex = word.substr(plusminusindex+1);

                }
                else
                {
                    beforeindex = word.substr(0,word.length());
                }
                symtab[label].first = symtab[beforeindex].first;
                if(plusminus == '+')
                {
                    if(afterindex!="0")
                    {
                        symtab[label].first +=stoi(afterindex);
                    }
                }
                else
                {
                    if(afterindex!="0")
                    {
                        symtab[label].first -= stoi(afterindex);
                    }
                }  
                fout<<"(C, "<<symtab[label].first<<" ) ";
                fout<<endl;

            }
            else if(operation == "ORIGIN")
            {
                fout << "    ";
                fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";
                st >> word;
                int plusminusindex = 0;
                for (int i = 0; i < word.length(); i++)
                {
                    if (word[i] == '+' || word[i] == '-')
                    {
                        plusminusindex = i;
                        break;
                    }
                }
                char plusminus = '0';
                string beforesign, aftersign = "0";
                if (plusminusindex != 0)
                {
                    plusminus = word[plusminusindex];
                    aftersign = word.substr(plusminusindex + 1);
                    beforesign = word.substr(0, plusminusindex);
                }
                else
                {
                    beforesign = word.substr(0, word.length());
                }
                LC = symtab[beforesign].first;
                fout << "(S, " << symtab[beforesign].second << ")";

                if (plusminus == '+')
                {
                    if(aftersign != "0")
                    {
                        LC += stoi(aftersign);
                        fout << "+" << aftersign << "\n";
                    }
                }
                else if (plusminus == '-')
                {
                    if(aftersign!="0")
                    {
                        LC -= stoi(aftersign);
                        fout << "-" << aftersign << "\n";
                    }
                }
            }
            else
            {
                fout<<LC<<" ";
                fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";
                while(st >> word)
                {
                    if(operation == "DC")
                    {
                        if(word.length() == 3)
                        {
                            word = word.substr(1,word.length()-2);

                        }
                        fout<<"(C, "<<word<<")";
                    }
                    else if(operation == "DS")
                    {
                        fout<<"(C,"<<word<<")";
                        LC += stoi(word) - 1;
                    }
                    else if(word[0] == '=')
                    {
                        littab.push_back({word,LC});
                        fout<<"(L, "<<littab.size()<<")"; 
                    }
                    else if(opcode.count(word) > 0)
                    {
                        fout << "(" << opcode[word].first << ") ";
                    }
                    else
                    {
                        if(symtab.count(word) == 0)
                        {
                            symtab[word] = {LC,to_string(symtab.size() + 1)};
                        }
                        fout<<"(S, "<<symtab[word].second<<")";
                    }
                }
                LC++;

            }
            fout<<endl;
        }
        fin.close();
        fout.close();
        writeSymTab();
        writeLitTab();
        writePoolTab();

    }
    void writeSymTab()
    {
        ofstream sout("sym1.txt");
       
        for(auto &i: symtab)
        {
            sout<<i.second.second<<" "<<i.first<<" "<<i.second.first<<endl;
        }
        sout.close();
    }
    void writeLitTab(){
        ofstream lout("lit1.txt");
        for(auto &i:littab)
        {
            lout<<i.first<<" "<<i.second<<endl;
        }
        lout.close();
    }

    void writePoolTab()
    {
        ofstream pout("pool1.txt");
        for(auto &i:pooltab)
        {
            pout<<i<<endl;
        }
        pout.close();
    }

    void displayOutput()
    {
        ifstream fin("output2.txt");
        string line;
        cout << "\nOutput:" << endl;
        while (getline(fin, line))
        {
            cout << line << endl;
        }
        fin.close();
    }
};
int main()
{
    Pass1 obj;
    obj.execute();
    obj.displayOutput();
    return 0;
}
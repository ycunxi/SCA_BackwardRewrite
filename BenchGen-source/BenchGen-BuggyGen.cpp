//
//  BenchGen-BuggyGen.cpp
//  buggy_benchGen
//
//  Created by Cunxi Yu on 6/29/15.
//  Copyright (c) 2015 Cunxi Yu. All rights reserved.
//

#include "BenchGen-BuggyGen.h"
#include <iostream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <unistd.h>
#include <functional>
#include <map>
#include <cmath>
#include <list>
#include <vector>
#include <set>
using namespace std;

bool buggy_skip(string input)
{
    if (*input.begin() == '/') {
        return false;
    }
    else{return true;}
}
bool buggy_If_assign(string input)
{
    int find = 0;
    find = input.find("assign",0);
    if(find>=0){ return true;}
    else{ return false;}
}
string buggy_AND_2_OR(string input)
{
    int find_and = 0 ; find_and = input.find("&",0);
    input.replace(find_and, 1, "|");
    return input+"\n";
}
string buggy_AND_2_XOR(string input)
{
    int find_and = 0 ; find_and = input.find("&",0);
    input.replace(find_and, 1, "^");
    return input+"\n";
}
string buggy_OR_2_AND(string input)
{
    int find_and = 0 ; find_and = input.find("|",0);
    input.replace(find_and, 1, "&");
    return input+"\n";
}
string buggy_OR_2_XOR(string input)
{
    int find_and = 0 ; find_and = input.find("|",0);
    input.replace(find_and, 1, "^");
    return input+"\n";
}
string buggy_XOR_2_AND(string input)
{
    int find_and = 0 ; find_and = input.find("^",0);
    input.replace(find_and, 1, "&");
    return input+"\n";
}
string buggy_XOR_2_OR(string input)
{
    int find_and = 0 ; find_and = input.find("^",0);
    input.replace(find_and, 1, "|");
    return input+"\n";
}
int how_many_gates(string file)
{
    ifstream fin(file.c_str());
    string input;
    int n_gates=0;
    while (getline(fin,input)) {
        if(buggy_If_assign(input))
        {
            ++n_gates;
        }
    }
    return n_gates;
}
string remove_dotV(string filename)
{
    int find_dotV=0; find_dotV = filename.find(".v",0);
    string new_str; new_str.assign(filename,0,find_dotV);
    return new_str;
}



void Gen_BuggyBench::buggy_gen(string file) {
    string location(getcwd(NULL,0));
    string filein=location+"/verilogGenerated/"+file;
    //string file = "Multiplier4Bits.v";

    //cout<<how_many_gates(filein);
    bool buggy_done = true;
    int bug_sequence=1; int bug_location=1;
    string input;
    //ifstream fin(filein.c_str());
    int find_and=0;int find_or=0;int find_xor=0;
    for(int i=1;i<=how_many_gates(filein);i++)
    {
        ifstream fin(filein.c_str());
        stringstream bug_line; bug_line<<i; string out_f; out_f = location+"/verilogGenerated/"+remove_dotV(file)+"_bug_"+bug_line.str()+".v";
        ofstream outfile(out_f.c_str());
        while (getline(fin,input)) {
            if(buggy_If_assign(input))
            {
                find_and = input.find("&",0);find_or = input.find("|",0);
                find_xor = input.find("^",0);
                if(buggy_done && (bug_sequence == bug_location))
                {
                    if (find_and>=0) {
                        outfile<<buggy_AND_2_OR(input);
//                        outfile<<"/* BUG IS HERE; BUG LOCATION : Line # "<<bug_sequence<<"\n/*OLD:"<<input<<"*/\n";
                    }
                    else if(find_or>=0)
                    {
                        outfile<<buggy_OR_2_AND(input);
//                        outfile<<"/* BUG IS HERE; BUG LOCATION : Line # "<<bug_sequence<<"\n/*OLD : "<<input<<"*/\n";
                    }
                    else if (find_xor>=0)
                    {
                        outfile<<buggy_XOR_2_AND(input);
//                        outfile<<"/* BUG IS HERE; BUG LOCATION : Line # "<<bug_sequence<<"\n/*OLD : "<<input<<"*/\n";
                    }
                    buggy_done = false; bug_location+=1;
                }
                else{
                    outfile<<input<<endl;
                }
                ++bug_sequence;
            }
            else
            {
                outfile<<input<<endl;
            }
        }
        buggy_done=true; bug_sequence=0;
        cout<<"buggy_done : "<<buggy_done<<"  bug_sequence : "<<bug_sequence<<" bug location : "<<bug_location<<endl;
        outfile.close();
        
    }
    
}







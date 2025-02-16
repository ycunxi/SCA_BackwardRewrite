#include "BenchGen-FormatToABC.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>

using namespace std;
string GetWireString(char file[50])
{
    string i=",";
    string printwire=" wire ";
    string input,nameofwire;
    string finaloutput;
    int findassign,findeq,findarray,findarray2,correctfinaloutput;
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory+file;
    ifstream fin(in_location);
    while(getline(fin, input))
    {
        findassign=input.find("assign",0);
        findarray=input.find("[",0);
        findeq=input.find("=",0);
        if (findassign>0) {
            findassign=findassign+7;
            nameofwire.assign(input,findassign,findeq-findassign);
            findarray=nameofwire.find("[",0);
            if (findarray<0) { 
                nameofwire=nameofwire+i;
                finaloutput=finaloutput+nameofwire;
            }
            else
            {
                //  cout<<"match but is array"<<endl;
            }
        }
        else
        {
            //   cout<<"no match"<<endl;
        }
    }
    finaloutput.replace(finaloutput.size()-1,1,";");
    printwire=printwire+finaloutput;
    return printwire;
}

void BenchGenFormatToABC::ToABC(char file[50])
{
    string input,newlineforverilog;
    string newfile="abc-format-";
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory+file;
    ifstream fin(in_location);
    cout<<in_location<<endl;
    newfile=newfile+file;
    string fileout_directory="/ABC-Verilog-Format/";
    string out_location=location+fileout_directory+newfile;
    ofstream outfile(out_location);
    newlineforverilog=GetWireString(file);
    int findoutput;
    while(getline(fin,input))
    {
        findoutput=input.find("output",0);
        if(findoutput>0)
        {
            outfile<<input<<endl;
            outfile<<newlineforverilog<<endl;
        }
        else
        {
            outfile<<input<<endl;
        }
    }
}

//void BenchGenFormatToABC::ToCVC4(char file[50])

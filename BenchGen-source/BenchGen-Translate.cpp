//
//  BenchGen-Translate.cpp
//  Tools
//
//  Created by Cunxi Yu on 7/25/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include "BenchGen-Translate.h"

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
#include <glob.h>
#include <stdlib.h>
#include "gmp.h"
#include "gmpxx.h"
using namespace std;


vector<string> Files_vector(const string& pattern){
    glob_t glob_result;
    glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
    vector<string> files;
    for(unsigned int i=0;i<glob_result.gl_pathc;++i){
        files.push_back(string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return files;
}

vector<string> BenchGenTrans::AllVerilogNeed2CSF()
{
    vector<string> files;
    files = Files_vector("./verilogGenerated/*.v");
    return files;
}
void BenchGenTrans::Translate(char s[50])
{
    string buf[2999999];
    long long int number_line=1;
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory;
    string finalinput;
    string input;
    int comp;
    int equalpos;
    int andpos;
    int xorpos;
   // int multpos;
    int orpos;
    //int invpos;/
    int size;
    int temp_orpos;
    int temp_xorpos;
    int del;
    int dataright;
    int dataleft;
    int binaryonefind;
    int binaryzerofind;
    const string str0="assign";
    const string ortranslate=" - ";
    string xortranslate=" - 2 * ";
    string orrepalce;
    string xorreplace;
    finalinput=in_location+s;
  //  cout<<"file location is"<<finalinput;
    
    ifstream fin(finalinput);

    string extension=".eqn";
    string fileout_directory="/EqnFromVerilog/";
    string out_location=location+fileout_directory+s;
    string outputfilename=out_location+extension;
    int correctextension;
    correctextension=outputfilename.find(".v",0);
    outputfilename.erase(correctextension,2);
    ofstream outfile(outputfilename);
//
    int out_sig_bits;
    int getoutputarray;
    int output_sig;
    int getoutputarrayend;
    int invfind,eraseinvfind;
    int invfindand,invfindor,invfindxor,invfindend;
    string invreplacebegin="(1-";
    string invreplaceend=")";
    string temp;
    //find the output signature bits
    while(getline(fin,input))
    {
        output_sig=input.find("output",0);
        if(output_sig>0)
        {
  
           string getoutputarraystr;
            getoutputarray=input.find("[",0);
            getoutputarrayend=input.find(":",getoutputarray);
            getoutputarraystr.assign(input,getoutputarray+1,getoutputarrayend-getoutputarray);
            out_sig_bits=atoi(getoutputarraystr.c_str());
            //cout<<out_sig_bits;
        }
        del=input.find(";",0);
        if(del>0)
        {
        input.erase(del,1);
        }
        //del is used for clean ";"
        dataleft=input.find("[",0);
        while(dataleft>0)
        {
            input.erase(dataleft,1);
            dataleft=input.find("[",0);
        }
        dataright=input.find("]",0);
        while(dataright>0)
        {
            input.erase(dataright,1);
            dataright=input.find("]",0);
        }
        //dataleft & dataright are used for re-write the array of the input&output variables in Verilog
        binaryonefind=input.find("1'b1",0);
        binaryzerofind=input.find("1'b0",0);
        if(binaryonefind>0)
        {
            input.replace(binaryonefind,4," 1 ");
        }
        else if(binaryzerofind>0)
        {
            input.replace(binaryzerofind,4," 0 ");
        }
            invfind=input.find("!",0);
            if(invfind>0)
            {
                invfindand=input.find("&",invfind);
                invfindor=input.find("|",invfind);
                invfindxor=input.find("^",invfind);
                if(invfindand>0)
                {
                    temp.assign(input,invfind,invfindand-invfind);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
		            invreplacebegin+=temp;
		            invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindand-invfind);
                    input.insert(invfind,invreplacebegin);

                }
                else if(invfindor>0)
                {
                    temp.assign(input,invfind,invfindor-invfind);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
                    invreplacebegin+=temp;
                    invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindor-invfind);
                    input.insert(invfind,invreplacebegin);
                }
                else if(invfindxor>0)
                {
                    temp.assign(input,invfind,invfindxor-invfind);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
                    invreplacebegin+=temp;
                    invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindxor-invfind);
                    input.insert(invfind,invreplacebegin);
                }
                else
                {
                    invfindend=input.size();
                    temp.assign(input,invfind,invfindend);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
                    invreplacebegin+=temp;
                    invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindend-invfind);
                    input.insert(invfind,invreplacebegin);
                }
                cout<<"inverter replace as :"<<invreplacebegin<<endl;
                invreplacebegin="(1-"; 
            }
         else{
          // continue;
          }
        comp=input.find("assign",0);
        if(comp>0)
        {
            size=input.size();
            input.erase(comp,7);
            equalpos=input.find('=',0);
            xorpos=input.find('^',0);
            andpos=input.find('&',0);
            orpos=input.find('|',0);
	   
            if(andpos>0)
            {
                input.replace(andpos,1,"*");
            }
            else if(orpos>0)
            {
                orrepalce.assign(input,equalpos,size);
                orrepalce.replace(0,2," - ");
                temp_orpos=orrepalce.find("|",0);
                orrepalce.replace(temp_orpos,1,"*");
                input.replace(orpos,1,"+");
                //cout<<"replacement is :"<<orrepalce<<endl;
                input.append(orrepalce);
            }
            else if(xorpos>0)
            {
                xorreplace.assign(input,equalpos,size);
                temp_xorpos=xorreplace.find("^",0);
                xorreplace.replace(temp_xorpos,1,"*");
                xorreplace.replace(0,2," - 2 * ");
                input.replace(xorpos,1,"+");
                input.append(xorreplace);
            }
            else
            {
                //cout<<"No match"<<endl;
            }
            number_line++;
            /*
        int eraseblock;
            eraseblock=input.find(" ",0,1);
        while(eraseblock>0)
            {
                input.erase(eraseblock,1);
                eraseblock=input.find(" ",0,1);
            }*/
            input.erase(0,comp);
            buf[number_line]=input;
            //outfile<<input<<endl;
        }           
        else
        {
           // cout<<"No match"<<endl;
        }
    }
    
     for(int outputsignature=0;outputsignature<=out_sig_bits;outputsignature++)
     {
        outfile<<"z"<<outputsignature<<"*2^"<<outputsignature;
        if(outputsignature!=out_sig_bits)
        {
            outfile<<" + ";
        };
     
     } 
    outfile<<endl;
    for(long long int i=number_line;i>=1;i--)
    {
        outfile<<buf[i]<<endl;
    }

    /*for(int outputsignature=0;outputsignature<=out_sig_bits;outputsignature++)
     {
        outfile<<"z"<<outputsignature<<"*2^"<<outputsignature;
        if(outputsignature!=out_sig_bits)
        {
            outfile<<" + ";
        };
     //outfile<<endl;
     }*/

}
void BenchGenTrans::TranslatePoly(char s[50])
{
    string location(getcwd(NULL,0));
    string directory="/verilogGenerated/";
    string in_location=location+directory+s;
    string input;
    //cin>>s;
    int dataleft;
    int dataright;
    int comp;
    int equalpos;
    int andpos;
    int xorpos;
    int multpos;
    int orpos;
    int invpos;
    int size;
    int temp_orpos;
    int temp_xorpos;
    int del;
    const string str0="assign";
    const string ortranslate=" - ";
    string xortranslate=" - 2 * ";
    string orrepalce;
    string xorreplace;
    
    ifstream fin(in_location);
    string out_directory="/PolyFromVerilog/";

    string outputfilename=location+out_directory+s;
    string polyextenstion=".poly";
    outputfilename+=polyextenstion;
    int correctextension;
    correctextension=outputfilename.find(".v",0);
    outputfilename.erase(correctextension,2);
    ofstream outfile(outputfilename);
    //cout<<outputfilename;
    

    int output_sig;
    while(getline(fin,input))
    {
        output_sig=input.find("output",0);
        if(output_sig>0)
        {
           int getoutputarray;
           string getoutputarraystr;
            getoutputarray=input.find("[",0);
            getoutputarraystr.assign(input,getoutputarray+1,1);
            int out_sig_bits=atoi(getoutputarraystr.c_str());
            cout<<out_sig_bits;
        }
        del=input.find(";",0);
        if(del>0)
        {
            input.erase(del,1);
        }
        dataleft=input.find("[",0);
        while(dataleft>0)
        {
            input.erase(dataleft,1);
            dataleft=input.find("[",0);
        }
        dataright=input.find("]",0);
        while(dataright>0)
        {
            input.erase(dataright,1);
            dataright=input.find("]",0);
        }
        comp=input.find("assign",0);
        if(comp>0)
        {
            size=input.size();
            input.erase(comp,7);
            equalpos=input.find('=',0);
            xorpos=input.find('^',0);
            andpos=input.find('&',0);
            orpos=input.find('|',0);
            if(andpos>0)
            {
                input.replace(andpos,1,"*");
            }
            else if(orpos>0)
            {
                orrepalce.assign(input,equalpos,size);
                orrepalce.replace(0,2," - ");
                temp_orpos=orrepalce.find("|",0);
                orrepalce.replace(temp_orpos,1,"*");
                input.replace(orpos,1,"+");
                //cout<<"replacement is :"<<orrepalce<<endl;
                input.append(orrepalce);
            }
            else if(xorpos>0)
            {
                xorreplace.assign(input,equalpos,size);
                temp_xorpos=xorreplace.find("^",0);
                xorreplace.replace(temp_xorpos,1,"*");
                xorreplace.replace(0,2," - 2 * ");
                input.replace(xorpos,1,"+");
                input.append(xorreplace);
            }
            else
            {
                //cout<<"No match"<<endl;
            }

            input.erase(0,comp);
            outfile<<"poly "<<input<<endl;
        }
        else
        {
            // cout<<"No match"<<endl;
            
            
        }
    }  
}

void BenchGenTrans::TranslateReverse(char file[50])
{
    string input;
    string q[10];
    int n=1;
    ifstream fin(file);
    ofstream outfile(file);
}


void BenchGenTrans::TranslateToCSF(string s)
{
    string buf[999999];
    long long int number_line=1;
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory;
    string finalinput;
    string input;
    int comp;
    int equalpos;
    int andpos;
    int xorpos;
    int orpos;
    int size;
    int temp_orpos;
    int temp_xorpos;
    int del;
    int dataright;
    int dataleft;
    int binaryonefind;
    int binaryzerofind;
    const string str0="assign";
    const string ortranslate=" - ";
    
    //replace output "z" to the real variable name
    string output_var;
    int output_var_start=0; int output_var_end = 0; int if_single_var=0;
    string xortranslate=" - 2 * ";
    string orrepalce;
    string xorreplace;
    finalinput=in_location+s;
  //  cout<<"file location is"<<finalinput;
    
    ifstream fin(finalinput);

    string extension=".csf";
    string fileout_directory="/csfFromVerilog/";
    string out_location=location+fileout_directory+s;
    string outputfilename=out_location+extension;
    int correctextension;
    correctextension=outputfilename.find(".v",0);
    outputfilename.erase(correctextension,2);
    ofstream outfile(outputfilename);
//
    int out_sig_bits;
    int getoutputarray;
    int output_sig;
    int getoutputarrayend;
    int invfind,eraseinvfind;
    int invfindand,invfindor,invfindxor,invfindend;
    string invreplacebegin="(1-";
    string invreplaceend=")";
    string temp;
    //find the output signature bits
    //
    //Create multi output signature
    int howmanyoutput=0;
    
    int temp_int=0;

    while(getline(fin,input))
    {
        output_sig=input.find("output",0);
        if(output_sig>0)
        {
            output_var_start = input.find("]",0);
            output_var_end = input.find(";",0);
            output_var.assign(input,output_var_start+2, output_var_end-output_var_start-2);
            if_single_var = output_var.find(",",0);
            if(if_single_var >= 0)
            {
                while(if_single_var>0)
                {
                    temp_int = if_single_var;
                    if_single_var = output_var.find(",",if_single_var+1);
                }
                output_var.erase(0,temp_int+1);
            }
            cout<<"Output variables is:"<<output_var<<endl;
            string getoutputarraystr;
            getoutputarray=input.find("[",0);
            getoutputarrayend=input.find(":",getoutputarray);
            getoutputarraystr.assign(input,getoutputarray+1,getoutputarrayend-getoutputarray);
            out_sig_bits=atoi(getoutputarraystr.c_str());
            //cout<<out_sig_bits;
        }
        del=input.find(";",0);
        if(del>0)
        {
        input.erase(del,1);
        }
        //del is used for clean ";"
        dataleft=input.find("[",0);
        while(dataleft>0)
        {
            input.erase(dataleft,1);
            dataleft=input.find("[",0);
        }
        dataright=input.find("]",0);
        while(dataright>0)
        {
            input.erase(dataright,1);
            dataright=input.find("]",0);
        }
        //dataleft & dataright are used for re-write the array of the input&output variables in Verilog
        binaryonefind=input.find("1'b1",0);
        binaryzerofind=input.find("1'b0",0);
        if(binaryonefind>0)
        {
            input.replace(binaryonefind,4," 1 ");
        }
        else if(binaryzerofind>0)
        {
            input.replace(binaryzerofind,4," 0 ");
        }
            invfind=input.find("!",0);
            if(invfind>0)
            {
                invfindand=input.find("&",invfind);
                invfindor=input.find("|",invfind);
                invfindxor=input.find("^",invfind);
                if(invfindand>0)
                {
                    temp.assign(input,invfind,invfindand-invfind);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
		            invreplacebegin+=temp;
		            invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindand-invfind);
                    input.insert(invfind,invreplacebegin);

                }
                else if(invfindor>0)
                {
                    temp.assign(input,invfind,invfindor-invfind);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
                    invreplacebegin+=temp;
                    invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindor-invfind);
                    input.insert(invfind,invreplacebegin);
                }
                else if(invfindxor>0)
                {
                    temp.assign(input,invfind,invfindxor-invfind);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
                    invreplacebegin+=temp;
                    invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindxor-invfind);
                    input.insert(invfind,invreplacebegin);
                }
                else
                {
                    invfindend=input.size();
                    temp.assign(input,invfind,invfindend);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
                    invreplacebegin+=temp;
                    invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindend-invfind);
                    input.insert(invfind,invreplacebegin);
                }
                cout<<"inverter replace as :"<<invreplacebegin<<endl;
                invreplacebegin="(1-"; 
            }
         else{
          // continue;
          }
        comp=input.find("assign",0);
        if(comp>0)
        {
            size=input.size();
            input.erase(comp,7);
            equalpos=input.find('=',0);
            xorpos=input.find('^',0);
            andpos=input.find('&',0);
            orpos=input.find('|',0);
	   
            if(andpos>0)
            {
                input.replace(andpos,1,"*");
            }
            else if(orpos>0)
            {
                orrepalce.assign(input,equalpos,size);
                orrepalce.replace(0,2," - ");
                temp_orpos=orrepalce.find("|",0);
                orrepalce.replace(temp_orpos,1,"*");
                input.replace(orpos,1,"+");
                //cout<<"replacement is :"<<orrepalce<<endl;
                input.append(orrepalce);
            }
            else if(xorpos>0)
            {
                xorreplace.assign(input,equalpos,size);
                temp_xorpos=xorreplace.find("^",0);
                xorreplace.replace(temp_xorpos,1,"*");
                xorreplace.replace(0,2," - 2 * ");
                input.replace(xorpos,1,"+");
                input.append(xorreplace);
            }
            else
            {
                //cout<<"No match"<<endl;
            }
            number_line++;
            /*
        int eraseblock;
            eraseblock=input.find(" ",0,1);
        while(eraseblock>0)
            {
                input.erase(eraseblock,1);
                eraseblock=input.find(" ",0,1);
            }*/
            input.erase(0,comp);
            buf[number_line]=input;
            //outfile<<input<<endl;
        }           
        else
        {
           // cout<<"No match"<<endl;
        }
    }
    for(long long int i=number_line;i>=1;i--)
    {
        outfile<<buf[i]<<endl;
    }
    
    if(output_var.length()>0)
    {
        for(int outputsignature=0;outputsignature<=out_sig_bits;outputsignature++)
        {
            outfile<<output_var<<outputsignature<<"*2^"<<outputsignature;
            if(outputsignature!=out_sig_bits)
            {
                outfile<<" + ";
            };
        } 
        outfile<<endl;
    }
    else
    {
        for(int outputsignature=0;outputsignature<=out_sig_bits;outputsignature++)
        {
            outfile<<"z"<<outputsignature<<"*2^"<<outputsignature;
            if(outputsignature!=out_sig_bits)
            {
                outfile<<" + ";
            };
        } 
        outfile<<endl;

    }

    /*for(int outputsignature=0;outputsignature<=out_sig_bits;outputsignature++)
     {
        outfile<<"z"<<outputsignature<<"*2^"<<outputsignature;
        if(outputsignature!=out_sig_bits)
        {
            outfile<<" + ";
        };
     //outfile<<endl;
     }*/

}

void BenchGenTrans::NoneReverseTranslate(char s[50])
{
  
    long long int number_line=1;
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory;
    string finalinput;
    string input;
    int comp;
    int equalpos;
    int andpos;
    int xorpos;
   // int multpos;
    int orpos;
    //int invpos;/
    int size;
    int temp_orpos;
    int temp_xorpos;
    int del;
    int dataright;
    int dataleft;
    int binaryonefind;
    int binaryzerofind;
    const string str0="assign";
    const string ortranslate=" - ";
    string xortranslate=" - 2 * ";
    string orrepalce;
    string xorreplace;
    finalinput=in_location+s;
  //  cout<<"file location is"<<finalinput;
    
    ifstream fin(finalinput);

    string extension=".eqn";
    string fileout_directory="/EqnFromVerilog/";
    string out_location=location+fileout_directory+s;
    string outputfilename=out_location+extension;
    int correctextension;
    correctextension=outputfilename.find(".v",0);
    outputfilename.erase(correctextension,2);
    ofstream outfile(outputfilename);
//
    int out_sig_bits;
    int getoutputarray;
    int output_sig;
    int getoutputarrayend;
    int invfind,eraseinvfind;
    int invfindand,invfindor,invfindxor,invfindend;
    string invreplacebegin="(1-";
    string invreplaceend=")";
    string temp;
    //find the output signature bits
    while(getline(fin,input))
    {
        output_sig=input.find("output",0);
        if(output_sig>0)
        {
             
            string getoutputarraystr;
            getoutputarray=input.find("[",0);
            getoutputarrayend=input.find(":",getoutputarray);
            getoutputarraystr.assign(input,getoutputarray+1,getoutputarrayend-getoutputarray);
            out_sig_bits=atoi(getoutputarraystr.c_str());
            //cout<<out_sig_bits;
        }
        del=input.find(";",0);
        if(del>0)
        {
        input.erase(del,1);
        }
        //del is used for clean ";"
        dataleft=input.find("[",0);
        while(dataleft>0)
        {
            input.erase(dataleft,1);
            dataleft=input.find("[",0);
        }
        dataright=input.find("]",0);
        while(dataright>0)
        {
            input.erase(dataright,1);
            dataright=input.find("]",0);
        }
        //dataleft & dataright are used for re-write the array of the input&output variables in Verilog
        binaryonefind=input.find("1'b1",0);
        binaryzerofind=input.find("1'b0",0);
        if(binaryonefind>0)
        {
            input.replace(binaryonefind,4," 1 ");
        }
        else if(binaryzerofind>0)
        {
            input.replace(binaryzerofind,4," 0 ");
        }
            invfind=input.find("!",0);
            if(invfind>0)
            {
                invfindand=input.find("&",invfind);
                invfindor=input.find("|",invfind);
                invfindxor=input.find("^",invfind);
                if(invfindand>0)
                {
                    temp.assign(input,invfind,invfindand-invfind);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
		            invreplacebegin+=temp;
		            invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindand-invfind);
                    input.insert(invfind,invreplacebegin);

                }
                else if(invfindor>0)
                {
                    temp.assign(input,invfind,invfindor-invfind);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
                    invreplacebegin+=temp;
                    invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindor-invfind);
                    input.insert(invfind,invreplacebegin);
                }
                else if(invfindxor>0)
                {
                    temp.assign(input,invfind,invfindxor-invfind);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
                    invreplacebegin+=temp;
                    invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindxor-invfind);
                    input.insert(invfind,invreplacebegin);
                }
                else
                {
                    invfindend=input.size();
                    temp.assign(input,invfind,invfindend);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
                    invreplacebegin+=temp;
                    invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindend-invfind);
                    input.insert(invfind,invreplacebegin);
                }
                cout<<"inverter replace as :"<<invreplacebegin<<endl;
                invreplacebegin="(1-"; 
            }
         else{
          // continue;
          }
        comp=input.find("assign",0);
        if(comp>0)
        {
            size=input.size();
            input.erase(comp,7);
            equalpos=input.find('=',0);
            xorpos=input.find('^',0);
            andpos=input.find('&',0);
            orpos=input.find('|',0);
	   
            if(andpos>0)
            {
                input.replace(andpos,1,"*");
            }
            else if(orpos>0)
            {
                orrepalce.assign(input,equalpos,size);
                orrepalce.replace(0,2," - ");
                temp_orpos=orrepalce.find("|",0);
                orrepalce.replace(temp_orpos,1,"*");
                input.replace(orpos,1,"+");
                //cout<<"replacement is :"<<orrepalce<<endl;
                input.append(orrepalce);
            }
            else if(xorpos>0)
            {
                xorreplace.assign(input,equalpos,size);
                temp_xorpos=xorreplace.find("^",0);
                xorreplace.replace(temp_xorpos,1,"*");
                xorreplace.replace(0,2," - 2 * ");
                input.replace(xorpos,1,"+");
                input.append(xorreplace);
            }
            else
            {
                //cout<<"No match"<<endl;
            }
            number_line++;
            /*
        int eraseblock;
            eraseblock=input.find(" ",0,1);
        while(eraseblock>0)
            {
                input.erase(eraseblock,1);
                eraseblock=input.find(" ",0,1);
            }*/
            input.erase(0,comp);
           
            outfile<<input<<endl;
        }           
        else
        {
           // cout<<"No match"<<endl;
        }
    }
    
     for(int outputsignature=0;outputsignature<=out_sig_bits;outputsignature++)
     {
        outfile<<"z"<<outputsignature<<"*2^"<<outputsignature;
        if(outputsignature!=out_sig_bits)
        {
            outfile<<" + ";
        };
     
     } 
    outfile<<endl;


}
bool If_assign(string input)
{
    int find = 0;
    find = input.find("assign",0);
    if(find>=0){ return true;}
    else{ return false;}
}
bool removeChar(char c)
{
    if (c == '[' | c ==']' | c == ';')
    {
        return true;
    }
    else
    {
        return false;
    }
}
string NewParse_PreProcess(string input)
{
    int find_assign=0; find_assign = input.find("assign",0);
    input.erase(0,find_assign+6);
    input.erase( std::remove_if( input.begin(), input.end(), ::isspace ), input.end() );
    input.erase( std::remove_if( input.begin(),input.end(),removeChar), input.end());
    return input;
}
string NewParse_Netlist(string input)
{
    input = NewParse_PreProcess(input);
    int find_and=0;int find_or=0;int find_xor=0;int find_eq=0;
    find_eq = input.find("=",0);
    find_and = input.find("&",0);
    find_or  = input.find("|",0);
    find_xor = input.find("^",0);
    string netlist = "=";
    string output,in1,in2;
    if (find_and>=0)
    {
        output.assign(input,0,find_eq); in1.assign(input,find_eq+1,find_and-find_eq-1);
        in2.assign(input,find_and+1,input.length()-find_and-1);
        netlist+=output+";1,"+in1+"*"+in2+";\n";
    }
    else if(find_or>=0)
    {
        output.assign(input,0,find_eq); in1.assign(input,find_eq+1,find_or-find_eq-1);
        in2.assign(input,find_or+1,input.length()-find_or-1);
        netlist+=output+";1,"+in1+";1,"+in2+";-1,"+in1+"*"+in2+"\n";
    }
    else if (find_xor>=0)
    {
        output.assign(input,0,find_eq); in1.assign(input,find_eq+1,find_xor-find_eq-1);
        in2.assign(input,find_xor+1,input.length()-find_xor-1);
        netlist+=output+";1,"+in1+";1,"+in2+";-2,"+in1+"*"+in2+"\n";
    }
    else if (find_eq>=0)
    {
        output.assign(input,0,find_eq);
        in1.assign(input,find_eq+1,input.length()-1-find_eq);
        netlist+=output+";1,"+in1+";\n";
    }
    return netlist;
}
int Num_outputs_sig(string input)
{
    int start=0; int end=0;
    start = input.find("[",0);
    end = input.find(":",0);
    string num; num.assign(input,start+1,end-start-1);
    return atoi(num.c_str());
}

string output_sig_EQN2(int num)
{
    mpq_class coef;
    stringstream label;string sig;
    for (int i=0; i<=num; i++) {
        label<<i;
        coef=pow(2,i);
        sig +=coef.get_str()+",z"+label.str()+";";
        coef = 0;label.str("");
    }
    return sig;
}
void BenchGenTrans::NEW_parse_outputfile(string file_in)
{
    int find_output=0; int size_out=0;
    vector<string> r;
    vector<string>::reverse_iterator i;
    string old_filein = file_in;
    string location(getcwd(NULL,0));
    file_in=location+"/verilogGenerated/"+file_in;
    ifstream fin(file_in.c_str());string input;
    string file_out = location+"/new_eqn2/"+old_filein+".eqn2";
    ofstream outfile(file_out.c_str());
    while (getline(fin,input)) {
        find_output = input.find("output",0);
        if(find_output>=0)
        {
            size_out = Num_outputs_sig(input);
        }
        if(If_assign(input))
        {
            //outfile<<NewParse_Netlist(input);
            r.push_back(NewParse_Netlist(input));
        }
    }
    outfile<<output_sig_EQN2(size_out)+"\n";
    for (i=r.rbegin(); i!=r.rend(); ++i) {
        outfile<<*i;   
    }

}













void BenchGenTrans::TranslateToCSF_TopSig(string s)
{
    string buf[999999];
    long long int number_line=1;
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory;
    string finalinput;
    string input;
    int comp;
    int equalpos;
    int andpos;
    int xorpos;
    int orpos;
    int size;
    int temp_orpos;
    int temp_xorpos;
    int del;
    int dataright;
    int dataleft;
    int binaryonefind;
    int binaryzerofind;
    const string str0="assign";
    const string ortranslate=" - ";
    
    //replace output "z" to the real variable name
    string output_var;
    int output_var_start=0; int output_var_end = 0; int if_single_var=0;
    string xortranslate=" - 2 * ";
    string orrepalce;
    string xorreplace;
    finalinput=in_location+s;
  //  cout<<"file location is"<<finalinput;
    
    ifstream fin(finalinput);

    string extension=".csf";
    string fileout_directory="/csfFromVerilog/";
    string out_location=location+fileout_directory+s;
    string outputfilename=out_location+extension;
    int correctextension;
    correctextension=outputfilename.find(".v",0);
    outputfilename.erase(correctextension,2);
    ofstream outfile(outputfilename);
//
    int out_sig_bits;
    int getoutputarray;
    int output_sig;
    int getoutputarrayend;
    int invfind,eraseinvfind;
    int invfindand,invfindor,invfindxor,invfindend;
    string invreplacebegin="(1-";
    string invreplaceend=")";
    string temp;
    //find the output signature bits
    //
    //Create multi output signature
    int howmanyoutput=0;
    
    int temp_int=0;

    while(getline(fin,input))
    {
        output_sig=input.find("output",0);
        if(output_sig>0)
        {
            output_var_start = input.find("]",0);
            output_var_end = input.find(";",0);
            output_var.assign(input,output_var_start+2, output_var_end-output_var_start-2);
            if_single_var = output_var.find(",",0);
            if(if_single_var >= 0)
            {
                while(if_single_var>0)
                {
                    temp_int = if_single_var;
                    if_single_var = output_var.find(",",if_single_var+1);
                }
                output_var.erase(0,temp_int+1);
            }
            cout<<"Output variables is:"<<output_var<<endl;
            string getoutputarraystr;
            getoutputarray=input.find("[",0);
            getoutputarrayend=input.find(":",getoutputarray);
            getoutputarraystr.assign(input,getoutputarray+1,getoutputarrayend-getoutputarray);
            out_sig_bits=atoi(getoutputarraystr.c_str());
            //cout<<out_sig_bits;
        }
        del=input.find(";",0);
        if(del>0)
        {
        input.erase(del,1);
        }
        //del is used for clean ";"
        dataleft=input.find("[",0);
        while(dataleft>0)
        {
            input.erase(dataleft,1);
            dataleft=input.find("[",0);
        }
        dataright=input.find("]",0);
        while(dataright>0)
        {
            input.erase(dataright,1);
            dataright=input.find("]",0);
        }
        //dataleft & dataright are used for re-write the array of the input&output variables in Verilog
        binaryonefind=input.find("1'b1",0);
        binaryzerofind=input.find("1'b0",0);
        if(binaryonefind>0)
        {
            input.replace(binaryonefind,4," 1 ");
        }
        else if(binaryzerofind>0)
        {
            input.replace(binaryzerofind,4," 0 ");
        }
            invfind=input.find("!",0);
            if(invfind>0)
            {
                invfindand=input.find("&",invfind);
                invfindor=input.find("|",invfind);
                invfindxor=input.find("^",invfind);
                if(invfindand>0)
                {
                    temp.assign(input,invfind,invfindand-invfind);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
		            invreplacebegin+=temp;
		            invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindand-invfind);
                    input.insert(invfind,invreplacebegin);

                }
                else if(invfindor>0)
                {
                    temp.assign(input,invfind,invfindor-invfind);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
                    invreplacebegin+=temp;
                    invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindor-invfind);
                    input.insert(invfind,invreplacebegin);
                }
                else if(invfindxor>0)
                {
                    temp.assign(input,invfind,invfindxor-invfind);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
                    invreplacebegin+=temp;
                    invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindxor-invfind);
                    input.insert(invfind,invreplacebegin);
                }
                else
                {
                    invfindend=input.size();
                    temp.assign(input,invfind,invfindend);
                    eraseinvfind=temp.find("!",0);
                    temp.erase(eraseinvfind,1);
                    invreplacebegin+=temp;
                    invreplacebegin+=invreplaceend;
                    input.erase(invfind,invfindend-invfind);
                    input.insert(invfind,invreplacebegin);
                }
                cout<<"inverter replace as :"<<invreplacebegin<<endl;
                invreplacebegin="(1-"; 
            }
         else{
          // continue;
          }
        comp=input.find("assign",0);
        if(comp>0)
        {
            size=input.size();
            input.erase(comp,7);
            equalpos=input.find('=',0);
            xorpos=input.find('^',0);
            andpos=input.find('&',0);
            orpos=input.find('|',0);
	   
            if(andpos>0)
            {
                input.replace(andpos,1,"*");
            }
            else if(orpos>0)
            {
                orrepalce.assign(input,equalpos,size);
                orrepalce.replace(0,2," - ");
                temp_orpos=orrepalce.find("|",0);
                orrepalce.replace(temp_orpos,1,"*");
                input.replace(orpos,1,"+");
                //cout<<"replacement is :"<<orrepalce<<endl;
                input.append(orrepalce);
            }
            else if(xorpos>0)
            {
                xorreplace.assign(input,equalpos,size);
                temp_xorpos=xorreplace.find("^",0);
                xorreplace.replace(temp_xorpos,1,"*");
                xorreplace.replace(0,2," - 2 * ");
                input.replace(xorpos,1,"+");
                input.append(xorreplace);
            }
            else
            {
                //cout<<"No match"<<endl;
            }
            number_line++;
            /*
        int eraseblock;
            eraseblock=input.find(" ",0,1);
        while(eraseblock>0)
            {
                input.erase(eraseblock,1);
                eraseblock=input.find(" ",0,1);
            }*/
            input.erase(0,comp);
            buf[number_line]=input;
            //outfile<<input<<endl;
        }           
        else
        {
           // cout<<"No match"<<endl;
        }
    }

    
    if(output_var.length()>0)
    {
        for(int outputsignature=0;outputsignature<=out_sig_bits;outputsignature++)
        {
            outfile<<output_var<<outputsignature<<"*2^"<<outputsignature;
            if(outputsignature!=out_sig_bits)
            {
                outfile<<" + ";
            };
        } 
        outfile<<endl;
    }
    else
    {
        for(int outputsignature=0;outputsignature<=out_sig_bits;outputsignature++)
        {
            outfile<<"z"<<outputsignature<<"*2^"<<outputsignature;
            if(outputsignature!=out_sig_bits)
            {
                outfile<<" + ";
            };
        } 
        outfile<<endl;
    }


    for(long long int i=number_line;i>=1;i--)
    {
        outfile<<buf[i]<<endl;
    }
    /*for(int outputsignature=0;outputsignature<=out_sig_bits;outputsignature++)
     {
        outfile<<"z"<<outputsignature<<"*2^"<<outputsignature;
        if(outputsignature!=out_sig_bits)
        {
            outfile<<" + ";
        };
     //outfile<<endl;
     }*/

}










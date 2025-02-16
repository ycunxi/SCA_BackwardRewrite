//
//  BenchGen-SeqBench.cpp
//  NewModelForSQ
//
//  Created by Cunxi Yu on 9/22/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include "BenchGen-SeqBench.h"
#include <iostream>
#include<fstream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

void inputassign(int x)
{
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory;
    string filename="Square-seq";
    stringstream outfilename;
    outfilename<<filename<<x<<".v";
    string f=outfilename.str();
    f=in_location+f;
    ofstream outfile(f,ios::app);
    for (int sig=0; sig<=2*x-1;sig++) {
        if (sig%2==0) {
            outfile<<"    "<<"assign a1_["<<sig<<"]"<<"=~a"<<sig/2<<";"<<endl;
        }
        else
        {
            outfile<<"    "<<"assign a1_["<<sig<<"]"<<"=1'b1"<<";"<<endl;
        }
    }
    //a1_* input define
    for (int i=1; i<=x; i++) {
        if(i%2==1 && i!=1)
        {
            for (int sig=0; sig<=2*x-1; sig++) {
                if (sig<=x+i-1 && sig%2==0 && (sig/2+(x-i-1)/2)-(x-i)>=0) {
                    outfile<<"    "<<"assign b"<<i<<"_["<<sig<<"]"<<"="<<"a"<<sig/2+(x-i-1)/2<<" & a"<<(sig/2+(x-i-1)/2)-(x-i)<<";"<<endl;
                }
                else
                {
                    outfile<<"    "<<"assign b"<<i<<"_["<<sig<<"]"<<"=1'b0"<<";"<<endl;
                }
            }
        }
        else if(i==1 && i%2==1)
        {
            for (int sig=0; sig<=2*x-1; sig++) {
                if (sig==0) {
                    outfile<<"    "<<"assign b"<<i<<"_["<<sig<<"]"<<"=1'b1"<<";"<<endl;
                }
                else if (sig<=x+i-1 && sig%2==0 && (sig/2+(x-i-1)/2)-(x-i)>=0) {
                    outfile<<"    "<<"assign b"<<i<<"_["<<sig<<"]"<<"="<<"a"<<sig/2+(x-i-1)/2<<" & a"<<(sig/2+(x-i-1)/2)-(x-i)<<";"<<endl;
                }
                else
                {
                    outfile<<"    "<<"assign b"<<i<<"_["<<sig<<"]"<<"=1'b0"<<";"<<endl;
                }
            }
            
        }
        else if(i!=x)
        {
            for (int sig=0; sig<=2*x-1; sig++) {
                if (sig<=x+i-1 && sig%2==1 && ((sig+1)/2+(x-i-1)/2)-(x-i)>=0) {
                    outfile<<"    "<<"assign b"<<i<<"_["<<sig<<"]"<<"="<<"a"<<(sig+1)/2+(x-i-1)/2<<" & a"<<((sig+1)/2+(x-i-1)/2)-(x-i)<<";"<<endl;
                }
                else
                {
                    outfile<<"    "<<"assign b"<<i<<"_["<<sig<<"]"<<"=1'b0"<<";"<<endl;
                }
            }
        }
        else
        {
            for (int sig=0; sig<=2*x-1;sig++) {
                if (sig%2==1) {
                    outfile<<"    "<<"assign b"<<i<<"_["<<sig<<"]"<<"=a"<<sig/2<<";"<<endl;
                }
                else
                {
                    outfile<<"    "<<"assign b"<<i<<"_["<<sig<<"]"<<"=1'b0"<<";"<<endl;
                }
            }
        }
    }
}


void firstadder(int num_adder,int x,int bit)
{
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory;
    string filename="Square-seq";
    stringstream outfilename;
    outfilename<<filename<<bit<<".v";
    string f=outfilename.str();
    f=in_location+f;
    ofstream outfile(f,ios::app);
    x--;
    outfile<<"    assign adder_"<<num_adder<<"_"<<"add_cout[0] = a"<<num_adder<<"_"<<"[0] & b"<<num_adder<<"_"<<"[0] ;"<<endl;
    outfile<<"    assign adder_"<<num_adder<<"_"<<"add_sum[0] = a"<<num_adder<<"_"<<"[0] ^ b"<<num_adder<<"_"<<"[0];"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i-2<<" = adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"] & a"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i-1<<" = adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"] & b"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i<<" = a"<<num_adder<<"_"<<"["<<i<<"] & b"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"or"<<i<<" = adder_"<<num_adder<<"_"<<"and"<<3*i-2<<" | "<<"adder_"<<num_adder<<"_"<<"and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"add_cout["<<i<<"] = adder_"<<num_adder<<"_"<<"or"<<i<<" | ""adder_"<<num_adder<<"_"<<"and"<<3*i<<";"<<endl;
            
            outfile<<"    assign adder_"<<num_adder<<"_"<<"xor"<<i<<" = a"<<num_adder<<"_"<<"["<<i<<"] ^ b"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"add_sum["<<i<<"] = adder_"<<num_adder<<"_"<<"xor"<<i<<" ^ "<<"adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i-2<<" = adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"] & a"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i-1<<" = adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"] & b"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i<<" = a"<<num_adder<<"_"<<"["<<i<<"] & b"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"or"<<i<<" = adder_"<<num_adder<<"_"<<"and"<<3*i-2<<" | "<<"adder_"<<num_adder<<"_"<<"and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"add_sum["<<i+1<<"] = adder_"<<num_adder<<"_"<<"or"<<i<<" | adder_"<<num_adder<<"_"<<"and"<<3*i<<";"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"xor"<<i<<" = a"<<num_adder<<"_"<<"["<<i<<"] ^ b"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"add_sum["<<i<<"] = adder_"<<num_adder<<"_"<<"xor"<<i<<" ^ "<<"adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"];"<<endl;
        }
    }
}

void regularadder(int num_adder,int x,int bit)
{
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory;
    string filename="Square-seq";
    stringstream outfilename;
    outfilename<<filename<<bit<<".v";
    string f=outfilename.str();
    f=in_location+f;
    ofstream outfile(f,ios::app);
    x--;
    outfile<<"    assign adder_"<<num_adder<<"_"<<"add_cout[0] = adder_"<<num_adder-1<<"_"<<"add_sum[0] & b"<<num_adder<<"_"<<"[0] ;"<<endl;
    outfile<<"    assign adder_"<<num_adder<<"_"<<"add_sum[0] = adder_"<<num_adder-1<<"_"<<"add_sum[0] ^ b"<<num_adder<<"_"<<"[0];"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i-2<<" = adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"] & adder_"<<num_adder-1<<"_"<<"add_sum["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i-1<<" = adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"] & b"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i<<" = adder_"<<num_adder-1<<"_"<<"add_sum["<<i<<"] & b"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"or"<<i<<" = adder_"<<num_adder<<"_"<<"and"<<3*i-2<<" | "<<"adder_"<<num_adder<<"_"<<"and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"add_cout["<<i<<"] = adder_"<<num_adder<<"_"<<"or"<<i<<" | ""adder_"<<num_adder<<"_"<<"and"<<3*i<<";"<<endl;
            
            outfile<<"    assign adder_"<<num_adder<<"_"<<"xor"<<i<<" = adder_"<<num_adder-1<<"_"<<"add_sum["<<i<<"] ^ b"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"add_sum["<<i<<"] = adder_"<<num_adder<<"_"<<"xor"<<i<<" ^ "<<"adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i-2<<" = adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"] & adder_"<<num_adder-1<<"_"<<"add_sum["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i-1<<" = adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i<<" = adder_"<<num_adder-1<<"_"<<"add_sum["<<i<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"or"<<i<<" = adder_"<<num_adder<<"_"<<"and"<<3*i-2<<" | "<<"adder_"<<num_adder<<"_"<<"and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"add_sum["<<i+1<<"] = adder_"<<num_adder<<"_"<<"or"<<i<<" | adder_"<<num_adder<<"_"<<"and"<<3*i<<";"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"xor"<<i<<" = adder_"<<num_adder-1<<"_"<<"add_sum["<<i<<"] ^ 1'b0;"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"add_sum["<<i<<"] = adder_"<<num_adder<<"_"<<"xor"<<i<<" ^ "<<"adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"];"<<endl;
        }
    }
}



void finaladder(int num_adder,int x,int bit)
{
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory;
    string filename="Square-seq";
    stringstream outfilename;
    outfilename<<filename<<bit<<".v";
    string f=outfilename.str();
    f=in_location+f;
    ofstream outfile(f,ios::app);
    x--;
    outfile<<"    assign adder_"<<num_adder<<"_"<<"add_cout[0] = adder_"<<num_adder-1<<"_"<<"add_sum[0] & b"<<num_adder<<"_"<<"[0] ;"<<endl;
    outfile<<"    assign z[0] = adder_"<<num_adder-1<<"_"<<"add_sum[0] ^ b"<<num_adder<<"_"<<"[0];"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i-2<<" = adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"] & adder_"<<num_adder-1<<"_"<<"add_sum["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i-1<<" = adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"] & b"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i<<" = adder_"<<num_adder-1<<"_"<<"add_sum["<<i<<"] & b"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"or"<<i<<" = adder_"<<num_adder<<"_"<<"and"<<3*i-2<<" | "<<"adder_"<<num_adder<<"_"<<"and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"add_cout["<<i<<"] = adder_"<<num_adder<<"_"<<"or"<<i<<" | ""adder_"<<num_adder<<"_"<<"and"<<3*i<<";"<<endl;
            
            outfile<<"    assign adder_"<<num_adder<<"_"<<"xor"<<i<<" = adder_"<<num_adder-1<<"_"<<"add_sum["<<i<<"] ^ b"<<num_adder<<"_"<<"["<<i<<"];"<<endl;
            outfile<<"    assign z["<<i<<"] = adder_"<<num_adder<<"_"<<"xor"<<i<<" ^ "<<"adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i-2<<" = adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"] & adder_"<<num_adder-1<<"_"<<"add_sum["<<i<<"];"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i-1<<" = adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"and"<<3*i<<" = adder_"<<num_adder-1<<"_"<<"add_sum["<<i<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"or"<<i<<" = adder_"<<num_adder<<"_"<<"and"<<3*i-2<<" | "<<"adder_"<<num_adder<<"_"<<"and"<<3*i-1<<";"<<endl;
            outfile<<"    assign z["<<i+1<<"] = adder_"<<num_adder<<"_"<<"or"<<i<<" | adder_"<<num_adder<<"_"<<"and"<<3*i<<";"<<endl;
            outfile<<"    assign adder_"<<num_adder<<"_"<<"xor"<<i<<" = adder_"<<num_adder-1<<"_"<<"add_sum["<<i<<"] ^ 1'b0;"<<endl;
            outfile<<"    assign z["<<i<<"] = adder_"<<num_adder<<"_"<<"xor"<<i<<" ^ "<<"adder_"<<num_adder<<"_"<<"add_cout["<<i-1<<"];"<<endl;
        }
    }
}


void BenchGenSeq::seqsq(int bit)
{
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory;
    string filename="Square-seq";
    stringstream outfilename;
    outfilename<<filename<<bit<<".v";
    string f=outfilename.str();
    f=in_location+f;
    ofstream outfile(f);
    outfile<<"module seqsqUnrolledModel();"<<endl;
    outfile<<"    input ["<<bit-1<<":0] a;"<<endl;
    outfile<<"    output ["<<3*bit-1<<":0] z;"<<endl;
    
    for (int i=1; i<=bit; i++) {
        if (i==1) {
            firstadder(i, 2*bit+i-1,bit);
        }
        else if(i!=bit)
        {
            regularadder(i, 2*bit+i-1,bit);
        }
        else
        {
            finaladder(i, 2*bit+i-1,bit);
        }
    }    
    inputassign(bit);
}

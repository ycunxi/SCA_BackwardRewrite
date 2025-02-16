//
//  main.cpp
//  verilogRTL-Multiplier
//
//  Created by Cunxi Yu on 6/27/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//
#include "BenchGen-Matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sstream>
using namespace std;

#include <iostream>
#include <math.h>
using namespace std;

void MatrixMult1Stage1(int x,int y,int row)
//N+1 bits * N bits
{
    x--;
    y--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult";
    int fileint=x+1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    int n=0;
    for (int i=0; i<=x; i++) {
        outfile<<"    assign row"<<row<<"_mult1_stage1"<<"_and"<<n<<" = a"<<3*row-2<<"["<<i<<"] & b1[0];"<<endl;
        n++;
        outfile<<"    assign row"<<row<<"_mult1_stage1"<<"_and"<<n<<" = a"<<3*row-2<<"["<<i<<"] & b1[1];"<<endl;
        n++;
    }
    outfile<<"    assign row"<<row<<"_z1[0] = a"<<3*row-2<<"[0] & b1[0];"<<endl;
    // outfile<<"    assign row"<<row<<"_mult1_stage1_cout0 = row"<<row<<"_mult1_stage1_and0;"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            outfile<<"    assign row"<<row<<"_mult1_stage1_sum"<<i_add-1<<" = row"<<row<<"_mult1_stage1_and"<<2*i_add-1<<" ^ row"<<row<<"_mult1_stage1_and"<<2*i_add<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_stage1_cout"<<i_add-1<<" = row"<<row<<"_mult1_stage1_and"<<2*i_add-1<<" & row"<<row<<"_mult1_stage1_and"<<2*i_add<<";"<<endl;
            
        }
        else
        {
            outfile<<"    assign row"<<row<<"_z1[1] = row"<<row<<"_mult1_stage1_and1 ^ row"<<row<<"_mult1_stage1_and2;"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_stage1_cout"<<i_add-1<<" = row"<<row<<"_mult1_stage1_and"<<i_add<<" & row"<<row<<"_mult1_stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    outfile<<" /* This is the CSA multiplier first Stage.*/"<<endl;
}
void MatrixMult1Stage2(int x_1,int x_2,int row)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    for (int stage2=2; stage2<=x_2-1; stage2++) {
        for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
            
            if (fulladder==x_1-2) {
                // outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_cout"<<fulladder<<" = ( a"<<3*row-2<<"["<<fulladder<<"] & b1["<<stage2<<"] & row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (a"<<3*row-2<<"["<<fulladder+1<<"] & b1["<<stage2-1<<"]"<<" & a"<<3*row-2<<"["<<fulladder<<"] & b1["<<stage2<<"]) | (row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" & a"<<3*row-2<<"["<<fulladder+1<<"] & b1["<<stage2-1<<"]"<<");"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = a"<<3*row-2<<"["<<fulladder<<"] & b1["<<stage2<<"];"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = a"<<3*row-2<<"["<<fulladder+1<<"] & b1["<<stage2-1<<"];"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_or"<<fulladder<<" = row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_cout"<<fulladder<<" = row"<<row<<"_mult1_stage"<<stage2<<"_or"<<fulladder<<" | row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                
                
                //outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_sum"<<fulladder<<" = ( a"<<3*row-2<<"["<<fulladder<<"] & b1["<<stage2<<"] ) ^ (a"<<3*row-2<<"["<<fulladder+1<<"] & b1["<<stage2-1<<"])"<<" ^ row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_xor"<<fulladder<<" = row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ row"<<row<<"_mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_sum"<<fulladder<<" = row"<<row<<"_mult1_stage"<<stage2<<"_xor"<<fulladder<<" ^ row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                //outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_cout"<<fulladder<<" = ( a"<<3*row-2<<"["<<fulladder<<"] & b1["<<stage2<<"] & row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (row"<<row<<"_mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & a"<<3*row-2<<"["<<fulladder<<"] & b1["<<stage2<<"]) | (row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a"<<3*row-2<<"["<<fulladder<<"] & b1["<<stage2<<"];"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & row"<<row<<"_mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_or"<<fulladder<<" = row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_cout"<<fulladder<<" = row"<<row<<"_mult1_stage"<<stage2<<"_or"<<fulladder<<" | row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign row"<<row<<"_z1["<<stage2<<"] = ( a"<<3*row-2<<"["<<fulladder<<"] & b1["<<stage2<<"] ) ^ row"<<row<<"_mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_xor"<<fulladder<<" = row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_z1["<<stage2<<"] = row"<<row<<"_mult1_stage"<<stage2<<"_xor"<<fulladder<<" ^ row"<<row<<"_mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                //outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_cout"<<fulladder<<" = ( a"<<3*row-2<<"["<<fulladder<<"] & b1["<<stage2<<"] & row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (row"<<row<<"_mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & (a"<<3*row-2<<"["<<fulladder<<"] & b1["<<stage2<<"]) ) | (row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a"<<3*row-2<<"["<<fulladder<<"] & b1["<<stage2<<"];"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & row"<<row<<"_mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_or"<<fulladder<<" = row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_cout"<<fulladder<<" = row"<<row<<"_mult1_stage"<<stage2<<"_or"<<fulladder<<" | row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_sum"<<fulladder<<" = ( a"<<3*row-2<<"["<<fulladder<<"] & b1["<<stage2<<"] ) ^ row"<<row<<"_mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_xor"<<fulladder<<" = row"<<row<<"_mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ row"<<row<<"_mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult1_stage"<<stage2<<"_sum"<<fulladder<<" = row"<<row<<"_mult1_stage"<<stage2<<"_xor"<<fulladder<<" ^ row"<<row<<"_mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
}

//Last stage of CSA Multiplier
void MatrixMult1Stage3(int x_1,int x_2,int row)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"/*This is the LAST stage for CSA multiplier.*/"<<endl;
    for (int fulladder=0; fulladder<=x_1-1; fulladder++) {
        if(fulladder==0)
        {
            outfile<<"    assign row"<<row<<"_mult1_laststage_cout"<<fulladder<<" = row"<<row<<"_mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_z1["<<x_2+fulladder<<"] = row"<<row<<"_mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            //outfile<<"    assign row"<<row<<"_mult1_laststage_cout"<<fulladder<<" = (a"<<3*row-2<<"["<<x_1-1<<"] & b1["<<x_2-1<<"]"<<" & row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<") | (a"<<3*row-2<<"["<<x_1-1<<"] & b1["<<x_1-1<<"] & row"<<row<<"_mult1_laststage_cout"<<fulladder-1<<") | (row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult1_laststage_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign row"<<row<<"_z1["<<x_2+x_1-1<<"] = row"<<row<<"_mult1_laststage_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            //outfile<<"    assign row"<<row<<"_mult1_laststage_cout"<<fulladder<<" = ( a"<<3*row-2<<"["<<x_1-1<<"] & b1["<<x_2-1<<"] & row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<") | ( a"<<3*row-2<<"["<<x_1-1<<"] & b1["<<x_2-1<<"] & row"<<row<<"_mult1_laststage"<<"_cout"<<fulladder-1<<") | (row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult1_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_laststage_and"<<4*fulladder-3<<" = a"<<3*row-2<<"["<<x_1-1<<"] & b1["<<x_2-1<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_laststage_and"<<4*fulladder-2<<" = row"<<row<<"_mult1_laststage_and"<<4*fulladder-3<<" & row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_laststage_and"<<4*fulladder-1<<" = row"<<row<<"_mult1_laststage_and"<<4*fulladder-3<<" & row"<<row<<"_mult1_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_laststage_and"<<4*fulladder<<" = row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult1_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_laststage_or"<<fulladder<<" = row"<<row<<"_mult1_laststage_and"<<4*fulladder-2<<" | row"<<row<<"_mult1_laststage_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_laststage_cout"<<fulladder<<" = row"<<row<<"_mult1_laststage_or"<<fulladder<<" | row"<<row<<"_mult1_laststage_and"<<4*fulladder<<";"<<endl;
            //outfile<<"    assign row"<<row<<"_z1["<<x_2+fulladder<<"] = row"<<row<<"_mult1_laststage_cout"<<fulladder-1<<" ^ ( a"<<3*row-2<<"["<<x_1-1<<"] & b1["<<x_2-1<<"] ) ^ row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_laststage_xor"<<fulladder<<" = row"<<row<<"_mult1_laststage_cout"<<fulladder-1<<" ^ row"<<row<<"_mult1_laststage_and"<<4*fulladder-3<<";"<<endl;
            outfile<<"    assign row"<<row<<"_z1["<<x_2+fulladder<<"] = row"<<row<<"_mult1_laststage_xor"<<fulladder<<" ^ row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            
            //outfile<<"    assign row"<<row<<"_mult1_laststage_cout"<<fulladder<<" = (row"<<row<<"_mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<") | (row"<<row<<"_mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult1_laststage"<<"_cout"<<fulladder-1<<") | (row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult1_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_laststage_and"<<4*fulladder-3<<" = row"<<row<<"_mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_laststage_and"<<4*fulladder-2<<" = row"<<row<<"_mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult1_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_laststage_and"<<4*fulladder-1<<" = row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult1_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_laststage_or"<<fulladder<<" = row"<<row<<"_mult1_laststage_and"<<4*fulladder-3<<" | row"<<row<<"_mult1_laststage_and"<<4*fulladder-2<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_laststage_cout"<<fulladder<<" = row"<<row<<"_mult1_laststage_or"<<fulladder<<" | row"<<row<<"_mult1_laststage_and"<<4*fulladder-1<<";"<<endl;
            //outfile<<"    assign row"<<row<<"_z1["<<x_2+fulladder<<"] = row"<<row<<"_mult1_laststage_cout"<<fulladder-1<<" ^ row"<<row<<"_mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult1_laststage_xor"<<fulladder<<" = row"<<row<<"_mult1_laststage_cout"<<fulladder-1<<" ^ row"<<row<<"_mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_z1["<<x_2+fulladder<<"] = row"<<row<<"_mult1_laststage_xor"<<fulladder<<" ^ row"<<row<<"_mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            
            
        }
    }
    
}
void MatrixMult2Stage1(int x,int y,int row)
//N+1 bits * N bits
{
    x--;
    y--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult";
    int fileint=x+1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    int n=0;
    for (int i=0; i<=x; i++) {
        outfile<<"    assign row"<<row<<"_mult2_stage1"<<"_and"<<n<<" = a"<<3*row-1<<"["<<i<<"] & b2[0];"<<endl;
        n++;
        outfile<<"    assign row"<<row<<"_mult2_stage1"<<"_and"<<n<<" = a"<<3*row-1<<"["<<i<<"] & b2[1];"<<endl;
        n++;
    }
    outfile<<"    assign row"<<row<<"_z2[0] = a"<<3*row-1<<"[0] & b2[0];"<<endl;
    // outfile<<"    assign row"<<row<<"_mult2_stage1_cout0 = row"<<row<<"_mult2_stage1_and0;"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            outfile<<"    assign row"<<row<<"_mult2_stage1_sum"<<i_add-1<<" = row"<<row<<"_mult2_stage1_and"<<2*i_add-1<<" ^ row"<<row<<"_mult2_stage1_and"<<2*i_add<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_stage1_cout"<<i_add-1<<" = row"<<row<<"_mult2_stage1_and"<<2*i_add-1<<" & row"<<row<<"_mult2_stage1_and"<<2*i_add<<";"<<endl;
            
        }
        else
        {
            outfile<<"    assign row"<<row<<"_z2[1] = row"<<row<<"_mult2_stage1_and1 ^ row"<<row<<"_mult2_stage1_and2;"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_stage1_cout"<<i_add-1<<" = row"<<row<<"_mult2_stage1_and"<<i_add<<" & row"<<row<<"_mult2_stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    outfile<<" /* This is the CSA multiplier first Stage.*/"<<endl;
}
void MatrixMult2Stage2(int x_1,int x_2,int row)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);

    for (int stage2=2; stage2<=x_2-1; stage2++) {
        for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
            
            if (fulladder==x_1-2) {
                // outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_cout"<<fulladder<<" = ( a"<<3*row-1<<"["<<fulladder<<"] & b2["<<stage2<<"] & row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (a"<<3*row-1<<"["<<fulladder+1<<"] & b2["<<stage2-1<<"]"<<" & a"<<3*row-1<<"["<<fulladder<<"] & b2["<<stage2<<"]) | (row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" & a"<<3*row-1<<"["<<fulladder+1<<"] & b2["<<stage2-1<<"]"<<");"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = a"<<3*row-1<<"["<<fulladder<<"] & b2["<<stage2<<"];"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = a"<<3*row-1<<"["<<fulladder+1<<"] & b2["<<stage2-1<<"];"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_or"<<fulladder<<" = row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_cout"<<fulladder<<" = row"<<row<<"_mult2_stage"<<stage2<<"_or"<<fulladder<<" | row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                
                
                //outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_sum"<<fulladder<<" = ( a"<<3*row-1<<"["<<fulladder<<"] & b2["<<stage2<<"] ) ^ (a"<<3*row-1<<"["<<fulladder+1<<"] & b2["<<stage2-1<<"])"<<" ^ row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_xor"<<fulladder<<" = row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ row"<<row<<"_mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_sum"<<fulladder<<" = row"<<row<<"_mult2_stage"<<stage2<<"_xor"<<fulladder<<" ^ row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                //outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_cout"<<fulladder<<" = ( a"<<3*row-1<<"["<<fulladder<<"] & b2["<<stage2<<"] & row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (row"<<row<<"_mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & a"<<3*row-1<<"["<<fulladder<<"] & b2["<<stage2<<"]) | (row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a"<<3*row-1<<"["<<fulladder<<"] & b2["<<stage2<<"];"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & row"<<row<<"_mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_or"<<fulladder<<" = row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_cout"<<fulladder<<" = row"<<row<<"_mult2_stage"<<stage2<<"_or"<<fulladder<<" | row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign row"<<row<<"_z2["<<stage2<<"] = ( a"<<3*row-1<<"["<<fulladder<<"] & b2["<<stage2<<"] ) ^ row"<<row<<"_mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_xor"<<fulladder<<" = row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_z2["<<stage2<<"] = row"<<row<<"_mult2_stage"<<stage2<<"_xor"<<fulladder<<" ^ row"<<row<<"_mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                //outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_cout"<<fulladder<<" = ( a"<<3*row-1<<"["<<fulladder<<"] & b2["<<stage2<<"] & row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (row"<<row<<"_mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & (a"<<3*row-1<<"["<<fulladder<<"] & b2["<<stage2<<"]) ) | (row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a"<<3*row-1<<"["<<fulladder<<"] & b2["<<stage2<<"];"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & row"<<row<<"_mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_or"<<fulladder<<" = row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_cout"<<fulladder<<" = row"<<row<<"_mult2_stage"<<stage2<<"_or"<<fulladder<<" | row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_sum"<<fulladder<<" = ( a"<<3*row-1<<"["<<fulladder<<"] & b2["<<stage2<<"] ) ^ row"<<row<<"_mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_xor"<<fulladder<<" = row"<<row<<"_mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ row"<<row<<"_mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult2_stage"<<stage2<<"_sum"<<fulladder<<" = row"<<row<<"_mult2_stage"<<stage2<<"_xor"<<fulladder<<" ^ row"<<row<<"_mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
}

//Last stage of CSA Multiplier
void MatrixMult2Stage3(int x_1,int x_2,int row)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"/*This is the LAST stage for CSA multiplier.*/"<<endl;
    for (int fulladder=0; fulladder<=x_1-1; fulladder++) {
        if(fulladder==0)
        {
            outfile<<"    assign row"<<row<<"_mult2_laststage_cout"<<fulladder<<" = row"<<row<<"_mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_z2["<<x_2+fulladder<<"] = row"<<row<<"_mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            //outfile<<"    assign row"<<row<<"_mult2_laststage_cout"<<fulladder<<" = (a"<<3*row-1<<"["<<x_1-1<<"] & b2["<<x_2-1<<"]"<<" & row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<") | (a"<<3*row-1<<"["<<x_1-1<<"] & b2["<<x_1-1<<"] & row"<<row<<"_mult2_laststage_cout"<<fulladder-1<<") | (row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult2_laststage_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign row"<<row<<"_z2["<<x_2+x_1-1<<"] = row"<<row<<"_mult2_laststage_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            //outfile<<"    assign row"<<row<<"_mult2_laststage_cout"<<fulladder<<" = ( a"<<3*row-1<<"["<<x_1-1<<"] & b2["<<x_2-1<<"] & row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<") | ( a"<<3*row-1<<"["<<x_1-1<<"] & b2["<<x_2-1<<"] & row"<<row<<"_mult2_laststage"<<"_cout"<<fulladder-1<<") | (row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult2_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_laststage_and"<<4*fulladder-3<<" = a"<<3*row-1<<"["<<x_1-1<<"] & b2["<<x_2-1<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_laststage_and"<<4*fulladder-2<<" = row"<<row<<"_mult2_laststage_and"<<4*fulladder-3<<" & row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_laststage_and"<<4*fulladder-1<<" = row"<<row<<"_mult2_laststage_and"<<4*fulladder-3<<" & row"<<row<<"_mult2_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_laststage_and"<<4*fulladder<<" = row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult2_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_laststage_or"<<fulladder<<" = row"<<row<<"_mult2_laststage_and"<<4*fulladder-2<<" | row"<<row<<"_mult2_laststage_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_laststage_cout"<<fulladder<<" = row"<<row<<"_mult2_laststage_or"<<fulladder<<" | row"<<row<<"_mult2_laststage_and"<<4*fulladder<<";"<<endl;
            //outfile<<"    assign row"<<row<<"_z2["<<x_2+fulladder<<"] = row"<<row<<"_mult2_laststage_cout"<<fulladder-1<<" ^ ( a"<<3*row-1<<"["<<x_1-1<<"] & b2["<<x_2-1<<"] ) ^ row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_laststage_xor"<<fulladder<<" = row"<<row<<"_mult2_laststage_cout"<<fulladder-1<<" ^ row"<<row<<"_mult2_laststage_and"<<4*fulladder-3<<";"<<endl;
            outfile<<"    assign row"<<row<<"_z2["<<x_2+fulladder<<"] = row"<<row<<"_mult2_laststage_xor"<<fulladder<<" ^ row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            
            //outfile<<"    assign row"<<row<<"_mult2_laststage_cout"<<fulladder<<" = (row"<<row<<"_mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<") | (row"<<row<<"_mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult2_laststage"<<"_cout"<<fulladder-1<<") | (row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult2_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_laststage_and"<<4*fulladder-3<<" = row"<<row<<"_mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_laststage_and"<<4*fulladder-2<<" = row"<<row<<"_mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult2_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_laststage_and"<<4*fulladder-1<<" = row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult2_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_laststage_or"<<fulladder<<" = row"<<row<<"_mult2_laststage_and"<<4*fulladder-3<<" | row"<<row<<"_mult2_laststage_and"<<4*fulladder-2<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_laststage_cout"<<fulladder<<" = row"<<row<<"_mult2_laststage_or"<<fulladder<<" | row"<<row<<"_mult2_laststage_and"<<4*fulladder-1<<";"<<endl;
            //outfile<<"    assign row"<<row<<"_z2["<<x_2+fulladder<<"] = row"<<row<<"_mult2_laststage_cout"<<fulladder-1<<" ^ row"<<row<<"_mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult2_laststage_xor"<<fulladder<<" = row"<<row<<"_mult2_laststage_cout"<<fulladder-1<<" ^ row"<<row<<"_mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_z2["<<x_2+fulladder<<"] = row"<<row<<"_mult2_laststage_xor"<<fulladder<<" ^ row"<<row<<"_mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            
            
        }
    }
    
}

void MatrixMult3Stage1(int x,int y,int row)
//N+1 bits * N bits
{
    x--;
    y--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult";
    int fileint=x+1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);

    //outfile<<"Multiplier begin."<<endl;
    int n=0;
    for (int i=0; i<=x; i++) {
        outfile<<"    assign row"<<row<<"_mult3stage1"<<"_and"<<n<<" = a"<<3*row<<"["<<i<<"] & b3[0];"<<endl;
        n++;
        outfile<<"    assign row"<<row<<"_mult3stage1"<<"_and"<<n<<" = a"<<3*row<<"["<<i<<"] & b3[1];"<<endl;
        n++;
    }
    outfile<<"    assign row"<<row<<"_z3[0] = a"<<3*row<<"[0] & b3[0];"<<endl;
    // outfile<<"    assign row"<<row<<"_mult3stage1_cout0 = row"<<row<<"_mult3stage1_and0;"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            outfile<<"    assign row"<<row<<"_mult3stage1_sum"<<i_add-1<<" = row"<<row<<"_mult3stage1_and"<<2*i_add-1<<" ^ row"<<row<<"_mult3stage1_and"<<2*i_add<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult3stage1_cout"<<i_add-1<<" = row"<<row<<"_mult3stage1_and"<<2*i_add-1<<" & row"<<row<<"_mult3stage1_and"<<2*i_add<<";"<<endl;
            
        }
        else
        {
            outfile<<"    assign row"<<row<<"_z3[1] = row"<<row<<"_mult3stage1_and1 ^ row"<<row<<"_mult3stage1_and2;"<<endl;
            outfile<<"    assign row"<<row<<"_mult3stage1_cout"<<i_add-1<<" = row"<<row<<"_mult3stage1_and"<<i_add<<" & row"<<row<<"_mult3stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    outfile<<" /* This is the CSA multiplier first Stage.*/"<<endl;
}
void MatrixMult3Stage2(int x_1,int x_2,int row)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);

    for (int stage2=2; stage2<=x_2-1; stage2++) {
        for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
            
            if (fulladder==x_1-2) {
                // outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_cout"<<fulladder<<" = ( a"<<3*row<<"["<<fulladder<<"] & b3["<<stage2<<"] & row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (a"<<3*row<<"["<<fulladder+1<<"] & b3["<<stage2-1<<"]"<<" & a"<<3*row<<"["<<fulladder<<"] & b3["<<stage2<<"]) | (row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<" & a"<<3*row<<"["<<fulladder+1<<"] & b3["<<stage2-1<<"]"<<");"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = a"<<3*row<<"["<<fulladder<<"] & b3["<<stage2<<"];"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = a"<<3*row<<"["<<fulladder+1<<"] & b3["<<stage2-1<<"];"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_or"<<fulladder<<" = row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_cout"<<fulladder<<" = row"<<row<<"_mult3stage"<<stage2<<"_or"<<fulladder<<" | row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                
                
                //outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_sum"<<fulladder<<" = ( a"<<3*row<<"["<<fulladder<<"] & b3["<<stage2<<"] ) ^ (a"<<3*row<<"["<<fulladder+1<<"] & b3["<<stage2-1<<"])"<<" ^ row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_xor"<<fulladder<<" = row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ row"<<row<<"_mult3stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_sum"<<fulladder<<" = row"<<row<<"_mult3stage"<<stage2<<"_xor"<<fulladder<<" ^ row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                //outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_cout"<<fulladder<<" = ( a"<<3*row<<"["<<fulladder<<"] & b3["<<stage2<<"] & row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (row"<<row<<"_mult3stage"<<stage2-1<<"_sum"<<fulladder+1<<" & a"<<3*row<<"["<<fulladder<<"] & b3["<<stage2<<"]) | (row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult3stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a"<<3*row<<"["<<fulladder<<"] & b3["<<stage2<<"];"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & row"<<row<<"_mult3stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult3stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_or"<<fulladder<<" = row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_cout"<<fulladder<<" = row"<<row<<"_mult3stage"<<stage2<<"_or"<<fulladder<<" | row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign row"<<row<<"_z3["<<stage2<<"] = ( a"<<3*row<<"["<<fulladder<<"] & b3["<<stage2<<"] ) ^ row"<<row<<"_mult3stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_xor"<<fulladder<<" = row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_z3["<<stage2<<"] = row"<<row<<"_mult3stage"<<stage2<<"_xor"<<fulladder<<" ^ row"<<row<<"_mult3stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                //outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_cout"<<fulladder<<" = ( a"<<3*row<<"["<<fulladder<<"] & b3["<<stage2<<"] & row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (row"<<row<<"_mult3stage"<<stage2-1<<"_sum"<<fulladder+1<<" & (a"<<3*row<<"["<<fulladder<<"] & b3["<<stage2<<"]) ) | (row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult3stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a"<<3*row<<"["<<fulladder<<"] & b3["<<stage2<<"];"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & row"<<row<<"_mult3stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult3stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_or"<<fulladder<<" = row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_cout"<<fulladder<<" = row"<<row<<"_mult3stage"<<stage2<<"_or"<<fulladder<<" | row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_sum"<<fulladder<<" = ( a"<<3*row<<"["<<fulladder<<"] & b3["<<stage2<<"] ) ^ row"<<row<<"_mult3stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_xor"<<fulladder<<" = row"<<row<<"_mult3stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ row"<<row<<"_mult3stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign row"<<row<<"_mult3stage"<<stage2<<"_sum"<<fulladder<<" = row"<<row<<"_mult3stage"<<stage2<<"_xor"<<fulladder<<" ^ row"<<row<<"_mult3stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
}

//Last stage of CSA Multiplier
void MatrixMult3Stage3(int x_1,int x_2,int row)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);

    outfile<<"/*This is the LAST stage for CSA multiplier.*/"<<endl;
    for (int fulladder=0; fulladder<=x_1-1; fulladder++) {
        if(fulladder==0)
        {
            outfile<<"    assign row"<<row<<"_mult3laststage_cout"<<fulladder<<" = row"<<row<<"_mult3stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_z3["<<x_2+fulladder<<"] = row"<<row<<"_mult3stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            //outfile<<"    assign row"<<row<<"_mult3laststage_cout"<<fulladder<<" = (a"<<3*row<<"["<<x_1-1<<"] & b3["<<x_2-1<<"]"<<" & row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<") | (a"<<3*row<<"["<<x_1-1<<"] & b3["<<x_1-1<<"] & row"<<row<<"_mult3laststage_cout"<<fulladder-1<<") | (row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult3laststage_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign row"<<row<<"_z3["<<x_2+x_1-1<<"] = row"<<row<<"_mult3laststage_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            //outfile<<"    assign row"<<row<<"_mult3laststage_cout"<<fulladder<<" = ( a"<<3*row<<"["<<x_1-1<<"] & b3["<<x_2-1<<"] & row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<") | ( a"<<3*row<<"["<<x_1-1<<"] & b3["<<x_2-1<<"] & row"<<row<<"_mult3laststage"<<"_cout"<<fulladder-1<<") | (row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult3laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign row"<<row<<"_mult3laststage_and"<<4*fulladder-3<<" = a"<<3*row<<"["<<x_1-1<<"] & b3["<<x_2-1<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_mult3laststage_and"<<4*fulladder-2<<" = row"<<row<<"_mult3laststage_and"<<4*fulladder-3<<" & row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult3laststage_and"<<4*fulladder-1<<" = row"<<row<<"_mult3laststage_and"<<4*fulladder-3<<" & row"<<row<<"_mult3laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult3laststage_and"<<4*fulladder<<" = row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult3laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult3laststage_or"<<fulladder<<" = row"<<row<<"_mult3laststage_and"<<4*fulladder-2<<" | row"<<row<<"_mult3laststage_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult3laststage_cout"<<fulladder<<" = row"<<row<<"_mult3laststage_or"<<fulladder<<" | row"<<row<<"_mult3laststage_and"<<4*fulladder<<";"<<endl;
            //outfile<<"    assign row"<<row<<"_z3["<<x_2+fulladder<<"] = row"<<row<<"_mult3laststage_cout"<<fulladder-1<<" ^ ( a"<<3*row<<"["<<x_1-1<<"] & b3["<<x_2-1<<"] ) ^ row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult3laststage_xor"<<fulladder<<" = row"<<row<<"_mult3laststage_cout"<<fulladder-1<<" ^ row"<<row<<"_mult3laststage_and"<<4*fulladder-3<<";"<<endl;
            outfile<<"    assign row"<<row<<"_z3["<<x_2+fulladder<<"] = row"<<row<<"_mult3laststage_xor"<<fulladder<<" ^ row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            
            //outfile<<"    assign row"<<row<<"_mult3laststage_cout"<<fulladder<<" = (row"<<row<<"_mult3stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<") | (row"<<row<<"_mult3stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult3laststage"<<"_cout"<<fulladder-1<<") | (row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult3laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign row"<<row<<"_mult3laststage_and"<<4*fulladder-3<<" = row"<<row<<"_mult3stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult3laststage_and"<<4*fulladder-2<<" = row"<<row<<"_mult3stage"<<x_2-1<<"_sum"<<fulladder+1<<" & row"<<row<<"_mult3laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult3laststage_and"<<4*fulladder-1<<" = row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<" & row"<<row<<"_mult3laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult3laststage_or"<<fulladder<<" = row"<<row<<"_mult3laststage_and"<<4*fulladder-3<<" | row"<<row<<"_mult3laststage_and"<<4*fulladder-2<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult3laststage_cout"<<fulladder<<" = row"<<row<<"_mult3laststage_or"<<fulladder<<" | row"<<row<<"_mult3laststage_and"<<4*fulladder-1<<";"<<endl;
            //outfile<<"    assign row"<<row<<"_z3["<<x_2+fulladder<<"] = row"<<row<<"_mult3laststage_cout"<<fulladder-1<<" ^ row"<<row<<"_mult3stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign row"<<row<<"_mult3laststage_xor"<<fulladder<<" = row"<<row<<"_mult3laststage_cout"<<fulladder-1<<" ^ row"<<row<<"_mult3stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_z3["<<x_2+fulladder<<"] = row"<<row<<"_mult3laststage_xor"<<fulladder<<" ^ row"<<row<<"_mult3stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            
            
        }
    }
    
}

void mult1(int x,int row)
{
    MatrixMult1Stage1(x, x,row);
    MatrixMult1Stage2(x, x,row);
    MatrixMult1Stage3(x, x,row);
}
void mult2(int x,int row)
{
    MatrixMult2Stage1(x, x,row);
    MatrixMult2Stage2(x, x,row);
    MatrixMult2Stage3(x, x,row);
}
void mult3(int x,int row)
{
    MatrixMult3Stage1(x, x,row);
    MatrixMult3Stage2(x, x,row);
    MatrixMult3Stage3(x, x,row);
}

void gateleveladder1(int x,int row)
{
    x--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult";
    int fileint=(x+1)/2;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);

    outfile<<"//Adder begin"<<endl;
    outfile<<"    assign row"<<row<<"_adder1_and0 = row"<<row<<"_z1[0] & row"<<row<<"_z2[0] ;"<<endl;
    outfile<<"    assign row"<<row<<"_adder1_add_cout[0] = row"<<row<<"_adder1_and0;"<<endl;
    outfile<<"    assign row"<<row<<"_adder1_add_sum[0] = row"<<row<<"_z1[0] ^ row"<<row<<"_z2[0];"<<endl;
    outfile<<"    assign row"<<row<<"_adder1_and0 = row"<<row<<"_z1[0] & row"<<row<<"_z2[0] ;"<<endl;
    outfile<<"    assign row"<<row<<"_adder1_add_cout[0] = row"<<row<<"_adder1_and0;"<<endl;
    outfile<<"    assign row"<<row<<"_adder1_add_sum[0] = row"<<row<<"_z1[0] ^ row"<<row<<"_z2[0];"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            outfile<<"    assign row"<<row<<"_adder1_and"<<3*i-2<<" = row"<<row<<"_adder1_add_cout["<<i-1<<"] & row"<<row<<"_z1["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder1_and"<<3*i-1<<" = row"<<row<<"_adder1_add_cout["<<i-1<<"] & row"<<row<<"_z2["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder1_and"<<3*i<<" = row"<<row<<"_z1["<<i<<"] & row"<<row<<"_z2["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder1_or"<<i<<" = row"<<row<<"_adder1_and"<<3*i-2<<" | "<<"row"<<row<<"_adder1_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_adder1_add_cout["<<i<<"] = row"<<row<<"_adder1_or"<<i<<" | ""row"<<row<<"_adder1_and"<<3*i<<";"<<endl;
            
            outfile<<"    assign row"<<row<<"_adder1_xor"<<i<<" = row"<<row<<"_z1["<<i<<"] ^ row"<<row<<"_z2["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder1_add_sum["<<i<<"] = row"<<row<<"_adder1_xor"<<i<<" ^ "<<"row"<<row<<"_adder1_add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            outfile<<"    assign row"<<row<<"_adder1_and"<<3*i-2<<" = row"<<row<<"_adder1_add_cout["<<i-1<<"] & row"<<row<<"_z1["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder1_and"<<3*i-1<<" = row"<<row<<"_adder1_add_cout["<<i-1<<"] & row"<<row<<"_z2["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder1_and"<<3*i<<" = row"<<row<<"_z1["<<i<<"] & row"<<row<<"_z2["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder1_or"<<i<<" = row"<<row<<"_adder1_and"<<3*i-2<<" | "<<"row"<<row<<"_adder1_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_adder1_add_sum["<<i+1<<"] = row"<<row<<"_adder1_or"<<i<<" | row"<<row<<"_adder1_and"<<3*i<<";"<<endl;
            outfile<<"    assign row"<<row<<"_adder1_xor"<<i<<" = row"<<row<<"_z1["<<i<<"] ^ row"<<row<<"_z2["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder1_add_sum["<<i<<"] = row"<<row<<"_adder1_xor"<<i<<" ^ "<<"row"<<row<<"_adder1_add_cout["<<i-1<<"];"<<endl;
        }
    }
    
}
void gateleveladder2(int x,int row)
{
    x--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult";
    int fileint=x/2;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);

    outfile<<"    assign row"<<row<<"_adder2_and0 = row"<<row<<"_adder1_add_sum[0] & row"<<row<<"_z3[0] ;"<<endl;
    outfile<<"    assign row"<<row<<"_adder2_add_cout[0] = row"<<row<<"_adder2_and0;"<<endl;
    outfile<<"    assign p"<<row<<"[0] = row"<<row<<"_adder1_add_sum[0] ^ row"<<row<<"_z3[0];"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            outfile<<"    assign row"<<row<<"_adder2_and"<<3*i-2<<" = row"<<row<<"_adder2_add_cout["<<i-1<<"] & row"<<row<<"_adder1_add_sum["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder2_and"<<3*i-1<<" = row"<<row<<"_adder2_add_cout["<<i-1<<"] & row"<<row<<"_z3["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder2_and"<<3*i<<" = row"<<row<<"_adder1_add_sum["<<i<<"] & row"<<row<<"_z3["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder2_or"<<i<<" = row"<<row<<"_adder2_and"<<3*i-2<<" | "<<"row"<<row<<"_adder2_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign row"<<row<<"_adder2_add_cout["<<i<<"] = row"<<row<<"_adder2_or"<<i<<" | ""row"<<row<<"_adder2_and"<<3*i<<";"<<endl;
            
            outfile<<"    assign row"<<row<<"_adder2_xor"<<i<<" = row"<<row<<"_adder1_add_sum["<<i<<"] ^ row"<<row<<"_z3["<<i<<"];"<<endl;
            outfile<<"    assign p"<<row<<"["<<i<<"] = row"<<row<<"_adder2_xor"<<i<<" ^ "<<"row"<<row<<"_adder2_add_cout["<<i-1<<"];"<<endl;
        }
        else if (i==x)
        {
            outfile<<"    assign row"<<row<<"_adder2_and"<<3*i-2<<" = row"<<row<<"_adder2_add_cout["<<i-1<<"] & row"<<row<<"_adder1_add_sum["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder2_and"<<3*i-1<<" = row"<<row<<"_adder2_add_cout["<<i-1<<"] & 1'b0;"<<endl;
            outfile<<"    assign row"<<row<<"_adder2_and"<<3*i<<" = row"<<row<<"_adder1_add_sum["<<i<<"] & 1'b0;"<<endl;
            outfile<<"    assign row"<<row<<"_adder2_or"<<i<<" = row"<<row<<"_adder2_and"<<3*i-2<<" | "<<"row"<<row<<"_adder2_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign p"<<row<<"["<<i+1<<"] = row"<<row<<"_adder2_or"<<i<<" | row"<<row<<"_adder2_and"<<3*i<<";"<<endl;
            outfile<<"    assign row"<<row<<"_adder2_xor"<<i<<" = row"<<row<<"_adder1_add_sum["<<i<<"] ^ 1'b0;"<<endl;
            outfile<<"    assign p"<<row<<"["<<i<<"] = row"<<row<<"_adder2_xor"<<i<<" ^ "<<"row"<<row<<"_adder2_add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            outfile<<"    assign row"<<row<<"_adder2_and"<<3*i-2<<" = row"<<row<<"_adder2_add_cout["<<i-1<<"] & row"<<row<<"_adder1_add_sum["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder2_and"<<3*i-1<<" = row"<<row<<"_adder2_add_cout["<<i-1<<"] & row"<<row<<"_z3["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder2_and"<<3*i<<" = row"<<row<<"_adder1_add_sum["<<i<<"] & row"<<row<<"_z3["<<i<<"];"<<endl;
            outfile<<"    assign row"<<row<<"_adder2_or"<<i<<" = row"<<row<<"_adder2_and"<<3*i-2<<" | "<<"row"<<row<<"_adder2_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign p"<<row<<"["<<i+1<<"] = row"<<row<<"_adder2_or"<<i<<" | row"<<row<<"_adder2_and"<<3*i<<";"<<endl;
            outfile<<"    assign row"<<row<<"_adder2_xor"<<i<<" = row"<<row<<"_adder1_add_sum["<<i<<"] ^ row"<<row<<"_z3["<<i<<"];"<<endl;
            outfile<<"    assign p"<<row<<"["<<i<<"] = row"<<row<<"_adder2_xor"<<i<<" ^ "<<"row"<<row<<"_adder2_add_cout["<<i-1<<"];"<<endl;
        }
    }
}

void Matrix3X3Multiply(int x,int row)
{
    for (int row=1; row<=3; row++) {
        
        
        mult1(x,row);
        mult2(x,row);
        mult3(x,row);
        gateleveladder1(2*x,row);
        gateleveladder2(2*x+1,row);
        
    }
}


void lastendmoduleverilog(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"endmodule"<<endl;

}
void BenchGenMatrix::MatrixMultiply(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename);

    outfile<<"/*This Verilog is generated by BechGen software.*/\n"
    "/*Designed by University of Massachusetts, Amherst, VLSI CAD LAB, Cunxi Yu*/\n"
    "/*/  Copyright (c) 2014 Cunxi Yu. All rights reserved. */ \n"
    "/*Contact: ycunxi@umass.edu */"<<endl;
    outfile<<"module MatrixMultiply(a1,a2,a3,a4,a5,a6,a7,a8,a9,b1,b2,b3,p1,p2,p3);"<<endl;
    outfile<<"   input ["<<x-1<<":0] a1,a2,a3,a4,a5,a6,a7,a8,a9,b1,b2,b3;"<<endl;
    outfile<<"   output ["<<2*x+1<<":0] p1,p2,p3;"<<endl;
    outfile<<"   wire ["<<2*x+1<<":0] p1,p2,p3;"<<endl;
    outfile<<"   wire ["<<2*x-1<<":0] row1_z1,row1_z2,row1_z3,row2_z1,row2_z2,row2_z3,row3_z1,row3_z2,row3_z3;"<<endl;
    outfile<<"   wire ["<<2*x<<":0] row1_adder1_add_sum,row2_adder1_add_sum,row3_adder1_add_sum;"<<endl;
    outfile<<"   wire ["<<2*x-1<<":0] row1_adder2_add_cout,row2_adder2_add_cout,row3_adder2_add_cout;"<<endl;
    outfile<<"   wire ["<<2*x-2<<":0] row1_adder1_add_cout,row2_adder1_add_cout,row3_adder1_add_cout;"<<endl;
    Matrix3X3Multiply(x,3);
    lastendmoduleverilog(x);
  
    
}

///Matrix  before this line. The rest is multiplier_3.


void SpecgatelevelAdder1(int x)
{
    
    x--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_";
    int fileint=(x+1)/2;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"//Adder begin"<<endl;
    outfile<<"    assign adder1_and0 = z1[0] & z2[0] ;"<<endl;
    outfile<<"    assign adder1_add_cout[0] = adder1_and0;"<<endl;
    outfile<<"    assign adder1_add_sum[0] = z1[0] ^ z2[0];"<<endl;
    outfile<<"    assign adder1_and0 = z1[0] & z2[0] ;"<<endl;
    outfile<<"    assign adder1_add_cout[0] = adder1_and0;"<<endl;
    outfile<<"    assign adder1_add_sum[0] = z1[0] ^ z2[0];"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            outfile<<"    assign adder1_and"<<3*i-2<<" = adder1_add_cout["<<i-1<<"] & z1["<<i<<"];"<<endl;
            outfile<<"    assign adder1_and"<<3*i-1<<" = adder1_add_cout["<<i-1<<"] & z2["<<i<<"];"<<endl;
            outfile<<"    assign adder1_and"<<3*i<<" = z1["<<i<<"] & z2["<<i<<"];"<<endl;
            outfile<<"    assign adder1_or"<<i<<" = adder1_and"<<3*i-2<<" | "<<"adder1_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder1_add_cout["<<i<<"] = adder1_or"<<i<<" | ""adder1_and"<<3*i<<";"<<endl;
            
            outfile<<"    assign adder1_xor"<<i<<" = z1["<<i<<"] ^ z2["<<i<<"];"<<endl;
            outfile<<"    assign adder1_add_sum["<<i<<"] = adder1_xor"<<i<<" ^ "<<"adder1_add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            outfile<<"    assign adder1_and"<<3*i-2<<" = adder1_add_cout["<<i-1<<"] & z1["<<i<<"];"<<endl;
            outfile<<"    assign adder1_and"<<3*i-1<<" = adder1_add_cout["<<i-1<<"] & z2["<<i<<"];"<<endl;
            outfile<<"    assign adder1_and"<<3*i<<" = z1["<<i<<"] & z2["<<i<<"];"<<endl;
            outfile<<"    assign adder1_or"<<i<<" = adder1_and"<<3*i-2<<" | "<<"adder1_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder1_add_sum["<<i+1<<"] = adder1_or"<<i<<" | adder1_and"<<3*i<<";"<<endl;
            outfile<<"    assign adder1_xor"<<i<<" = z1["<<i<<"] ^ z2["<<i<<"];"<<endl;
            outfile<<"    assign adder1_add_sum["<<i<<"] = adder1_xor"<<i<<" ^ "<<"adder1_add_cout["<<i-1<<"];"<<endl;
        }
    }
    
}
void SpecgatelevelAdder2(int x)
{
    x--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_";
    int fileint=x/2;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"    assign adder2_and0 = adder1_add_sum[0] & z3[0] ;"<<endl;
    outfile<<"    assign adder2_add_cout[0] = adder2_and0;"<<endl;
    outfile<<"    assign p[0] = adder1_add_sum[0] ^ z3[0];"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            outfile<<"    assign adder2_and"<<3*i-2<<" = adder2_add_cout["<<i-1<<"] & adder1_add_sum["<<i<<"];"<<endl;
            outfile<<"    assign adder2_and"<<3*i-1<<" = adder2_add_cout["<<i-1<<"] & z3["<<i<<"];"<<endl;
            outfile<<"    assign adder2_and"<<3*i<<" = adder1_add_sum["<<i<<"] & z3["<<i<<"];"<<endl;
            outfile<<"    assign adder2_or"<<i<<" = adder2_and"<<3*i-2<<" | "<<"adder2_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder2_add_cout["<<i<<"] = adder2_or"<<i<<" | ""adder2_and"<<3*i<<";"<<endl;
            
            outfile<<"    assign adder2_xor"<<i<<" = adder1_add_sum["<<i<<"] ^ z3["<<i<<"];"<<endl;
            outfile<<"    assign p["<<i<<"] = adder2_xor"<<i<<" ^ "<<"adder2_add_cout["<<i-1<<"];"<<endl;
        }
        else if (i==x)
        {
            outfile<<"    assign adder2_and"<<3*i-2<<" = adder2_add_cout["<<i-1<<"] & adder1_add_sum["<<i<<"];"<<endl;
            outfile<<"    assign adder2_and"<<3*i-1<<" = adder2_add_cout["<<i-1<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder2_and"<<3*i<<" = adder1_add_sum["<<i<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder2_or"<<i<<" = adder2_and"<<3*i-2<<" | "<<"adder2_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign p["<<i+1<<"] = adder2_or"<<i<<" | adder2_and"<<3*i<<";"<<endl;
            outfile<<"    assign adder2_xor"<<i<<" = adder1_add_sum["<<i<<"] ^ 1'b0;"<<endl;
            outfile<<"    assign p["<<i<<"] = adder2_xor"<<i<<" ^ "<<"adder2_add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            outfile<<"    assign adder2_and"<<3*i-2<<" = adder2_add_cout["<<i-1<<"] & adder1_add_sum["<<i<<"];"<<endl;
            outfile<<"    assign adder2_and"<<3*i-1<<" = adder2_add_cout["<<i-1<<"] & z3["<<i<<"];"<<endl;
            outfile<<"    assign adder2_and"<<3*i<<" = adder1_add_sum["<<i<<"] & z3["<<i<<"];"<<endl;
            outfile<<"    assign adder2_or"<<i<<" = adder2_and"<<3*i-2<<" | "<<"adder2_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign p["<<i+1<<"] = adder2_or"<<i<<" | adder2_and"<<3*i<<";"<<endl;
            outfile<<"    assign adder2_xor"<<i<<" = adder1_add_sum["<<i<<"] ^ z3["<<i<<"];"<<endl;
            outfile<<"    assign p["<<i<<"] = adder2_xor"<<i<<" ^ "<<"adder2_add_cout["<<i-1<<"];"<<endl;
        }
    }
    outfile<<"endmodule"<<endl;
}

void SpecmultiplierCSAstage1(int x,int y)
//N+1 bits * N bits
{
    x--;
    y--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_";
    int fileint=x+1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);

    int n=0;
    for (int i=0; i<=x; i++) {
        outfile<<"    assign mult1_stage1"<<"_and"<<n<<" = a1["<<i<<"] & b1[0];"<<endl;
        n++;
        outfile<<"    assign mult1_stage1"<<"_and"<<n<<" = a1["<<i<<"] & b1[1];"<<endl;
        n++;
    }
    outfile<<"    assign z1[0] = a1[0] & b1[0];"<<endl;
    // outfile<<"    assign mult1_stage1_cout0 = mult1_stage1_and0;"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            outfile<<"    assign mult1_stage1_sum"<<i_add-1<<" = mult1_stage1_and"<<2*i_add-1<<" ^ mult1_stage1_and"<<2*i_add<<";"<<endl;
            outfile<<"    assign mult1_stage1_cout"<<i_add-1<<" = mult1_stage1_and"<<2*i_add-1<<" & mult1_stage1_and"<<2*i_add<<";"<<endl;
            
        }
        else
        {
            outfile<<"    assign z1[1] = mult1_stage1_and1 ^ mult1_stage1_and2;"<<endl;
            outfile<<"    assign mult1_stage1_cout"<<i_add-1<<" = mult1_stage1_and"<<i_add<<" & mult1_stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    outfile<<" /* This is the CSA multiplier first Stage.*/"<<endl;
}
void SpecmultiplierCSAstage2(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    for (int stage2=2; stage2<=x_2-1; stage2++) {
        for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
            
            if (fulladder==x_1-2) {
                // outfile<<"    assign mult1_stage"<<stage2<<"_cout"<<fulladder<<" = ( a1["<<fulladder<<"] & b1["<<stage2<<"] & mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (a1["<<fulladder+1<<"] & b1["<<stage2-1<<"]"<<" & a1["<<fulladder<<"] & b1["<<stage2<<"]) | (mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" & a1["<<fulladder+1<<"] & b1["<<stage2-1<<"]"<<");"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = a1["<<fulladder<<"] & b1["<<stage2<<"];"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = a1["<<fulladder+1<<"] & b1["<<stage2-1<<"];"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_or"<<fulladder<<" = mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_cout"<<fulladder<<" = mult1_stage"<<stage2<<"_or"<<fulladder<<" | mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                
                
                //outfile<<"    assign mult1_stage"<<stage2<<"_sum"<<fulladder<<" = ( a1["<<fulladder<<"] & b1["<<stage2<<"] ) ^ (a1["<<fulladder+1<<"] & b1["<<stage2-1<<"])"<<" ^ mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_xor"<<fulladder<<" = mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ mult1_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_sum"<<fulladder<<" = mult1_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                //outfile<<"    assign mult1_stage"<<stage2<<"_cout"<<fulladder<<" = ( a1["<<fulladder<<"] & b1["<<stage2<<"] & mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & a1["<<fulladder<<"] & b1["<<stage2<<"]) | (mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a1["<<fulladder<<"] & b1["<<stage2<<"];"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_or"<<fulladder<<" = mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_cout"<<fulladder<<" = mult1_stage"<<stage2<<"_or"<<fulladder<<" | mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign z1["<<stage2<<"] = ( a1["<<fulladder<<"] & b1["<<stage2<<"] ) ^ mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_xor"<<fulladder<<" = mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign z1["<<stage2<<"] = mult1_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                //outfile<<"    assign mult1_stage"<<stage2<<"_cout"<<fulladder<<" = ( a1["<<fulladder<<"] & b1["<<stage2<<"] & mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & (a1["<<fulladder<<"] & b1["<<stage2<<"]) ) | (mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a1["<<fulladder<<"] & b1["<<stage2<<"];"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult1_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_or"<<fulladder<<" = mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_cout"<<fulladder<<" = mult1_stage"<<stage2<<"_or"<<fulladder<<" | mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign mult1_stage"<<stage2<<"_sum"<<fulladder<<" = ( a1["<<fulladder<<"] & b1["<<stage2<<"] ) ^ mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_xor"<<fulladder<<" = mult1_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult1_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult1_stage"<<stage2<<"_sum"<<fulladder<<" = mult1_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult1_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
}

//Last stage of CSA Multiplier
void SpecmultiplierCSAlastStage(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"/*This is the LAST stage for CSA multiplier.*/"<<endl;
    for (int fulladder=0; fulladder<=x_1-1; fulladder++) {
        if(fulladder==0)
        {
            outfile<<"    assign mult1_laststage_cout"<<fulladder<<" = mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign z1["<<x_2+fulladder<<"] = mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            //outfile<<"    assign mult1_laststage_cout"<<fulladder<<" = (a1["<<x_1-1<<"] & b1["<<x_2-1<<"]"<<" & mult1_stage"<<x_2-1<<"_cout"<<fulladder<<") | (a1["<<x_1-1<<"] & b1["<<x_1-1<<"] & mult1_laststage_cout"<<fulladder-1<<") | (mult1_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult1_laststage_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign z1["<<x_2+x_1-1<<"] = mult1_laststage_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            //outfile<<"    assign mult1_laststage_cout"<<fulladder<<" = ( a1["<<x_1-1<<"] & b1["<<x_2-1<<"] & mult1_stage"<<x_2-1<<"_cout"<<fulladder<<") | ( a1["<<x_1-1<<"] & b1["<<x_2-1<<"] & mult1_laststage"<<"_cout"<<fulladder-1<<") | (mult1_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult1_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign mult1_laststage_and"<<4*fulladder-3<<" = a1["<<x_1-1<<"] & b1["<<x_2-1<<"];"<<endl;
            outfile<<"    assign mult1_laststage_and"<<4*fulladder-2<<" = mult1_laststage_and"<<4*fulladder-3<<" & mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult1_laststage_and"<<4*fulladder-1<<" = mult1_laststage_and"<<4*fulladder-3<<" & mult1_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult1_laststage_and"<<4*fulladder<<" = mult1_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult1_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult1_laststage_or"<<fulladder<<" = mult1_laststage_and"<<4*fulladder-2<<" | mult1_laststage_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign mult1_laststage_cout"<<fulladder<<" = mult1_laststage_or"<<fulladder<<" | mult1_laststage_and"<<4*fulladder<<";"<<endl;
            //outfile<<"    assign z1["<<x_2+fulladder<<"] = mult1_laststage_cout"<<fulladder-1<<" ^ ( a1["<<x_1-1<<"] & b1["<<x_2-1<<"] ) ^ mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult1_laststage_xor"<<fulladder<<" = mult1_laststage_cout"<<fulladder-1<<" ^ mult1_laststage_and"<<4*fulladder-3<<";"<<endl;
            outfile<<"    assign z1["<<x_2+fulladder<<"] = mult1_laststage_xor"<<fulladder<<" ^ mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            
            //outfile<<"    assign mult1_laststage_cout"<<fulladder<<" = (mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult1_stage"<<x_2-1<<"_cout"<<fulladder<<") | (mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult1_laststage"<<"_cout"<<fulladder-1<<") | (mult1_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult1_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign mult1_laststage_and"<<4*fulladder-3<<" = mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult1_laststage_and"<<4*fulladder-2<<" = mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult1_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult1_laststage_and"<<4*fulladder-1<<" = mult1_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult1_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult1_laststage_or"<<fulladder<<" = mult1_laststage_and"<<4*fulladder-3<<" | mult1_laststage_and"<<4*fulladder-2<<";"<<endl;
            outfile<<"    assign mult1_laststage_cout"<<fulladder<<" = mult1_laststage_or"<<fulladder<<" | mult1_laststage_and"<<4*fulladder-1<<";"<<endl;
            //outfile<<"    assign z1["<<x_2+fulladder<<"] = mult1_laststage_cout"<<fulladder-1<<" ^ mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult1_laststage_xor"<<fulladder<<" = mult1_laststage_cout"<<fulladder-1<<" ^ mult1_stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
            outfile<<"    assign z1["<<x_2+fulladder<<"] = mult1_laststage_xor"<<fulladder<<" ^ mult1_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            
            
        }
    }
    
}
void Specm2stage1(int x,int y)
//N+1 bits * N bits
{
    x--;
    y--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_";
    int fileint=x+1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    int n=0;
    for (int i=0; i<=x; i++) {
        outfile<<"    assign mult2_stage1"<<"_and"<<n<<" = a2["<<i<<"] & b2[0];"<<endl;
        n++;
        outfile<<"    assign mult2_stage1"<<"_and"<<n<<" = a2["<<i<<"] & b2[1];"<<endl;
        n++;
    }
    outfile<<"    assign z2[0] = a2[0] & b2[0];"<<endl;
    // outfile<<"    assign mult2_stage1_cout0 = mult2_stage1_and0;"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            outfile<<"    assign mult2_stage1_sum"<<i_add-1<<" = mult2_stage1_and"<<2*i_add-1<<" ^ mult2_stage1_and"<<2*i_add<<";"<<endl;
            outfile<<"    assign mult2_stage1_cout"<<i_add-1<<" = mult2_stage1_and"<<2*i_add-1<<" & mult2_stage1_and"<<2*i_add<<";"<<endl;
            
        }
        else
        {
            outfile<<"    assign z2[1] = mult2_stage1_and1 ^ mult2_stage1_and2;"<<endl;
            outfile<<"    assign mult2_stage1_cout"<<i_add-1<<" = mult2_stage1_and"<<i_add<<" & mult2_stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    outfile<<" /* This is the CSA multiplier first Stage.*/"<<endl;
}
void Specm2stage2(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    for (int stage2=2; stage2<=x_2-1; stage2++) {
        for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
            
            if (fulladder==x_1-2) {
                // outfile<<"    assign mult2_stage"<<stage2<<"_cout"<<fulladder<<" = ( a2["<<fulladder<<"] & b2["<<stage2<<"] & mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (a2["<<fulladder+1<<"] & b2["<<stage2-1<<"]"<<" & a2["<<fulladder<<"] & b2["<<stage2<<"]) | (mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" & a2["<<fulladder+1<<"] & b2["<<stage2-1<<"]"<<");"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = a2["<<fulladder<<"] & b2["<<stage2<<"];"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = a2["<<fulladder+1<<"] & b2["<<stage2-1<<"];"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_or"<<fulladder<<" = mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_cout"<<fulladder<<" = mult2_stage"<<stage2<<"_or"<<fulladder<<" | mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                
                
                //outfile<<"    assign mult2_stage"<<stage2<<"_sum"<<fulladder<<" = ( a2["<<fulladder<<"] & b2["<<stage2<<"] ) ^ (a2["<<fulladder+1<<"] & b2["<<stage2-1<<"])"<<" ^ mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_xor"<<fulladder<<" = mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ mult2_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_sum"<<fulladder<<" = mult2_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                //outfile<<"    assign mult2_stage"<<stage2<<"_cout"<<fulladder<<" = ( a2["<<fulladder<<"] & b2["<<stage2<<"] & mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & a2["<<fulladder<<"] & b2["<<stage2<<"]) | (mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a2["<<fulladder<<"] & b2["<<stage2<<"];"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_or"<<fulladder<<" = mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_cout"<<fulladder<<" = mult2_stage"<<stage2<<"_or"<<fulladder<<" | mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign z2["<<stage2<<"] = ( a2["<<fulladder<<"] & b2["<<stage2<<"] ) ^ mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_xor"<<fulladder<<" = mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign z2["<<stage2<<"] = mult2_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                //outfile<<"    assign mult2_stage"<<stage2<<"_cout"<<fulladder<<" = ( a2["<<fulladder<<"] & b2["<<stage2<<"] & mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & (a2["<<fulladder<<"] & b2["<<stage2<<"]) ) | (mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a2["<<fulladder<<"] & b2["<<stage2<<"];"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult2_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_or"<<fulladder<<" = mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_cout"<<fulladder<<" = mult2_stage"<<stage2<<"_or"<<fulladder<<" | mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign mult2_stage"<<stage2<<"_sum"<<fulladder<<" = ( a2["<<fulladder<<"] & b2["<<stage2<<"] ) ^ mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_xor"<<fulladder<<" = mult2_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult2_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult2_stage"<<stage2<<"_sum"<<fulladder<<" = mult2_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult2_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
}

//Last stage of CSA Multiplier
void Specm2stage3(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"/*This is the LAST stage for CSA multiplier.*/"<<endl;
    for (int fulladder=0; fulladder<=x_1-1; fulladder++) {
        if(fulladder==0)
        {
            outfile<<"    assign mult2_laststage_cout"<<fulladder<<" = mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign z2["<<x_2+fulladder<<"] = mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            //outfile<<"    assign mult2_laststage_cout"<<fulladder<<" = (a2["<<x_1-1<<"] & b2["<<x_2-1<<"]"<<" & mult2_stage"<<x_2-1<<"_cout"<<fulladder<<") | (a2["<<x_1-1<<"] & b2["<<x_1-1<<"] & mult2_laststage_cout"<<fulladder-1<<") | (mult2_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult2_laststage_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign z2["<<x_2+x_1-1<<"] = mult2_laststage_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            //outfile<<"    assign mult2_laststage_cout"<<fulladder<<" = ( a2["<<x_1-1<<"] & b2["<<x_2-1<<"] & mult2_stage"<<x_2-1<<"_cout"<<fulladder<<") | ( a2["<<x_1-1<<"] & b2["<<x_2-1<<"] & mult2_laststage"<<"_cout"<<fulladder-1<<") | (mult2_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult2_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign mult2_laststage_and"<<4*fulladder-3<<" = a2["<<x_1-1<<"] & b2["<<x_2-1<<"];"<<endl;
            outfile<<"    assign mult2_laststage_and"<<4*fulladder-2<<" = mult2_laststage_and"<<4*fulladder-3<<" & mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult2_laststage_and"<<4*fulladder-1<<" = mult2_laststage_and"<<4*fulladder-3<<" & mult2_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult2_laststage_and"<<4*fulladder<<" = mult2_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult2_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult2_laststage_or"<<fulladder<<" = mult2_laststage_and"<<4*fulladder-2<<" | mult2_laststage_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign mult2_laststage_cout"<<fulladder<<" = mult2_laststage_or"<<fulladder<<" | mult2_laststage_and"<<4*fulladder<<";"<<endl;
            //outfile<<"    assign z2["<<x_2+fulladder<<"] = mult2_laststage_cout"<<fulladder-1<<" ^ ( a2["<<x_1-1<<"] & b2["<<x_2-1<<"] ) ^ mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult2_laststage_xor"<<fulladder<<" = mult2_laststage_cout"<<fulladder-1<<" ^ mult2_laststage_and"<<4*fulladder-3<<";"<<endl;
            outfile<<"    assign z2["<<x_2+fulladder<<"] = mult2_laststage_xor"<<fulladder<<" ^ mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            
            //outfile<<"    assign mult2_laststage_cout"<<fulladder<<" = (mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult2_stage"<<x_2-1<<"_cout"<<fulladder<<") | (mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult2_laststage"<<"_cout"<<fulladder-1<<") | (mult2_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult2_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign mult2_laststage_and"<<4*fulladder-3<<" = mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult2_laststage_and"<<4*fulladder-2<<" = mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult2_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult2_laststage_and"<<4*fulladder-1<<" = mult2_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult2_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult2_laststage_or"<<fulladder<<" = mult2_laststage_and"<<4*fulladder-3<<" | mult2_laststage_and"<<4*fulladder-2<<";"<<endl;
            outfile<<"    assign mult2_laststage_cout"<<fulladder<<" = mult2_laststage_or"<<fulladder<<" | mult2_laststage_and"<<4*fulladder-1<<";"<<endl;
            //outfile<<"    assign z2["<<x_2+fulladder<<"] = mult2_laststage_cout"<<fulladder-1<<" ^ mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult2_laststage_xor"<<fulladder<<" = mult2_laststage_cout"<<fulladder-1<<" ^ mult2_stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
            outfile<<"    assign z2["<<x_2+fulladder<<"] = mult2_laststage_xor"<<fulladder<<" ^ mult2_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            
            
        }
    }
    
}

void Specm3stage1(int x,int y)
//N+1 bits * N bits
{
    x--;
    y--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_";
    int fileint=x+1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    //outfile<<"Multiplier begin."<<endl;
    int n=0;
    for (int i=0; i<=x; i++) {
        outfile<<"    assign mult3_stage1"<<"_and"<<n<<" = a3["<<i<<"] & b3[0];"<<endl;
        n++;
        outfile<<"    assign mult3_stage1"<<"_and"<<n<<" = a3["<<i<<"] & b3[1];"<<endl;
        n++;
    }
    outfile<<"    assign z3[0] = a3[0] & b3[0];"<<endl;
    // outfile<<"    assign mult3_stage1_cout0 = mult3_stage1_and0;"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            outfile<<"    assign mult3_stage1_sum"<<i_add-1<<" = mult3_stage1_and"<<2*i_add-1<<" ^ mult3_stage1_and"<<2*i_add<<";"<<endl;
            outfile<<"    assign mult3_stage1_cout"<<i_add-1<<" = mult3_stage1_and"<<2*i_add-1<<" & mult3_stage1_and"<<2*i_add<<";"<<endl;
            
        }
        else
        {
            outfile<<"    assign z3[1] = mult3_stage1_and1 ^ mult3_stage1_and2;"<<endl;
            outfile<<"    assign mult3_stage1_cout"<<i_add-1<<" = mult3_stage1_and"<<i_add<<" & mult3_stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    outfile<<" /* This is the CSA multiplier first Stage.*/"<<endl;
}
void Specm3stage2(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    for (int stage2=2; stage2<=x_2-1; stage2++) {
        for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
            
            if (fulladder==x_1-2) {
                // outfile<<"    assign mult3_stage"<<stage2<<"_cout"<<fulladder<<" = ( a3["<<fulladder<<"] & b3["<<stage2<<"] & mult3_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (a3["<<fulladder+1<<"] & b3["<<stage2-1<<"]"<<" & a3["<<fulladder<<"] & b3["<<stage2<<"]) | (mult3_stage"<<stage2-1<<"_cout"<<fulladder<<" & a3["<<fulladder+1<<"] & b3["<<stage2-1<<"]"<<");"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = a3["<<fulladder<<"] & b3["<<stage2<<"];"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = a3["<<fulladder+1<<"] & b3["<<stage2-1<<"];"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult3_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & mult3_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_or"<<fulladder<<" = mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_cout"<<fulladder<<" = mult3_stage"<<stage2<<"_or"<<fulladder<<" | mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                
                
                //outfile<<"    assign mult3_stage"<<stage2<<"_sum"<<fulladder<<" = ( a3["<<fulladder<<"] & b3["<<stage2<<"] ) ^ (a3["<<fulladder+1<<"] & b3["<<stage2-1<<"])"<<" ^ mult3_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_xor"<<fulladder<<" = mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ mult3_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_sum"<<fulladder<<" = mult3_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult3_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                //outfile<<"    assign mult3_stage"<<stage2<<"_cout"<<fulladder<<" = ( a3["<<fulladder<<"] & b3["<<stage2<<"] & mult3_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult3_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & a3["<<fulladder<<"] & b3["<<stage2<<"]) | (mult3_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult3_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a3["<<fulladder<<"] & b3["<<stage2<<"];"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult3_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult3_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult3_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult3_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_or"<<fulladder<<" = mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_cout"<<fulladder<<" = mult3_stage"<<stage2<<"_or"<<fulladder<<" | mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign z3["<<stage2<<"] = ( a3["<<fulladder<<"] & b3["<<stage2<<"] ) ^ mult3_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult3_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_xor"<<fulladder<<" = mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult3_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign z3["<<stage2<<"] = mult3_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult3_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                //outfile<<"    assign mult3_stage"<<stage2<<"_cout"<<fulladder<<" = ( a3["<<fulladder<<"] & b3["<<stage2<<"] & mult3_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult3_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & (a3["<<fulladder<<"] & b3["<<stage2<<"]) ) | (mult3_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult3_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a3["<<fulladder<<"] & b3["<<stage2<<"];"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult3_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult3_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult3_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult3_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_or"<<fulladder<<" = mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_cout"<<fulladder<<" = mult3_stage"<<stage2<<"_or"<<fulladder<<" | mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign mult3_stage"<<stage2<<"_sum"<<fulladder<<" = ( a3["<<fulladder<<"] & b3["<<stage2<<"] ) ^ mult3_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult3_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_xor"<<fulladder<<" = mult3_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult3_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult3_stage"<<stage2<<"_sum"<<fulladder<<" = mult3_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult3_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
}

//Last stage of CSA Multiplier
void Specm3stage3(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"/*This is the LAST stage for CSA multiplier.*/"<<endl;
    for (int fulladder=0; fulladder<=x_1-1; fulladder++) {
        if(fulladder==0)
        {
            outfile<<"    assign mult3_laststage_cout"<<fulladder<<" = mult3_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult3_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign z3["<<x_2+fulladder<<"] = mult3_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult3_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            //outfile<<"    assign mult3_laststage_cout"<<fulladder<<" = (a3["<<x_1-1<<"] & b3["<<x_2-1<<"]"<<" & mult3_stage"<<x_2-1<<"_cout"<<fulladder<<") | (a3["<<x_1-1<<"] & b3["<<x_1-1<<"] & mult3_laststage_cout"<<fulladder-1<<") | (mult3_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult3_laststage_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign z3["<<x_2+x_1-1<<"] = mult3_laststage_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            //outfile<<"    assign mult3_laststage_cout"<<fulladder<<" = ( a3["<<x_1-1<<"] & b3["<<x_2-1<<"] & mult3_stage"<<x_2-1<<"_cout"<<fulladder<<") | ( a3["<<x_1-1<<"] & b3["<<x_2-1<<"] & mult3_laststage"<<"_cout"<<fulladder-1<<") | (mult3_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult3_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign mult3_laststage_and"<<4*fulladder-3<<" = a3["<<x_1-1<<"] & b3["<<x_2-1<<"];"<<endl;
            outfile<<"    assign mult3_laststage_and"<<4*fulladder-2<<" = mult3_laststage_and"<<4*fulladder-3<<" & mult3_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult3_laststage_and"<<4*fulladder-1<<" = mult3_laststage_and"<<4*fulladder-3<<" & mult3_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult3_laststage_and"<<4*fulladder<<" = mult3_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult3_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult3_laststage_or"<<fulladder<<" = mult3_laststage_and"<<4*fulladder-2<<" | mult3_laststage_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign mult3_laststage_cout"<<fulladder<<" = mult3_laststage_or"<<fulladder<<" | mult3_laststage_and"<<4*fulladder<<";"<<endl;
            //outfile<<"    assign z3["<<x_2+fulladder<<"] = mult3_laststage_cout"<<fulladder-1<<" ^ ( a3["<<x_1-1<<"] & b3["<<x_2-1<<"] ) ^ mult3_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult3_laststage_xor"<<fulladder<<" = mult3_laststage_cout"<<fulladder-1<<" ^ mult3_laststage_and"<<4*fulladder-3<<";"<<endl;
            outfile<<"    assign z3["<<x_2+fulladder<<"] = mult3_laststage_xor"<<fulladder<<" ^ mult3_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            
            //outfile<<"    assign mult3_laststage_cout"<<fulladder<<" = (mult3_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult3_stage"<<x_2-1<<"_cout"<<fulladder<<") | (mult3_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult3_laststage"<<"_cout"<<fulladder-1<<") | (mult3_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult3_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign mult3_laststage_and"<<4*fulladder-3<<" = mult3_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult3_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult3_laststage_and"<<4*fulladder-2<<" = mult3_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult3_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult3_laststage_and"<<4*fulladder-1<<" = mult3_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult3_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult3_laststage_or"<<fulladder<<" = mult3_laststage_and"<<4*fulladder-3<<" | mult3_laststage_and"<<4*fulladder-2<<";"<<endl;
            outfile<<"    assign mult3_laststage_cout"<<fulladder<<" = mult3_laststage_or"<<fulladder<<" | mult3_laststage_and"<<4*fulladder-1<<";"<<endl;
            //outfile<<"    assign z3["<<x_2+fulladder<<"] = mult3_laststage_cout"<<fulladder-1<<" ^ mult3_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult3_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult3_laststage_xor"<<fulladder<<" = mult3_laststage_cout"<<fulladder-1<<" ^ mult3_stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
            outfile<<"    assign z3["<<x_2+fulladder<<"] = mult3_laststage_xor"<<fulladder<<" ^ mult3_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            
            
        }
    }
    
}

void Specmult1(int x)
{
    SpecmultiplierCSAstage1(x, x);
    SpecmultiplierCSAstage2(x, x);
    SpecmultiplierCSAlastStage(x, x);
}
void Specmult2(int x)
{
    Specm2stage1(x, x);
    Specm2stage2(x, x);
    Specm2stage3(x, x);
}
void Specmult3(int x)
{
    Specm3stage1(x, x);
    Specm3stage2(x, x);
    Specm3stage3(x, x);
}
void Specbegin(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename);
    outfile<<"module AddMultForMatrix(a1,b1,a2,b2,a3,b3,p);"<<endl;
    outfile<<"  input ["<<x-1<<":0] a1,b1,a2,b2,a3,b3;"<<endl;
    outfile<<"  output ["<<2*x+1<<":0] p;"<<endl;
    outfile<<"  wire ["<<2*x+1<<":0] p;"<<endl;
    outfile<<"  wire ["<<2*x-1<<":0] z1,z2,z3;"<<endl;
    outfile<<"  wire ["<<2*x<<":0] adder1_add_sum;"<<endl;
    outfile<<"  wire ["<<2*x-2<<":0] adder1_add_cout;"<<endl;
    outfile<<"  wire ["<<2*x-1<<":0] adder2_add_cout;"<<endl;
}

void BenchGenMatrix::ThreeMultAndAddition(int x)

{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename);
    outfile<<"/*This Verilog is generated by BechGen software.*/\n"
    "/*Designed by University of Massachusetts, Amherst, VLSI CAD LAB, Cunxi Yu*/\n"
    "/*/  Copyright (c) 2014 Cunxi Yu. All rights reserved. */ \n"
    "/*Contact: ycunxi@umass.edu */"<<endl;
    
    Specbegin(x);
    Specmult1(x);
    Specmult2(x);
    Specmult3(x);
    SpecgatelevelAdder1(2*x);

    SpecgatelevelAdder2(2*x+1);

}

void BenchGenMatrix::ThreeMultAndAdditionRTL(int x)

{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGeneratedRTL/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Multiplier_3_RTL";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename);
    outfile<<"/*This Verilog is generated by BechGen software.*/\n"
    "/*Designed by University of Massachusetts, Amherst, VLSI CAD LAB, Cunxi Yu*/\n"
    "/*/  Copyright (c) 2014 Cunxi Yu. All rights reserved. */ \n"
    "/*Contact: ycunxi@umass.edu */"<<endl;
    
    outfile<<"module ThreeMultRTL"<<x-1<<"Bits(a1,b1,a2,b2,a3,b3,z);"<<endl;
    outfile<<"  input ["<<x-1<<":0] a1,b1,a2,b2,a3,b3;"<<endl;
    outfile<<"  output ["<<2*x+1<<":0] z;\n"
    "  wire ["<<2*x+1<<":0] z;\n"
    "    assign z=a1*b1+a2*b2+a3*b3;\n"<<endl;
    outfile<<"endmodule"<<endl;
    
}
void BenchGenMatrix::MatrixMultiplyRTL(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGeneratedRTL/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Matrix_mult_RTL";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename);
    outfile<<"module MatrixMultiplyRTL(a1,a2,a3,a4,a5,a6,a7,a8,a9,b1,b2,b3,p,p2,p3);"<<endl;
    outfile<<"input ["<<x-1<<"3:0] a1,a2,a3,a4,a5,a6,a7,a8,a9,b1,b2,b3;"<<endl;
    outfile<<"output ["<<2*x+1<<":0] p,p2,p3;"<<endl;
    outfile<<"assign p=a1*b1+a2*b2+a3*b3;"<<endl;
    outfile<<"assign p2=a4*b1+a5*b2+a6*b3;"<<endl;
    outfile<<"assign p3=a7*b1+a8*b2+a9*b3;"<<endl;
    outfile<<"endmodule"<<endl;
    
}



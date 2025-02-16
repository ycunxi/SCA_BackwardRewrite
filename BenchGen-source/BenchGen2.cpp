//
//  BenchGen2.cpp
//  Tools
//
//  Created by Cunxi Yu on 7/13/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//


/*This file contain Ripple adder and a*(b+c) and a*b+a*c in gate level*/
#include "BenchGen2.h"
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <fstream>
using namespace std;

void BenchGen2::RippleCarryAdder(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Ripple_Adder";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename);
    int n=0;
    for (int fulladder=0; fulladder<=x; fulladder++) {
        if (fulladder==0)
        {
            
            
            outfile<<"    assign s[0] = a[0] ^ b[0];"<<endl;
            outfile<<"    assign c1= a[0] & b[0];"<<endl;
        }
        else
        {
            outfile<<"    assign and"<<n<<" = a["<<fulladder<<"] & b["<<fulladder<<"];"<<endl;
            outfile<<"    assign and"<<n+1<<" = a["<<fulladder<<"] & c"<<fulladder<<";"<<endl;
            outfile<<"    assign and"<<n+2<<" = b["<<fulladder<<"] & c"<<fulladder<<";"<<endl;
            outfile<<"    assign s["<<fulladder<<"] = a["<<fulladder<<"] ^ b["<<fulladder<<"] ^ c"<<fulladder<<endl;
            outfile<<"    assign c"<<fulladder+1<<" = and"<<n<<" | and"<<n+1<<" | and"<<n+2<<";"<<endl;
            
        }
    }
}
void Mixstage1(int x,int y)
//N+1 bits * N bits
{
    x--;
    y--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="MixAdd_Mult";
    int fileint=x+1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);

    int n=0;
    for (int i=0; i<=x; i++) {
        outfile<<"    assign mult_stage1"<<"_and"<<n<<" = a["<<i<<"] & adder_add_sum[0];"<<endl;
        n++;
        outfile<<"    assign mult_stage1"<<"_and"<<n<<" = a["<<i<<"] & adder_add_sum[1];"<<endl;
        n++;
    }
    outfile<<"    assign z[0] = a[0] & adder_add_sum[0];"<<endl;
    // outfile<<"    assign mult_stage1_cout0 = mult_stage1_and0;"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            outfile<<"    assign mult_stage1_sum"<<i_add-1<<" = mult_stage1_and"<<2*i_add-1<<" ^ mult_stage1_and"<<2*i_add<<";"<<endl;
            outfile<<"    assign mult_stage1_cout"<<i_add-1<<" = mult_stage1_and"<<2*i_add-1<<" & mult_stage1_and"<<2*i_add<<";"<<endl;
            
        }
        else
        {
            outfile<<"    assign z[1] = mult_stage1_and1 ^ mult_stage1_and2;"<<endl;
            outfile<<"    assign mult_stage1_cout"<<i_add-1<<" = mult_stage1_and"<<i_add<<" & mult_stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    outfile<<" /* This is the CSA multiplier first Stage.*/"<<endl;
}
//After first stage

void Mixstage2(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="MixAdd_Mult";
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
                // outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( a["<<fulladder<<"] & adder_add_sum["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (a["<<fulladder+1<<"] & adder_add_sum["<<stage2-1<<"]"<<" & a["<<fulladder<<"] & adder_add_sum["<<stage2<<"]) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & a["<<fulladder+1<<"] & adder_add_sum["<<stage2-1<<"]"<<");"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = a["<<fulladder<<"] & adder_add_sum["<<stage2<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = a["<<fulladder+1<<"] & adder_add_sum["<<stage2-1<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                
                
                //outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = ( a["<<fulladder<<"] & adder_add_sum["<<stage2<<"] ) ^ (a["<<fulladder+1<<"] & adder_add_sum["<<stage2-1<<"])"<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                //outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( a["<<fulladder<<"] & adder_add_sum["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & a["<<fulladder<<"] & adder_add_sum["<<stage2<<"]) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a["<<fulladder<<"] & adder_add_sum["<<stage2<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign z["<<stage2<<"] = ( a["<<fulladder<<"] & adder_add_sum["<<stage2<<"] ) ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign z["<<stage2<<"] = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                //outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( a["<<fulladder<<"] & adder_add_sum["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & (a["<<fulladder<<"] & adder_add_sum["<<stage2<<"]) ) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a["<<fulladder<<"] & adder_add_sum["<<stage2<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = ( a["<<fulladder<<"] & adder_add_sum["<<stage2<<"] ) ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
}

//Last stage of CSA Multiplier
void MixlastStage(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="MixAdd_Mult";
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
            outfile<<"    assign mult_laststage_cout"<<fulladder<<" = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign z["<<x_2+fulladder<<"] = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            //outfile<<"    assign mult_laststage_cout"<<fulladder<<" = (a["<<x_1-1<<"] & adder_add_sum["<<x_2-1<<"]"<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | (a["<<x_1-1<<"] & adder_add_sum["<<x_1-1<<"] & mult_laststage_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign z["<<x_2+x_1-1<<"] = mult_laststage_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            //outfile<<"    assign mult_laststage_cout"<<fulladder<<" = ( a["<<x_1-1<<"] & adder_add_sum["<<x_2-1<<"] & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | ( a["<<x_1-1<<"] & adder_add_sum["<<x_2-1<<"] & mult_laststage"<<"_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-3<<" = a["<<x_1-1<<"] & adder_add_sum["<<x_2-1<<"];"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-2<<" = mult_laststage_and"<<4*fulladder-3<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-1<<" = mult_laststage_and"<<4*fulladder-3<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder<<" = mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_laststage_or"<<fulladder<<" = mult_laststage_and"<<4*fulladder-2<<" | mult_laststage_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign mult_laststage_cout"<<fulladder<<" = mult_laststage_or"<<fulladder<<" | mult_laststage_and"<<4*fulladder<<";"<<endl;
            //outfile<<"    assign z["<<x_2+fulladder<<"] = mult_laststage_cout"<<fulladder-1<<" ^ ( a["<<x_1-1<<"] & adder_add_sum["<<x_2-1<<"] ) ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult_laststage_xor"<<fulladder<<" = mult_laststage_cout"<<fulladder-1<<" ^ mult_laststage_and"<<4*fulladder-3<<";"<<endl;
            outfile<<"    assign z["<<x_2+fulladder<<"] = mult_laststage_xor"<<fulladder<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            
            //outfile<<"    assign mult_laststage_cout"<<fulladder<<" = (mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | (mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_laststage"<<"_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-3<<" = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-2<<" = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-1<<" = mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_laststage_or"<<fulladder<<" = mult_laststage_and"<<4*fulladder-3<<" | mult_laststage_and"<<4*fulladder-2<<";"<<endl;
            outfile<<"    assign mult_laststage_cout"<<fulladder<<" = mult_laststage_or"<<fulladder<<" | mult_laststage_and"<<4*fulladder-1<<";"<<endl;
            //outfile<<"    assign z["<<x_2+fulladder<<"] = mult_laststage_cout"<<fulladder-1<<" ^ mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult_laststage_xor"<<fulladder<<" = mult_laststage_cout"<<fulladder-1<<" ^ mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
            outfile<<"    assign z["<<x_2+fulladder<<"] = mult_laststage_xor"<<fulladder<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            
            
        }
    }
    outfile<<"endmodule"<<endl<<endl;
    outfile<<"/* This is verilog file of multiplier designed by BechGen software.*/"<<endl;
}
void AdderMix(int x)
//The gate level Verilog HDL code for Addition(in1+in2)
{
    x--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="MixAdd_Mult";
    int fileint=x+1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    //verilogFile();
    outfile<<"module MixAddMultiply"<<x+1<<"Bits(a,b,c,z);"<<endl;
    outfile<<" input ["<<x<<":0] a,b,c;"<<endl;
    outfile<<" output ["<<2*x+2<<":0] z;"<<endl;
    outfile<<" wire ["<<2*x+2<<":0] z;"<<endl;
    outfile<<" wire ["<<x+1<<":0] adder_add_sum;"<<endl;
    outfile<<" wire ["<<x-1<<":0] adder_add_cout;"<<endl;
    outfile<<"    assign adder_and0 = c[0] & b[0] ;"<<endl;
    outfile<<"    assign adder_add_cout[0] = adder_and0;"<<endl;
    outfile<<"    assign adder_add_sum[0] = c[0] ^ b[0];"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            
            
            outfile<<"    assign adder_and"<<3*i-2<<" = adder_add_cout["<<i-1<<"] & c["<<i<<"];"<<endl;
            outfile<<"    assign adder_and"<<3*i-1<<" = adder_add_cout["<<i-1<<"] & b["<<i<<"];"<<endl;
            outfile<<"    assign adder_and"<<3*i<<" = c["<<i<<"] & b["<<i<<"];"<<endl;
            outfile<<"    assign adder_or"<<i<<" = adder_and"<<3*i-2<<" | "<<"adder_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder_add_cout["<<i<<"] = adder_or"<<i<<" | ""adder_and"<<3*i<<";"<<endl;
            // outfile<<"    assign adder_add_cout["<<i<<"] = adder_and_"<<3*i-2<<" | "<<"adder_and_"<<3*i-1<<" | "<<"adder_and_"<<3*i<<";"<<endl;
            outfile<<"    assign adder_xor"<<i<<" = c["<<i<<"] ^ b["<<i<<"];"<<endl;
            outfile<<"    assign adder_add_sum["<<i<<"] = adder_xor"<<i<<" ^ "<<"adder_add_cout["<<i-1<<"];"<<endl;
            //outfile<<"    assign adder_add_sum["<<i<<"] = c["<<i<<"] ^ b["<<i<<"] ^ "<<"adder_add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            outfile<<"    assign adder_and"<<3*i-2<<" = adder_add_cout["<<i-1<<"] & c["<<i<<"];"<<endl;
            outfile<<"    assign adder_and"<<3*i-1<<" = adder_add_cout["<<i-1<<"] & b["<<i<<"];"<<endl;
            outfile<<"    assign adder_and"<<3*i<<" = c["<<i<<"] & b["<<i<<"];"<<endl;
            outfile<<"    assign adder_or"<<i<<" = adder_and"<<3*i-2<<" | "<<"adder_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder_add_sum["<<i+1<<"] = adder_or"<<i<<" | adder_and"<<3*i<<";"<<endl;
            outfile<<"    assign adder_xor"<<i<<" = c["<<i<<"] ^ b["<<i<<"];"<<endl;
            outfile<<"    assign adder_add_sum["<<i<<"] = adder_xor"<<i<<" ^ "<<"adder_add_cout["<<i-1<<"];"<<endl;
        }
    }
    //outfile<<"endmodule"<<endl;
}

void BenchGen2::MixAddMultiply(int bit1,int bit2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="MixAdd_Mult";
    int fileint=bit1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename);
    outfile<<"/*This Verilog is generated by BechGen software.*/\n"
    "/*Designed by University of Massachusetts, Amherst, VLSI CAD LAB, Cunxi Yu*/\n"
    "/*/  Copyright (c) 2014 Cunxi Yu. All rights reserved. */ \n"
    "/*Contact: ycunxi@umass.edu */"
    "//************************************************************\n"
    "//This file is verilog of gate-level for F=a*(b+c) \n"<<endl;
    AdderMix(bit1);
    Mixstage1(bit1, bit1+1);
    Mixstage2(bit1, bit1+1);
    MixlastStage(bit1,bit1+1);
}

void BenchGen2::MixAddMultRTL(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGeneratedRTL/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="RTL_MixAdd_Mult";
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
    "/*Contact: ycunxi@umass.edu */"
    "//************************************************************\n"
    "//This file is verilog of gate-level for F=a*(b+c) \n"<<endl;
    outfile<<"module MixAddMultiply"<<x<<"Bits(a,b,c,z);"<<endl;
    outfile<<" input ["<<x-1<<":0] a,b,c;"<<endl;
    outfile<<" output ["<<2*x<<":0] z;"<<endl;
    outfile<<" wire ["<<2*x<<":0] z;"<<endl;
    outfile<<"    assign z=a*b+a*c;"<<endl;
    outfile<<"endmodule"<<endl;
}


void BenchGen2::subtracotrTwoComplement(int x)
{

    x--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Subtractor";
    int fileint=x+1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename);
    outfile<<"module sub"<<x+1<<"Bits(a,b,z);"<<endl;
    outfile<<" input ["<<x<<":0] a;"<<endl;
    outfile<<" input ["<<x<<":0] b;"<<endl;
    outfile<<" output ["<<x+1<<":0] z;"<<endl;
    outfile<<"    assign sub_and0 = a[0] & !b[0];"<<endl;
    outfile<<"    assign sub_or0 = a[0] | !b[0];"<<endl;
    outfile<<"    assign sub_or_0 = sub_or0 | sub_and0;"<<endl;
    outfile<<"    assign sub_add_cout[0] = sub_or_0;"<<endl;
    outfile<<"    assign sub_xor0 = a[0] ^ !b[0];"<<endl;
    outfile<<"    assign z[0] = sub_xor0 ^ 1'b0;"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            outfile<<"    assign sub_and"<<3*i-2<<" = sub_add_cout["<<i-1<<"] & a["<<i<<"];"<<endl;
            outfile<<"    assign sub_and"<<3*i-1<<" = sub_add_cout["<<i-1<<"] & !b["<<i<<"];"<<endl;
            outfile<<"    assign sub_and"<<3*i<<" = a["<<i<<"] & !b["<<i<<"];"<<endl;
            outfile<<"    assign sub_or"<<i<<" = sub_and"<<3*i-2<<" | "<<"sub_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign sub_add_cout["<<i<<"] = sub_or"<<i<<" | ""sub_and"<<3*i<<";"<<endl;
            
            outfile<<"    assign sub_xor"<<i<<" = a["<<i<<"] ^ !b["<<i<<"];"<<endl;
            outfile<<"    assign z["<<i<<"] = sub_xor"<<i<<" ^ "<<"sub_add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            outfile<<"    assign sub_and"<<3*i-2<<" = sub_add_cout["<<i-1<<"] & a["<<i<<"];"<<endl;
            outfile<<"    assign sub_and"<<3*i-1<<" = sub_add_cout["<<i-1<<"] & !b["<<i<<"];"<<endl;
            outfile<<"    assign sub_and"<<3*i<<" = a["<<i<<"] & !b["<<i<<"];"<<endl;
            outfile<<"    assign sub_or"<<i<<" = sub_and"<<3*i-2<<" | "<<"sub_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign z["<<i+1<<"] = sub_or"<<i<<" | sub_and"<<3*i<<";"<<endl;
            outfile<<"    assign sub_xor"<<i<<" = a["<<i<<"] ^ !b["<<i<<"];"<<endl;
            outfile<<"    assign z["<<i<<"] = sub_xor"<<i<<" ^ "<<"sub_add_cout["<<i-1<<"];"<<endl;
        }
    }
    outfile<<"endmodule"<<endl;
}

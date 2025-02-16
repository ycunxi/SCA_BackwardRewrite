//
//  BenchGen-ALU.cpp
//  Tools
//
//  Created by Cunxi Yu on 8/4/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include "BenchGen-ALU.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sstream>
using namespace std;
void alumultiply1(int x,int y)
//N+1 bits * N bits
{
    x--;
    y--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Integer_ALU";
    int fileint=x+1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    int n=0;
    for (int i=0; i<=x; i++) {
        outfile<<"    assign mult_stage1"<<"_and"<<n<<" = mux_a["<<i<<"] & mux_b[0];"<<endl;
        n++;
        outfile<<"    assign mult_stage1"<<"_and"<<n<<" = mux_a["<<i<<"] & mux_b[1];"<<endl;
        n++;
    }
    outfile<<"    assign alu_mult[0] = mux_a[0] & mux_b[0];"<<endl;
    // outfile<<"    assign mult_stage1_cout0 = mult_stage1_and0;"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            outfile<<"    assign mult_stage1_sum"<<i_add-1<<" = mult_stage1_and"<<2*i_add-1<<" ^ mult_stage1_and"<<2*i_add<<";"<<endl;
            outfile<<"    assign mult_stage1_cout"<<i_add-1<<" = mult_stage1_and"<<2*i_add-1<<" & mult_stage1_and"<<2*i_add<<";"<<endl;
        }
        else
        {
            outfile<<"    assign alu_mult[1] = mult_stage1_and1 ^ mult_stage1_and2;"<<endl;
            outfile<<"    assign mult_stage1_cout"<<i_add-1<<" = mult_stage1_and"<<i_add<<" & mult_stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    outfile<<" /* This is the CSA multiplier first Stage.*/"<<endl;
}
//After first stage

void alumultiply2(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Integer_ALU";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    for (int stage2=2; stage2<=x_2-1; stage2++) {
        for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
            
            if (fulladder==x_1-2) {
                // outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( mux_a["<<fulladder<<"] & mux_b["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mux_a["<<fulladder+1<<"] & mux_b["<<stage2-1<<"]"<<" & mux_a["<<fulladder<<"] & mux_b["<<stage2<<"]) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mux_a["<<fulladder+1<<"] & mux_b["<<stage2-1<<"]"<<");"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = mux_a["<<fulladder<<"] & mux_b["<<stage2<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = mux_a["<<fulladder+1<<"] & mux_b["<<stage2-1<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                
                
                //outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = ( mux_a["<<fulladder<<"] & mux_b["<<stage2<<"] ) ^ (mux_a["<<fulladder+1<<"] & mux_b["<<stage2-1<<"])"<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                //outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( mux_a["<<fulladder<<"] & mux_b["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & mux_a["<<fulladder<<"] & mux_b["<<stage2<<"]) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = mux_a["<<fulladder<<"] & mux_b["<<stage2<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign alu_mult["<<stage2<<"] = ( mux_a["<<fulladder<<"] & mux_b["<<stage2<<"] ) ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign alu_mult["<<stage2<<"] = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                //outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( mux_a["<<fulladder<<"] & mux_b["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & (mux_a["<<fulladder<<"] & mux_b["<<stage2<<"]) ) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = mux_a["<<fulladder<<"] & mux_b["<<stage2<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = ( mux_a["<<fulladder<<"] & mux_b["<<stage2<<"] ) ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
}

//Last stage of CSA Multiplier
void alumultiply3(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Integer_ALU";
    int fileint=x_1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"/*This is the LAST stage for CSA multiplier.*/"<<endl;
    for (int fulladder=0; fulladder<=x_1-1; fulladder++) {
        if(fulladder==0)
        {
            outfile<<"    assign mult_laststage_cout"<<fulladder<<" = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign alu_mult["<<x_2+fulladder<<"] = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            //outfile<<"    assign mult_laststage_cout"<<fulladder<<" = (mux_a["<<x_1-1<<"] & mux_b["<<x_2-1<<"]"<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | (mux_a["<<x_1-1<<"] & mux_b["<<x_1-1<<"] & mult_laststage_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign alu_mult["<<x_2+x_1-1<<"] = mult_laststage_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            //outfile<<"    assign mult_laststage_cout"<<fulladder<<" = ( mux_a["<<x_1-1<<"] & mux_b["<<x_2-1<<"] & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | ( mux_a["<<x_1-1<<"] & mux_b["<<x_2-1<<"] & mult_laststage"<<"_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-3<<" = mux_a["<<x_1-1<<"] & mux_b["<<x_2-1<<"];"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-2<<" = mult_laststage_and"<<4*fulladder-3<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-1<<" = mult_laststage_and"<<4*fulladder-3<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder<<" = mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_laststage_or"<<fulladder<<" = mult_laststage_and"<<4*fulladder-2<<" | mult_laststage_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign mult_laststage_cout"<<fulladder<<" = mult_laststage_or"<<fulladder<<" | mult_laststage_and"<<4*fulladder<<";"<<endl;
            //outfile<<"    assign alu_mult["<<x_2+fulladder<<"] = mult_laststage_cout"<<fulladder-1<<" ^ ( mux_a["<<x_1-1<<"] & mux_b["<<x_2-1<<"] ) ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult_laststage_xor"<<fulladder<<" = mult_laststage_cout"<<fulladder-1<<" ^ mult_laststage_and"<<4*fulladder-3<<";"<<endl;
            outfile<<"    assign alu_mult["<<x_2+fulladder<<"] = mult_laststage_xor"<<fulladder<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            
            //outfile<<"    assign mult_laststage_cout"<<fulladder<<" = (mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | (mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_laststage"<<"_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-3<<" = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-2<<" = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-1<<" = mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_laststage_or"<<fulladder<<" = mult_laststage_and"<<4*fulladder-3<<" | mult_laststage_and"<<4*fulladder-2<<";"<<endl;
            outfile<<"    assign mult_laststage_cout"<<fulladder<<" = mult_laststage_or"<<fulladder<<" | mult_laststage_and"<<4*fulladder-1<<";"<<endl;
            //outfile<<"    assign alu_mult["<<x_2+fulladder<<"] = mult_laststage_cout"<<fulladder-1<<" ^ mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult_laststage_xor"<<fulladder<<" = mult_laststage_cout"<<fulladder-1<<" ^ mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
            outfile<<"    assign alu_mult["<<x_2+fulladder<<"] = mult_laststage_xor"<<fulladder<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
    }
}

void aluEntireMultiply(int x)
{
    alumultiply1(x, x);
    alumultiply2(x, x);
    alumultiply3(x, x);
}

void alu_adder(int x)
//The gate level Verilog HDL code for circuit-(a+b)
{
    x--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Integer_ALU";
    int fileint=(x+1)/2;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"    assign adder_and0 = mult_en[0] & mux_c_en[0] ;"<<endl;
    outfile<<"    assign adder_add_cout[0] = adder_and0;"<<endl;
    outfile<<"    assign adder_add_sum[0] = mult_en[0] ^ mux_c_en[0];"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            outfile<<"    assign adder_and"<<3*i-2<<" = adder_add_cout["<<i-1<<"] & mult_en["<<i<<"];"<<endl;
            outfile<<"    assign adder_and"<<3*i-1<<" = adder_add_cout["<<i-1<<"] & mux_c_en["<<i<<"];"<<endl;
            outfile<<"    assign adder_and"<<3*i<<" = mult_en["<<i<<"] & mux_c_en["<<i<<"];"<<endl;
            outfile<<"    assign adder_or"<<i<<" = adder_and"<<3*i-2<<" | "<<"adder_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder_add_cout["<<i<<"] = adder_or"<<i<<" | ""adder_and"<<3*i<<";"<<endl;
            
            outfile<<"    assign adder_xor"<<i<<" = mult_en["<<i<<"] ^ mux_c_en["<<i<<"];"<<endl;
            outfile<<"    assign adder_add_sum["<<i<<"] = adder_xor"<<i<<" ^ "<<"adder_add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            outfile<<"    assign adder_and"<<3*i-2<<" = adder_add_cout["<<i-1<<"] & mult_en["<<i<<"];"<<endl;
            outfile<<"    assign adder_and"<<3*i-1<<" = adder_add_cout["<<i-1<<"] & mux_c_en["<<i<<"];"<<endl;
            outfile<<"    assign adder_and"<<3*i<<" = mult_en["<<i<<"] & mux_c_en["<<i<<"];"<<endl;
            outfile<<"    assign adder_or"<<i<<" = adder_and"<<3*i-2<<" | "<<"adder_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder_add_sum["<<i+1<<"] = adder_or"<<i<<" | adder_and"<<3*i<<";"<<endl;
            outfile<<"    assign adder_xor"<<i<<" = mult_en["<<i<<"] ^ mux_c_en["<<i<<"];"<<endl;
            outfile<<"    assign adder_add_sum["<<i<<"] = adder_xor"<<i<<" ^ "<<"adder_add_cout["<<i-1<<"];"<<endl;
        }
    }
}
void alu_last(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Integer_ALU";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    
    /*
    for (int y_mux=1; y_mux<=2*x; y_mux++) {
        outfile<<"    assign y_mux_and"<<2*y_mux-1<<" = !adder_add_sum["<<y_mux-1<<"] & neg_y;"<<endl;
        outfile<<"    assign y_mux_and"<<2*y_mux<<" = adder_add_sum["<<y_mux-1<<"] & !neg_y;"<<endl;
        outfile<<"    assign y["<<y_mux-1<<"] = y_mux_and"<<2*y_mux-1<<" | y_mux_and"<<2*y_mux<<";"<<endl;
    }*/

    //negator y
    for (int bits=0; bits<2*x; bits++) {
        if (bits==0) {
            outfile<<"    assign negator_y["<<bits<<"] = !adder_add_sum["<<bits<<"] ^ 1'b1;"<<endl;
            outfile<<"    assign negator_y_cout"<<bits<<" = !adder_add_sum["<<bits<<"] & 1'b1;"<<endl;
        }
        else if(bits==2*x-1)
        {
            outfile<<"    assign negator_y["<<bits<<"] = !adder_add_sum["<<bits<<"] ^ negator_y_cout"<<bits-1<<";"<<endl;
        }
        else
        {
            outfile<<"    assign negator_y["<<bits<<"] = !adder_add_sum["<<bits<<"] ^ negator_y_cout"<<bits-1<<";"<<endl;
            outfile<<"    assign negator_y_cout"<<bits<<" = !adder_add_sum["<<bits<<"] & negator_y_cout"<<bits-1<<";"<<endl;
        }
        
    }
    for (int y_mux=1; y_mux<=2*x; y_mux++) {
        outfile<<"    assign y_mux_and"<<2*y_mux-1<<" = negator_y["<<y_mux-1<<"] & neg_y;"<<endl;
        outfile<<"    assign y_mux_and"<<2*y_mux<<" = adder_add_sum["<<y_mux-1<<"] & !neg_y;"<<endl;
        outfile<<"    assign y["<<y_mux-1<<"] = y_mux_and"<<2*y_mux-1<<" | y_mux_and"<<2*y_mux<<";"<<endl;
    }
    outfile<<"endmodule"<<endl;
}

void beforeadd(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Integer_ALU";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    for (int mult_en=0; mult_en<=2*x-1; mult_en++) {
        outfile<<"    assign mult_en["<<mult_en<<"] = alu_mult["<<mult_en<<"] & en_ab;"<<endl;
    }
    
    //mux_c en_c and gate
    for (int mux_c_en=0; mux_c_en<=2*x-1; mux_c_en++) {
        if(mux_c_en<=x-1)
        {
            outfile<<"    assign mux_c_en["<<mux_c_en<<"] = mux_c["<<mux_c_en<<"] & en_c;"<<endl;
        }
        else
        {
            outfile<<"    assign mux_c_en["<<mux_c_en<<"] = 1'b0 | neg_c;"<<endl;
        }
    }
}
void begin(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Integer_ALU";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename);
    outfile<<"/*This Verilog is generated by BechGen software.*/\n"
    "/*Designed by University of Massachusetts, Amherst, VLSI CAD LAB, Cunxi Yu*/\n"
    "/*/  Copyright (c) 2014 Cunxi Yu. All rights reserved. */ \n"
    "/*Contact: ycunxi@umass.edu */"<<endl;
    int mux_num=3;
    //three muxes at beginning
    outfile<<"module InitialIntegerALU(a,b,c,neg_a,neg_b,neg_c,en_ab,en_c,neg_y,y);"<<endl;
    outfile<<" input ["<<x-1<<":0] a,b,c;"<<endl;
    outfile<<" input neg_a,neg_b,neg_c,en_ab,en_c,neg_y;"<<endl;
    outfile<<" output ["<<2*x-1<<":0] y;"<<endl;
    outfile<<" wire ["<<2*x-1<<":0] y;"<<endl;
    outfile<<" wire ["<<x-1<<":0] mux_a,mux_b,mux_c;"<<endl;
    outfile<<" wire ["<<2*x-1<<":0] alu_mult,mult_en,mux_c_en,negator_y;"<<endl;
    outfile<<" wire ["<<2*x<<":0] adder_add_sum;"<<endl;
    outfile<<" wire ["<<2*x-2<<":0] adder_add_cout;"<<endl;
    outfile<<" wire ["<<x-1<<":0] negator_a,negator_b,negator_c;"<<endl;
    //negator a
    for (int bits=0; bits<4; bits++) {
        if (bits==0) {
            outfile<<"    assign negator_a["<<bits<<"] = !a["<<bits<<"] ^ 1'b1;"<<endl;
            outfile<<"    assign negator_a_cout"<<bits<<" = !a["<<bits<<"] & 1'b1;"<<endl;
        }
        else if(bits==x-1)
        {
            outfile<<"    assign negator_a["<<bits<<"] = !a["<<bits<<"] ^ negator_a_cout"<<bits-1<<";"<<endl;
        }
        else
        {
            outfile<<"    assign negator_a["<<bits<<"] = !a["<<bits<<"] ^ negator_a_cout"<<bits-1<<";"<<endl;
            outfile<<"    assign negator_a_cout"<<bits<<" = !a["<<bits<<"] & negator_a_cout"<<bits-1<<";"<<endl;
        }
        
    }
    //negator b
    for (int bits=0; bits<4; bits++) {
        if (bits==0) {
            outfile<<"    assign negator_b["<<bits<<"] = !b["<<bits<<"] ^ 1'b1;"<<endl;
            outfile<<"    assign negator_b_cout"<<bits<<" = !b["<<bits<<"] & 1'b1;"<<endl;
        }
        else if(bits==x-1)
        {
            outfile<<"    assign negator_b["<<bits<<"] = !b["<<bits<<"] ^ negator_b_cout"<<bits-1<<";"<<endl;
        }
        else
        {
            outfile<<"    assign negator_b["<<bits<<"] = !b["<<bits<<"] ^ negator_b_cout"<<bits-1<<";"<<endl;
            outfile<<"    assign negator_b_cout"<<bits<<" = !b["<<bits<<"] & negator_b_cout"<<bits-1<<";"<<endl;
        }
        
    }
    //negator c
    for (int bits=0; bits<4; bits++) {
        if (bits==0) {
            outfile<<"    assign negator_c["<<bits<<"] = !c["<<bits<<"] ^ 1'b1;"<<endl;
            outfile<<"    assign negator_c_cout"<<bits<<" = !c["<<bits<<"] & 1'b1;"<<endl;
        }
        else if(bits==x-1)
        {
            outfile<<"    assign negator_c["<<bits<<"] = !c["<<bits<<"] ^ negator_c_cout"<<bits-1<<";"<<endl;
        }
        else
        {
            outfile<<"    assign negator_c["<<bits<<"] = !c["<<bits<<"] ^ negator_c_cout"<<bits-1<<";"<<endl;
            outfile<<"    assign negator_c_cout"<<bits<<" = !c["<<bits<<"] & negator_c_cout"<<bits-1<<";"<<endl;
        }
        
    }
    for (int mux=1; mux<=mux_num; mux++) {
        if(mux==1)
        {
            for (int bit=1; bit<=x; bit++) {
                outfile<<"    assign mux_a_and"<<2*bit-1<<" = !a["<<bit-1<<"] & neg_a;"<<endl;
                outfile<<"    assign mux_a_and"<<2*bit<<" = a["<<bit-1<<"] & !neg_a;"<<endl;
                outfile<<"    assign mux_a"<<"["<<bit-1<<"] = mux_a_and"<<2*bit-1<<" | mux_a_and"<<2*bit<<";"<<endl;
            }
        }
        else if(mux==2)
        {
            for (int bit=1; bit<=x; bit++) {
                outfile<<"    assign mux_b_and"<<2*bit-1<<" = !b["<<bit-1<<"] & neg_b;"<<endl;
                outfile<<"    assign mux_b_and"<<2*bit<<" = b["<<bit-1<<"] & !neg_b;"<<endl;
                outfile<<"    assign mux_b"<<"["<<bit-1<<"] = mux_b_and"<<2*bit-1<<" | mux_b_and"<<2*bit<<";"<<endl;
            }
        }
        else
        {
            for (int bit=1; bit<=x; bit++) {
                outfile<<"    assign mux_c_and"<<2*bit-1<<" = !c["<<bit-1<<"] & neg_c;"<<endl;
                outfile<<"    assign mux_c_and"<<2*bit<<" = c["<<bit-1<<"] & !neg_c;"<<endl;
                outfile<<"    assign mux_c"<<"["<<bit-1<<"] = mux_c_and"<<2*bit-1<<" | mux_c_and"<<2*bit<<";"<<endl;
            }
        }
    }//Muxes end
}

void BenchGenALU::ALU(int x)
{
    begin(x);
    aluEntireMultiply(x);
    //multiplier en_ab and gate
    beforeadd(x);
    alu_adder(2*x);
    
    alu_last(x);
    
    
}


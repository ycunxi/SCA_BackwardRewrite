//
//  BenchGen-Squarer.cpp
//  Tools
//
//  Created by Cunxi Yu on 7/29/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include "BenchGen-Squarer.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sstream>
#include <string>
#include <stdio.h>
using namespace std;

void sq_mult1(int x,int y)
//N+1 bits * N bits
{
    x--;
    y--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp1_";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    int n=0;
    for (int i=0; i<=x; i++) {
        outfile<<"    assign mult_stage1"<<"_and"<<n<<" = sq_input["<<i<<"] & sq_input[0];"<<endl;
        n++;
        outfile<<"    assign mult_stage1"<<"_and"<<n<<" = sq_input["<<i<<"] & sq_input[1];"<<endl;
        n++;
    }
    outfile<<"    assign z[0] = sq_input[0] & sq_input[0];"<<endl;
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

void sq_mult2(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp1_";
    int fileint=x_1-1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    for (int stage2=2; stage2<=x_2-1; stage2++) {
        for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
            
            if (fulladder==x_1-2) {
                // outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( sq_input["<<fulladder<<"] & sq_input["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (sq_input["<<fulladder+1<<"] & sq_input["<<stage2-1<<"]"<<" & sq_input["<<fulladder<<"] & sq_input["<<stage2<<"]) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & sq_input["<<fulladder+1<<"] & sq_input["<<stage2-1<<"]"<<");"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = sq_input["<<fulladder<<"] & sq_input["<<stage2<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = sq_input["<<fulladder+1<<"] & sq_input["<<stage2-1<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                
                
                //outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = ( sq_input["<<fulladder<<"] & sq_input["<<stage2<<"] ) ^ (sq_input["<<fulladder+1<<"] & sq_input["<<stage2-1<<"])"<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                //outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( sq_input["<<fulladder<<"] & sq_input["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & sq_input["<<fulladder<<"] & sq_input["<<stage2<<"]) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = sq_input["<<fulladder<<"] & sq_input["<<stage2<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign z["<<stage2<<"] = ( sq_input["<<fulladder<<"] & sq_input["<<stage2<<"] ) ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign z["<<stage2<<"] = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                //outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( sq_input["<<fulladder<<"] & sq_input["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & (sq_input["<<fulladder<<"] & sq_input["<<stage2<<"]) ) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = sq_input["<<fulladder<<"] & sq_input["<<stage2<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = ( sq_input["<<fulladder<<"] & sq_input["<<stage2<<"] ) ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
}

//Last stage of CSA Multiplier
void sq_mult3(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp1_";
    int fileint=x_1-1;
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
            outfile<<"    assign z["<<x_2+fulladder<<"] = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            //outfile<<"    assign mult_laststage_cout"<<fulladder<<" = (sq_input["<<x_1-1<<"] & sq_input["<<x_2-1<<"]"<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | (sq_input["<<x_1-1<<"] & sq_input["<<x_1-1<<"] & mult_laststage_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign z["<<x_2+x_1-1<<"] = mult_laststage_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            //outfile<<"    assign mult_laststage_cout"<<fulladder<<" = ( sq_input["<<x_1-1<<"] & sq_input["<<x_2-1<<"] & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | ( sq_input["<<x_1-1<<"] & sq_input["<<x_2-1<<"] & mult_laststage"<<"_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-3<<" = sq_input["<<x_1-1<<"] & sq_input["<<x_2-1<<"];"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-2<<" = mult_laststage_and"<<4*fulladder-3<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder-1<<" = mult_laststage_and"<<4*fulladder-3<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_laststage_and"<<4*fulladder<<" = mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_laststage_or"<<fulladder<<" = mult_laststage_and"<<4*fulladder-2<<" | mult_laststage_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign mult_laststage_cout"<<fulladder<<" = mult_laststage_or"<<fulladder<<" | mult_laststage_and"<<4*fulladder<<";"<<endl;
            //outfile<<"    assign z["<<x_2+fulladder<<"] = mult_laststage_cout"<<fulladder-1<<" ^ ( sq_input["<<x_1-1<<"] & sq_input["<<x_2-1<<"] ) ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
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
  outfile<<"endmodule"<<endl;
}

void squareAddition(int x)
//The gate level Verilog HDL code for circuit-(a+b)
{
    x--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp1_";
    int fileint=x+1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"    assign adder_and0 = x[0] & 1'b1 ;"<<endl;
    outfile<<"    assign adder_add_cout[0] = adder_and0;"<<endl;
    outfile<<"    assign sq_input[0] = x[0] ^ 1'b1;"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            outfile<<"    assign adder_and"<<3*i-2<<" = adder_add_cout["<<i-1<<"] & x["<<i<<"];"<<endl;
            outfile<<"    assign adder_and"<<3*i-1<<" = adder_add_cout["<<i-1<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder_and"<<3*i<<" = x["<<i<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder_or"<<i<<" = adder_and"<<3*i-2<<" | "<<"adder_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder_add_cout["<<i<<"] = adder_or"<<i<<" | ""adder_and"<<3*i<<";"<<endl;
            
            outfile<<"    assign adder_xor"<<i<<" = x["<<i<<"] ^ 1'b0;"<<endl;
            outfile<<"    assign sq_input["<<i<<"] = adder_xor"<<i<<" ^ "<<"adder_add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            outfile<<"    assign adder_and"<<3*i-2<<" = adder_add_cout["<<i-1<<"] & x["<<i<<"];"<<endl;
            outfile<<"    assign adder_and"<<3*i-1<<" = adder_add_cout["<<i-1<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder_and"<<3*i<<" = x["<<i<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder_or"<<i<<" = adder_and"<<3*i-2<<" | "<<"adder_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign sq_input["<<i+1<<"] = adder_or"<<i<<" | adder_and"<<3*i<<";"<<endl;
            outfile<<"    assign adder_xor"<<i<<" = x["<<i<<"] ^ 1'b0;"<<endl;
            outfile<<"    assign sq_input["<<i<<"] = adder_xor"<<i<<" ^ "<<"adder_add_cout["<<i-1<<"];"<<endl;
        }
    }

}
void EntierMultiplierGen(int bit1,int bit2)
{
  
    sq_mult1(bit1, bit2);
    sq_mult2(bit1, bit2);
    sq_mult3(bit1,bit2);
}

void BenchGenSquare::datapathAddSquare(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp1_";
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
    outfile<<"module datapathAddSquare"<<x<<"Bits"<<"(x,z);"<<endl;
    outfile<<"  input ["<<x-1<<":0] x;"<<endl;
    outfile<<"  output ["<<2*x+1<<":0] z;"<<endl;
    outfile<<"  wire ["<<2*x+1<<":0] z;"<<endl;
    outfile<<"  wire ["<<x+1<<":0] sq_input;"<<endl;
    outfile<<"  wire ["<<x-1<<":0] adder_add_cout;"<<endl;
    squareAddition(x);
    EntierMultiplierGen(x+1,x+1);
  
}

void squareAdd1(int x)
//The gate level Verilog HDL code for circuit-(a+b)
{
    x--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp2_";
    int fileint=x+1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"    assign adder_and0 = x[0] & 1'b1 ;"<<endl;
    outfile<<"    assign adder_add_cout[0] = adder_and0;"<<endl;
    outfile<<"    assign mult_in_1[0] = x[0] ^ 1'b1;"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            outfile<<"    assign adder_and"<<3*i-2<<" = adder_add_cout["<<i-1<<"] & x["<<i<<"];"<<endl;
            outfile<<"    assign adder_and"<<3*i-1<<" = adder_add_cout["<<i-1<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder_and"<<3*i<<" = x["<<i<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder_or"<<i<<" = adder_and"<<3*i-2<<" | "<<"adder_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder_add_cout["<<i<<"] = adder_or"<<i<<" | ""adder_and"<<3*i<<";"<<endl;
            
            outfile<<"    assign adder_xor"<<i<<" = x["<<i<<"] ^ 1'b0;"<<endl;
            outfile<<"    assign mult_in_1["<<i<<"] = adder_xor"<<i<<" ^ "<<"adder_add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            outfile<<"    assign adder_and"<<3*i-2<<" = adder_add_cout["<<i-1<<"] & x["<<i<<"];"<<endl;
            outfile<<"    assign adder_and"<<3*i-1<<" = adder_add_cout["<<i-1<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder_and"<<3*i<<" = x["<<i<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder_or"<<i<<" = adder_and"<<3*i-2<<" | "<<"adder_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign mult_in_1["<<i+1<<"] = adder_or"<<i<<" | adder_and"<<3*i<<";"<<endl;
            outfile<<"    assign adder_xor"<<i<<" = x["<<i<<"] ^ 1'b0;"<<endl;
            outfile<<"    assign mult_in_1["<<i<<"] = adder_xor"<<i<<" ^ "<<"adder_add_cout["<<i-1<<"];"<<endl;
        }
    }
}

void squareAdd2(int x)
//The gate level Verilog HDL code for circuit-(a+b)
{
    x--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp2_";
    int fileint=(x+1)/2;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"    assign adder2_and0 = sq_out[0] & 1'b1 ;"<<endl;
    outfile<<"    assign adder2_add_cout[0] = adder2_and0;"<<endl;
    outfile<<"    assign mult_in_2[0] = sq_out[0] ^ 1'b1;"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            outfile<<"    assign adder2_and"<<3*i-2<<" = adder2_add_cout["<<i-1<<"] & sq_out["<<i<<"];"<<endl;
            outfile<<"    assign adder2_and"<<3*i-1<<" = adder2_add_cout["<<i-1<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder2_and"<<3*i<<" = sq_out["<<i<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder2_or"<<i<<" = adder2_and"<<3*i-2<<" | "<<"adder2_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign adder2_add_cout["<<i<<"] = adder2_or"<<i<<" | ""adder2_and"<<3*i<<";"<<endl;
            
            outfile<<"    assign adder2_xor"<<i<<" = sq_out["<<i<<"] ^ 1'b0;"<<endl;
            outfile<<"    assign mult_in_2["<<i<<"] = adder2_xor"<<i<<" ^ "<<"adder2_add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            outfile<<"    assign adder2_and"<<3*i-2<<" = adder2_add_cout["<<i-1<<"] & sq_out["<<i<<"];"<<endl;
            outfile<<"    assign adder2_and"<<3*i-1<<" = adder2_add_cout["<<i-1<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder2_and"<<3*i<<" = sq_out["<<i<<"] & 1'b0;"<<endl;
            outfile<<"    assign adder2_or"<<i<<" = adder2_and"<<3*i-2<<" | "<<"adder2_and"<<3*i-1<<";"<<endl;
            outfile<<"    assign mult_in_2["<<i+1<<"] = adder2_or"<<i<<" | adder2_and"<<3*i<<";"<<endl;
            outfile<<"    assign adder2_xor"<<i<<" = sq_out["<<i<<"] ^ 1'b0;"<<endl;
            outfile<<"    assign mult_in_2["<<i<<"] = adder2_xor"<<i<<" ^ "<<"adder2_add_cout["<<i-1<<"];"<<endl;
        }
    }
}

void sqmult1(int x,int y)
//N+1 bits * N bits
{
    x--;
    y--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp2_";
    int fileint=x+1;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    int n=0;
    for (int i=0; i<=x; i++) {
        outfile<<"    assign mult_stage1"<<"_and"<<n<<" = x["<<i<<"] & x[0];"<<endl;
        n++;
        outfile<<"    assign mult_stage1"<<"_and"<<n<<" = x["<<i<<"] & x[1];"<<endl;
        n++;
    }
    outfile<<"    assign sq_out[0] = x[0] & x[0];"<<endl;
    // outfile<<"    assign mult_stage1_cout0 = mult_stage1_and0;"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            outfile<<"    assign mult_stage1_sum"<<i_add-1<<" = mult_stage1_and"<<2*i_add-1<<" ^ mult_stage1_and"<<2*i_add<<";"<<endl;
            outfile<<"    assign mult_stage1_cout"<<i_add-1<<" = mult_stage1_and"<<2*i_add-1<<" & mult_stage1_and"<<2*i_add<<";"<<endl;
            
        }
        else
        {
            outfile<<"    assign sq_out[1] = mult_stage1_and1 ^ mult_stage1_and2;"<<endl;
            outfile<<"    assign mult_stage1_cout"<<i_add-1<<" = mult_stage1_and"<<i_add<<" & mult_stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    outfile<<" /* This is the CSA multiplier first Stage.*/"<<endl;
}
//After first stage

void sqmult2(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp2_";
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
                // outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( x["<<fulladder<<"] & x["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (x["<<fulladder+1<<"] & x["<<stage2-1<<"]"<<" & x["<<fulladder<<"] & x["<<stage2<<"]) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & x["<<fulladder+1<<"] & x["<<stage2-1<<"]"<<");"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = x["<<fulladder<<"] & x["<<stage2<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = x["<<fulladder+1<<"] & x["<<stage2-1<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                
                
                //outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = ( x["<<fulladder<<"] & x["<<stage2<<"] ) ^ (x["<<fulladder+1<<"] & x["<<stage2-1<<"])"<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                //outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( x["<<fulladder<<"] & x["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & x["<<fulladder<<"] & x["<<stage2<<"]) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = x["<<fulladder<<"] & x["<<stage2<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign sq_out["<<stage2<<"] = ( x["<<fulladder<<"] & x["<<stage2<<"] ) ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign sq_out["<<stage2<<"] = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                //outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( x["<<fulladder<<"] & x["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & (x["<<fulladder<<"] & x["<<stage2<<"]) ) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = x["<<fulladder<<"] & x["<<stage2<<"];"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = ( x["<<fulladder<<"] & x["<<stage2<<"] ) ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
}

//Last stage of CSA Multiplier
void sqmult3(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp2_";
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
            outfile<<"    assign mult_last_cout"<<fulladder<<" = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign sq_out["<<x_2+fulladder<<"] = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            //outfile<<"    assign mult_last_cout"<<fulladder<<" = (x["<<x_1-1<<"] & x["<<x_2-1<<"]"<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | (x["<<x_1-1<<"] & x["<<x_1-1<<"] & mult_last_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_last_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign sq_out["<<x_2+x_1-1<<"] = mult_last_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            //outfile<<"    assign mult_last_cout"<<fulladder<<" = ( x["<<x_1-1<<"] & x["<<x_2-1<<"] & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | ( x["<<x_1-1<<"] & x["<<x_2-1<<"] & mult_last"<<"_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_last"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign mult_last_and"<<4*fulladder-3<<" = x["<<x_1-1<<"] & x["<<x_2-1<<"];"<<endl;
            outfile<<"    assign mult_last_and"<<4*fulladder-2<<" = mult_last_and"<<4*fulladder-3<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult_last_and"<<4*fulladder-1<<" = mult_last_and"<<4*fulladder-3<<" & mult_last"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_last_and"<<4*fulladder<<" = mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_last"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_last_or"<<fulladder<<" = mult_last_and"<<4*fulladder-2<<" | mult_last_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign mult_last_cout"<<fulladder<<" = mult_last_or"<<fulladder<<" | mult_last_and"<<4*fulladder<<";"<<endl;
            //outfile<<"    assign sq_out["<<x_2+fulladder<<"] = mult_last_cout"<<fulladder-1<<" ^ ( x["<<x_1-1<<"] & x["<<x_2-1<<"] ) ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult_last_xor"<<fulladder<<" = mult_last_cout"<<fulladder-1<<" ^ mult_last_and"<<4*fulladder-3<<";"<<endl;
            outfile<<"    assign sq_out["<<x_2+fulladder<<"] = mult_last_xor"<<fulladder<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            
            //outfile<<"    assign mult_last_cout"<<fulladder<<" = (mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | (mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_last"<<"_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_last"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign mult_last_and"<<4*fulladder-3<<" = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult_last_and"<<4*fulladder-2<<" = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_last"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_last_and"<<4*fulladder-1<<" = mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_last"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mult_last_or"<<fulladder<<" = mult_last_and"<<4*fulladder-3<<" | mult_last_and"<<4*fulladder-2<<";"<<endl;
            outfile<<"    assign mult_last_cout"<<fulladder<<" = mult_last_or"<<fulladder<<" | mult_last_and"<<4*fulladder-1<<";"<<endl;
            //outfile<<"    assign sq_out["<<x_2+fulladder<<"] = mult_last_cout"<<fulladder-1<<" ^ mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mult_last_xor"<<fulladder<<" = mult_last_cout"<<fulladder-1<<" ^ mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
            outfile<<"    assign sq_out["<<x_2+fulladder<<"] = mult_last_xor"<<fulladder<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            
            
        }
    }
}

void mult1sq(int x,int y)
//N+1 bits * N bits
{
    x--;
    y--;
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp2_";
    int fileint=x/2;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    int n=0;
    for (int i=0; i<=x; i++) {
        outfile<<"    assign sqmult_stage1"<<"_and"<<n<<" = mult_in_2["<<i<<"] & mult_in_1[0];"<<endl;
        n++;
        outfile<<"    assign sqmult_stage1"<<"_and"<<n<<" = mult_in_2["<<i<<"] & mult_in_1[1];"<<endl;
        n++;
    }
    outfile<<"    assign z[0] = mult_in_2[0] & mult_in_1[0];"<<endl;
    // outfile<<"    assign sqmult_stage1_cout0 = sqmult_stage1_and0;"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            outfile<<"    assign sqmult_stage1_sum"<<i_add-1<<" = sqmult_stage1_and"<<2*i_add-1<<" ^ sqmult_stage1_and"<<2*i_add<<";"<<endl;
            outfile<<"    assign sqmult_stage1_cout"<<i_add-1<<" = sqmult_stage1_and"<<2*i_add-1<<" & sqmult_stage1_and"<<2*i_add<<";"<<endl;
            
        }
        else
        {
            outfile<<"    assign z[1] = sqmult_stage1_and1 ^ sqmult_stage1_and2;"<<endl;
            outfile<<"    assign sqmult_stage1_cout"<<i_add-1<<" = sqmult_stage1_and"<<i_add<<" & sqmult_stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    outfile<<" /* This is the CSA multiplier first Stage.*/"<<endl;
}
//After first stage

void mult2sq(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp2_";
    int fileint=(x_1-1)/2;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //cout<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    for (int stage2=2; stage2<=x_2-1; stage2++) {
        for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
            
            if (fulladder==x_1-2) {
                // outfile<<"    assign sqmult_stage"<<stage2<<"_cout"<<fulladder<<" = ( mult_in_2["<<fulladder<<"] & mult_in_1["<<stage2<<"] & sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult_in_2["<<fulladder+1<<"] & mult_in_1["<<stage2-1<<"]"<<" & mult_in_2["<<fulladder<<"] & mult_in_1["<<stage2<<"]) | (sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_in_2["<<fulladder+1<<"] & mult_in_1["<<stage2-1<<"]"<<");"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = mult_in_2["<<fulladder<<"] & mult_in_1["<<stage2<<"];"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = mult_in_2["<<fulladder+1<<"] & mult_in_1["<<stage2-1<<"];"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_or"<<fulladder<<" = sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_cout"<<fulladder<<" = sqmult_stage"<<stage2<<"_or"<<fulladder<<" | sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                
                
                //outfile<<"    assign sqmult_stage"<<stage2<<"_sum"<<fulladder<<" = ( mult_in_2["<<fulladder<<"] & mult_in_1["<<stage2<<"] ) ^ (mult_in_2["<<fulladder+1<<"] & mult_in_1["<<stage2-1<<"])"<<" ^ sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_xor"<<fulladder<<" = sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ sqmult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_sum"<<fulladder<<" = sqmult_stage"<<stage2<<"_xor"<<fulladder<<" ^ sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                //outfile<<"    assign sqmult_stage"<<stage2<<"_cout"<<fulladder<<" = ( mult_in_2["<<fulladder<<"] & mult_in_1["<<stage2<<"] & sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (sqmult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & mult_in_2["<<fulladder<<"] & mult_in_1["<<stage2<<"]) | (sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<" & sqmult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = mult_in_2["<<fulladder<<"] & mult_in_1["<<stage2<<"];"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & sqmult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<" & sqmult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_or"<<fulladder<<" = sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_cout"<<fulladder<<" = sqmult_stage"<<stage2<<"_or"<<fulladder<<" | sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign z["<<stage2<<"] = ( mult_in_2["<<fulladder<<"] & mult_in_1["<<stage2<<"] ) ^ sqmult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_xor"<<fulladder<<" = sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign z["<<stage2<<"] = sqmult_stage"<<stage2<<"_xor"<<fulladder<<" ^ sqmult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                //outfile<<"    assign sqmult_stage"<<stage2<<"_cout"<<fulladder<<" = ( mult_in_2["<<fulladder<<"] & mult_in_1["<<stage2<<"] & sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (sqmult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & (mult_in_2["<<fulladder<<"] & mult_in_1["<<stage2<<"]) ) | (sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<" & sqmult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = mult_in_2["<<fulladder<<"] & mult_in_1["<<stage2<<"];"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & sqmult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<" & sqmult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_or"<<fulladder<<" = sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_cout"<<fulladder<<" = sqmult_stage"<<stage2<<"_or"<<fulladder<<" | sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //outfile<<"    assign sqmult_stage"<<stage2<<"_sum"<<fulladder<<" = ( mult_in_2["<<fulladder<<"] & mult_in_1["<<stage2<<"] ) ^ sqmult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_xor"<<fulladder<<" = sqmult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ sqmult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign sqmult_stage"<<stage2<<"_sum"<<fulladder<<" = sqmult_stage"<<stage2<<"_xor"<<fulladder<<" ^ sqmult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
}

//Last stage of CSA Multiplier
void mult3sq(int x_1,int x_2)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp2_";
    int fileint=(x_1-1)/2;
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
            outfile<<"    assign sqmult_last_cout"<<fulladder<<" = sqmult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign z["<<x_2+fulladder<<"] = sqmult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            //outfile<<"    assign sqmult_last_cout"<<fulladder<<" = (mult_in_2["<<x_1-1<<"] & mult_in_1["<<x_2-1<<"]"<<" & sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<") | (mult_in_2["<<x_1-1<<"] & mult_in_1["<<x_1-1<<"] & sqmult_last_cout"<<fulladder-1<<") | (sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<" & sqmult_last_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign z["<<x_2+x_1-1<<"] = sqmult_last_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            //outfile<<"    assign sqmult_last_cout"<<fulladder<<" = ( mult_in_2["<<x_1-1<<"] & mult_in_1["<<x_2-1<<"] & sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<") | ( mult_in_2["<<x_1-1<<"] & mult_in_1["<<x_2-1<<"] & sqmult_last"<<"_cout"<<fulladder-1<<") | (sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<" & sqmult_last"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign sqmult_last_and"<<4*fulladder-3<<" = mult_in_2["<<x_1-1<<"] & mult_in_1["<<x_2-1<<"];"<<endl;
            outfile<<"    assign sqmult_last_and"<<4*fulladder-2<<" = sqmult_last_and"<<4*fulladder-3<<" & sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign sqmult_last_and"<<4*fulladder-1<<" = sqmult_last_and"<<4*fulladder-3<<" & sqmult_last"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign sqmult_last_and"<<4*fulladder<<" = sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<" & sqmult_last"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign sqmult_last_or"<<fulladder<<" = sqmult_last_and"<<4*fulladder-2<<" | sqmult_last_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign sqmult_last_cout"<<fulladder<<" = sqmult_last_or"<<fulladder<<" | sqmult_last_and"<<4*fulladder<<";"<<endl;
            //outfile<<"    assign z["<<x_2+fulladder<<"] = sqmult_last_cout"<<fulladder-1<<" ^ ( mult_in_2["<<x_1-1<<"] & mult_in_1["<<x_2-1<<"] ) ^ sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign sqmult_last_xor"<<fulladder<<" = sqmult_last_cout"<<fulladder-1<<" ^ sqmult_last_and"<<4*fulladder-3<<";"<<endl;
            outfile<<"    assign z["<<x_2+fulladder<<"] = sqmult_last_xor"<<fulladder<<" ^ sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            
            //outfile<<"    assign sqmult_last_cout"<<fulladder<<" = (sqmult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<") | (sqmult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & sqmult_last"<<"_cout"<<fulladder-1<<") | (sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<" & sqmult_last"<<"_cout"<<fulladder-1<<");"<<endl;
            outfile<<"    assign sqmult_last_and"<<4*fulladder-3<<" = sqmult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign sqmult_last_and"<<4*fulladder-2<<" = sqmult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & sqmult_last"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign sqmult_last_and"<<4*fulladder-1<<" = sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<" & sqmult_last"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign sqmult_last_or"<<fulladder<<" = sqmult_last_and"<<4*fulladder-3<<" | sqmult_last_and"<<4*fulladder-2<<";"<<endl;
            outfile<<"    assign sqmult_last_cout"<<fulladder<<" = sqmult_last_or"<<fulladder<<" | sqmult_last_and"<<4*fulladder-1<<";"<<endl;
            //outfile<<"    assign z["<<x_2+fulladder<<"] = sqmult_last_cout"<<fulladder-1<<" ^ sqmult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign sqmult_last_xor"<<fulladder<<" = sqmult_last_cout"<<fulladder-1<<" ^ sqmult_stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
            outfile<<"    assign z["<<x_2+fulladder<<"] = sqmult_last_xor"<<fulladder<<" ^ sqmult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            
            
        }
    }
    outfile<<"endmodule"<<endl;
}
void BenchGenSquare::PowThreeSqMultiply(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="SQComp2_";
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
    outfile<<"module sqmultiply"<<x<<"Bits(x,z);"<<endl;
    outfile<<"  input ["<<x-1<<":0] x;"<<endl;
    outfile<<"  output ["<<3*x+1<<":0] z;"<<endl;
    outfile<<"  wire ["<<3*x+1<<":0] z;"<<endl;
    outfile<<"  wire ["<<x<<":0] mult_in1;"<<endl;
    outfile<<"  wire ["<<2*x<<":0] mult_in2;"<<endl;
    outfile<<"  wire ["<<2*x-1<<":0] sq_out;"<<endl;
    outfile<<"  wire ["<<x-2<<":0] adder_add_cout;"<<endl;
    outfile<<"  wire ["<<2*x-2<<":0] adder2_add_cout;"<<endl;
    squareAdd1(x);
    sqmult1(x, x);
    sqmult2(x, x);
    sqmult3(x, x);
    squareAdd2(2*x);
    mult1sq(2*x+1, x+1);
    mult2sq(2*x+1, x+1);
    mult3sq(2*x+1, x+1);

}
void BenchGenSquare::PowThreeSqMultiplyRTL(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGeneratedRTL/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="RTL_SQComp2_";
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
    outfile<<"module sqmultiply"<<x<<"Bits(x,z);"<<endl;
    outfile<<"  input ["<<x-1<<":0] x;"<<endl;
    outfile<<"  output ["<<3*x+1<<":0] z;"<<endl;
    outfile<<"		assign z=x*x*x+x*x+x+1;"<<endl; 
    outfile<<"endmodule"<<endl;




}

void BenchGenSquare::PowTwoSqMultiplyRTL(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGeneratedRTL/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="RTL_SQComp1_";
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
    outfile<<"module sq_comp1RTL"<<x<<"Bits(x,z);"<<endl;
    outfile<<"  input ["<<x-1<<":0] x;"<<endl;
    outfile<<"  output ["<<2*x+1<<":0] z;"<<endl;
    outfile<<"   	assign z=x*x+2*x+1;"<<endl; 
    outfile<<"endmodule"<<endl;

}

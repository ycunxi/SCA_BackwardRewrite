//
//  BenchGen-MultiAccum.cpp
//  Tools
//
//  Created by Cunxi Yu on 7/14/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include "BenchGen-MultiAccum.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sstream>
using namespace std;

void MAmultiplierCSAstage1(int x,int y)
//N+1 bits * N bits
{
    x--;
    y--;
    /*
     cout<<"module CSAMultiplier(a,b,z);"<<endl;
     cout<<" input ["<<x<<":0] a;"<<endl;
     cout<<" input ["<<y<<":0] b;"<<endl;
     cout<<" output ["<<x+y+1<<":0] z;"<<endl;
     cout<<" wire ["<<x+y+1<<":0] z;"<<endl;  */
    int n=0;
    for (int i=0; i<=x; i++) {
        cout<<"    assign mult_stage1"<<"_and"<<n<<" = a["<<i<<"] & b[0];"<<endl;
        n++;
        cout<<"    assign mult_stage1"<<"_and"<<n<<" = a["<<i<<"] & b[1];"<<endl;
        n++;
    }
    cout<<"    assign z_multiply[0] = a[0] & b[0];"<<endl;
    // cout<<"    assign mult_stage1_cout0 = mult_stage1_and0;"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            cout<<"    assign mult_stage1_sum"<<i_add-1<<" = mult_stage1_and"<<2*i_add-1<<" ^ mult_stage1_and"<<2*i_add<<";"<<endl;
            cout<<"    assign mult_stage1_cout"<<i_add-1<<" = mult_stage1_and"<<2*i_add-1<<" & mult_stage1_and"<<2*i_add<<";"<<endl;
            
        }
        else
        {
            cout<<"    assign z_multiply[1] = mult_stage1_and1 ^ mult_stage1_and2;"<<endl;
            cout<<"    assign mult_stage1_cout"<<i_add-1<<" = mult_stage1_and"<<i_add<<" & mult_stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    cout<<" /* This is the CSA multiplier first Stage.*/"<<endl;
}
//After first stage

void MAmultiplierCSAstage2(int x_1,int x_2)
{
    for (int stage2=2; stage2<=x_2-1; stage2++) {
        for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
            
            if (fulladder==x_1-2) {
                cout<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( a["<<fulladder<<"] & b["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (a["<<fulladder+1<<"] & b["<<stage2-1<<"]"<<" & a["<<fulladder<<"] & b["<<stage2<<"]) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & a["<<fulladder+1<<"] & b["<<stage2-1<<"]"<<");"<<endl;
                cout<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = ( a["<<fulladder<<"] & b["<<stage2<<"] ) ^ (a["<<fulladder+1<<"] & b["<<stage2-1<<"])"<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                cout<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( a["<<fulladder<<"] & b["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & a["<<fulladder<<"] & b["<<stage2<<"]) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                cout<<"    assign z_multiply["<<stage2<<"] = ( a["<<fulladder<<"] & b["<<stage2<<"] ) ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            
            else
            {
                cout<<"    assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( a["<<fulladder<<"] & b["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & (a["<<fulladder<<"] & b["<<stage2<<"]) ) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                cout<<"    assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = ( a["<<fulladder<<"] & b["<<stage2<<"] ) ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            
        }
    }
    
}

//Last stage of CSA Multiplier
void MAmultiplierCSAlastStage(int x_1,int x_2)
{
    cout<<"/*This is the LAST stage for CSA multiplier.*/"<<endl;
    for (int fulladder=0; fulladder<=x_1-1; fulladder++) {
        if(fulladder==0)
        {
            cout<<"    assign mult_laststage_cout"<<fulladder<<" = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            cout<<"    assign z_multiply["<<x_2+fulladder<<"] = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            //cout<<"    assign mult_laststage_cout"<<fulladder<<" = (a["<<x_1-1<<"] & b["<<x_2-1<<"]"<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | (a["<<x_1-1<<"] & b["<<x_1-1<<"] & mult_laststage_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage_cout"<<fulladder-1<<");"<<endl;
            cout<<"    assign z_multiply["<<x_2+x_1-1<<"] = mult_laststage_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            cout<<"    assign mult_laststage_cout"<<fulladder<<" = ( a["<<x_1-1<<"] & b["<<x_2-1<<"] & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | ( a["<<x_1-1<<"] & b["<<x_2-1<<"] & mult_laststage"<<"_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            cout<<"    assign z_multiply["<<x_2+fulladder<<"] = mult_laststage_cout"<<fulladder-1<<" ^ ( a["<<x_1-1<<"] & b["<<x_2-1<<"] ) ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            
            cout<<"    assign mult_laststage_cout"<<fulladder<<" = (mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | (mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_laststage"<<"_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            cout<<"    assign z_multiply["<<x_2+fulladder<<"] = mult_laststage_cout"<<fulladder-1<<" ^ mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            
            
        }
    }
    //cout<<"endmodule"<<endl<<endl;
   // cout<<"/* This is verilog file of multiplier designed by BechGen software.*/"<<endl;
}
void MAarbitraryAdder(int x)
//The gate level Verilog HDL code for Addition(in1+in2)
{
    x=2*x-1;
    /*
     cout<<"module adder"<<x+1<<"Bits(a,b,adder_add_sum);"<<endl;
     cout<<" input ["<<x<<":0] a,b;"<<endl;
     cout<<" output ["<<x+1<<":0] adder_add_sum;"<<endl;
     cout<<" wire ["<<x+1<<":0] adder_add_sum;"<<endl;
     cout<<" wire ["<<x-1<<":0] adder_add_cout;"<<endl; */
    cout<<"    assign adder_and_0 = z_multiply[0] & z_old[0] ;"<<endl;
    cout<<"    assign adder_add_cout[0] = adder_and_0;"<<endl;
    cout<<"    assign z[0] = z_multiply[0] ^ z_old[0];"<<endl;
    for (int i=1; i<=x; i++) {
        if (i!=x) {
            
            
            cout<<"    assign adder_and_"<<3*i-2<<" = adder_add_cout["<<i-1<<"] & z_multiply["<<i<<"];"<<endl;
            cout<<"    assign adder_and_"<<3*i-1<<" = adder_add_cout["<<i-1<<"] & z_old["<<i<<"];"<<endl;
            cout<<"    assign adder_and_"<<3*i<<" = z_multiply["<<i<<"] & z_old["<<i<<"];"<<endl;
            cout<<"    assign adder_add_cout["<<i<<"] = adder_and_"<<3*i-2<<" | "<<"adder_and_"<<3*i-1<<" | "<<"adder_and_"<<3*i<<";"<<endl;
            cout<<"    assign z["<<i<<"] = z_multiply["<<i<<"] ^ z_old["<<i<<"] ^ "<<"adder_add_cout["<<i-1<<"];"<<endl;
        }
        else
        {
            cout<<"    assign adder_and_"<<3*i-2<<" = adder_add_cout["<<i-1<<"] & z_multiply["<<i<<"];"<<endl;
            cout<<"    assign adder_and_"<<3*i-1<<" = adder_add_cout["<<i-1<<"] & z_old["<<i<<"];"<<endl;
            cout<<"    assign adder_and_"<<3*i<<" = z_multiply["<<i<<"] & z_old["<<i<<"];"<<endl;
            cout<<"    assign z["<<i+1<<"] = adder_and_"<<3*i-2<<" | "<<"adder_and_"<<3*i-1<<" | "<<"adder_and_"<<3*i<<";"<<endl;
            cout<<"    assign z["<<i<<"] = z_multiply["<<i<<"] ^ z_old["<<i<<"] ^ "<<"adder_add_cout["<<i-1<<"];"<<endl;
        }
    }
    cout<<"endmodule"<<endl;
}
void Begin(int x)
{
    cout<<"/*This Verilog is generated by BechGen software.*/\n"
    "/*Designed by University of Massachusetts, Amherst, VLSI CAD LAB, Cunxi Yu*/\n"
    "/*/  Copyright (c) 2014 Cunxi Yu. All rights reserved. */ \n"
    "/* If you find any BUG,please Contact: ycunxi@umass.edu  Thank you!*/"<<endl;
    cout<<"module MultiplyAccum(a,b,z_old,z);"<<endl;
    cout<<"  input ["<<x<<":0] a,b;"<<endl;
    cout<<"  input ["<<2*x+1<<":0] z_old;"<<endl;
    cout<<"  wire ["<<2*x+1<<":0] z_multiply;"<<endl;
    cout<<"  wire ["<<2*x<<":0] adder_add_cout;"<<endl;
    cout<<"  output ["<<2*x+2<<":0] z;"<<endl;
}

void BenchGen_MultiAccum::MultiplyAccum(int bit1)
{
    Begin(bit1);
    MAmultiplierCSAstage1(bit1, bit1);
    MAmultiplierCSAstage2(bit1, bit1);
    MAmultiplierCSAlastStage(bit1,bit1);
    MAarbitraryAdder(bit1);
}
void BenchGen_MultiAccum::RTLMultilyAccum(int x)
{
    x--;
    cout<<"/*This Verilog is generated by BechGen software.*/\n"
    "/*Designed by University of Massachusetts, Amherst, VLSI CAD LAB, Cunxi Yu*/\n"
    "/*/  Copyright (c) 2014 Cunxi Yu. All rights reserved. */ \n"
    "/*Contact: ycunxi@umass.edu */"<<endl;

    cout<<"module RTLunsig_altmult_accum\n"
          "(\n";
    cout<<"         input ["<<x<<":0] dataa,datab,"<<endl;
    cout<<"         input clk,aclr,clken,sload,"<<endl;
    cout<<"         output reg ["<<2*x+1<<":0] adder_out"<<endl;
    cout<<");"<<endl;
    cout<<"     reg ["<<2*x+1<<":0] dataa_reg,datab_reg;"<<endl;
    cout<<"     reg sload_reg;"<<endl;
    cout<<"     reg ["<<2*x+1<<":0] old_result;"<<endl;
    cout<<"     wire ["<<2*x+1<<":0] multa;"<<endl;
    cout<<"     // Store the results of the operations on the current data\n"
	      "    assign multa = dataa_reg * datab_reg;\n"
	
	"       // Store the value of the accumulation (or clear it)\n"
	"       always @ (adder_out, sload_reg)\n"
	"       begin\n"
    "           if (sload_reg)\n"
    "               old_result <= 0;\n"
    "           else\n"
    "               old_result <= adder_out;\n"
	"       end\n"
	
	"           // Clear or update data, as appropriate\n"
	"           always @ (posedge clk or posedge aclr)\n"
	"           begin\n"
    "               if (aclr)\n"
    "                   begin\n"
    "                       dataa_reg <= 0;\n"
    "                       datab_reg <= 0;\n"
    "                       sload_reg <= 0;\n"
    "                       adder_out <= 0;\n"
    "                   end\n"
    "               else if (clken)\n"
    "                   begin\n"
    "                       dataa_reg <= dataa;\n"
    "                       datab_reg <= datab;\n"
    "                       sload_reg <= sload;\n"
    "                       adder_out <= old_result + multa;\n"
    "                   end\n"
	"               end\n"
    " endmodule\n"<<endl;

}
void lastlineofverilog(int x)
{
   string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Mult-AccumModel";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"endmodule"<<endl;
}


void MACaddition(int x,int clkcycle)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Mult-AccumModel";
    int fileint=x/2;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    x--;
    if (clkcycle==1) {

        outfile<<"    assign mac_add"<<clkcycle<<"_and0 = mac_multout"<<clkcycle<<"_[0] & initial"<<"_[0];"<<endl;
        outfile<<"    assign mac_add"<<clkcycle<<"_add_cout[0] = mac_add"<<clkcycle<<"_and0;"<<endl;
        outfile<<"    assign mac_add"<<clkcycle<<"_sum[0] = mac_multout"<<clkcycle<<"_[0] ^ initial"<<"_[0];"<<endl;
        for (int i=1; i<=x; i++) {
            if (i!=x) {
                if (i>=(x+1)/2) {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & initial"<<"_["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & initial"<<"_["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ initial"<<"_["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
            else
            {
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & 1'b0;"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i+1<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ 1'b0;"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
            }
        }
    }
     else
    {
        
        outfile<<"    assign mac_add"<<clkcycle<<"_and0 = mac_multout"<<clkcycle<<"_[0] & mac_add"<<clkcycle-1<<"_sum"<<"[0];"<<endl;
        outfile<<"    assign mac_add"<<clkcycle<<"_add_cout[0] = mac_add"<<clkcycle<<"_and0;"<<endl;
        outfile<<"    assign z[0] = mac_multout"<<clkcycle<<"_[0] ^ mac_add"<<clkcycle-1<<"_sum"<<"[0];"<<endl;
        for (int i=1; i<=x; i++) {
            if (i!=x) {
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                
                outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign z["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
            }
            else
            {
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                outfile<<"    assign z["<<i+1<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign z["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
            }
        }
    }
}



void MACmultiplier(int x,int clkcycle)
//N+1 bits * N bits
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Mult-AccumModel";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    x--;
   // int y=x-1;
  

        int n=0;
        for (int i=0; i<=x; i++) {
            outfile<<"    assign mac_mult_"<<clkcycle<<"stage1"<<"_and"<<n<<" = a"<<clkcycle<<"_["<<i<<"] & b"<<clkcycle<<"_[0];"<<endl;
            n++;
            outfile<<"    assign mac_mult_"<<clkcycle<<"stage1"<<"_and"<<n<<" = a"<<clkcycle<<"_["<<i<<"] & b"<<clkcycle<<"_[1];"<<endl;
            n++;
        }
        outfile<<"    assign mac_multout"<<clkcycle<<"_[0] = a"<<clkcycle<<"_[0] & b"<<clkcycle<<"_[0];"<<endl;
        for (int i_add=1; i_add<=x; i_add++) {
            if (i_add!=1) {
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage1_sum"<<i_add-1<<" = mac_mult_"<<clkcycle<<"stage1_and"<<2*i_add-1<<" ^ mac_mult_"<<clkcycle<<"stage1_and"<<2*i_add<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage1_cout"<<i_add-1<<" = mac_mult_"<<clkcycle<<"stage1_and"<<2*i_add-1<<" & mac_mult_"<<clkcycle<<"stage1_and"<<2*i_add<<";"<<endl;
                
            }
            else
            {
                outfile<<"    assign mac_multout"<<clkcycle<<"_[1] = mac_mult_"<<clkcycle<<"stage1_and1 ^ mac_mult_"<<clkcycle<<"stage1_and2;"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage1_cout"<<i_add-1<<" = mac_mult_"<<clkcycle<<"stage1_and"<<i_add<<" & mac_mult_"<<clkcycle<<"stage1_and"<<i_add+1<<";"<<endl;
            }
        }
        //outfile<<" /* This is the CSA multiplier first Stage.*/"<<endl;
        int x_1,x_2;
        x_1=x_2=x+1;
        for (int stage2=2; stage2<=x_2-1; stage2++) {
            for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
                
                if (fulladder==x_1-2) {
                    
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = a"<<clkcycle<<"_["<<fulladder<<"] & b"<<clkcycle<<"_["<<stage2<<"];"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = a"<<clkcycle<<"_["<<fulladder+1<<"] & b"<<clkcycle<<"_["<<stage2-1<<"];"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_sum"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                }
                else if(fulladder==0)
                {
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a"<<clkcycle<<"_["<<fulladder<<"] & b"<<clkcycle<<"_["<<stage2<<"];"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                    
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                    outfile<<"    assign mac_multout"<<clkcycle<<"_["<<stage2<<"] = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                    
                }
                
                else
                {
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a"<<clkcycle<<"_["<<fulladder<<"] & b"<<clkcycle<<"_["<<stage2<<"];"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                    outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_sum"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                    
                }
                
            }
        }
        
        outfile<<"/*This is the LAST stage for CSA multiplier.*/"<<endl;
        for (int fulladder=0; fulladder<=x_1-1; fulladder++) {
            if(fulladder==0)
            {
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mac_multout"<<clkcycle<<"_["<<x_2+fulladder<<"] = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if (fulladder==x_1-1)
            {
                outfile<<"    assign mac_multout"<<clkcycle<<"_["<<x_2+x_1-1<<"] = mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder-1<<";"<<endl;
            }
            else if(fulladder==x_1-2)
            {
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" = a"<<clkcycle<<"_["<<x_1-1<<"] & b"<<clkcycle<<"_["<<x_2-1<<"];"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-2<<" = mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" & mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-1<<" = mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" & mac_mult_"<<clkcycle<<"laststage"<<"_cout"<<fulladder-1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<" & mac_mult_"<<clkcycle<<"laststage"<<"_cout"<<fulladder-1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-2<<" | mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder-1<<" ^ mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<";"<<endl;
                outfile<<"    assign mac_multout"<<clkcycle<<"_["<<x_2+fulladder<<"] = mac_mult_"<<clkcycle<<"laststage_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else
            {
                
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-2<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mac_mult_"<<clkcycle<<"laststage"<<"_cout"<<fulladder-1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-1<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<" & mac_mult_"<<clkcycle<<"laststage"<<"_cout"<<fulladder-1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" | mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-2<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder-1<<" ^ mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mac_multout"<<clkcycle<<"_["<<x_2+fulladder<<"] = mac_mult_"<<clkcycle<<"laststage_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
                
                
            }
        }
}
    

void BenchGen_MultiAccum::MacModelGen(int x)
{
    
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Mult-AccumModel";
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
    outfile<<"module macModel(a1_,b1_,a2_,b2_,initial_,z);"<<endl;
    outfile<<" input ["<<x-1<<":0] a1_,b1_,a2_,b2_,initial_;"<<endl;
    outfile<<" output ["<<2*x+1<<":0] z;"<<endl;
    outfile<<" wire ["<<2*x<<":0] mac_add1_sum;"<<endl;
    outfile<<" wire ["<<2*x-2<<":0] mac_add1_add_cout;"<<endl;
    outfile<<" wire ["<<2*x<<":0] z;"<<endl;
    outfile<<" wire ["<<2*x-2<<":0] mac_add2_add_cout;"<<endl;
    outfile<<" wire ["<<2*x-1<<":0] mac_multout1_,mac_multout2_;"<<endl;
    
    MACmultiplier(x,1);
    MACaddition(2*x, 1);
   // outfile<<"fist addition"<<endl;
    MACmultiplier(x,2);
    MACaddition(2*x+1, 2);
    lastlineofverilog(x);

}


void MACaddition4Clock(int x,int clkcycle,int fbit)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Mult-AccumModel4Clock";
    int fileint=fbit;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    x--;
    if (clkcycle==1) {
        
        outfile<<"    assign mac_add"<<clkcycle<<"_and0 = mac_multout"<<clkcycle<<"_[0] & initial"<<"_[0];"<<endl;
        outfile<<"    assign mac_add"<<clkcycle<<"_add_cout[0] = mac_add"<<clkcycle<<"_and0;"<<endl;
        outfile<<"    assign mac_add"<<clkcycle<<"_sum[0] = mac_multout"<<clkcycle<<"_[0] ^ initial"<<"_[0];"<<endl;
        for (int i=1; i<=x; i++) {
            if (i!=x) {
                if (i>=fbit) {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & initial"<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & initial"<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ initial"<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
            else
            {
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & 1'b0;"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i+1<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ 1'b0;"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
            }
        }
    }
    else if(clkcycle==4)
    {
        
        outfile<<"    assign mac_add"<<clkcycle<<"_and0 = mac_multout"<<clkcycle<<"_[0] & mac_add"<<clkcycle-1<<"_sum"<<"[0];"<<endl;
        outfile<<"    assign mac_add"<<clkcycle<<"_add_cout[0] = mac_add"<<clkcycle<<"_and0;"<<endl;
        outfile<<"    assign z[0] = mac_multout"<<clkcycle<<"_[0] ^ mac_add"<<clkcycle-1<<"_sum"<<"[0];"<<endl;
        for (int i=1; i<=x; i++) {
            if (i!=x) {
                if(i<=2*fbit-1)
                {
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                
                outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign z["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = 1'b0 & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = 1'b0 ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign z["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
            else
            {
                if (i<=2*fbit-1) {
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                outfile<<"    assign z["<<i+1<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign z["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = 1'b0 & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign z["<<i+1<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = 1'b0 ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign z["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
        }
    }
    
    
    
    
    
    
    
    
    
    
    else
    {
        
        
        outfile<<"    assign mac_add"<<clkcycle<<"_and0 = mac_multout"<<clkcycle<<"_[0] & mac_add"<<clkcycle-1<<"_sum"<<"[0];"<<endl;
        outfile<<"    assign mac_add"<<clkcycle<<"_add_cout[0] = mac_add"<<clkcycle<<"_and0;"<<endl;
        outfile<<"    assign mac_add"<<clkcycle<<"_sum[0] = mac_multout"<<clkcycle<<"_[0] ^ mac_add"<<clkcycle-1<<"_sum"<<"[0];"<<endl;
        for (int i=1; i<=x; i++) {
            if (i!=x) {
                if(i<=2*fbit-1)
                {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = 1'b0 & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = 1'b0 ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
            else
            {
                if (i<=2*fbit-1) {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i+1<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = 1'b0 & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i+1<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = 1'b0 ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
        }
    }
}

void MACmultiplier4Clock(int x,int clkcycle,int fbit)
//N+1 bits * N bits
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Mult-AccumModel4Clock";
    int fileint=fbit;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    x--;
    // int y=x-1;
    
    
    int n=0;
    for (int i=0; i<=x; i++) {
        outfile<<"    assign mac_mult_"<<clkcycle<<"stage1"<<"_and"<<n<<" = a"<<clkcycle<<"_["<<i<<"] & b"<<clkcycle<<"_[0];"<<endl;
        n++;
        outfile<<"    assign mac_mult_"<<clkcycle<<"stage1"<<"_and"<<n<<" = a"<<clkcycle<<"_["<<i<<"] & b"<<clkcycle<<"_[1];"<<endl;
        n++;
    }
    outfile<<"    assign mac_multout"<<clkcycle<<"_[0] = a"<<clkcycle<<"_[0] & b"<<clkcycle<<"_[0];"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            outfile<<"    assign mac_mult_"<<clkcycle<<"stage1_sum"<<i_add-1<<" = mac_mult_"<<clkcycle<<"stage1_and"<<2*i_add-1<<" ^ mac_mult_"<<clkcycle<<"stage1_and"<<2*i_add<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"stage1_cout"<<i_add-1<<" = mac_mult_"<<clkcycle<<"stage1_and"<<2*i_add-1<<" & mac_mult_"<<clkcycle<<"stage1_and"<<2*i_add<<";"<<endl;
            
        }
        else
        {
            outfile<<"    assign mac_multout"<<clkcycle<<"_[1] = mac_mult_"<<clkcycle<<"stage1_and1 ^ mac_mult_"<<clkcycle<<"stage1_and2;"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"stage1_cout"<<i_add-1<<" = mac_mult_"<<clkcycle<<"stage1_and"<<i_add<<" & mac_mult_"<<clkcycle<<"stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    //outfile<<" /* This is the CSA multiplier first Stage.*/"<<endl;
    int x_1,x_2;
    x_1=x_2=x+1;
    for (int stage2=2; stage2<=x_2-1; stage2++) {
        for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
            
            if (fulladder==x_1-2) {
                
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = a"<<clkcycle<<"_["<<fulladder<<"] & b"<<clkcycle<<"_["<<stage2<<"];"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = a"<<clkcycle<<"_["<<fulladder+1<<"] & b"<<clkcycle<<"_["<<stage2-1<<"];"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_sum"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a"<<clkcycle<<"_["<<fulladder<<"] & b"<<clkcycle<<"_["<<stage2<<"];"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mac_multout"<<clkcycle<<"_["<<stage2<<"] = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a"<<clkcycle<<"_["<<fulladder<<"] & b"<<clkcycle<<"_["<<stage2<<"];"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_sum"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
    outfile<<"/*This is the LAST stage for CSA multiplier.*/"<<endl;
    for (int fulladder=0; fulladder<=x_1-1; fulladder++) {
        if(fulladder==0)
        {
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mac_multout"<<clkcycle<<"_["<<x_2+fulladder<<"] = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            outfile<<"    assign mac_multout"<<clkcycle<<"_["<<x_2+x_1-1<<"] = mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" = a"<<clkcycle<<"_["<<x_1-1<<"] & b"<<clkcycle<<"_["<<x_2-1<<"];"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-2<<" = mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" & mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-1<<" = mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" & mac_mult_"<<clkcycle<<"laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<" & mac_mult_"<<clkcycle<<"laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-2<<" | mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder-1<<" ^ mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<";"<<endl;
            outfile<<"    assign mac_multout"<<clkcycle<<"_["<<x_2+fulladder<<"] = mac_mult_"<<clkcycle<<"laststage_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-2<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mac_mult_"<<clkcycle<<"laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-1<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<" & mac_mult_"<<clkcycle<<"laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" | mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-2<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder-1<<" ^ mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
            outfile<<"    assign mac_multout"<<clkcycle<<"_["<<x_2+fulladder<<"] = mac_mult_"<<clkcycle<<"laststage_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            
            
        }
    }
}

void lastlineofverilog4ClockMAC(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Mult-AccumModel4Clock";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"endmodule"<<endl;
}

void BenchGen_MultiAccum::MacModelGen4Clock(int x)
{
    
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Mult-AccumModel4Clock";
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
    outfile<<"module macModel(a1_,b1_,a2_,b2_,a3_,b3_,a4_,b4_,initial_,z);"<<endl;
    outfile<<" input ["<<x-1<<":0] a1_,b1_,a2_,b2_,a3_,b3_,a4_,b4_,initial_;"<<endl;
    outfile<<" output ["<<2*x+3<<":0] z;"<<endl;
    outfile<<" wire ["<<2*x+3<<":0] z;"<<endl;
    outfile<<" wire ["<<2*x-2<<":0] mac_add1_add_cout;"<<endl;
    outfile<<" wire ["<<2*x<<":0] mac_add1_sum;"<<endl;
    outfile<<" wire ["<<2*x-1<<":0] mac_add2_add_cout;"<<endl;
    outfile<<" wire ["<<2*x+1<<":0] mac_add2_sum;"<<endl;
    outfile<<" wire ["<<2*x<<":0] mac_add3_add_cout;"<<endl;
    outfile<<" wire ["<<2*x+2<<":0] mac_add3_sum;"<<endl;
    outfile<<" wire ["<<2*x+1<<":0] mac_add4_add_cout;"<<endl;
    outfile<<" wire ["<<2*x-1<<":0] mac_multout1_,mac_multout2_,mac_multout3_,mac_multout4_;"<<endl;
    //clock1
    MACmultiplier4Clock(x,1,x);
    MACaddition4Clock(2*x, 1,x);
    //clock2
    MACmultiplier4Clock(x,2,x);
    MACaddition4Clock(2*x+1, 2,x);
    
    //clock3
    MACmultiplier4Clock(x,3,x);
    MACaddition4Clock(2*x+2, 3,x);
    //clock4
    MACmultiplier4Clock(x, 4,x);
    MACaddition4Clock(2*x+3, 4,x);
    lastlineofverilog4ClockMAC(x);
}


void MACaddition6Clock(int x,int clkcycle,int fbit)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Mult-AccumModel6Clock";
    int fileint=fbit;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    x--;
    if (clkcycle==1) {
        
        outfile<<"    assign mac_add"<<clkcycle<<"_and0 = mac_multout"<<clkcycle<<"_[0] & initial"<<"_[0];"<<endl;
        outfile<<"    assign mac_add"<<clkcycle<<"_add_cout[0] = mac_add"<<clkcycle<<"_and0;"<<endl;
        outfile<<"    assign mac_add"<<clkcycle<<"_sum[0] = mac_multout"<<clkcycle<<"_[0] ^ initial"<<"_[0];"<<endl;
        for (int i=1; i<=x; i++) {
            if (i!=x) {
                if (i>=fbit) {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & initial"<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & initial"<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ initial"<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
            else
            {
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & 1'b0;"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i+1<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ 1'b0;"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
            }
        }
    }
    else if(clkcycle==6)
    {
        
        outfile<<"    assign mac_add"<<clkcycle<<"_and0 = mac_multout"<<clkcycle<<"_[0] & mac_add"<<clkcycle-1<<"_sum"<<"[0];"<<endl;
        outfile<<"    assign mac_add"<<clkcycle<<"_add_cout[0] = mac_add"<<clkcycle<<"_and0;"<<endl;
        outfile<<"    assign z[0] = mac_multout"<<clkcycle<<"_[0] ^ mac_add"<<clkcycle-1<<"_sum"<<"[0];"<<endl;
        for (int i=1; i<=x; i++) {
            if (i!=x) {
                if(i<=2*fbit-1)
                {
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                
                outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign z["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = 1'b0 & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = 1'b0 ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign z["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
            else
            {
                if (i<=2*fbit-1) {
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                outfile<<"    assign z["<<i+1<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                outfile<<"    assign z["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = 1'b0 & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign z["<<i+1<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = 1'b0 ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign z["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
        }
    }
    
    
    
    
    
    
    
    
    
    
    else
    {
        
        
        outfile<<"    assign mac_add"<<clkcycle<<"_and0 = mac_multout"<<clkcycle<<"_[0] & mac_add"<<clkcycle-1<<"_sum"<<"[0];"<<endl;
        outfile<<"    assign mac_add"<<clkcycle<<"_add_cout[0] = mac_add"<<clkcycle<<"_and0;"<<endl;
        outfile<<"    assign mac_add"<<clkcycle<<"_sum[0] = mac_multout"<<clkcycle<<"_[0] ^ mac_add"<<clkcycle-1<<"_sum"<<"[0];"<<endl;
        for (int i=1; i<=x; i++) {
            if (i!=x) {
                if(i<=2*fbit-1)
                {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = 1'b0 & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_add_cout["<<i<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | ""mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = 1'b0 ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
            else
            {
                if (i<=2*fbit-1) {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_multout"<<clkcycle<<"_["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i+1<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = mac_multout"<<clkcycle<<"_["<<i<<"] ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-2<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i-1<<" = mac_add"<<clkcycle<<"_add_cout["<<i-1<<"] & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_and"<<3*i<<" = 1'b0 & mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_or"<<i<<" = mac_add"<<clkcycle<<"_and"<<3*i-2<<" | "<<"mac_add"<<clkcycle<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i+1<<"] = mac_add"<<clkcycle<<"_or"<<i<<" | mac_add"<<clkcycle<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_xor"<<i<<" = 1'b0 ^ mac_add"<<clkcycle-1<<"_sum"<<"["<<i<<"];"<<endl;
                    outfile<<"    assign mac_add"<<clkcycle<<"_sum["<<i<<"] = mac_add"<<clkcycle<<"_xor"<<i<<" ^ "<<"mac_add"<<clkcycle<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
        }
    }
}

void MACmultiplier6Clock(int x,int clkcycle,int fbit)
//N+1 bits * N bits
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Mult-AccumModel6Clock";
    int fileint=fbit;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    x--;
    // int y=x-1;
    
    
    int n=0;
    for (int i=0; i<=x; i++) {
        outfile<<"    assign mac_mult_"<<clkcycle<<"stage1"<<"_and"<<n<<" = a"<<clkcycle<<"_["<<i<<"] & b"<<clkcycle<<"_[0];"<<endl;
        n++;
        outfile<<"    assign mac_mult_"<<clkcycle<<"stage1"<<"_and"<<n<<" = a"<<clkcycle<<"_["<<i<<"] & b"<<clkcycle<<"_[1];"<<endl;
        n++;
    }
    outfile<<"    assign mac_multout"<<clkcycle<<"_[0] = a"<<clkcycle<<"_[0] & b"<<clkcycle<<"_[0];"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            outfile<<"    assign mac_mult_"<<clkcycle<<"stage1_sum"<<i_add-1<<" = mac_mult_"<<clkcycle<<"stage1_and"<<2*i_add-1<<" ^ mac_mult_"<<clkcycle<<"stage1_and"<<2*i_add<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"stage1_cout"<<i_add-1<<" = mac_mult_"<<clkcycle<<"stage1_and"<<2*i_add-1<<" & mac_mult_"<<clkcycle<<"stage1_and"<<2*i_add<<";"<<endl;
            
        }
        else
        {
            outfile<<"    assign mac_multout"<<clkcycle<<"_[1] = mac_mult_"<<clkcycle<<"stage1_and1 ^ mac_mult_"<<clkcycle<<"stage1_and2;"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"stage1_cout"<<i_add-1<<" = mac_mult_"<<clkcycle<<"stage1_and"<<i_add<<" & mac_mult_"<<clkcycle<<"stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    //outfile<<" /* This is the CSA multiplier first Stage.*/"<<endl;
    int x_1,x_2;
    x_1=x_2=x+1;
    for (int stage2=2; stage2<=x_2-1; stage2++) {
        for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
            
            if (fulladder==x_1-2) {
                
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = a"<<clkcycle<<"_["<<fulladder<<"] & b"<<clkcycle<<"_["<<stage2<<"];"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = a"<<clkcycle<<"_["<<fulladder+1<<"] & b"<<clkcycle<<"_["<<stage2-1<<"];"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_sum"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a"<<clkcycle<<"_["<<fulladder<<"] & b"<<clkcycle<<"_["<<stage2<<"];"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mac_multout"<<clkcycle<<"_["<<stage2<<"] = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a"<<clkcycle<<"_["<<fulladder<<"] & b"<<clkcycle<<"_["<<stage2<<"];"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<" & mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                outfile<<"    assign mac_mult_"<<clkcycle<<"stage"<<stage2<<"_sum"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<stage2<<"_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
    outfile<<"/*This is the LAST stage for CSA multiplier.*/"<<endl;
    for (int fulladder=0; fulladder<=x_1-1; fulladder++) {
        if(fulladder==0)
        {
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mac_multout"<<clkcycle<<"_["<<x_2+fulladder<<"] = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            outfile<<"    assign mac_multout"<<clkcycle<<"_["<<x_2+x_1-1<<"] = mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" = a"<<clkcycle<<"_["<<x_1-1<<"] & b"<<clkcycle<<"_["<<x_2-1<<"];"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-2<<" = mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" & mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-1<<" = mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" & mac_mult_"<<clkcycle<<"laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<" & mac_mult_"<<clkcycle<<"laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-2<<" | mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder-1<<" ^ mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<";"<<endl;
            outfile<<"    assign mac_multout"<<clkcycle<<"_["<<x_2+fulladder<<"] = mac_mult_"<<clkcycle<<"laststage_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-2<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mac_mult_"<<clkcycle<<"laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-1<<" = mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<" & mac_mult_"<<clkcycle<<"laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_or"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-3<<" | mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-2<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_or"<<fulladder<<" | mac_mult_"<<clkcycle<<"laststage_and"<<4*fulladder-1<<";"<<endl;
            outfile<<"    assign mac_mult_"<<clkcycle<<"laststage_xor"<<fulladder<<" = mac_mult_"<<clkcycle<<"laststage_cout"<<fulladder-1<<" ^ mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
            outfile<<"    assign mac_multout"<<clkcycle<<"_["<<x_2+fulladder<<"] = mac_mult_"<<clkcycle<<"laststage_xor"<<fulladder<<" ^ mac_mult_"<<clkcycle<<"stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            
            
        }
    }
}

void lastlineofverilog6ClockMAC(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Mult-AccumModel6Clock";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"endmodule"<<endl;
}

void BenchGen_MultiAccum::MacModelGen6Clock(int x)
{
    
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Mult-AccumModel6Clock";
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
    outfile<<"module macModel(a1_,b1_,a2_,b2_,a3_,b3_,a4_,b4_,a5_,b5_,a6_,b6_,initial_,z);"<<endl;
    outfile<<" input ["<<x-1<<":0] a1_,b1_,a2_,b2_,a3_,b3_,a4_,b4_,a5_,b5_,a6_,b6_,initial_;"<<endl;
    outfile<<" output ["<<2*x+5<<":0] z;"<<endl;
    outfile<<" wire ["<<2*x+5<<":0] z;"<<endl;
    outfile<<" wire ["<<2*x-2<<":0] mac_add1_add_cout;"<<endl;
    outfile<<" wire ["<<2*x<<":0] mac_add1_sum;"<<endl;
    outfile<<" wire ["<<2*x-1<<":0] mac_add2_add_cout;"<<endl;
    outfile<<" wire ["<<2*x+1<<":0] mac_add2_sum;"<<endl;
    outfile<<" wire ["<<2*x<<":0] mac_add3_add_cout;"<<endl;
    outfile<<" wire ["<<2*x+2<<":0] mac_add3_sum;"<<endl;
    outfile<<" wire ["<<2*x+1<<":0] mac_add4_add_cout;"<<endl;
    outfile<<" wire ["<<2*x+3<<":0] mac_add4_sum;"<<endl;
    outfile<<" wire ["<<2*x+2<<":0] mac_add5_add_cout;"<<endl;
    outfile<<" wire ["<<2*x+4<<":0] mac_add5_sum;"<<endl;
    outfile<<" wire ["<<2*x+3<<":0] mac_add6_add_cout;"<<endl;
    outfile<<" wire ["<<2*x-1<<":0] mac_multout1_,mac_multout2_,mac_multout3_,mac_multout4_,mac_multout5_,mac_multout6_;"<<endl;
    //clock1
    MACmultiplier6Clock(x,1,x);
    MACaddition6Clock(2*x, 1,x);
    //clock2
    MACmultiplier6Clock(x,2,x);
    MACaddition6Clock(2*x+1, 2,x);
    
    //clock3
    MACmultiplier6Clock(x,3,x);
    MACaddition6Clock(2*x+2, 3,x);
    //clock4
    MACmultiplier6Clock(x, 4,x);
    MACaddition6Clock(2*x+3, 4,x);

    //clock5
    MACmultiplier6Clock(x, 5,x);
    MACaddition6Clock(2*x+4, 5,x);
    //clock6
    MACmultiplier6Clock(x, 6,x);
    MACaddition6Clock(2*x+5, 6,x);
    lastlineofverilog6ClockMAC(x);
    
}





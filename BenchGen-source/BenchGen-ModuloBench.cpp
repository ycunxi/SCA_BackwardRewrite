//
//  BenchGen-ModuloBench.cpp
//  tranTO-ABC
//
//  Created by Cunxi Yu on 8/25/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include "BenchGen-ModuloBench.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
using namespace std;
// Shifter 1 bit / x mod 2
void shift1bit(int x,int num_shift)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Modulo4_";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    
    int num_and=1;
    for (int shiftonebit=x-1; shiftonebit>=0; shiftonebit--) {
        if (shiftonebit==x-1)
        {
            outfile<<"    assign shifter"<<num_shift<<"_and_"<<num_and<<" = 1'b0 & !s;"<<endl;
            outfile<<"    assign shifter"<<num_shift<<"_and_"<<num_and+1<<" = x["<<shiftonebit<<"] & s;"<<endl;
            outfile<<"    assign shifter"<<num_shift<<"_out["<<shiftonebit<<"] = shifter"<<num_shift<<"_and_"<<num_and<<" | shifter"<<num_shift<<"_and_"<<num_and+1<<";"<<endl;
            num_and=num_and+2;
        }
        else
        {
            outfile<<"    assign shifter"<<num_shift<<"_and_"<<num_and<<" = x["<<shiftonebit+1<<"] & !s;"<<endl;
            outfile<<"    assign shifter"<<num_shift<<"_and_"<<num_and+1<<" = x["<<shiftonebit<<"] & s;"<<endl;
            outfile<<"    assign shifter"<<num_shift<<"_out["<<shiftonebit<<"] = shifter"<<num_shift<<"_and_"<<num_and<<" | shifter"<<num_shift<<"_and_"<<num_and+1<<";"<<endl;
            num_and=num_and+2;
        }
    }
    
}
//Shifter right 2 bits/  x mod 4
void shift2bit(int x,int num_shift)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Modulo4_";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    int num_and=1;
    for (int shiftonebit=x-1; shiftonebit>=0; shiftonebit--) {
        if (shiftonebit==x-1 | shiftonebit==x-2)
        {
            outfile<<"    assign shifter"<<num_shift<<"_and_"<<num_and<<" = 1'b0 & !s;"<<endl;
            outfile<<"    assign shifter"<<num_shift<<"_and_"<<num_and+1<<" = x["<<shiftonebit<<"] & s;"<<endl;
            outfile<<"    assign shifter"<<num_shift<<"_out["<<shiftonebit<<"] = shifter"<<num_shift<<"_and_"<<num_and<<" | shifter"<<num_shift<<"_and_"<<num_and+1<<";"<<endl;
            num_and=num_and+2;
        }
        else
        {
            outfile<<"    assign shifter"<<num_shift<<"_and_"<<num_and<<" = x["<<shiftonebit+2<<"] & !s;"<<endl;
            outfile<<"    assign shifter"<<num_shift<<"_and_"<<num_and+1<<" = x["<<shiftonebit+1<<"] & s;"<<endl;
            outfile<<"    assign shifter"<<num_shift<<"_out["<<shiftonebit<<"] = shifter"<<num_shift<<"_and_"<<num_and<<" | shifter"<<num_shift<<"_and_"<<num_and+1<<";"<<endl;
            num_and=num_and+2;
        }
    }
    
}

void shift3bit(int x,int num_shift)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Modulo4_";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    int num_and=1;
    for (int shiftonebit=x-1; shiftonebit>=0; shiftonebit--) {
        if (shiftonebit==x-1 | shiftonebit==x-2 | shiftonebit==x-3)
        {
            outfile<<"    assign shifter"<<num_shift<<"_and_"<<num_and<<" = 1'b0 & !s;"<<endl;
            outfile<<"    assign shifter"<<num_shift<<"_and_"<<num_and+1<<" = x["<<shiftonebit<<"] & s;"<<endl;
            outfile<<"    assign shifter"<<num_shift<<"_out["<<shiftonebit<<"] = shifter"<<num_shift<<"_and_"<<num_and<<" | shifter"<<num_shift<<"_and_"<<num_and+1<<";"<<endl;
            num_and=num_and+2;
        }
        else
        {
            outfile<<"    assign shifter"<<num_shift<<"_and_"<<num_and<<" = x["<<shiftonebit+3<<"] & !s;"<<endl;
            outfile<<"    assign shifter"<<num_shift<<"_and_"<<num_and+1<<" = x["<<shiftonebit+2<<"] & s;"<<endl;
            outfile<<"    assign shifter"<<num_shift<<"_out["<<shiftonebit<<"] = shifter"<<num_shift<<"_and_"<<num_and<<" | shifter"<<num_shift<<"_and_"<<num_and+1<<";"<<endl;
            num_and=num_and+2;
        }
    }
    
}
void ModulorAdder(int x,int num_adder,int circuitbit)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Modulo4_";
    int fileint=circuitbit;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    x--;
    if (num_adder==1) {
        outfile<<"    assign adder"<<num_adder<<"_and0 = shifter"<<num_adder<<"_out[0] & x[0];"<<endl;
        outfile<<"    assign adder"<<num_adder<<"_add_cout[0] = adder"<<num_adder<<"_and0;"<<endl;
        outfile<<"    assign adder"<<num_adder<<"_add_sum[0] = shifter"<<num_adder<<"_out[0] ^ x[0];"<<endl;
        for (int i=1; i<=x; i++) {
            if (i!=x) {
                if (i<=circuitbit-1) {
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-2<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-1<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & x["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i<<" = shifter"<<num_adder<<"_out["<<i<<"] & x["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_or"<<i<<" = adder"<<num_adder<<"_and"<<3*i-2<<" | "<<"adder"<<num_adder<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_cout["<<i<<"] = adder"<<num_adder<<"_or"<<i<<" | ""adder"<<num_adder<<"_and"<<3*i<<";"<<endl;
                    
                    outfile<<"    assign adder"<<num_adder<<"_xor"<<i<<" = shifter"<<num_adder<<"_out["<<i<<"] ^ x["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_sum["<<i<<"] = adder"<<num_adder<<"_xor"<<i<<" ^ "<<"adder"<<num_adder<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-2<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-1<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & x["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i<<" = 1'b0 & x["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_or"<<i<<" = adder"<<num_adder<<"_and"<<3*i-2<<" | "<<"adder"<<num_adder<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_cout["<<i<<"] = adder"<<num_adder<<"_or"<<i<<" | ""adder"<<num_adder<<"_and"<<3*i<<";"<<endl;
                    
                    outfile<<"    assign adder"<<num_adder<<"_xor"<<i<<" = 1'b0 ^ x["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_sum["<<i<<"] = adder"<<num_adder<<"_xor"<<i<<" ^ "<<"adder"<<num_adder<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
            else
            {
                if (i<=circuitbit-1) {
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-2<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-1<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & x["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i<<" = shifter"<<num_adder<<"_out["<<i<<"] & x["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_or"<<i<<" = adder"<<num_adder<<"_and"<<3*i-2<<" | "<<"adder"<<num_adder<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_sum["<<i+1<<"] = adder"<<num_adder<<"_or"<<i<<" | adder"<<num_adder<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_xor"<<i<<" = shifter"<<num_adder<<"_out["<<i<<"] ^ x["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_sum["<<i<<"] = adder"<<num_adder<<"_xor"<<i<<" ^ "<<"adder"<<num_adder<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-2<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-1<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & x["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i<<" = 1'b0 & x["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_or"<<i<<" = adder"<<num_adder<<"_and"<<3*i-2<<" | "<<"adder"<<num_adder<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_sum["<<i+1<<"] = adder"<<num_adder<<"_or"<<i<<" | adder"<<num_adder<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_xor"<<i<<" = 1'b0 ^ x["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_sum["<<i<<"] = adder"<<num_adder<<"_xor"<<i<<" ^ "<<"adder"<<num_adder<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
        }
    }
    //ADDER 1 Inputs are all shifter's
    else if (num_adder!=3) {
        outfile<<"    assign adder"<<num_adder<<"_and0 = adder"<<num_adder-1<<"_add_sum[0] & shifter"<<num_adder<<"_out[0];"<<endl;
        outfile<<"    assign adder"<<num_adder<<"_add_cout[0] = adder"<<num_adder<<"_and0;"<<endl;
        outfile<<"    assign adder"<<num_adder<<"_add_sum[0] = adder"<<num_adder-1<<"_add_sum[0] ^ shifter"<<num_adder<<"_out[0];"<<endl;
        for (int i=1; i<=x; i++) {
            if (i!=x) {
                if (i<=circuitbit-1) {
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-2<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & adder"<<num_adder-1<<"_add_sum["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-1<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] & shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_or"<<i<<" = adder"<<num_adder<<"_and"<<3*i-2<<" | "<<"adder"<<num_adder<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_cout["<<i<<"] = adder"<<num_adder<<"_or"<<i<<" | ""adder"<<num_adder<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_xor"<<i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] ^ shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_sum["<<i<<"] = adder"<<num_adder<<"_xor"<<i<<" ^ "<<"adder"<<num_adder<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-2<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & adder"<<num_adder-1<<"_add_sum["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-1<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] & 1'b0;"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_or"<<i<<" = adder"<<num_adder<<"_and"<<3*i-2<<" | "<<"adder"<<num_adder<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_cout["<<i<<"] = adder"<<num_adder<<"_or"<<i<<" | ""adder"<<num_adder<<"_and"<<3*i<<";"<<endl;
                    
                    outfile<<"    assign adder"<<num_adder<<"_xor"<<i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] ^ 1'b0;"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_sum["<<i<<"] = adder"<<num_adder<<"_xor"<<i<<" ^ "<<"adder"<<num_adder<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
            else
            {
                if (i<=circuitbit-1) {
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-2<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & adder"<<num_adder-1<<"_add_sum["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-1<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] & shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_or"<<i<<" = adder"<<num_adder<<"_and"<<3*i-2<<" | "<<"adder"<<num_adder<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_sum["<<i+1<<"] = adder"<<num_adder<<"_or"<<i<<" | adder"<<num_adder<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_xor"<<i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] ^ shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_sum["<<i<<"] = adder"<<num_adder<<"_xor"<<i<<" ^ "<<"adder"<<num_adder<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-2<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & adder"<<num_adder-1<<"_add_sum["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-1<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] & 1'b0;"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_or"<<i<<" = adder"<<num_adder<<"_and"<<3*i-2<<" | "<<"adder"<<num_adder<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_sum["<<i+1<<"] = adder"<<num_adder<<"_or"<<i<<" | adder"<<num_adder<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_xor"<<i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] ^ 1'b0;"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_sum["<<i<<"] = adder"<<num_adder<<"_xor"<<i<<" ^ "<<"adder"<<num_adder<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
        }
    }
    //ADDER INPUTS are shifter & last adder
    else {
        outfile<<"    assign adder"<<num_adder<<"_and0 = adder"<<num_adder-1<<"_add_sum[0] & shifter"<<num_adder<<"_out[0];"<<endl;
        outfile<<"    assign adder"<<num_adder<<"_add_cout[0] = adder"<<num_adder<<"_and0;"<<endl;
        outfile<<"    assign z[0] = adder"<<num_adder-1<<"_add_sum[0] ^ shifter"<<num_adder<<"_out[0];"<<endl;
        for (int i=1; i<=x; i++) {
            if (i!=x) {
                if (i<=circuitbit-1) {
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-2<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & adder"<<num_adder-1<<"_add_sum["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-1<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] & shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_or"<<i<<" = adder"<<num_adder<<"_and"<<3*i-2<<" | "<<"adder"<<num_adder<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_cout["<<i<<"] = adder"<<num_adder<<"_or"<<i<<" | ""adder"<<num_adder<<"_and"<<3*i<<";"<<endl;
                    
                    outfile<<"    assign adder"<<num_adder<<"_xor"<<i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] ^ shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign z["<<i<<"] = adder"<<num_adder<<"_xor"<<i<<" ^ "<<"adder"<<num_adder<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-2<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & adder"<<num_adder-1<<"_add_sum["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-1<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] & 1'b0;"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_or"<<i<<" = adder"<<num_adder<<"_and"<<3*i-2<<" | "<<"adder"<<num_adder<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_add_cout["<<i<<"] = adder"<<num_adder<<"_or"<<i<<" | ""adder"<<num_adder<<"_and"<<3*i<<";"<<endl;
                    
                    outfile<<"    assign adder"<<num_adder<<"_xor"<<i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] ^ 1'b0;"<<endl;
                    outfile<<"    assign z["<<i<<"] = adder"<<num_adder<<"_xor"<<i<<" ^ "<<"adder"<<num_adder<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
            else
            {
                if (i<=circuitbit-1) {
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-2<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & adder"<<num_adder-1<<"_add_sum["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-1<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] & shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_or"<<i<<" = adder"<<num_adder<<"_and"<<3*i-2<<" | "<<"adder"<<num_adder<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign z["<<i+1<<"] = adder"<<num_adder<<"_or"<<i<<" | adder"<<num_adder<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_xor"<<i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] ^ shifter"<<num_adder<<"_out["<<i<<"];"<<endl;
                    outfile<<"    assign z["<<i<<"] = adder"<<num_adder<<"_xor"<<i<<" ^ "<<"adder"<<num_adder<<"_add_cout["<<i-1<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-2<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & adder"<<num_adder-1<<"_add_sum["<<i<<"];"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i-1<<" = adder"<<num_adder<<"_add_cout["<<i-1<<"] & 1'b0;"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_and"<<3*i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] & 1'b0;"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_or"<<i<<" = adder"<<num_adder<<"_and"<<3*i-2<<" | "<<"adder"<<num_adder<<"_and"<<3*i-1<<";"<<endl;
                    outfile<<"    assign z["<<i+1<<"] = adder"<<num_adder<<"_or"<<i<<" | adder"<<num_adder<<"_and"<<3*i<<";"<<endl;
                    outfile<<"    assign adder"<<num_adder<<"_xor"<<i<<" = adder"<<num_adder-1<<"_add_sum["<<i<<"] ^ 1'b0;"<<endl;
                    outfile<<"    assign z["<<i<<"] = adder"<<num_adder<<"_xor"<<i<<" ^ "<<"adder"<<num_adder<<"_add_cout["<<i-1<<"];"<<endl;
                }
            }
        }
    }
}

void endverilog(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Modulo4_";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename,ios::app);
    outfile<<"endmodule"<<endl;
}
void BenchGenModuloBench::MODBench(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Modulo4_";
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
    outfile<<"module MOD(x,z);"<<endl;
    outfile<<" input ["<<x-1<<":0] x;"<<endl;
    outfile<<" output ["<<x+2<<":0] z;"<<endl;
    outfile<<" wire ["<<x-1<<":0] shifter1_out,shifter2_out,shifter3_out;"<<endl;
    outfile<<" wire ["<<x<<":0] adder1_add_sum;"<<endl;
    outfile<<" wire ["<<x-2<<":0] adder1_add_cout;"<<endl;
    outfile<<" wire ["<<x+1<<":0] adder2_add_sum;"<<endl;
    outfile<<" wire ["<<x-1<<":0] adder2_add_cout;"<<endl;
    outfile<<" wire ["<<x+2<<":0] z;"<<endl;
    outfile<<" wire ["<<x<<":0] adder3_add_cout;"<<endl;
    outfile<<"    assign s=1'b0;"<<endl;
    shift1bit(x,1);
    shift2bit(x,2);
    shift3bit(x,3);
    ModulorAdder(x,1,x);
    ModulorAdder(x+1,2,x);
    ModulorAdder(x+2,3,x);
    endverilog(x);
    
}

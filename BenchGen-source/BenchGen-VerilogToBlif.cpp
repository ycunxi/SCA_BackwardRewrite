//
//  BenchGen-VerilogToBlif.cpp
//  多项式运算
//
//  Created by Cunxi Yu on 9/29/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include "BenchGen-VerilogToBlif.h"
//
//  main.cpp
//  find the same monomials
//
//  Created by Cunxi Yu on 3/3/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

string modulename(string input)
{
    string modulename;
    int module1,module2;
    module1=input.find("module",0);
    module2=input.find("(",0);
    modulename.assign(input,module1+6,module2-module1-6);
    modulename=".model "+modulename;
    return modulename;
}
string getridofspace(string input)
{
    int i;
    i=input.find(" ",0);
    while (i>=0) {
        input.erase(i,1);
        i=input.find(" ",0);
    }
    return input;
}

string getridofarray(string input)
{
    int i;
    i=input.find("[", 0);
    while (i>=0) {
        input.erase(i,1);
        i=input.find("[",0);
    }
    
    i=input.find("]", 0);
    while (i>=0) {
        input.erase(i,1);
        i=input.find("]",0);
    }
    
    i=input.find(";", 0);
    while (i>=0) {
        input.erase(i,1);
        i=input.find(";",0);
    }
    return input;
}

string inputdefine(string input)
{
    string inputdefine,in_bits,var_in1;
    int inputfind1,inputfind2,inputfind3,inputfind4,inputfind5,bit;
    inputfind1=input.find("input");
    inputfind3=input.find(":");
    inputfind4=input.find(";");
    inputfind5=input.find("0");
    var_in1.assign(input,inputfind5+1,input.size());
    in_bits.assign(input,inputfind1+5,inputfind3-inputfind1-5);
    istringstream num_bit(in_bits);
    num_bit >> bit;
    inputdefine=".inputs ";
    for (int in_define=0; in_define<=bit; in_define++) {
        stringstream in_define_int;
        in_define_int << in_define;
        string in_define_intstr=in_define_int.str();
        inputdefine=inputdefine+var_in1+in_define_intstr+" ";
    }
    return inputdefine;
}

string outputdefine(string input)
{
    string inputdefine,in_bits,var_in1;
    int inputfind1,inputfind2,inputfind3,inputfind4,inputfind5,bit;
    inputfind1=input.find("output");
    inputfind3=input.find(":");
    inputfind5=input.find("0");
    var_in1.assign(input,inputfind5+1,input.size());
    in_bits.assign(input,inputfind1+6,inputfind3-inputfind1-6);
    istringstream num_bit(in_bits);
    num_bit >> bit;
    inputdefine=".outputs ";
    for (int in_define=0; in_define<=bit; in_define++) {
        stringstream in_define_int;
        in_define_int << in_define;
        string in_define_intstr=in_define_int.str();
        inputdefine=inputdefine+var_in1+in_define_intstr+" ";
    }
    return inputdefine;
}

string verilog2blifAND(string input)
{
    string blifoutput,O,a,b;
    int findequal,findand,findassign;
    findequal=input.find("=");
    findand=input.find("&");
    O.assign(input,6,findequal-6);
    a.assign(input,findequal+1,findand-findequal-1);
    b.assign(input,findand+1,input.size());
    blifoutput=".gate and2  ";
    a="a="+a+" ";
    b="b="+b+" ";
    O="O="+O+" ";
    blifoutput=blifoutput+a+b+O;
    return blifoutput;
    
}

string verilog2blifXOR(string input)
{
    string blifoutput,O,a,b;
    int findequal,findand,findassign;
    findequal=input.find("=");
    findand=input.find("^");
    O.assign(input,6,findequal-6);
    a.assign(input,findequal+1,findand-findequal-1);
    b.assign(input,findand+1,input.size());
    blifoutput=".gate xor2  ";
    a="a="+a+" ";
    b="b="+b+" ";
    O="O="+O+" ";
    blifoutput=blifoutput+a+b+O;
    return blifoutput;
    
}
string verilog2blifOR(string input)
{
    string blifoutput,O,a,b;
    int findequal,findand,findassign;
    findequal=input.find("=");
    findand=input.find("|");
    O.assign(input,6,findequal-6);
    a.assign(input,findequal+1,findand-findequal-1);
    b.assign(input,findand+1,input.size());
    blifoutput=".gate or2  ";
    a="a="+a+" ";
    b="b="+b+" ";
    O="O="+O+" ";
    blifoutput=blifoutput+a+b+O;
    return blifoutput;
    
}
string verilogToblifINV(string input)
{
    string blifoutput,a,O;
    int findequal,findinv1,findinv2,findinv;
    findequal=input.find("=");
    findinv1=input.find("~");
    findinv2=input.find("!");
    findinv = findinv1+findinv2;
    O.assign(input,6,findequal-6);
    a.assign(input,findinv+1,input.size());
    blifoutput=".gate inv1 ";
    a="a="+a+" ";
    O="O="+O+" ";
    blifoutput=blifoutput+a+O;
    return blifoutput;
}

string verilogToblifwire(string input)
{
    string blifoutput,a,O;
    int findequal;
    findequal=input.find("=");
    O.assign(input,6,findequal-6);
    a.assign(input,findequal+1,input.size());
    blifoutput=".gate buf  ";
    a="a="+a+" ";
    O="O="+O+" ";
    blifoutput=blifoutput+a+O;
    return blifoutput;
}

void BenchGenVerilog2Blif::verilogToblif(std::string file)
{
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory;
    string finalinput=in_location+file;

    string extension=".blif";
    string fileout_directory="/VerilogToBlif/";
    string out_location=location+fileout_directory+file;
    string outputfilename=out_location+extension;
    int correctextension;
    correctextension=outputfilename.find(".v",0);
    outputfilename.erase(correctextension,2);
    ofstream outfile(outputfilename);

    ifstream fin(finalinput);
    string input,blifoutput;
    int findnamemodule,findand,findor,findxor,findinput,findoutput,findassign,findendmodule,findinverter,findinverter1;
    while (getline(fin,input)) {
        input=getridofspace(input);
        input=getridofarray(input);
        findand=input.find("&");
        findor=input.find("|");
        findxor=input.find("^");
        findinput=input.find("input");
        findoutput=input.find("output");
        findnamemodule=input.find("module");
        findassign=input.find("assign");
        findendmodule=input.find("endmodule");
        findinverter=input.find("~");
	findinverter1=input.find("!");
        if(findand>0)
        {
            blifoutput=verilog2blifAND(input);
		outfile<<blifoutput<<endl;
        }
        else if(findor>0)
        {
            blifoutput=verilog2blifOR(input);
		outfile<<blifoutput<<endl;
        }
        else if(findxor>0)
        {
            blifoutput=verilog2blifXOR(input);
		outfile<<blifoutput<<endl;
        }
        else if(findinput>=0)
        {
            blifoutput=inputdefine(input);
		outfile<<blifoutput<<endl;
        }
        else if(findoutput>=0)
        {
            blifoutput=outputdefine(input);
		outfile<<blifoutput<<endl;
        }
        else if(findnamemodule==0)
        {
            blifoutput=modulename(input);
		outfile<<blifoutput<<endl;
        }
        else if(findinverter>=0 or findinverter1>=0)
        {
            blifoutput=verilogToblifINV(input);
            outfile<<blifoutput<<endl;
        }
        else if(findassign>=0)
        {
            blifoutput=verilogToblifwire(input);
            outfile<<blifoutput<<endl;
        }
        else if(findendmodule>=0)
        {
            
        }
        else
        {
            //no match , no output
        }
    }
    outfile<<".end"<<endl;
}

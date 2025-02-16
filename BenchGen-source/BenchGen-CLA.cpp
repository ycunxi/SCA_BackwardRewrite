//
//  BenchGen-CLA.cpp
//  Tools
//
//  Created by Cunxi Yu on 7/23/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include "BenchGen-CLA.h"

#include <iostream>
#include <sstream> /* stringstream */
#include <string>
using namespace std;
void makeAnd(int sliver)
{
    cout << "//AND #" << sliver << endl;
    //These are named: and[sliver base is in]_[sliver placing this AND]
    //All base ANDS, the ones that don't have any inputs from other ANDs,\
    // are andX_X
    
    //All of the macro-ands we are representing have a G, a generate,
    // and a set of Ps, propagates.  G is called c0 for the first base.
    //The base has no propagates.
    
    //First, build your base AND, which is really just a buffer.
    cout << "wire and" << sliver << "_" << sliver << ";\n";
    cout << "assign and" << sliver << "_" << sliver << " = ";
    if(sliver == 0){
        cout << "cin";
    }
    else{
        cout << "g" << (sliver - 1);
    }
    cout << ";\n";
    
    //Next, properly add ands off of the current bases.
    for(int i = 0; i < sliver; i++){
        cout << "wire and" << i << "_" << sliver << ";\n";
        cout << "assign and" << i << "_" << sliver <<
        " = and" << i << "_" << (sliver - 1) <<
        " & p" << (sliver - 1) << ";\n";
    }
}

/*
 * Produces the OR associated with a given sliver.
 */
void makeOr(int sliver)
{
    //assign ca0(375) = nn0_1105 | nn0_1104;
    cout << "//OR\n";
    stringstream makerstream;
    makerstream << "and0_" << sliver;
    string orendname;
    makerstream >> orendname;
    string nextname;
    int bonussliver = sliver + 1;
    for(int i = 1; i < bonussliver; i++)
    {
        //Figure out what the next intermediate variable will be.
        makerstream.str("");
        makerstream.clear();
        makerstream << "insideor" << sliver << "_" << i;
        makerstream >> nextname;
        
        //Place the sub-or.
        cout << "wire " << nextname << ";\n";
        cout << "assign " << nextname << " = " << orendname << " | " << \
        "and" << i << "_" << sliver << ";\n";
        
        //Prepare for the next cycle.
        orendname = nextname;
    }
    
    //Buffer
    cout << "wire c" << sliver << ";\n";
    cout << "assign c" << sliver << " = " << orendname << ";\n\n";
}

/*
 * This makes a sliver of the adder associated with a certain sum output.
 * This includes the HA making the G and P, the lookahead generator,
 * and the final xor.
 */
void makeSliver(int sliver, bool lastSliver)
{
    cout << "//Sliver #" << sliver << endl;
    //Make the proper HA if this isn't the last sliver.
    if(!lastSliver){
        cout << "wire p" << sliver << ";\n";
        cout << "wire g" << sliver << ";\n";
        cout << "ha sum_" << sliver << \
        "(p" << sliver << ", a[" << sliver\
        << "], b[" << sliver << "], g" << sliver << ");\n";
    }
    
    //Build the ANDs of the lookahead.
    makeAnd(sliver);
    //Place the OR of the lookahead.
    makeOr(sliver);
    //Place that final xor or buffer after the lookahead
    cout << "assign ";
    if(lastSliver)
    {
        cout << "cout = c";
    }
    else
    {
        cout << "sum[" << sliver << "] = c" << sliver << " ^ p";
    }
    cout << sliver << ";\n\n\n";
}

void BenchGenCLA::carrylookahead(int x)
{
    //First, start with some basic header information.
    cout << "module cla" << x << "(a, b, cin, sum, cout);\n\n";
    cout << "// Here are our inputs:\n";
    cout << "input [" << (x - 1) << ":0] a;\n";
    cout << "input [" << (x - 1) << ":0] b;\n";
    cout << "input cin;\n";
    cout << "\n//Here is the sum:\n";
    cout << "output [" << (x-1) << ":0] sum;\n";
    cout << "output cout;\n\n\n\n";
    
    //Now go through and make a setup for each one of the inputs.
    //int subx = x - 1;
    for(int i = 0; i <= x; i++)
    {
        makeSliver(i, (i == x));
    }
    
    //This finishes the document.
    cout << "endmodule\n\n";
    cout << "module ha (sum, inp0, inp1, carry);\n";
    cout << "input inp0, inp1;\n";
    cout << "output sum, carry;\n";
    cout << "assign sum = inp0 ^ inp1;\n";
    cout << "assign carry = inp0 & inp1;\n";
    cout << "endmodule\n\n";
    cout << "//cla" << x << " is complete.  Thank you for using Genadd2!\n";

}

void claModel(int bit)
{
        cout<<"module cla(a,b,z);\n"
        "input ["<<bit-1<<":0] a,b;\n"
        "output ["<<bit<<":0] z;\n"
        "wire ["<<bit-1<<":0] p,g;\n"
        "wire ["<<bit<<":0] c;"<<endl;
        
    for (int i_p=0; i_p<=bit-1; i_p++) {
                cout<<"    assign g["<<i_p<<"] = a["<<i_p<<"] & b["<<i_p<<"] ;"<<endl;
                cout<<"    assign p["<<i_p<<"] = a["<<i_p<<"] ^ b["<<i_p<<"] ;"<<endl;
            
    }
    for (int i_c=1; i_c<=bit; i_c++) {
                if (i_c==1)
        {
                        cout<<"    assign c["<<i_c<<"] = g[0] ;"<<endl;
                    
        }
                else
        {
                        cout<<"    assign c["<<i_c<<"] = g["<<i_c-1<<"] | p["<<i_c-1<<"] & c["<<i_c-1<<"];"<<endl;
                    
        }
            
    }
    for (int i_s=0; i_s<bit; i_s++) {
                cout<<"    assign z["<<i_s<<"] = p["<<i_s<<"] ^ c["<<i_s<<"] ;"<<endl;
            
    }
        cout<<"    assign z["<<bit<<"] = c["<<bit<<"];"<<endl;
        cout<<"endmodule"<<endl;
        

}


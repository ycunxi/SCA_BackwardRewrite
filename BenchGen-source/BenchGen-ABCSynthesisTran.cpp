//
//  BenchGen-ABCSynthesisTran.cpp
//  多项式运算
//
//  Created by Cunxi Yu on 9/27/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include "BenchGen-ABCSynthesisTran.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
using namespace std;

//find inverter and parse to eqn format
string synthesisABCinv(string input)
{
    int findinv,inv_in1,inv_in2,inv_out1,inv_out2;
    string inv_in,inv_out;
    const string inverter="inv1";
    findinv=input.find(inverter,0);
    inv_in1 = input.find(".a",findinv);
    inv_in2 = input.find(")",inv_in1);
    inv_in.assign(input,inv_in1+3,inv_in2-inv_in1-3);
    inv_out1 = input.find(".O",inv_in2);
    inv_out2 = input.find(")",inv_out1);
    inv_out.assign(input,inv_out1+3,inv_out2-inv_out1-3);
    inv_in=inv_out+"="+"1-"+inv_in;
    return inv_in;
}

string synthesisABCnand2(string input)
{
    int nand2_in1,nand2_in2,nand2_in3,nand2_in4,nand2_out1,nand2_out2;
    int findnand2;
    const string nand2="nand2";
    findnand2=input.find(nand2,0);
    string nand2_innode1,nand2_innode2,nand2_outnode;
    nand2_in1 = input.find(".a",findnand2);
    nand2_in2 = input.find(")",nand2_in1);
    nand2_in3 = input.find(".b",nand2_in2);
    nand2_in4 = input.find(")",nand2_in3);
    nand2_innode1.assign(input,nand2_in1+3,nand2_in2-nand2_in1-3);
    nand2_innode2.assign(input,nand2_in3+3,nand2_in4-nand2_in3-3);
    nand2_out1 = input.find(".O",nand2_in4);
    nand2_out2 = input.find(")",nand2_out1);
    nand2_outnode.assign(input,nand2_out1+3,nand2_out2-nand2_out1-3);
    nand2_innode1=nand2_outnode+"="+"1-("+nand2_innode1+"*"+nand2_innode2+")";
    return nand2_innode1;
}
string synthesisABCnand3(string input)
{
    const string nand3="nand3";
    int findnand3=input.find(nand3,0);
    int nand3_in1,nand3_in2,nand3_in3,nand3_in4,nand3_in5,nand3_in6,nand3_out1,nand3_out2;
    string nand3_innode1,nand3_innode2,nand3_innode3,nand3_outnode;
    nand3_in1 = input.find(".a",findnand3);
    nand3_in2 = input.find(")",nand3_in1);
    nand3_in3 = input.find(".b",nand3_in2);
    nand3_in4 = input.find(")",nand3_in3);
    nand3_in5 = input.find(".c",nand3_in4);
    nand3_in6 = input.find(")",nand3_in5);
    nand3_out1 = input.find(".O",nand3_in6);
    nand3_out2 = input.find(")",nand3_out1);
    nand3_innode1.assign(input,nand3_in1+3,nand3_in2-nand3_in1-3);
    nand3_innode2.assign(input,nand3_in3+3,nand3_in4-nand3_in3-3);
    nand3_innode3.assign(input,nand3_in5+3,nand3_in6-nand3_in5-3);
    nand3_outnode.assign(input,nand3_out1+3,nand3_out2-nand3_out1-3);
    nand3_innode1=nand3_outnode+"="+"1+("+nand3_innode1+"*"+nand3_innode2+"*"+nand3_innode3+")";
    return nand3_innode1;
}
string synthesisABCnor2(string input)
{
    int nor2_in1,nor2_in2,nor2_in3,nor2_in4,nor2_out1,nor2_out2;
    string nor2_innode1,nor2_innode2,nor2_outnode;
    const string nor2="nor2";
    int findnor2=input.find(nor2,0);
    nor2_in1 = input.find(".a",findnor2);
    nor2_in2 = input.find(")",nor2_in1);
    nor2_in3 = input.find(".b",nor2_in2);
    nor2_in4 = input.find(")",nor2_in3);
    nor2_innode1.assign(input,nor2_in1+3,nor2_in2-nor2_in1-3);
    nor2_innode2.assign(input,nor2_in3+3,nor2_in4-nor2_in3-3);
    nor2_out1 = input.find(".O",nor2_in4);
    nor2_out2 = input.find(")",nor2_out1);
    nor2_outnode.assign(input,nor2_out1+3,nor2_out2-nor2_out1-3);
    nor2_innode1=nor2_outnode+" = 1 - ("+nor2_innode1+" + "+nor2_innode2+" - "+nor2_innode1+" * "+nor2_innode2+")";
    return nor2_innode1;
}

string synthesisABCnor3(string input)
{
    int nor3_in1,nor3_in2,nor3_in3,nor3_in4,nor3_in5,nor3_in6,nor3_out1,nor3_out2;
    string nor3_innode1,nor3_innode2,nor3_innode3,nor3_outnode;
    const string nor3="nor3";
    int findnor3=input.find(nor3,0);
    nor3_in1 = input.find(".a",findnor3);
    nor3_in2 = input.find(")",nor3_in1);
    nor3_in3 = input.find(".b",nor3_in2);
    nor3_in4 = input.find(")",nor3_in3);
    nor3_in5 = input.find(".c",nor3_in4);
    nor3_in6 = input.find(")",nor3_in5);
    nor3_out1 = input.find(".O",nor3_in6);
    nor3_out2 = input.find(")",nor3_out1);
    nor3_innode1.assign(input,nor3_in1+3,nor3_in2-nor3_in1-3);
    nor3_innode2.assign(input,nor3_in3+3,nor3_in4-nor3_in3-3);
    nor3_innode3.assign(input,nor3_in5+3,nor3_in6-nor3_in5-3);
    nor3_outnode.assign(input,nor3_out1+3,nor3_out2-nor3_out1-3);
    nor3_innode1=nor3_outnode+" = "+"1 + ("+nor3_innode1+" + "+nor3_innode2+" + "+nor3_innode3+" + "+nor3_innode1+" * "+nor3_innode2+" + "+nor3_innode1+" * "+nor3_innode3+" + "+nor3_innode2+" * "+nor3_innode3+" + "+nor3_innode1+"*"+nor3_innode2+"*"+nor3_innode3+")";
    return nor3_innode1;
}

string synthesisABCand2(string input)
{
    int and2_in1,and2_in2,and2_in3,and2_in4,and2_out1,and2_out2;
    string and2_innode1,and2_innode2,and2_outnode;
    const string and2="and2";
    int findand2=input.find(and2,0);
    and2_in1 = input.find(".a",findand2);
    and2_in2 = input.find(")",and2_in1);
    and2_in3 = input.find(".b",and2_in2);
    and2_in4 = input.find(")",and2_in3);
    and2_innode1.assign(input,and2_in1+3,and2_in2-and2_in1-3);
    and2_innode2.assign(input,and2_in3+3,and2_in4-and2_in3-3);
    and2_out1 = input.find(".O",and2_in4);
    and2_out2 = input.find(")",and2_out1);
    and2_outnode.assign(input,and2_out1+3,and2_out2-and2_out1-3);
    and2_innode1=and2_outnode+" = "+and2_innode1+" * "+and2_innode2;
    return and2_innode1;
}

string synthesisABCor2(string input)
{
    int or2_in1,or2_in2,or2_in3,or2_in4,or2_out1,or2_out2;
    string or2_innode1,or2_innode2,or2_outnode;
    const string or2="or2";
    int findor2=input.find(or2,0);
    or2_in1 = input.find(".a",findor2);
    or2_in2 = input.find(")",or2_in1);
    or2_in3 = input.find(".b",findor2);
    or2_in4 = input.find(")",or2_in3);
    or2_innode1.assign(input,or2_in1+3,or2_in2-or2_in1-3);
    or2_innode2.assign(input,or2_in3+3,or2_in4-or2_in3-3);
    or2_out1 = input.find(".O",findor2);
    or2_out2 = input.find(")",or2_out1);
    or2_outnode.assign(input,or2_out1+3,or2_out2-or2_out1-3);
    or2_innode1=or2_outnode+" = "+or2_innode1+" + "+or2_innode2+" - "+or2_innode1+"*"+or2_innode2;
    return or2_innode1;
}

string synthesisABCxor2(string input)
{
    int xor2_in1,xor2_in2,xor2_in3,xor2_in4,xor2_out1,xor2_out2;
    string xor2_innode1,xor2_innode2,xor2_outnode;
    const string xor2="xor2";
    int findxor2=input.find(xor2,0);
    xor2_in1 = input.find(".a",findxor2);
    xor2_in2 = input.find(")",xor2_in1);
    xor2_in3 = input.find(".b",findxor2);
    xor2_in4 = input.find(")",xor2_in3);
    xor2_innode1.assign(input,xor2_in1+3,xor2_in2-xor2_in1-3);
    xor2_innode2.assign(input,xor2_in3+3,xor2_in4-xor2_in3-3);
    xor2_out1 = input.find(".O",findxor2);
    xor2_out2 = input.find(")",xor2_out1);
    xor2_outnode.assign(input,xor2_out1+3,xor2_out2-xor2_out1-3);
    xor2_innode1=xor2_outnode+" = "+xor2_innode1+"+"+xor2_innode2 + " - 2 * "+xor2_innode1 + "*" + xor2_innode2;
    return xor2_innode1;
}

string synthesisABCxnor2(string input)
{
    int xnor2_in1,xnor2_in2,xnor2_in3,xnor2_in4,xnor2_out1,xnor2_out2;
    string xnor2_innode1,xnor2_innode2,xnor2_outnode;
    const string xnor2="xnor2";
    int findxnor2=input.find(xnor2,0);
    xnor2_in1 = input.find(".a",findxnor2);
    xnor2_in2 = input.find(")",xnor2_in1);
    xnor2_in3 = input.find(".b",findxnor2);
    xnor2_in4 = input.find(")",xnor2_in3);
    xnor2_innode1.assign(input,xnor2_in1+3,xnor2_in2-xnor2_in1-3);
    xnor2_innode2.assign(input,xnor2_in3+3,xnor2_in4-xnor2_in3-3);
    xnor2_out1 = input.find(".O",findxnor2);
    xnor2_out2 = input.find(")",xnor2_out1);
    xnor2_outnode.assign(input,xnor2_out1+3,xnor2_out2-xnor2_out1-3);
    xnor2_innode1=xnor2_outnode+" = 1+("+xnor2_innode1+"+"+xnor2_innode2+"+2*"+xnor2_innode1+"*"+xnor2_innode2+")";
    return xnor2_innode1;
}
string synthesisABCaoi21(string input)
{
    int aoib1_1,aoib1_2,aoib2_1,aoib2_2,aoia_1,aoia_2,aoiout1,aoiout2;
    string aoib1,aoib2,aoiout,aoia;
    const string aoi21="aoi21";
    int findaoi21=input.find(aoi21,0);
    aoib1_1 = input.find(".a",findaoi21);
    aoib1_2 = input.find(")",aoib1_1);
    aoib2_1 = input.find(".b",findaoi21);
    aoib2_2 = input.find(")",aoib2_1);
    aoia_1 = input.find(".c",findaoi21);
    aoia_2 = input.find(")",aoia_1);
    aoiout1 = input.find(".O",findaoi21);
    aoiout2 = input.find(")",aoiout1);
    aoib1.assign(input,aoib1_1+3,aoib1_2-aoib1_1-3);
    aoib2.assign(input,aoib2_1+3,aoib2_2-aoib2_1-3);
    aoia.assign(input,aoia_1+3,aoia_2-aoia_1-3);
    aoiout.assign(input,aoiout1+3,aoiout2-aoiout1-3);
    aoib1=aoiout+" = "+"1 + ("+aoia+"+"+aoib1+"*"+aoib2+"+"+aoia+"*"+aoib1+"*"+aoib2+")";
    return aoib1;
}

string synthesisABCaoi22(string input)
{
    int aoi22b1_1,aoi22b1_2,aoi22b2_1,aoi22b2_2,aoi22a1_1,aoi22a1_2,aoi22a2_1,aoi22a2_2,aoi22out1,aoi22out2;
    string aoi22b1,aoi22b2,aoi22out,aoi22a1,aoi22a2;
    const string aoi22="aoi22";
    int findaoi22=input.find(aoi22,0);
    aoi22b1_1 = input.find(".a",findaoi22);
    aoi22b1_2 = input.find(")",aoi22b1_1);
    aoi22b2_1 = input.find(".b",findaoi22);
    aoi22b2_2 = input.find(")",aoi22b2_1);
    aoi22a1_1 = input.find(".c",findaoi22);
    aoi22a1_2 = input.find(")",aoi22a1_1);
    aoi22a2_1 = input.find(".d",findaoi22);
    aoi22a2_2 = input.find(")",aoi22a2_1);
    aoi22a1.assign(input,aoi22a1_1+3,aoi22a1_2-aoi22a1_1-3);
    aoi22a2.assign(input,aoi22a2_1+3,aoi22a2_2-aoi22a2_1-3);
    aoi22b1.assign(input,aoi22b1_1+3,aoi22b1_2-aoi22b1_1-3);
    aoi22b2.assign(input,aoi22b2_1+3,aoi22b2_2-aoi22b2_1-3);
    aoi22out1 = input.find(".O",findaoi22);
    aoi22out2 = input.find(")",aoi22out1);
    aoi22out.assign(input,aoi22out1+4,aoi22out2-aoi22out1-4);
    aoi22b1=aoi22out+" = "+"1 + ("+aoi22a1+"*"+aoi22a2+"+"+aoi22b1+"*"+aoi22b2+"-"+aoi22a1+"*"+aoi22a2+"*"+aoi22b1+"*"+aoi22b2+")";
    return aoi22b1;
}

string synthesisABCoai21(string input)
{
    const string oai21="oai21";
    int oaib1_1,oaib1_2,oaib2_1,oaib2_2,oaia_1,oaia_2,oaiout1,oaiout2;
    string oaib1,oaib2,oaiout,oaia;
    int findoai21=input.find(oai21,0);
    oaib1_1 = input.find(".a",findoai21);
    oaib1_2 = input.find(")",oaib1_1);
    oaib2_1 = input.find(".b",oaib1_2);
    oaib2_2 = input.find(")",oaib2_1);
    oaia_1 = input.find(".c",oaib2_2);
    oaia_2 = input.find(")",oaia_1);
    oaiout1 = input.find(".O",oaia_2);
    oaiout2 = input.find(")",oaiout1);
    oaib1.assign(input,oaib1_1+3,oaib1_2-oaib1_1-3);
    oaib2.assign(input,oaib2_1+3,oaib2_2-oaib2_1-3);
    oaia.assign(input,oaia_1+3,oaia_2-oaia_1-3);
    oaiout.assign(input,oaiout1+3,oaiout2-oaiout1-3);
    oaib1=oaiout+" = 1 + ("+oaib1+" + "+oaib2+" + "+oaib1+"*"+oaib2+" ) * "+oaia;
    return oaib1;
    
}

string synthesisABCoai22(string input)
{
    int oai22b1_1,oai22b1_2,oai22b2_1,oai22b2_2,oai22a1_1,oai22a1_2,oai22a2_1,oai22a2_2,oai22out1,oai22out2;
    string oai22b1,oai22b2,oai22out,oai22a1,oai22a2;
    const string oai22="oai22";
    int findoai22=input.find(oai22,0);
    oai22b1_1 = input.find(".a",findoai22);
    oai22b1_2 = input.find(")",oai22b1_1);
    oai22b2_1 = input.find(".b",findoai22);
    oai22b2_2 = input.find(")",oai22b2_1);
    oai22a1_1 = input.find(".c",findoai22);
    oai22a1_2 = input.find(")",oai22a1_1);
    oai22a2_1 = input.find(".d",findoai22);
    oai22a2_2 = input.find(")",oai22a2_1);
    oai22a1.assign(input,oai22b1_1+3,oai22b1_2-oai22b1_1-3);
    oai22a2.assign(input,oai22b2_1+3,oai22b2_2-oai22b2_1-3);
    oai22b1.assign(input,oai22a1_1+3,oai22a1_2-oai22a1_1-3);
    oai22b2.assign(input,oai22a2_1+3,oai22b2_2-oai22b2_1-3);
    oai22out1 = input.find(".O",findoai22);
    oai22out2 = input.find(")",oai22out1);
    oai22out.assign(input,oai22out1+3,oai22out2-oai22out1-3);
    oai22b1=oai22out+"="+"1-("+oai22b1+"+"+oai22b2+"-"+oai22b1+"*"+oai22b2+")*("+oai22a1+"+"+oai22a2+"-"+oai22a1+"*"+oai22a2+")";
    return oai22b1;
}

//Split the complex gates into several simple gates (for example, AOI21=and(a,b,and)->or(and,c,or)-> inv(or,aoi21) )

void BenchGen_ABCSynthesisTran::ABCSynthesisTran(char file[50])
{
    string location(getcwd(NULL,0));
    //string filein_directory="/Mapped-Verilog/";
    string filein_directory;
    string in_location=location+filein_directory;
    string finalinput;
    finalinput=in_location+"/"+file;
    //cout<<"Input file path "<<finalinput<<endl;
    const string inv1="inv1";
    const string nand2="nand2";
    const string nand3="nand3";
    const string nor2="nor2";
    const string nor3="nor3";
    const string and2="and2";
    const string or21="or2";
    //const string or22="or2 g";
    const string xor2="xor2";
    const string xnor2="xnor2";
    const string aoi21="aoi21";
    const string aoi22="aoi22";
    const string oai21="oai21";
    const string oai22="oai22";
    const string empty="";
    int choice,findspace;
   // char file[50];
   // cout<<"Enter file name";
   // cin>>file;
    int findinv,findnand2,findnand3,findnor2,findnor3,findand2,findor2,findxor2,findxnor2,findaoi21,findaoi22,findoai21,findoai22,findor21;
    string input,eqnoutput;
    ifstream fin(finalinput.c_str());
    //output file define
    string fileoutput=file;
    string extension=".eqn";
    //string fileout_directory="/EqnFromVerilog/";
    string fileout_directory="/";
    string out_location=location+fileout_directory+"mapped-"+file;
    string outputfile=out_location+extension;
    int correctextension;
    correctextension=outputfile.find(".v",0);
    outputfile.erase(correctextension,2);
    //cout<<"Input file path "<<outputfile<<endl;
    ofstream outfile(outputfile.c_str());

    string key;
    while (getline(fin, input))
    {
	    findinv=input.find(inv1);
        findnand2=input.find(nand2);
        findnand3=input.find(nand3);
        findnor2=input.find(nor2);
        findnor3=input.find(nor3);
        findand2=input.find(and2);
        findor21=input.find(or21);
        findxor2=input.find(xor2);
        findxnor2=input.find(xnor2);
        findaoi21=input.find(aoi21);
        findaoi22=input.find(aoi22);
        findoai21=input.find(oai21);
        findoai22=input.find(oai22);
        if(input==empty)
        {
            continue;
        }
        else
        {
            if(findinv==2)
            {
                eqnoutput=synthesisABCinv(input);
                outfile<<eqnoutput<<endl;
            }
            else if(findnand2==2)
            {
                eqnoutput=synthesisABCnand2(input);
                outfile<<eqnoutput<<endl;
                
            }
            else if(findnand3==2)
            {
                eqnoutput=synthesisABCnand3(input);
                outfile<<eqnoutput<<endl;
            }
            else if(findand2==2)
            {
                eqnoutput=synthesisABCand2(input);
                outfile<<eqnoutput<<endl;
            }
            else if(findnor2==2)
            {
                eqnoutput=synthesisABCnor2(input);
                outfile<<eqnoutput<<endl;
            }
            else if(findnor3==2)
            {
                eqnoutput=synthesisABCnor3(input);
                outfile<<eqnoutput<<endl;
            }
            else if(findxor2==2)
            {
                eqnoutput=synthesisABCxor2(input);
                outfile<<eqnoutput<<endl;
            }
            else if(findxnor2==2)
            {
                eqnoutput=synthesisABCxnor2(input);
                outfile<<eqnoutput<<endl;
            }
            else if(findor21==2)
            {
                eqnoutput=synthesisABCor2(input);
                outfile<<eqnoutput<<endl;
            }
            else if(findaoi21==2)
            {
                eqnoutput=synthesisABCaoi21(input);
                outfile<<eqnoutput<<endl;
            }
            else if(findaoi22==2)
            {
                eqnoutput=synthesisABCaoi22(input);
                outfile<<eqnoutput<<endl;
            }
            else if(findoai21==2)
            {
                eqnoutput=synthesisABCoai21(input);
                outfile<<eqnoutput<<endl;
            }
            else if(findoai22==2)
            {
                eqnoutput=synthesisABCoai22(input);
                outfile<<eqnoutput<<endl;
            }
            else
            {
                //  outfile<<input<<endl;
            }
        }
    }
    string command = "tac "+outputfile+" > "+ finalinput+".eqn";
    string rm = "rm "+outputfile;
    system(command.c_str());
    system(rm.c_str());
    
}


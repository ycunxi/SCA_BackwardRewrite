//
//  BenchGen-DesginCompilerTran.cpp
//  tranTO-ABC
//
//  Created by Cunxi Yu on 9/1/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include "BenchGen-DesginCompilerTran.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

string dc_getridofspace(string input)
{
    int i;
    i=input.find(" ",0);
    while (i>=0) {
        input.erase(i,1);
        i=input.find(" ",0);
    }
    return input;
}

string dc_getridofarray(string input)
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


void BenchGenDCtran::unitlibtran(char filename[50])
{
    int findinv,findnor2,findnor3,findnor4,findnand2,findnand3,findnand4,findor2,findor4,findoai21,findoai22,findoai33,findmux,findxor2,findaoi21,findaoi22,findand2;
    
    const string INV="INV_X1";
    int inv_in1,inv_in2,inv_out1,inv_out2;
    string inv_in,inv_out;
    const string NOR2="NOR2_X1";
    int nor2_in1,nor2_in2,nor2_in3,nor2_in4,nor2_out1,nor2_out2;
    string nor2_innode1,nor2_innode2,nor2_outnode;
    const string NOR3="NOR3_X1";
    int nor3_in1,nor3_in2,nor3_in3,nor3_in4,nor3_in5,nor3_in6,nor3_out1,nor3_out2;
    string nor3_innode1,nor3_innode2,nor3_innode3,nor3_outnode;
    const string NOR4="NOR4_X1";
    const string NAND2="NAND2_X1";
    int nand2_in1,nand2_in2,nand2_in3,nand2_in4,nand2_out1,nand2_out2;
    string nand2_innode1,nand2_innode2,nand2_outnode;
    const string NAND3="NAND3_X1";
    int nand3_in1,nand3_in2,nand3_in3,nand3_in4,nand3_in5,nand3_in6,nand3_out1,nand3_out2;
    string nand3_innode1,nand3_innode2,nand3_innode3,nand3_outnode;
    const string NAND4="NAND4_X1";
    const string OR2="OR2_X1";
    int or2_in1,or2_in2,or2_in3,or2_in4,or2_out1,or2_out2;
    string or2_innode1,or2_innode2,or2_outnode;
    
    const string OR4="OR4_X1";
    
    
    const string AND2="AND2_X1";
    int and2_in1,and2_in2,and2_in3,and2_in4,and2_out1,and2_out2;
    string and2_innode1,and2_innode2,and2_outnode;

    
    const string OAI21="OAI21_X1";
    int oaib1_1,oaib1_2,oaib2_1,oaib2_2,oaia_1,oaia_2,oaiout1,oaiout2;
    string oaib1,oaib2,oaiout,oaia;
    //
    const string OAI22="OAI22_X1";
    int oai22b1_1,oai22b1_2,oai22b2_1,oai22b2_2,oai22a1_1,oai22a1_2,oai22a2_1,oai22a2_2,oai22out1,oai22out2;
    string oai22b1,oai22b2,oai22out,oai22a1,oai22a2;
    //
    const string OAI33="OAI33_X1";
    const string AOI21="AOI21_X1";
    int aoib1_1,aoib1_2,aoib2_1,aoib2_2,aoia_1,aoia_2,aoiout1,aoiout2;
    string aoib1,aoib2,aoiout,aoia;
    //
    const string AOI22="AOI22_X1";
    int aoi22b1_1,aoi22b1_2,aoi22b2_1,aoi22b2_2,aoi22a1_1,aoi22a1_2,aoi22a2_1,aoi22a2_2,aoi22out1,aoi22out2;
    string aoi22b1,aoi22b2,aoi22out,aoi22a1,aoi22a2;
    //MUX2
    const string MUX="MUX2_X1";
    int mux2_in1,mux2_in2,mux2_in3,mux2_in4,mux2_out1,mux2_out2,muxs1,muxs2;
    string mux2_innode1,mux2_innode2,mux2_outnode,mux2s;
    //XOR2
    const string XOR2="XOR2_X1";
    int xor2_in1,xor2_in2,xor2_in3,xor2_in4,xor2_out1,xor2_out2;
    string xor2_innode1,xor2_innode2,xor2_outnode;
    //gate name
    int function;
    //switch
    string gateoutput;
    //for ZNi
    //recognize the XOR / OR
    int findCapitalX;
    string input;
    string location(getcwd(NULL,0));
    string filein_directory="/dc_shell-Verilog/";
    string in_location=location+filein_directory;
    string finalinputname=in_location+filename;
    ifstream fin(finalinputname);
    cout<<finalinputname;
    string temp;
    while(getline(fin, input))
    {
    input = dc_getridofarray(input); 
    findor2=input.find(OR2,0);
    findCapitalX=input.find("X",0);
    findor4=input.find(OR4,0);
    findinv=input.find(INV,0);
    findnor2=input.find(NOR2,0);
    findnor3=input.find(NOR3,0);
    findnor4=input.find(NOR4,0);
    findnand2=input.find(NAND2,0);
    findnand3=input.find(NAND3,0);
    findnand4=input.find(NAND4,0);

    findand2=input.find(AND2,0);
    findoai21=input.find(OAI21,0);
    findoai22=input.find(OAI22,0);
    findoai33=input.find(OAI33,0);
    findaoi21=input.find(AOI21,0);
    findaoi22=input.find(AOI22,0);
    findmux=input.find(MUX,0);
    findxor2=input.find(XOR2,0);
    if (findinv>0) {
        function=1;
    }
    else if(findnor2>0)
    {
        function=2;
    }
    else if(findnor3>0)
    {
        function=3;
    }
    else if (findnor4>0)
    {
        function=4;
    }
    else if (findnand2>0)
    {
        function=5;
    }
    else if (findnand3>0)
    {
        function=6;
    }
    else if(findnand4>0)
    {
        function=7;
    }
    else if(findor2>0 && findCapitalX==-1)
    {
        function=8;
    }
    else if(findor4==2)
    {
        function=9;
    }
    else if (findand2>0)
    {
        function=10;
    }
    else if(findoai21>0)
    {
        function=11;
    }
    else if (findoai22>0)
    {
        function=12;
    }
    else if (findoai33>0)
    {
        function=13;
    }
    else if (findaoi21>0)
    {
        function=14;
    }
    else if (findaoi22>0)
    {
        function=15;
    }
    else if(findmux>0)
    {
        function=16;
    }
    else if (findxor2>0)
    {
        function=17;
    }
    else
    {
        function=18;
    }
    
    switch (function) {
        case 1:
            //invert gate replace
            inv_in1 = input.find(".A",findinv);
            inv_in2 = input.find(")",inv_in1);
            inv_in.assign(input,inv_in1+3,inv_in2-inv_in1-3);
            //cout<<inv_in<<endl;
            inv_out1 = input.find(".ZN",inv_in2);
            inv_out2 = input.find(")",inv_out1);
            inv_out.assign(input,inv_out1+4,inv_out2-inv_out1-4);
            //cout<<inv_out;
            cout<<inv_out<<" = "<<"1 - "<<inv_in<<endl;
            continue;
        case 2:
            //NOR2
            nor2_in1 = input.find(".A1",findnor2);
            nor2_in2 = input.find(")",nor2_in1);
            nor2_in3 = input.find(".A2",nor2_in2);
            nor2_in4 = input.find(")",nor2_in3);
            nor2_innode1.assign(input,nor2_in1+4,nor2_in2-nor2_in1-4);
            nor2_innode2.assign(input,nor2_in3+4,nor2_in4-nor2_in3-4);
            nor2_out1 = input.find(".ZN",nor2_in4);
            nor2_out2 = input.find(")",nor2_out1);
            nor2_outnode.assign(input,nor2_out1+4,nor2_out2-nor2_out1-4);

            cout<<nor2_outnode<<" = 1 - ("<<nor2_innode1<<" + "<<nor2_innode2<<" - "<<nor2_innode1<<" * "<<nor2_innode2<<")"<<endl;
            continue;
       
        case 3:
            //NOR3
            nor3_in1 = input.find(".A1",findnor3);
            nor3_in2 = input.find(")",nor3_in1);
            nor3_in3 = input.find(".A2",nor3_in2);
            nor3_in4 = input.find(")",nor3_in3);
            nor3_in5 = input.find(".A3",nor3_in4);
            nor3_in6 = input.find(")",nor3_in5);
            nor3_out1 = input.find(".ZN",nor3_in6);
            nor3_out2 = input.find(")",nor3_out1);
            nor3_innode1.assign(input,nor3_in1+4,nor3_in2-nor3_in1-4);
            nor3_innode2.assign(input,nor3_in3+4,nor3_in4-nor3_in3-4);
            nor3_innode3.assign(input,nor3_in5+4,nor3_in6-nor3_in5-4);
            nor3_outnode.assign(input,nor3_out1+4,nor3_out2-nor3_out1-4);
            cout<<nor3_outnode<<" = "<<"1 - ("<<nor3_innode1<<" + "<<nor3_innode2<<" + "<<nor3_innode3<<" - "<<nor3_innode1<<" * "<<nor3_innode2<<" - "<<nor3_innode1<<" * "<<nor3_innode3<<" - "<<nor3_innode2<<" * "<<nor3_innode3<<" + "<<nor3_innode1<<"*"<<nor3_innode2<<"*"<<nor3_innode3<<")"<<endl;
            continue;
            
        case 4:
            //NOR4
        case 5:
            //NAND2
            nand2_in1 = input.find(".A1",findnand2);
            nand2_in2 = input.find(")",nand2_in1);
            nand2_in3 = input.find(".A2",nand2_in2);
            nand2_in4 = input.find(")",nand2_in3);
            nand2_innode1.assign(input,nand2_in1+4,nand2_in2-nand2_in1-4);
            nand2_innode2.assign(input,nand2_in3+4,nand2_in4-nand2_in3-4);
            nand2_out1 = input.find(".ZN",nand2_in4);
            nand2_out2 = input.find(")",nand2_out1);
            nand2_outnode.assign(input,nand2_out1+4,nand2_out2-nand2_out1-4);
            cout<<nand2_outnode<<" = "<<"1 - ("<<nand2_innode1<<" * "<<nand2_innode2<<")"<<endl;
            continue;
        case 6:
            //NAND3
            nand3_in1 = input.find(".A1",findnand3);
            nand3_in2 = input.find(")",nand3_in1);
            nand3_in3 = input.find(".A2",nand3_in2);
            nand3_in4 = input.find(")",nand3_in3);
            nand3_in5 = input.find(".A3",nand3_in4);
            nand3_in6 = input.find(")",nand3_in5);
            nand3_out1 = input.find(".ZN",nand3_in6);
            nand3_out2 = input.find(")",nand3_out1);
            nand3_innode1.assign(input,nand3_in1+4,nand3_in2-nand3_in1-4);
            nand3_innode2.assign(input,nand3_in3+4,nand3_in4-nand3_in3-4);
            nand3_innode3.assign(input,nand3_in5+4,nand3_in6-nand3_in5-4);
            nand3_outnode.assign(input,nand3_out1+4,nand3_out2-nand3_out1-4);
            cout<<nand3_outnode<<" = "<<"1 - ("<<nand3_innode1<<" * "<<nand3_innode2<<" * "<<nand3_innode3<<")"<<endl;
            continue;
        case 7:
            //NAND4
        case 8:
            //OR2
        
            or2_in1 = input.find(".A1",findor2);
            or2_in2 = input.find(")",or2_in1);
            or2_in3 = input.find(".A2",findor2);
            or2_in4 = input.find(")",or2_in3);
            or2_innode1.assign(input,or2_in1+4,or2_in2-or2_in1-4);
            or2_innode2.assign(input,or2_in3+4,or2_in4-or2_in3-4);
            or2_out1 = input.find(".ZN",findor2);
            or2_out2 = input.find(")",or2_out1);
            or2_outnode.assign(input,or2_out1+4,or2_out2-or2_out1-4);
            cout<<or2_outnode<<" = "<<or2_innode1<<" + "<<or2_innode2<<" - "<<or2_innode1<<"*"<<or2_innode2<<endl;
            continue;
        case 9:
            //OR4
        case 10:
            //and2
            and2_in1 = input.find(".A1",findand2);
            and2_in2 = input.find(")",and2_in1);
            and2_in3 = input.find(".A2",and2_in2);
            and2_in4 = input.find(")",and2_in3);
            and2_innode1.assign(input,and2_in1+4,and2_in2-and2_in1-4);
            and2_innode2.assign(input,and2_in3+4,and2_in4-and2_in3-4);
            and2_out1 = input.find(".ZN",and2_in4);
            and2_out2 = input.find(")",and2_out1);
            and2_outnode.assign(input,and2_out1+4,and2_out2-and2_out1-4);
            cout<<and2_outnode<<" = "<<and2_innode1<<" * "<<and2_innode2<<endl;
            continue;
        case 11:
            //oai21
            oaib1_1 = input.find(".B1",findoai21);
            oaib1_2 = input.find(")",oaib1_1);
            oaib2_1 = input.find(".B2",oaib1_2);
            oaib2_2 = input.find(")",oaib2_1);
            oaia_1 = input.find(".A",oaib2_2);
            oaia_2 = input.find(")",oaia_1);
            oaiout1 = input.find(".ZN",oaia_2);
            oaiout2 = input.find(")",oaiout1);
            oaib1.assign(input,oaib1_1+4,oaib1_2-oaib1_1-4);
            oaib2.assign(input,oaib2_1+4,oaib2_2-oaib2_1-4);
            oaia.assign(input,oaia_1+3,oaia_2-oaia_1-3);
            oaiout.assign(input,oaiout1+4,oaiout2-oaiout1-4);
            cout<<oaiout<<" = 1 - ("<<oaib1<<" + "<<oaib2<<" - "<<oaib1<<"*"<<oaib2<<" ) * "<<oaia<<endl;
            continue;
            
            
            
            
        case 12:
            //OAI22
            oai22b1_1 = input.find(".B1",findoai22);
            oai22b1_2 = input.find(")",oai22b1_1);
            oai22b2_1 = input.find(".B2",findoai22);
            oai22b2_2 = input.find(")",oai22b2_1);
            oai22a1_1 = input.find(".A1",findoai22);
            oai22a1_2 = input.find(")",oai22a1_1);
            oai22a2_1 = input.find(".A2",findoai22);
            oai22a2_2 = input.find(")",oai22a2_1);
            oai22a1.assign(input,oai22a1_1+4,oai22a1_2-oai22a1_2-4);
            oai22a2.assign(input,oai22a2_1+4,oai22a2_2-oai22a2_2-4);
            oai22b1.assign(input,oai22b1_1+4,oai22b1_2-oai22b1_2-4);
            oai22b2.assign(input,oai22b2_1+4,oai22b2_2-oai22b2_2-4);
            oai22out1 = input.find(".ZN",findoai22);
            oai22out2 = input.find(")",oai22out1);
            oai22out.assign(input,oai22out1+4,oai22out2-oai22out2-4);
            continue;
            

        case 13:
            //OAI33
        case 14:
            //AOI21
            aoib1_1 = input.find(".B1",findaoi21);
            aoib1_2 = input.find(")",aoib1_1);
            aoib2_1 = input.find(".B2",findaoi21);
            aoib2_2 = input.find(")",aoib2_1);
            aoia_1 = input.find(".A",findaoi21);
            aoia_2 = input.find(")",aoia_1);
            aoiout1 = input.find(".ZN",findaoi21);
            aoiout2 = input.find(")",aoiout1);
            aoib1.assign(input,aoib1_1+4,aoib1_2-aoib1_1-4);
            aoib2.assign(input,aoib2_1+4,aoib2_2-aoib2_1-4);
            aoia.assign(input,aoia_1+3,aoia_2-aoia_1-3);
            aoiout.assign(input,aoiout1+4,aoiout2-aoiout1-4);
            cout<<aoiout<<" = "<<"1 - ("<<aoia<<"+"<<aoib1<<"*"<<aoib2<<"-"<<aoia<<"*"<<aoib1<<"*"<<aoib2<<")"<<endl;
            continue;
        case 15:
            //AOI22
            aoi22b1_1 = input.find(".B1",findaoi22);
            aoi22b1_2 = input.find(")",aoi22b1_1);
            aoi22b2_1 = input.find(".B2",findaoi22);
            aoi22b2_2 = input.find(")",aoi22b2_1);
            aoi22a1_1 = input.find(".A1",findaoi22);
            aoi22a1_2 = input.find(")",aoi22a1_1);
            aoi22a2_1 = input.find(".A2",findaoi22);
            aoi22a2_2 = input.find(")",aoi22a2_1);
            aoi22a1.assign(input,aoi22a1_1+4,aoi22a1_2-aoi22a1_1-4);
            aoi22a2.assign(input,aoi22a2_1+4,aoi22a2_2-aoi22a2_1-4);
            aoi22b1.assign(input,aoi22b1_1+4,aoi22b1_2-aoi22b1_1-4);
            aoi22b2.assign(input,aoi22b2_1+4,aoi22b2_2-aoi22b2_1-4);
            aoi22out1 = input.find(".ZN",findaoi22);
            aoi22out2 = input.find(")",aoi22out1);
            aoi22out.assign(input,aoi22out1+4,aoi22out2-aoi22out1-4);
            cout<<aoi22out<<" = "<<"1 - ("<<aoi22a1<<"*"<<aoi22a2<<"+"<<aoi22b1<<"*"<<aoi22b2<<"-"<<aoi22a1<<"*"<<aoi22a2<<"*"<<aoi22b1<<"*"<<aoi22b2<<")"<<endl;
            continue;
        case 16:
            //MUX2
            mux2_in1 = input.find(".A",findmux);
            mux2_in2 = input.find(")",mux2_in1);
            mux2_in3 = input.find(".B",findmux);
            mux2_in4 = input.find(")",mux2_in3);
            muxs1 = input.find(".S",findmux);
            muxs2 = input.find(")",muxs1);
            mux2_innode1.assign(input,mux2_in1+3,mux2_in2-mux2_in1-3);
            mux2_innode2.assign(input,mux2_in3+3,mux2_in4-mux2_in3-3);
            mux2s.assign(input,muxs1+3,muxs2-muxs1-3);
            mux2_out1 = input.find(".Z",findmux);
            mux2_out2 = input.find(")",mux2_out1);
            mux2_outnode.assign(input,mux2_out1+3,mux2_out2-mux2_out1-3);
            cout<<mux2_outnode<<" = "<<mux2_innode1<<"*(1-"<<mux2s<<")+"<<mux2_innode2<<"*"<<mux2s<<endl;
            continue;
        case 17:
            //XOR2
            xor2_in1 = input.find(".A",findxor2);
            xor2_in2 = input.find(")",xor2_in1);
            xor2_in3 = input.find(".B",findxor2);
            xor2_in4 = input.find(")",xor2_in3);
            xor2_innode1.assign(input,xor2_in1+3,xor2_in2-xor2_in1-3);
            xor2_innode2.assign(input,xor2_in3+3,xor2_in4-xor2_in3-3);
            xor2_out1 = input.find(".Z",findxor2);
            xor2_out2 = input.find(")",xor2_out1);
            xor2_outnode.assign(input,xor2_out1+3,xor2_out2-xor2_out1-3);
            cout<<xor2_outnode<<" = "<<xor2_innode1<<"+"<<xor2_innode2<<"-2*"<<xor2_innode1<<"*"<<xor2_innode2<<endl;
            continue;
        case 18:
            continue;

            
            
            
        default:
            continue;
    }
    }
  //  cout<<input;
}

int A1pos(string input)
{
    int a1pos;
    a1pos = input.find(".A1");
    return a1pos;
}
int A2pos(string input)
{
    int a2pos;
    a2pos = input.find(".A2");
    return a2pos;
}
int Ypos(string input)
{
    int ypos;
    ypos = input.find(".ZN");
    return ypos;
}
int Ainxorpos(string input)
{
    int a_inxorpos;
    a_inxorpos = input.find(".A",0);
    return a_inxorpos;
}
int Binxorpos(string input)
{
    int b_inxorpos;
    b_inxorpos = input.find(".B");
    return b_inxorpos;
}
int Zinxorpos(string input)
{
    int z_inxorpos;
    z_inxorpos = input.find(".Z");
    return z_inxorpos;
}
string tranBlifDCINVX1(string input)
{
    string and2blif;
    string a1var,a2var,yvar;
    int a1 = Ainxorpos(input);
    int a1_p1=input.find("(",a1);
    int a1_p2=input.find(")",a1_p1);
    a1var.assign(input,a1_p1+1,a1_p2-a1_p1-1);
    int y1 = Ypos(input);
    int y1_p1 = input.find("(",y1);
    int y1_p2 = input.find(")",y1_p1);
    yvar.assign(input,y1_p1+1,y1_p2-y1_p1-1);
    and2blif = ".gate inv1 a="+a1var+" O="+yvar+"\n";
    return and2blif;
}
string tranBlifDCXOR2X1(string input)
{
    string xor2blif;
    string a1var,a2var,yvar;
    int a1 = Ainxorpos(input);
    int a2 = Binxorpos(input);
    int a1_p1 = input.find("(",a1);
    int a1_p2 = input.find(")",a1_p1);
    a1var.assign(input,a1_p1+1,a1_p2-a1_p1-1);
    int a2_p1 = input.find("(",a2);
    int a2_p2 = input.find(")",a2_p1);
    a2var.assign(input,a2_p1+1,a2_p2-a2_p1-1);
    int y1 = Zinxorpos(input);
    int y1_p1 = input.find("(",y1);
    int y1_p2 = input.find(")",y1_p1);
    yvar.assign(input,y1_p1+1,y1_p2-y1_p1-1);
    xor2blif = ".gate xor2 a="+a1var+" b="+a2var+" O="+yvar+"\n";
    return xor2blif;
}
string tranBlifDCNOR2X1(string input)
{
    string nor2blif;
    string a1var,a2var,yvar;
    int a1 = A1pos(input);
    int a2 = A2pos(input);
    int a1_p1 = input.find("(",a1);
    int a1_p2 = input.find(")",a1_p1);
    a1var.assign(input,a1_p1+1,a1_p2-a1_p1-1);
    int a2_p1 = input.find("(",a2);
    int a2_p2 = input.find(")",a2_p1);
    a2var.assign(input,a2_p1+1,a2_p2-a2_p1-1);
    int y1 = Ypos(input);
    int y1_p1 = input.find("(",y1);
    int y1_p2 = input.find(")",y1_p1);
    yvar.assign(input,y1_p1+1,y1_p2-y1_p1-1);
    nor2blif = ".gate nor2 a="+a1var+" b="+a2var+" O="+yvar+"\n";
    return nor2blif;
}

string tranBlifDCAND2X1(string input)
{
    string and2blif;
    string a1var,a2var,yvar;
    int a1 = A1pos(input);
    int a2 = A2pos(input);
    int a1_p1 = input.find("(",a1);
    int a1_p2 = input.find(")",a1_p1);
    a1var.assign(input,a1_p1+1,a1_p2-a1_p1-1);
    int a2_p1 = input.find("(",a2);
    int a2_p2 = input.find(")",a2_p1);
    a2var.assign(input,a2_p1+1,a2_p2-a2_p1-1);
    int y1 = Ypos(input);
    int y1_p1 = input.find("(",y1);
    int y1_p2 = input.find(")",y1_p1);
    yvar.assign(input,y1_p1+1,y1_p2-y1_p1-1);
    and2blif = ".gate and2 a="+a1var+" b="+a2var+" O="+yvar+"\n";
    return and2blif;
}

string dc_inputdefine(string input)
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

string dc_outputdefine(string input)
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



void BenchGenDCtran::dcVerilogToBlif(char *filename)
{
    const string inv1="INV_X1";
    const string nor2="NOR2_X1";
    const string and2="AND2_X1";
    const string xor2="XOR2_X1";
    const string inputdefine="input";
    const string outputdefine="output";
    const string model="module";
    int finv1,fnor2,fand2,fxor2,finput,foutput,fmodel;
    string input;
    string location(getcwd(NULL,0));
    string filein_directory="/dc_shell-Verilog/";
    string in_location=location+filein_directory;
    string finalinputname=in_location+filename;
    ifstream fin(finalinputname);
    string temp;

    string extension=".blif";
    string fileout_directory="/VerilogToBlif/";
    string out_location=location+fileout_directory+filename;
    string outputfilename=out_location+extension;
    int correctextension;
    correctextension=outputfilename.find(".v",0);
    outputfilename.erase(correctextension,2);
    ofstream outfile(outputfilename);
    
    while(getline(fin, input))
    {
        input = dc_getridofarray(input);
        finv1 = input.find(inv1);          
        fand2 = input.find(and2);
        fnor2 = input.find(nor2);
        fxor2 = input.find(xor2);
        finput = input.find(inputdefine);
        foutput = input.find(outputdefine);
        fmodel = input.find(model);
        if(finput>=0)
        {
            outfile<<dc_inputdefine(input)<<endl;
        }
        else if(foutput>=0)
        {
            outfile<<dc_outputdefine(input)<<endl;
        }
        else if(fmodel==0)
        {
            outfile<<".model"<<" benchgen"<<endl;
        }
        else if(fnor2>=0) 
        {
            outfile<<tranBlifDCNOR2X1(input);
        }
        else if(finv1>=0)
        {
            outfile<<tranBlifDCINVX1(input);
        }
        else if(fxor2>=0)
        {
            outfile<<tranBlifDCXOR2X1(input);
        }
        else if(fand2>=0)
        {
            outfile<<tranBlifDCAND2X1(input);
        }
        else
        {
            
        }
    }
	outfile<<".end"<<endl;
}



string tranBlifDCINVX1ToVerilog(string input)
{
    string and2blif;
    string a1var,a2var,yvar;
    int a1 = Ainxorpos(input);
    int a1_p1=input.find("(",a1);
    int a1_p2=input.find(")",a1_p1);
    a1var.assign(input,a1_p1+1,a1_p2-a1_p1-1);
    int y1 = Ypos(input);
    int y1_p1 = input.find("(",y1);
    int y1_p2 = input.find(")",y1_p1);
    yvar.assign(input,y1_p1+1,y1_p2-y1_p1-1);
    and2blif = "    assign "+yvar+" = ~"+a1var+";\n";
    return and2blif;
}
string tranBlifDCXOR2X1ToVerilog(string input)
{
    string xor2blif;
    string a1var,a2var,yvar;
    int a1 = Ainxorpos(input);
    int a2 = Binxorpos(input);
    int a1_p1 = input.find("(",a1);
    int a1_p2 = input.find(")",a1_p1);
    a1var.assign(input,a1_p1+1,a1_p2-a1_p1-1);
    int a2_p1 = input.find("(",a2);
    int a2_p2 = input.find(")",a2_p1);
    a2var.assign(input,a2_p1+1,a2_p2-a2_p1-1);
    int y1 = Zinxorpos(input);
    int y1_p1 = input.find("(",y1);
    int y1_p2 = input.find(")",y1_p1);
    yvar.assign(input,y1_p1+1,y1_p2-y1_p1-1);
    xor2blif = "    assign "+yvar+" = "+a1var+" ^ "+a2var+";\n";
    return xor2blif;
}
string tranBlifDCNOR2X1ToVerilog(string input)
{
    string nor2blif;
    string a1var,a2var,yvar;
    int a1 = A1pos(input);
    int a2 = A2pos(input);
    int a1_p1 = input.find("(",a1);
    int a1_p2 = input.find(")",a1_p1);
    a1var.assign(input,a1_p1+1,a1_p2-a1_p1-1);
    int a2_p1 = input.find("(",a2);
    int a2_p2 = input.find(")",a2_p1);
    a2var.assign(input,a2_p1+1,a2_p2-a2_p1-1);
    int y1 = Ypos(input);
    int y1_p1 = input.find("(",y1);
    int y1_p2 = input.find(")",y1_p1);
    yvar.assign(input,y1_p1+1,y1_p2-y1_p1-1);
    nor2blif = "    assign "+yvar+" = ~("+a1var+" + "+a2var+");\n";
    return nor2blif;
}

string tranBlifDCAND2X1ToVerilog(string input)
{
    string and2blif;
    string a1var,a2var,yvar;
    int a1 = A1pos(input);
    int a2 = A2pos(input);
    int a1_p1 = input.find("(",a1);
    int a1_p2 = input.find(")",a1_p1);
    a1var.assign(input,a1_p1+1,a1_p2-a1_p1-1);
    int a2_p1 = input.find("(",a2);
    int a2_p2 = input.find(")",a2_p1);
    a2var.assign(input,a2_p1+1,a2_p2-a2_p1-1);
    int y1 = Ypos(input);
    int y1_p1 = input.find("(",y1);
    int y1_p2 = input.find(")",y1_p1);
    yvar.assign(input,y1_p1+1,y1_p2-y1_p1-1);
    and2blif = "    assign "+yvar+" = "+a1var+" & "+a2var+";\n";
    return and2blif;
}


void BenchGenDCtran::dcVerilogToBlifToVerilog(char *filename)
{
    const string inv1="INV_X1";
    const string nor2="NOR2_X1";
    const string and2="AND2_X1";
    const string xor2="XOR2_X1";
    const string inputdefine="input";
    const string outputdefine="output";
    const string model="module";
    int finv1,fnor2,fand2,fxor2,finput,foutput,fmodel;
    string input;
    string location(getcwd(NULL,0));
    string filein_directory="/dc_shell-Verilog/";
    string in_location=location+filein_directory;
    string finalinputname=in_location+filename;
    ifstream fin(finalinputname);
    string temp;

    string extension=".v";
    string fileout_directory="/verilogGenerated/";
    string out_location=location+fileout_directory+filename;
    string outputfilename=out_location+extension;
    int correctextension;
    correctextension=outputfilename.find(".v",0);
    outputfilename.erase(correctextension,2);
    ofstream outfile(outputfilename);
    
    while(getline(fin, input))
    {
       // input = dc_getridofarray(input);
        finv1 = input.find(inv1);          
        fand2 = input.find(and2);
        fnor2 = input.find(nor2);
        fxor2 = input.find(xor2);


        if(fnor2>=0) 
        {
            outfile<<tranBlifDCNOR2X1ToVerilog(input);
        }
        else if(finv1>=0)
        {
            outfile<<tranBlifDCINVX1ToVerilog(input);
        }
        else if(fxor2>=0)
        {
            outfile<<tranBlifDCXOR2X1ToVerilog(input);
        }
        else if(fand2>=0)
        {
            outfile<<tranBlifDCAND2X1ToVerilog(input);
        }
        else
        {
            outfile<<input<<endl;   
        }
    }
	
}


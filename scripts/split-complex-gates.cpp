//
//  BenchGen-SplitComplexGate.cpp
//  多项式运算
//
//  Created by Cunxi Yu on 10/30/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
using namespace std;
string verilog2verilogSplitaoi21Variable1(string input)
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
    //aoib1=aoiout+" = "+"1 - ("+aoia+"+"+aoib1+"*"+aoib2+"-"+aoia+"*"+aoib1+"*"+aoib2+")";
    return aoib1;
    //return aoib1;
}
string verilog2verilogSplitaoi21Variable2(string input)
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
    //aoib1=aoiout+" = "+"1 - ("+aoia+"+"+aoib1+"*"+aoib2+"-"+aoia+"*"+aoib1+"*"+aoib2+")";
    return aoib2;
    //return aoib1;
}
string verilog2verilogSplitaoi21Variable3(string input)
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
    //aoib1=aoiout+" = "+"1 - ("+aoia+"+"+aoib1+"*"+aoib2+"-"+aoia+"*"+aoib1+"*"+aoib2+")";
    return aoia;
    //return aoib1;
}
string verilog2verilogSplitaoi21Variable4(string input)
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
    //aoib1=aoiout+" = "+"1 - ("+aoia+"+"+aoib1+"*"+aoib2+"-"+aoia+"*"+aoib1+"*"+aoib2+")";
    return aoiout;
    //return aoib1;
}

string verilog2verilogSplitaoi22V1(string input)
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
    //cout<<aoi22out<<" = "<<"1 - ("<<aoi22a1<<"*"<<aoi22a2<<"+"<<aoi22b1<<"*"<<aoi22b2<<"-"<<aoi22a1<<"*"<<aoi22a2<<"*"<<aoi22b1<<"*"<<aoi22b2<<")"<<endl;
    //aoi22b1=aoi22out+" = "+"1 - ("+aoi22a1+"*"+aoi22a2+"+"+aoi22b1+"*"+aoi22b2+"-"+aoi22a1+"*"+aoi22a2+"*"+aoi22b1+"*"+aoi22b2+")";
    return aoi22a1;
}
string verilog2verilogSplitaoi22V2(string input)
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
    //cout<<aoi22out<<" = "<<"1 - ("<<aoi22a1<<"*"<<aoi22a2<<"+"<<aoi22b1<<"*"<<aoi22b2<<"-"<<aoi22a1<<"*"<<aoi22a2<<"*"<<aoi22b1<<"*"<<aoi22b2<<")"<<endl;
    //aoi22b1=aoi22out+" = "+"1 - ("+aoi22a1+"*"+aoi22a2+"+"+aoi22b1+"*"+aoi22b2+"-"+aoi22a1+"*"+aoi22a2+"*"+aoi22b1+"*"+aoi22b2+")";
    return aoi22a2;
}
string verilog2verilogSplitaoi22V3(string input)
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
    //cout<<aoi22out<<" = "<<"1 - ("<<aoi22a1<<"*"<<aoi22a2<<"+"<<aoi22b1<<"*"<<aoi22b2<<"-"<<aoi22a1<<"*"<<aoi22a2<<"*"<<aoi22b1<<"*"<<aoi22b2<<")"<<endl;
    //aoi22b1=aoi22out+" = "+"1 - ("+aoi22a1+"*"+aoi22a2+"+"+aoi22b1+"*"+aoi22b2+"-"+aoi22a1+"*"+aoi22a2+"*"+aoi22b1+"*"+aoi22b2+")";
    return aoi22b1;
}
string verilog2verilogSplitaoi22V4(string input)
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
    //cout<<aoi22out<<" = "<<"1 - ("<<aoi22a1<<"*"<<aoi22a2<<"+"<<aoi22b1<<"*"<<aoi22b2<<"-"<<aoi22a1<<"*"<<aoi22a2<<"*"<<aoi22b1<<"*"<<aoi22b2<<")"<<endl;
    //aoi22b1=aoi22out+" = "+"1 - ("+aoi22a1+"*"+aoi22a2+"+"+aoi22b1+"*"+aoi22b2+"-"+aoi22a1+"*"+aoi22a2+"*"+aoi22b1+"*"+aoi22b2+")";
    return aoi22b2;
}
string verilog2verilogSplitaoi22V5(string input)
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
    aoi22out.assign(input,aoi22out1+3,aoi22out2-aoi22out1-3);
    //cout<<aoi22out<<" = "<<"1 - ("<<aoi22a1<<"*"<<aoi22a2<<"+"<<aoi22b1<<"*"<<aoi22b2<<"-"<<aoi22a1<<"*"<<aoi22a2<<"*"<<aoi22b1<<"*"<<aoi22b2<<")"<<endl;
    //aoi22b1=aoi22out+" = "+"1 - ("+aoi22a1+"*"+aoi22a2+"+"+aoi22b1+"*"+aoi22b2+"-"+aoi22a1+"*"+aoi22a2+"*"+aoi22b1+"*"+aoi22b2+")";
    return aoi22out;
}


string verilog2verilogSplitoai21V1(string input)
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
    //oaib1=oaiout+" = 1 - ("+oaib1+" + "+oaib2+" - "+oaib1+"*"+oaib2+" ) * "+oaia;
    return oaib1;
}
string verilog2verilogSplitoai21V2(string input)
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
    oaib1=oaiout+" = 1 - ("+oaib1+" + "+oaib2+" - "+oaib1+"*"+oaib2+" ) * "+oaia;
    return oaib2;
}
string verilog2verilogSplitoai21V3(string input)
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
    oaib1=oaiout+" = 1 - ("+oaib1+" + "+oaib2+" - "+oaib1+"*"+oaib2+" ) * "+oaia;
    return oaia;
}
string verilog2verilogSplitoai21V4(string input)
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
    oaib1=oaiout+" = 1 - ("+oaib1+" + "+oaib2+" - "+oaib1+"*"+oaib2+" ) * "+oaia;
    return oaiout;
}

string verilog2verilogSplitoai22V1(string input)
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
    //oai22b1=oai22out+"="+"1-("+oai22b1+"+"+oai22b2+"-"+oai22b1+"*"+oai22b2+")*("+oai22a1+"+"+oai22a2+"-"+oai22a1+"*"+oai22a2+")";
    return oai22a1;
}
string verilog2verilogSplitoai22V2(string input)
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
    //oai22b1=oai22out+"="+"1-("+oai22b1+"+"+oai22b2+"-"+oai22b1+"*"+oai22b2+")*("+oai22a1+"+"+oai22a2+"-"+oai22a1+"*"+oai22a2+")";
    return oai22a2;
}
string verilog2verilogSplitoai22V3(string input)
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
    //oai22b1=oai22out+"="+"1-("+oai22b1+"+"+oai22b2+"-"+oai22b1+"*"+oai22b2+")*("+oai22a1+"+"+oai22a2+"-"+oai22a1+"*"+oai22a2+")";
    return oai22b1;
}
string verilog2verilogSplitoai22V4(string input)
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
    //oai22b1=oai22out+"="+"1-("+oai22b1+"+"+oai22b2+"-"+oai22b1+"*"+oai22b2+")*("+oai22a1+"+"+oai22a2+"-"+oai22a1+"*"+oai22a2+")";
    return oai22b2;
}
string verilog2verilogSplitoai22V5(string input)
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
    //oai22b1=oai22out+"="+"1-("+oai22b1+"+"+oai22b2+"-"+oai22b1+"*"+oai22b2+")*("+oai22a1+"+"+oai22a2+"-"+oai22a1+"*"+oai22a2+")";
    return oai22out;
}
void SplitOAI22(string input,int ex)
{
    cout<<"  or2 g(.a("<<verilog2verilogSplitoai22V1(input)<<"), .b("<<verilog2verilogSplitoai22V2(input)<<"), .O(extra"<<ex<<"));"<<endl;
    cout<<"  or2 g(.a("<<verilog2verilogSplitoai22V3(input)<<"), .b("<<verilog2verilogSplitoai22V4(input)<<"), .O(extra"<<ex+1<<"));"<<endl;
    cout<<"  and2 g(.a(extra"<<ex<<"), .b(extra"<<ex+1<<"), .O(extra"<<ex+2<<"));"<<endl;
    cout<<"  inv1 g(.a(extra"<<ex+2<<"), .O("<<verilog2verilogSplitoai22V5(input)<<"));"<<endl;
}

void SplitAOI22(string input, int ex)
{
    cout<<"  and2 g(.a("<<verilog2verilogSplitaoi22V1(input)<<"), .b("<<verilog2verilogSplitaoi22V2(input)<<"), .O(extra"<<ex<<"));"<<endl;
    cout<<"  and2 g(.a("<<verilog2verilogSplitaoi22V3(input)<<"), .b("<<verilog2verilogSplitaoi22V4(input)<<"), .O(extra"<<ex+1<<"));"<<endl;
    cout<<"  or2 g(.a(extra"<<ex<<"), .b(extra"<<ex+1<<"), .O(extra"<<ex+2<<"));"<<endl;
    cout<<"  inv1 g(.a(extra"<<ex+2<<"), .O("<<verilog2verilogSplitaoi22V5(input)<<"));"<<endl;
}
void SplitAOI21(string input, int ex)
{
    cout<<"  and2 g(.a("<<verilog2verilogSplitaoi21Variable1(input)<<"), .b("<<verilog2verilogSplitaoi21Variable2(input)<<"), .O(extra"<<ex<<"));"<<endl;
    cout<<"  or2 g(.a(extra"<<ex<<"), .b("<<verilog2verilogSplitaoi21Variable3(input)<<"), .O(extra"<<ex+1<<"));"<<endl;
    cout<<"  inv1 g(.a(extra"<<ex+1<<"), .O("<<verilog2verilogSplitaoi21Variable4(input)<<"));"<<endl;
}
void SplitOAI21(string input, int ex)
{
    cout<<"  or2 g(.a("<<verilog2verilogSplitoai21V1(input)<<"), .b("<<verilog2verilogSplitoai21V2(input)<<"), .O(extra"<<ex<<"));"<<endl;
    cout<<"  and2 g(.a(extra"<<ex<<"), .b("<<verilog2verilogSplitoai21V3(input)<<"), .O(extra"<<ex+1<<"));"<<endl;
    cout<<"  inv1 g(.a(extra"<<ex+1<<"), .O("<<verilog2verilogSplitoai21V4(input)<<"));"<<endl;
}



void split(string file)
{
    const string aoi21="aoi21";
    const string aoi22="aoi22";
    const string oai21="oai21";
    const string oai22="oai22";
    string input;
    ifstream fin(file.c_str());
    int aoi21find,aoi22find,oai21find,oai22find;
    int extranode=0;
    while (getline(fin, input))
    {
	aoi21find=input.find(aoi21,0);
	aoi22find=input.find(aoi22,0);
	oai21find=input.find(oai21,0);
	oai22find=input.find(oai22,0);
	if(aoi21find>=0)
	{
		SplitAOI21(input,extranode);
		extranode=extranode+2;
	}
	else if(aoi22find>=0)
	{
		SplitAOI22(input,extranode);
		extranode=extranode+3;
	}
	else if(oai21find>=0)
	{
		SplitOAI21(input,extranode);
		extranode=extranode+2;
	}
	else if(oai22find>=0)
	{
		SplitOAI22(input,extranode);
		extranode=extranode+3;
	}
	else
	{
		cout<<input<<endl;
	}

}
}

void split_outfile(string file)
{
    const string aoi21="aoi21";
    const string aoi22="aoi22";
    const string oai21="oai21";
    const string oai22="oai22";
    string input;
    ifstream fin(file.c_str());
    string output_file = file + "Complex-split.v";
    ofstream outfile(output_file.c_str());
    int aoi21find,aoi22find,oai21find,oai22find;
    int extranode=0;
    while (getline(fin, input))
    {
	aoi21find=input.find(aoi21,0);
	aoi22find=input.find(aoi22,0);
	oai21find=input.find(oai21,0);
	oai22find=input.find(oai22,0);
	if(aoi21find>=0)
	{
		SplitAOI21(input,extranode);
		extranode=extranode+2;
	}
	else if(aoi22find>=0)
	{
		SplitAOI22(input,extranode);
		extranode=extranode+3;
	}
	else if(oai21find>=0)
	{
		SplitOAI21(input,extranode);
		extranode=extranode+2;
	}
	else if(oai22find>=0)
	{
		SplitOAI22(input,extranode);
		extranode=extranode+3;
	}
	else
	{
		outfile<<input<<endl;
	}

}
}


int main(int argc, const char * argv[])
{
	string file = argv[argc -1];
    split(file);
    //split_outfile(file);
    
}

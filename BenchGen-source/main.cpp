//
//  main.cpp
//  BenchmarkGenerator
//  Created by Cunxi Yu on 7/12/14.
//  StringMath.h: The "verify" function library which is written by Walter Brown on 06/2014.
//  Thanks to everyone in Maciej Ciesielski's group(Duo Liu, Walter Brown, Prof.Maciej Ciesielski).
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//  Type "-help" to find the commands you need. Enjoy!
#include <stdio.h>
#include <glob.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "BenchGen.h"
#include "BenchGen2.h"
#include "BenchGen-MultiAccum.h"
#include "EqnBenchGen.h"
#include "BenchGen-Comparator.h"
#include "BenchGen-Matrix.h"
#include "BenchGen-CLA.h"
#include "BenchGen-Translate.h"
#include "BenchGen-Shifter.h"
#include "BenchGen-Squarer.h"
#include "BenchGen-ALU.h"
#include "BenchGen-FormatToABC.h"
#include "BenchGen-ModuloBench.h"
#include "BenchGen-SMT2Paser.h"
#include "BenchGen-DesginCompilerTran.h"
#include "BenchGen-SeqBench.h"
#include "BenchGen-AddShifterMult.h"
#include "BenchGen-ABCSynthesisTran.h"
#include "BenchGen-VerilogToBlif.h"
#include "BenchGen-Divider.h"
#include "BenchGen-BuggyGen.h"
//#include "boost/filesystem.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <vector>
using namespace std;
const string white="";
string filename;
//Gate-Level keyword
const string GenMUX="gen mux";
const string GenMixAddMult="gen mixadd_mult";
const string GenAdder="gen adder";
const string GenMultiplier="gen multiplier";
const string GenMatrixMultiply="gen matrix_mult";
const string GenThreeMult="gen multiplier_3";
const string GenComparator="gen comparator";
const string GenSubtractor="gen subtractor";
const string GenCarryLookAheadAdder="gen cla";
const string GenFindMaxNumber="gen findmax";
const string GenFindMinNumber="gen findmin";
const string GenFindMeanNumber="gen findmean";
const string GenCompleteSquare1="gen squarecomplete1";
const string GenCompleteSquare2="gen squarecomplete2";
const string GenALU="gen alu";
const string GenMacModel2="gen mac 2";
const string GenMacModel4="gen mac 4";
const string GenMacModel6="gen mac 6";
const string GenModulo4="gen modulo 4";
const string GenNonRestoringDivider="gen divider nr";
const string GenRestoringDivider="gen divider r";
//Sequential Circuit
const string GenSquareSeq="gen square seq";
const string GenAddShifterMult="gen addshiftmult seq";
//RTL keyword
const string GenMixAddMultRTL="gen mixadd_mult RTL";
const string GenAdderRTL="gen adder RTL";
const string GenMultiplierRTL="gen multiplier RTL";
const string GenMultiply_AccuRTL="gen multiply_accumulator RTL";
const string GenComparatorRTL="gen comparator RTL";
const string GenThreeMultRTL="gen multiplier_3 RTL";
const string GenFindMaxNumberRTL="gen findmax RTL";
const string GenFindMinNumberRTL="gen findmin RTL";
const string GenMatrixMultiplyRTL="gen matrix_mult RTL";
const string GenFindMeanNumberRTL="gen findmean RTL";
const string GenCompleteSquare1RTL="gen squarecomplete1 RTL";
const string GenCompleteSquare2RTL="gen squarecomplete2 RTL";
//Eqn keyword
const string GenEqnAdder="gen adder eqn";
const string GenMathModelofComparator="gen comparator math";
//debugging 
const string GenBuggyVerilog_training="gen training";
const string GenBuggyVerilog_training_dir="gen training -r";

//function keyword
const string help="help";
const string exitword="exit";
const string translate="tran";
const string verify="verify";
const string tranpoly="tran poly";
const string ABCformat="tran abc";
const string csfformat="tran csf";
const string csfformat_dir="tran csf -r";
const string eqnformat_dir = "tran eqn -r";
const string smt2format="tran smt2";
const string trandcshellverilog="tran dc_verilog";
const string trandcshelleqn="tran dc_eqn";
const string tranabcMappedVerilogToEqn="tran abc_eqn";
const string tranverilog2blif="tran blif";
const string tranverilog2blif_dir="tran blif -r";
const string traneqnNoreverse="tran -r";
const string tranDCverilogToBlif="tran blif dc";
const string tran_neweqn2 = "tran eqn2";
//generate multiple files in one command. for example, gen adder => enter bits: 4 6 8, the software will generate 4bit,6bit,8bit verilog file
string inputbits;
//files
char files[50];
//using namespace boost::filesystem;
void printVEC(vector<string> v)
{
    vector<string>::iterator i;
    for(i = v.begin();i!=v.end();i++)
    {
        cout<<*i<<endl;
    }
}
/*
vector<string> getall_Vfiles()
{
    vector<string> v;  
    path p = "/home/cunxi/cunxi/research/BenchGen-V-0.2/verilogGenerated/";
      directory_iterator it{p};
    int find=0;
    while (it != directory_iterator{})
    {
                
        string temp = it->path().filename().string();
        find = temp.find(".v",0); 
        if( find  >=0 )
        {
            v.push_back(temp);
        }
        it++;    
    }
    return v;
}
*/

void helpprint()

{
   cout<<"\n/**Gate-Level Verilog Generation Command **/ \n\n"
    "------Basic Datapath Circuit Benchmarks------\n"
    " - gen mux                      ---Function(gate-level): F=s?A:B\n"
    " - gen mixadd_mult              ---Function(gate-level): F=a*(b+c)\n"
    " - gen adder                    ---Function(gate-level): F=a+b\n"
    " - gen multiplier               ---Function(gate-level): F=a*b\n"
    " - gen multiplier_3             ---Function(gate-level): F=a1*b1+a2*b2+a3*b3\n"
    " - gen comparator               ---Function(gate-level): F=sign, if A>B,sign=0,or sign=1\n"
    " - gen subtractor               ---Function(gate-level): F=a-b\n\n"
    " - gen divider nr               ---Function(gate-level): F-> X/D=Q,R, R=Reminder,Q=Quotient,D=divisor\n"
    " - gen divider r                ---Function(hieriarch):  Restoring array divideri\n"
    "------Advanced Datapath Circuit Benchmarks---------\n"
    " - gen mixadd_mult              ---Function(gate-level): F=a*(b+c)\n"
    " - gen squarecomplete1          ---Function(gate-level): F=x^2+x+1 =? (x+1)^2\n"
    " - gen squarecomplete2          ---Function(gate-level): F=1+x+x^2+x^3 =? (x+1)*(x^2+1)\n"
    " - gen matrix_mult              ---Function(gate-level): [p1,p2,p3]T=[A1~A9(3*3)]*[B1,B2,B3]T\n"
    " - gen findmax                  ---Function(gate-level): F=Max(a,b,c,d)\n"
    " - gen mac 2                    ---Function(gate-level): Multiply Accum Transform 2 clocks\n"
    " - gen mac 4                    ---Function(gate-level): Multiply Accum Transform 4 clocks\n"
    " - gen mac 6                    ---Function(gate-level): Multiply Accum Transform 6 clocks\n"
    " - gen modulo 4                 ---Function(gate-level): F=x+x/2+x/4+x/8\n"
    " - gen findmin                  ---Function(gate-level): F=Min(a,b,c,d)\n"
    " - gen findmean                 ---Function(gate-level): F=Mean(a,b,c,d)-(Divide(mod 2) 2 use 1Bits Right shifter)\n\n"
    "------Multi-Functions Arithmetic Logic Benchmarks---------\n"
    " - gen shifter                  ---Function(gate-level): Generate 2^n bits shifter with n bits control signals\n"
    " - gen comparator math "
    " - gen alu                      ---Function(gate-Level): This ALU has 64 Functions(6 control signals).\n"
    "------Sequential Circuit Benchmarks.\n\n"
    " - gen square seq\n"
    " - gen addshiftmult seq\n\n"
    "------Control Logic Circuits Benchmarks---------\n"
    " - gen trafficlight             ---Function\n\n"
    "/**RTL Verilog Generation Command**/ \n"
    " - gen mixadd_mult RTL          ---Function(RTL-level): F=a*b+a*c \n"
    " - gen adder RTL                ---Function(RTL-level): F=a+b \n"
    " - gen multiplier RTL           ---Function(RTL-level): F=a*b \n"
    " - gen multiplier_3 RTL         ---Function(RTL-level): F=a1*b1+a2*b2+a3*b3\n"
    " - gen comparator RTL           ---Function(RTL-level): If a>=b,sel=0;or sel=1\n"
    " - gen multiply_accumulator RTL ---Function(RTL-level): F<-a*b+F\n"
    " - gen matrix_mult RTL          ---Function(RTL-level): F=[p1,p2,p3]T=[A1~A9(3*3)]*[B1,B2,B3]T\n"
    " - gen findmax RTL              ---Function(RTL-level): F=Max(a,b,c,d)\n"
    " - gen findmin RTL              ---Function(RTL-level): F=Min(a,b,c,d)\n"
    " - gen findmean RTL             ---Function(RTL-level): F=Mean(a,b,c,d)=(Max+Min)/2\n"
    " - gen squarecomplete1 RTL      ---Function(RTL-level): F=x^2+x+1\n"
    " - gen squarecomplete2 RTL      ---Function(RTL-level): F=1+x+x^2+x^3\n\n"
    "/** Verification Function **/ \n"
    " - help                         ---Check software commands\n"
    " - exit                         ---Quit BenchGen\n"
    " - verify                       ---Verify the circuit (eqn format)\n"
    " - tran                         ---Translate behavior verilog to eqn\n"
    " - ted                          ---Generate TED *.ps file derived from Poly files\n"
    " - tran abc                     ---Translate BenchGen Verilog format to ABCformat\n"
    " - tran smt2                    ---Translate BenchGen verilog file to SMT2-LIB files\n"
    " - tran abc_eqn                 ---Translate ABC mapped (algebra golden genlib) verilog file to equation format\n"
    " - tran blif                    ---Translate verilog format to blif format\n"
    " - tran blif -r                 ---Translate all verilog in the dir into blif format\n"
    " - tran dc_verilog              ---Translate RTL Verilog after systhesised by DC_SHELL to RTL Verilog \n"
    " - tran dc_eqn                  ---Translate RTL Verilog after systhesised by DC_SHELL to eqnuation file\n"
    " - tran csf                     ---Translate BenchGen Verilog format to CSF format for petBoss\n"
    " - tran csf -r                  ---Translate BenchGen Verilog foramt to CSF, tran the entire directory\n"
    " - tran eqn2                    ---Translate BenchGen verilog into new equation format (new_eqn2)\n"
    " - tran poly                    ---Translate behavior verilog poly\n"
    " - gen training (-r)            ---generate buggy verilog files for training purpose\n"<<endl;
}
void software()
{
    cout<<"BenchGen (V0.2) < ";
}
float t1,t2;

int main()
{
string temp;   
vector<string> file_vec; //file_vec = allverilog();
vector<string>::iterator i;
    // clock_t tStart=clock();    
    int num;
    int blockerase;
    char *buf;
    //BenchGen::welcomeTile();
    BenchGen::welcomeTile();
    int choice;
    string key;
    cout<<"BenchGen (V0.2) < ";
      while((buf = readline(""))!=NULL) {
        if (buf[0]!=0)
            add_history(buf);

        key=buf;        
    
    if (key==GenAdder) {
        choice=1;
    }
    else if (key==GenAdderRTL)
    {
        choice=2;
    }
    else if (key==GenMixAddMult)
    {
        choice=3;
    }
    else if (key==GenMixAddMultRTL)
    {
        choice=4;
    }
    else if (key==GenMultiplier)
    {
        choice=5;
    }
    else if (key==GenMultiplierRTL)
    {
        choice=6;
    }
    else if (key==GenMultiply_AccuRTL)
    {
        choice=8;
    }
    else if (key==GenMatrixMultiply)
    {
        choice=9;
    }
    else if (key==GenComparator)
    {
        choice=10;
    }
    else if (key==GenComparatorRTL)
    {
        choice=11;
    }
    else if (key==GenThreeMult)
    {
        choice=12;
    }
    else if (key==GenThreeMultRTL)
    {
        choice=13;
    }
    else if(key==GenCarryLookAheadAdder)
    {
        choice=14;
    }
    else if(key==GenFindMaxNumber)
    {
        choice=15;
    }
    else if(key==GenFindMinNumber)
    {
        choice=16;
    }
    else if(key==GenFindMaxNumberRTL)
    {
        choice=17;
    }
    else if(key==GenFindMinNumberRTL)
    {
        choice=18;
    }
    else if (key==GenFindMeanNumber)
    {
        choice=19;
    }
    else if (key==GenMatrixMultiplyRTL)
    {
        choice=20;
    }
    else if (key==GenFindMeanNumberRTL)
    {
        choice=21;
    }
    else if (key==GenCompleteSquare1)
    {
        choice=22;
    }
    else if (key==GenCompleteSquare2)
    {
        choice=23;
    }
    else if(key==GenALU)
    {
        choice=24;
    }
    else if(key==GenMacModel2)
    {
        choice=25;
    }
    else if(key==GenMacModel4)
    {
        choice=26;
    }
    else if(key==GenMacModel6)
    {
        choice=27;
    }
    else if(key==GenModulo4)
    {
        choice=28;
    }
    else if(key==GenCompleteSquare1RTL)
    {
        choice=29;
    }
    else if(key==GenCompleteSquare2RTL)
    {
        choice=30;
    }
    else if(key==GenNonRestoringDivider)
    {
        choice=31;
    }
    else if(key==GenSubtractor)
    {
        choice=32;
    }
    else if(key==GenMUX)
    {
	choice=33;
    }
    else if (key==GenMathModelofComparator)
    {
        choice=51;
    }
    else if(key==GenSquareSeq)
    {
        choice=52;
    }
    else if(key==GenAddShifterMult)
    {
        choice=53;
    }
    else if(key==GenRestoringDivider)
    {
	choice=54;
    }
    else if(key==tran_neweqn2)
    {
        choice=55;
    }
    else if(key==GenBuggyVerilog_training)
    {
        choice=56;
    }
    else if(key==csfformat_dir)
    {
        choice=57;
    }
    else if(key==eqnformat_dir)
    {
        choice=58;
    }
    else if(key == tranverilog2blif_dir)
    {
        choice = 59;
    }
    else if(key==trandcshellverilog)
    {
        choice=88;
    }
    else if (key==traneqnNoreverse)
    {
        choice=89;
    }
    else if(key==tranDCverilogToBlif)
    {
        choice=90;
    }
    else if(key==trandcshelleqn)
    {
        choice=91;
    }
    else if(key==smt2format)
    {
        choice=92;
    }
    else if(key==csfformat)
    {
        choice=93;
    }
    else if(key==ABCformat)
    {
        choice=94;
    }
    else if(key==verify)
    {
        choice=95;
    }
    else if(key==tranpoly)
    {
        choice=96;
    }
    else if(key==translate)
    {
        choice=97;
    }
    else if(key==help)
    {
        choice=98;
    }
    else if(key==tranabcMappedVerilogToEqn)
    {
        choice=101;
    }
    else if(key==tranverilog2blif)
    {
        choice=102;
    }
    else if (key==exitword)
    {
        cout<<"BenchGen (V0.2) < "<<"Thanks,Bye!"<<endl;
        break;
    }
   /* else if(key==verify)
    {
        choice=100;
    }*/
    else if (key==white)
    {
        choice=0;
    }
    else
    {
        choice=999;
        //cout<<"BenchGen (V0.2) < "<<"Command not exit,please try again.(You can type /help/ to check the commands.)"<<endl;
    }
    
   
    int bit;
   
    //int bit1,bit2;
    switch (choice) {
        case 0:
            cout<<"---Empty Function!(You can type /#help#/ to check more commands.)---"<<endl;
            software();
            continue;
        case 1:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            //cin>>bit;
            //cin>>inputbits;
            getline(cin,inputbits); 

    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGen::gatelevelbenchADD(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGen::gatelevelbenchADD(num);
            software();
            continue;
        case 2:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGen::arbitraryRTLAdder(bit);
            software();
            continue;
        case 3:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGen2::MixAddMultiply(num, num-1);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGen2::MixAddMultiply(num, num-1);
            software();
            continue;
        case 4:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGen2::MixAddMultRTL(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGen2::MixAddMultRTL(num);
            software();
            continue;
        case 5:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGen::EntierMultiplierGen(num, num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGen::EntierMultiplierGen(num, num);
            software();
            continue;
        case 6:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            t1=clock();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGen::MultiplierRTL(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGen::MultiplierRTL(num);
            software();
            continue;
            t2=(clock()-t1)/(double)CLOCKS_PER_SEC;
            printf("Time taken: %.6fs\n", t2);
            software();
            continue;
        case 7:
            
        case 8:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGen_MultiAccum::RTLMultilyAccum(bit);
            software();
            continue;
        case 9:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGenMatrix::MatrixMultiply(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGenMatrix::MatrixMultiply(num);
            software();
            continue;
        case 10:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGenComparator::comp(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGenComparator::comp(num);
            software();
            continue;
        case 11:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGenComparator::compRTL(bit);
            software();
            continue;
        case 12:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGenMatrix::ThreeMultAndAddition(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGenMatrix::ThreeMultAndAddition(num);
            software();
            continue;
        case 13:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGenMatrix::ThreeMultAndAdditionRTL(bit);
            software();
            continue;
        case 14:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGenCLA::carrylookahead(bit);
            software();
            continue;
        case 15:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGenComparator::FindMaxNumber(bit);
            software();
            continue;
        case 16:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGenComparator::FindMinNumber(bit);
            software();
            continue;
        case 17:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGenComparator::FindMaxNumberRTL(bit);
            software();
            continue;
        case 18:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGenComparator::FindMinNumberRTL(bit);
            software();
            continue;
        case 19:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGenComparator::FindMeanNumber(bit);
            software();
            continue;
        case 20:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGenMatrix::MatrixMultiplyRTL(bit);
            software();
            continue;
        case 21:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGenComparator::FindMeanNumberRTL(bit);
            software();
            continue;
        case 22:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits);
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGenSquare::datapathAddSquare(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGenSquare::datapathAddSquare(num);
            software();
            continue;
        case 23:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGenSquare::PowThreeSqMultiply(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGenSquare::PowThreeSqMultiply(num);
            software();
            continue;
        case 24:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGenALU::ALU(bit);
            software();
            continue;
        case 25:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGen_MultiAccum::MacModelGen(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGen_MultiAccum::MacModelGen(num);
            software();
            continue;
        case 26:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGen_MultiAccum::MacModelGen4Clock(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGen_MultiAccum::MacModelGen4Clock(num);
            software();
            continue;
        case 27:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGen_MultiAccum::MacModelGen6Clock(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGen_MultiAccum::MacModelGen6Clock(num);
            software();
            continue;
        case 28:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGenModuloBench::MODBench(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGenModuloBench::MODBench(num);
            software();
            continue;
        case 29:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGenSquare::PowTwoSqMultiplyRTL(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGenSquare::PowTwoSqMultiplyRTL(num);
            software();
            continue;
        case 30:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGenSquare::PowThreeSqMultiplyRTL(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGenSquare::PowThreeSqMultiplyRTL(num);
            software();
            continue;
        case 31:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGenDivider::ArrayNonRestoringDiv(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGenDivider::ArrayNonRestoringDiv(num);
            software();
            continue;
        case 32:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGen2::subtracotrTwoComplement(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGen2::subtracotrTwoComplement(num);
            software();
            continue;
        case 33:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGenComparator::GenMathModelofComparator(bit);
            software();
            continue;
        case 51:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            cin>>bit;
            BenchGenShifter::mean_max_mux1(bit);
            software();
            continue;
        case 52:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGenSeq::seqsq(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGenSeq::seqsq(num);
            software();
            continue;
        case 53:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGenAddShiftMult::AddShifterMult(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGenAddShiftMult::AddShifterMult(num);
            software();
            continue;
        case 54:
            cout<<"BenchGen (V0.2) < "<<"Please enter number of Bits"<<endl;
            software();
            getline(cin,inputbits); 
    	    blockerase=inputbits.find(" ",0);
    	    //cout<<"input string is "<<inputbits<<endl;
            //cout<<blockerase<<endl; 
    		while (blockerase+1) {
        		num=atoi(inputbits.c_str());
        		//cout<<"current operation bits is"<<num<<endl;
                 	BenchGenDivider::hierarchicalRestoringDiv(num);
        		ostringstream temn;
        		temn<<num;
        		string tem;
        		tem=temn.str();
        		inputbits.erase(0,inputbits.find(" ",0)+1);
        	//	cout<<num<<endl;
        	//	cout<<"current string is "<<str<<endl;
        		blockerase=inputbits.find(" ",0); 
    	   		}
            num=atoi(inputbits.c_str());
            //cout<<"current operation bits is"<<num<<endl;
            BenchGenDivider::hierarchicalRestoringDiv(num);
            software();
            continue;
        case 55:
            cout<<"BenchGen (V0.2) < "<<"Please enter file name"<<endl;
            software();
            cin>>files;
            BenchGenTrans::NEW_parse_outputfile(files);
            software();
            continue;
        case 56:
            cout<<"BenchGen (V0.2) < "<<"Please enter file name"<<endl;
            software();
            getline(cin,inputbits);
            blockerase = inputbits.find(" ",0);
            while(blockerase+1){
                Gen_BuggyBench::buggy_gen(inputbits);
                inputbits.erase(0,inputbits.find(" ",0)+1);
                blockerase = inputbits.find(" ",0);
            }
            Gen_BuggyBench::buggy_gen(inputbits);
            software();
            continue;
        case 57:
            cout<<"BenchGen (V0.2) < "<<"Turn all verilog files(verilogGenerated) into csf"<<endl;
            file_vec =  BenchGenTrans::AllVerilogNeed2CSF();
            for(i = file_vec.begin();i != file_vec.end(); ++i)
            {
                temp = *i;
                temp.erase(0,19);
                cout<<temp<<endl;
                BenchGenTrans::TranslateToCSF(temp.c_str() ); 
            }
            software();
            continue;
         case 58:
            cout<<"BenchGen (V0.2) < "<<"Turn all verilog files(verilogGenerated) into csf"<<endl;
            file_vec =  BenchGenTrans::AllVerilogNeed2CSF();
            for(i = file_vec.begin();i != file_vec.end(); ++i)
            {
                temp = *i;
                temp.erase(0,19);
                cout<<temp<<endl;
                BenchGenTrans::TranslateToCSF_TopSig(temp.c_str() ); 
            }
            software();
            continue;
        case 59:
            cout<<"BenchGen (V0.2) < "<<"Turn all verilog files(verilogGenerated) into BLIF"<<endl;
            file_vec =  BenchGenTrans::AllVerilogNeed2CSF();
            for(i = file_vec.begin();i != file_vec.end(); ++i)
            {
                temp = *i;
                temp.erase(0,19);
                cout<<temp<<endl;
                BenchGenVerilog2Blif::verilogToblif(temp.c_str());
            }
            software();
            continue;
       
        case 88:
            cout<<"BenchGen (V0.2) < "<<"Please enter file name"<<endl;
            software();
            cin>>files;
            BenchGenDCtran::dcVerilogToBlifToVerilog(files);
            software();
            continue;
        case 89:
            cout<<"BenchGen (V0.2) < "<<"Please enter file name"<<endl;
            software();
            cin>>files;
            BenchGenTrans::NoneReverseTranslate(files);
            software();
            continue;
        case 90:
            cout<<"BenchGen (V0.2) < "<<"Please enter file name"<<endl;
            software();
            cin>>files;
            BenchGenDCtran::dcVerilogToBlif(files);
            software();
            continue;
        case 91:
            cout<<"BenchGen (V0.2) < "<<"Please enter file name"<<endl;
            software();
            cin>>files;
            BenchGenDCtran::unitlibtran(files);
            software();
            continue;
        case 92:
            cout<<"BenchGen (V0.2) < "<<"Please enter file name"<<endl;
            software();
            cin>>files;
            BenchGensmt2::smt2fromverilog(files);
            software();
            continue;
        case 93:
            cout<<"BenchGen (V0.2) < "<<"Please enter file name"<<endl;
            software();
            cin>>filename;
            BenchGenTrans::TranslateToCSF(filename);
            software();
            continue;
        case 94:
            cout<<"BenchGen (V0.2) < "<<"Please enter file name"<<endl;
            software();
            cin>>files;
            BenchGenFormatToABC::ToABC(files);
            software();
            continue;
        case 95:
            cout<<"BenchGen (V0.2) < "<<"Please enter File Name"<<endl;
            software();
            //string systemcommandtime="/usr/bin/time -v ";
            //string interactiveStringMath="."
            cin>>files;
            //Verify::dofile(files);
            software();
            continue;
        case 96:
            cout<<"BenchGen (V0.2) < "<<"Please enter File Name"<<endl;
            software();
            cin>>files;
            BenchGenTrans::TranslatePoly(files);
            software();
            continue;
        case 97:
            cout<<"BenchGen (V0.2) < "<<"Please enter File Name"<<endl;
            software();
            //system("cd Verilog-eqn");
            cin>>files;
           // double tStart = clock();
            //files is char variable
            BenchGenTrans::Translate(files);
            software();       
            continue;
        case 98:
            helpprint();
            software();
            continue;
        case 99:
            cout<<"BenchGen (V0.2) < "<<"Hope you enjoy the software!Thanks,Bye!"<<endl;
            software();
            break;
        case 101:
            cout<<"BenchGen (V0.2) < "<<"Please enter File Name"<<endl;
            software();
            cin>>files;
            BenchGen_ABCSynthesisTran::ABCSynthesisTran(files);
            software();
            continue;
        case 102:
            cout<<"BenchGen (V0.2) < "<<"Please enter File name"<<endl;
            software();
            cin>>files;
            BenchGenVerilog2Blif::verilogToblif(files);
            software();
            continue;
        case 999:
            cout<<"BenchGen (V0.2) < "<<"-------Wrong command!!!! Please type -help to check the commands--------"<<endl;
            software();
            continue;
        default:
            cout<<"Function success!(You can type /#help#/ to check more commands.)"<<endl;
            continue;
    //double t=clock()-tStart;
    //cout<<"Time is"<<t<<endl;
    }
    
   
  }
  free(buf);
}

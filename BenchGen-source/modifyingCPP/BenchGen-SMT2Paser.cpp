//
//  BenchGen-SMT2Paser.cpp
//  tranTO-ABC
//
//  Created by Cunxi Yu on 9/1/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include "BenchGen-SMT2Paser.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <cmath>
using namespace std;

string binaryvector(int num,int bits)
{
    int b[bits];
    string vectoroutput;
    for (int i=0; i<bits; i++) {
        b[i]=num%2;
        num=num/2;
    }
    for (int i=bits-1; i>=0; i--) {
        ostringstream vecstring;
        vecstring<<b[i];
        vectoroutput=vectoroutput+vecstring.str();
    }
    return vectoroutput;
}

string declarefunction(string var)
{
    string declarebegin="(declare-fun ";
    string declareend="() (_ BitVec 1))";
    declarebegin=declarebegin+var+declareend;
    return declarebegin;
}
string erasearray(string input)
{
    int array,semicolon;
    array=input.find("[",0);
    semicolon=input.find(";",0);
    while(array>0) {
        input.erase(array,1);
        array=input.find("]",0);
        input.erase(array,1);
        array=input.find("[",0);
    }
    return input;
}
string erasesemicolon(string input)
{
    int semicolon;
    semicolon=input.find(";",0);
    if (semicolon>0) {

    input.erase(semicolon,1);
    }
    else
    {
        input=input;
    }
    return input;
}

string eraseblock(string input)
{
    int block;
    block=input.find(" ",0);
    while (block>=0) {
        input.erase(block,1);
        block=input.find(" ",0);
    }
    return input;
}
string definethevarible(string var,int bits)
{
    int temp=bits-1;
    ostringstream temp_bits;
    temp_bits<<temp;

    string extend="((_ zero_extend "+temp_bits.str()+") ";
    string extendend=")";
    string variablewithextend=extend+var+extendend;
    return variablewithextend;
}

int detectoutputsignatur(char files[50])
{
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory;
    string finalinputfile=in_location+files;
    ifstream fin(finalinputfile);
    int findoutput,findmsboutput,findmsboutput2,num_msb;
    string input,msb;
    while(getline(fin, input))
    {
        findoutput=input.find("output",0);
        if(findoutput>0)
        {
            findmsboutput=input.find("[",0);
            findmsboutput2=input.find(":",0);
            msb.assign(input,findmsboutput+1,findmsboutput2-findmsboutput-1);
            istringstream(msb) >> num_msb;
        }
        else
        {
        }
    } 
    return num_msb+1;
}

void detectredundancydeclare(string lib[],string var,int n)
{
    for(int i=1;i<=n;i++)
    {
        if(lib[i]==var)
        {
            lib[n+1]=var;
            n++;
            break;
        }
        else
        {
        }
    }
}

int detectsamestring(string lib[],string var,int num)
{
    int temp;
    for (int i=1; i<=num; i++) {
        if (lib[i]==var) {
            temp=1;
            break;
        }
        else
        {
            temp=0;
        }
    }
    return temp;
}

void declarevariabletop(char files[50])
{
    int sigoutbit;
    sigoutbit=detectoutputsignatur(files);
    cout<<"How many bits output has "<<sigoutbit<<endl;
    string input;
    int equal,assign,findand,findor,findxor,findinv;
    int n_declarevar=1;
    string declare_var[99999];
    string newstring[99999];

    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory;
    string finalinputfile=in_location+files;
    ifstream fin(finalinputfile);

    string extension=".smt2";
    string fileout_directory="/SMT2-LIB/";
    string out_location=location+fileout_directory+files;
    string outputfilename=out_location+extension;
    int correctextension;
    correctextension=outputfilename.find(".v",0);
    outputfilename.erase(correctextension,2);
    ofstream outfile(outputfilename);
    
    outfile<<"(set-option :produce-models true) ; enable model generation\n"<<endl;
    string tempofdefineconsts;
    for(int define_i=1;define_i<=sigoutbit-1;define_i++)
    {
       tempofdefineconsts=binaryvector(pow(2,define_i-1),sigoutbit);
       outfile<<"(define-fun const"<<define_i+1<<" () (_ BitVec "<<sigoutbit<<") #b"<<tempofdefineconsts<<")"<<endl;
    }
    while(getline(fin, input))
    {
        input=eraseblock(input);
        input=erasearray(input);
        input=erasesemicolon(input);
        string smtbegin="(assert (=";
        findand=input.find("&",0);
        int andinput1,andinput2;
        string andin1,andin2,andout;
        findor=input.find("|",0);
        string orin1,orin2,orout;
        findinv=input.find("!",0);
        //
        findxor=input.find("^",0);
        string xorin1,xorin2,xorout;
        assign=input.find("assign",0);
        if (findand>0) {
            equal=input.find("=",0);
            andout.assign(input,assign+6,equal-assign-6);
            //detectredundancydeclare(declare_var,andout,n_declarevar);
            //n_declarevar=detectredundancydeclareint(declare_var,andout,n_declarevar);
            declare_var[n_declarevar]=andout;
            n_declarevar++;
            andout=definethevarible(andout,sigoutbit);
            andin1.assign(input,equal+1,findand-equal-1);
            declare_var[n_declarevar]=andin1;
            n_declarevar++;
            andin1=definethevarible(andin1,sigoutbit);
            andin2.assign(input,findand+1,sizeof(input)-findand-1);
            declare_var[n_declarevar]=andin2;
            n_declarevar++;
            andin2=definethevarible(andin2,sigoutbit);         
        }
        else if(findor>0)
        {
            equal=input.find("=",0);
            orout.assign(input,assign+6,equal-assign-6);
            declare_var[n_declarevar]=orout;
            n_declarevar++;
            orout=definethevarible(orout,sigoutbit);
            orin1.assign(input,equal+1,findor-equal-1);
            declare_var[n_declarevar]=orin1;
            n_declarevar++;
            orin1=definethevarible(orin1,sigoutbit);
            orin2.assign(input,findor+1,sizeof(input)-findor-1);
            declare_var[n_declarevar]=orin2;
            n_declarevar++;
            orin2=definethevarible(orin2,sigoutbit);
        }
        else if(findxor>0)
        {
            equal=input.find("=",0);
            xorout.assign(input,assign+6,equal-assign-6);
            declare_var[n_declarevar]=xorout;
            n_declarevar++;
            xorout=definethevarible(xorout,sigoutbit);
            xorin1.assign(input,equal+1,findxor-equal-1);
            declare_var[n_declarevar]=xorin1;
            n_declarevar++;
            xorin1=definethevarible(xorin1,sigoutbit);
            xorin2.assign(input,findxor+1,sizeof(input)-findxor-1);
            declare_var[n_declarevar]=xorin2;
            n_declarevar++;
            xorin2=definethevarible(xorin2,sigoutbit);
            
            
        }
    }
    // outfile<<n_declarevar<<endl;
    int newstringint=1;
    int temp;
    for (int iprint=1; iprint<=n_declarevar; iprint++) {
        temp=detectsamestring(newstring,declare_var[iprint], newstringint);
        if (temp==0) {
            newstring[newstringint]=declare_var[iprint];
            newstringint++;
            cout<<newstringint<<endl;
        }
        else
        {
            
        }
    }

    for (int i22=1; i22<=newstringint;i22++) {
        cout<<newstring[i22];
    }
    for(int sigoutbitdeclare=0;sigoutbitdeclare<sigoutbit;sigoutbitdeclare++)
    {
        outfile<<"(declare-fun z"<<sigoutbitdeclare<<" () "<<"(_ BitVec 1))"<<endl;
    }
    string printoutdeclare;
    for (int i=1; i<newstringint; i++) {
        printoutdeclare=declarefunction(newstring[i]);
        outfile<<printoutdeclare<<endl;
    } 
}

void assertpart(char files[50])
{
    int sigoutbit;
    sigoutbit=detectoutputsignatur(files);
    string constzero=binaryvector(0,sigoutbit);
    string input;
    int equal,assign,findand,findor,findxor,findinv;
    int n_declarevar=1;
    string location(getcwd(NULL,0));
    string filein_directory="/verilogGenerated/";
    string in_location=location+filein_directory;
    string finalinputfile=in_location+files;
    ifstream fin(finalinputfile);
   

    string extension=".smt2";
    string fileout_directory="/SMT2-LIB/";
    string out_location=location+fileout_directory+files;
    string outputfilename=out_location+extension;
    int correctextension;
    correctextension=outputfilename.find(".v",0);
    outputfilename.erase(correctextension,2);
    ofstream outfile(outputfilename,ios::app);
    while(getline(fin, input))
    {
        input=eraseblock(input);
        input=erasearray(input);
        input=erasesemicolon(input);
        
        string smtbegin="(assert (=";
        findand=input.find("&",0);
        int andinput1,andinput2;
        string andin1,andin2,andout;
        findor=input.find("|",0);
        string orin1,orin2,orout;
        findinv=input.find("!",0);
        //
        findxor=input.find("^",0);
        string xorin1,xorin2,xorout;
        assign=input.find("assign",0);
        if (findand>0) {
            equal=input.find("=",0);
            andout.assign(input,assign+6,equal-assign-6);

            andout=definethevarible(andout,sigoutbit);
            andin1.assign(input,equal+1,findand-equal-1);
 
            andin1=definethevarible(andin1,sigoutbit);
            andin2.assign(input,findand+1,sizeof(input)-findand-1);

            andin2=definethevarible(andin2,sigoutbit);
            outfile<<"(assert (= (bvadd "<<andout<<"(bvneg (bvmul "<<andin1<<andin2<<"))) #b"<<constzero<<"))"<<endl;
            
        }
        else if(findor>0)
        {
            equal=input.find("=",0);
            orout.assign(input,assign+6,equal-assign-6);

            orout=definethevarible(orout,sigoutbit);
            orin1.assign(input,equal+1,findor-equal-1);

            orin1=definethevarible(orin1,sigoutbit);
            orin2.assign(input,findor+1,sizeof(input)-findor-1);

            orin2=definethevarible(orin2,sigoutbit);
            outfile<<"(assert (= (bvadd "<<orout<<" (bvneg (bvadd (bvadd"<<orin1<<orin2<<") (bvneg (bvmul "<<orin1<<orin2<<"))))) #b"<<constzero<<"))"<<endl;
            
        }
        else if(findxor>0)
        {
            equal=input.find("=",0);
            xorout.assign(input,assign+6,equal-assign-6);

            xorout=definethevarible(xorout,sigoutbit);
            xorin1.assign(input,equal+1,findxor-equal-1);

            xorin1=definethevarible(xorin1,sigoutbit);
            xorin2.assign(input,findxor+1,sizeof(input)-findxor-1);

            xorin2=definethevarible(xorin2,sigoutbit);
            outfile<<"(assert (= (bvadd "<<xorout<<" (bvneg (bvadd (bvadd"<<xorin1<<xorin2<<") (bvneg (bvmul (bvmul "<<xorin1<<xorin2<<") const2))))) #b"<<constzero<<"))"<<endl;
        }
    }
    outfile<<endl;
    outfile<<"(check-sat)\n"
    "(get-model)\n"
    "(exit)\n";
}

void BenchGensmt2::smt2fromverilog(char files[50])
{
    declarevariabletop(files);
    assertpart(files);

}

//
//  EqnBenchGen.cpp
//  Tools
//
//  Created by Cunxi Yu on 7/18/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include "EqnBenchGen.h"
#include <cmath>
using namespace std;

void EqnBenchGen::gatelevelAdderEqn(int x)
//The gate level Verilog HDL code for circuit-(a+b)
{
    int pw;
x--;

cout<<"and0 = a0 * b0"<<endl;
cout<<"add_cout0 = and0"<<endl;
cout<<"add_sum0 = a0 + b0 - 2 * a0 * b0"<<endl;
for (int i=1; i<=x; i++) {
if (i!=x) {


cout<<"and"<<3*i-2<<" = add_cout"<<i-1<<" * a"<<i<<endl;
cout<<"and"<<3*i-1<<" = add_cout"<<i-1<<" * b"<<i<<endl;
cout<<"and"<<3*i<<" = a"<<i<<" * b"<<i<<endl;
cout<<"or"<<i<<" = and"<<3*i-2<<" + "<<"and"<<3*i-1<<" - and"<<3*i-2<<" * "<<"and"<<3*i-1<<endl;
cout<<"add_cout"<<i<<" = or"<<i<<" + ""and"<<3*i<<" - or"<<i<<" * ""and"<<3*i<<endl;
// cout<<" add_cout"<<i<<" = and_"<<3*i-2<<" | "<<"and_"<<3*i-1<<" | "<<"and_"<<3*i<<endl;
cout<<"xor"<<i<<" = a"<<i<<" + b"<<i<<" - 2 * a"<<i<<" * b"<<i<<endl;
cout<<"add_sum"<<i<<" = xor"<<i<<" + "<<"add_cout"<<i-1<<" - 2 * xor"<<i<<" * "<<"add_cout"<<i-1<<endl;
//cout<<" add_sum"<<i<<" = a"<<i<<" ^ b"<<i<<" ^ "<<"add_cout"<<i-1<<endl;
}
else
{
cout<<"and"<<3*i-2<<" = add_cout"<<i-1<<" * a"<<i<<endl;
cout<<"and"<<3*i-1<<" = add_cout"<<i-1<<" * b"<<i<<endl;
cout<<"and"<<3*i<<" = a"<<i<<" * b"<<i<<endl;
cout<<"or"<<i<<" = and"<<3*i-2<<" + "<<"and"<<3*i-1<<" - and"<<3*i-2<<" * "<<"and"<<3*i-1<<endl;
cout<<"add_sum"<<i+1<<" = or"<<i<<" + and"<<3*i<<"- or"<<i<<" * and"<<3*i<<endl;
cout<<"xor"<<i<<" = a"<<i<<" + b"<<i<<" - 2 * a"<<i<<" * b"<<i<<endl;
cout<<"add_sum"<<i<<" = xor"<<i<<" + "<<"add_cout"<<i-1<<" - 2 * xor"<<i<<" * "<<"add_cout"<<i-1<<endl;
}
}
    //Signature output print
    for (int sigout=0; sigout<=x+1; sigout++) {
        pw=pow(2, sigout);
        cout<<"add_sum"<<sigout<<"*"<<pw;
        if (sigout!=x+1) {
        cout<<" + ";
        }
        }
            cout<<endl;

}

void eqnMultstage1(int x,int y)
//N+1 bits * N bits
{
    x--;
    y--;
    int n=0;
    for (int i=0; i<=x; i++) {
        cout<<"     assign mult_stage1"<<"_and"<<n<<" = a["<<i<<"] & b[0];"<<endl;
        n++;
        cout<<"     assign mult_stage1"<<"_and"<<n<<" = a["<<i<<"] & b[1];"<<endl;
        n++;
    }
    cout<<"     assign z[0] = a[0] & b[0];"<<endl;
    // cout<<"     assign mult_stage1_cout0 = mult_stage1_and0;"<<endl;
    for (int i_add=1; i_add<=x; i_add++) {
        if (i_add!=1) {
            cout<<"     assign mult_stage1_sum"<<i_add-1<<" = mult_stage1_and"<<2*i_add-1<<" ^ mult_stage1_and"<<2*i_add<<";"<<endl;
            cout<<"     assign mult_stage1_cout"<<i_add-1<<" = mult_stage1_and"<<2*i_add-1<<" & mult_stage1_and"<<2*i_add<<";"<<endl;
            
        }
        else
        {
            cout<<"     assign z[1] = mult_stage1_and1 ^ mult_stage1_and2;"<<endl;
            cout<<"     assign mult_stage1_cout"<<i_add-1<<" = mult_stage1_and"<<i_add<<" & mult_stage1_and"<<i_add+1<<";"<<endl;
        }
    }
    cout<<" /* This is the CSA multiplier first Stage.*/"<<endl;
}
//After first stage

void eqnMultstage2(int x_1,int x_2)
{
    for (int stage2=2; stage2<=x_2-1; stage2++) {
        for (int fulladder=0; fulladder<=x_1-2; fulladder++) {
            
            if (fulladder==x_1-2) {
                // cout<<"     assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( a["<<fulladder<<"] & b["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (a["<<fulladder+1<<"] & b["<<stage2-1<<"]"<<" & a["<<fulladder<<"] & b["<<stage2<<"]) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & a["<<fulladder+1<<"] & b["<<stage2-1<<"]"<<");"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" = a["<<fulladder<<"] & b["<<stage2<<"];"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" = a["<<fulladder+1<<"] & b["<<stage2-1<<"];"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_and"<<5*(fulladder+1)<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" & mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-1<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<5*(fulladder+1)<<";"<<endl;
                
                
                //cout<<"     assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = ( a["<<fulladder<<"] & b["<<stage2<<"] ) ^ (a["<<fulladder+1<<"] & b["<<stage2-1<<"])"<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-4<<" ^ mult_stage"<<stage2<<"_and"<<5*(fulladder+1)-3<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
            }
            else if(fulladder==0)
            {
                //cout<<"     assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( a["<<fulladder<<"] & b["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & a["<<fulladder<<"] & b["<<stage2<<"]) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a["<<fulladder<<"] & b["<<stage2<<"];"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //cout<<"     assign z["<<stage2<<"] = ( a["<<fulladder<<"] & b["<<stage2<<"] ) ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                cout<<"     assign z["<<stage2<<"] = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                
            }
            
            else
            {
                //cout<<"     assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = ( a["<<fulladder<<"] & b["<<stage2<<"] & mult_stage"<<stage2-1<<"_cout"<<fulladder<<" ) | (mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" & (a["<<fulladder<<"] & b["<<stage2<<"]) ) | (mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<");"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" = a["<<fulladder<<"] & b["<<stage2<<"];"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<" = mult_stage"<<stage2-1<<"_cout"<<fulladder<<" & mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_or"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-2<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-1<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_cout"<<fulladder<<" = mult_stage"<<stage2<<"_or"<<fulladder<<" | mult_stage"<<stage2<<"_and"<<4*(fulladder+1)<<";"<<endl;
                
                //cout<<"     assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = ( a["<<fulladder<<"] & b["<<stage2<<"] ) ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                cout<<"      assign mult_stage"<<stage2<<"_xor"<<fulladder<<" = mult_stage"<<stage2<<"_and"<<4*(fulladder+1)-3<<" ^ mult_stage"<<stage2-1<<"_sum"<<fulladder+1<<";"<<endl;
                cout<<"     assign mult_stage"<<stage2<<"_sum"<<fulladder<<" = mult_stage"<<stage2<<"_xor"<<fulladder<<" ^ mult_stage"<<stage2-1<<"_cout"<<fulladder<<";"<<endl;
                
            }
            
        }
    }
    
}

//Last stage of CSA Multiplier
void eqnMultlastStage(int x_1,int x_2)
{
    cout<<"/*This is the LAST stage for CSA multiplier.*/"<<endl;
    for (int fulladder=0; fulladder<=x_1-1; fulladder++) {
        if(fulladder==0)
        {
            cout<<"     assign mult_laststage_cout"<<fulladder<<" = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            cout<<"     assign z["<<x_2+fulladder<<"] = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else if (fulladder==x_1-1)
        {
            //cout<<"     assign mult_laststage_cout"<<fulladder<<" = (a["<<x_1-1<<"] & b["<<x_2-1<<"]"<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | (a["<<x_1-1<<"] & b["<<x_1-1<<"] & mult_laststage_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage_cout"<<fulladder-1<<");"<<endl;
            cout<<"     assign z["<<x_2+x_1-1<<"] = mult_laststage_cout"<<fulladder-1<<";"<<endl;
        }
        else if(fulladder==x_1-2)
        {
            //cout<<"     assign mult_laststage_cout"<<fulladder<<" = ( a["<<x_1-1<<"] & b["<<x_2-1<<"] & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | ( a["<<x_1-1<<"] & b["<<x_2-1<<"] & mult_laststage"<<"_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            cout<<"     assign mult_laststage_and"<<4*fulladder-3<<" = a["<<x_1-1<<"] & b["<<x_2-1<<"];"<<endl;
            cout<<"     assign mult_laststage_and"<<4*fulladder-2<<" = mult_laststage_and"<<4*fulladder-3<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            cout<<"     assign mult_laststage_and"<<4*fulladder-1<<" = mult_laststage_and"<<4*fulladder-3<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            cout<<"     assign mult_laststage_and"<<4*fulladder<<" = mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            cout<<"     assign mult_laststage_or"<<fulladder<<" = mult_laststage_and"<<4*fulladder-2<<" | mult_laststage_and"<<4*fulladder-1<<";"<<endl;
            cout<<"     assign mult_laststage_cout"<<fulladder<<" = mult_laststage_or"<<fulladder<<" | mult_laststage_and"<<4*fulladder<<";"<<endl;
            //cout<<"     assign z["<<x_2+fulladder<<"] = mult_laststage_cout"<<fulladder-1<<" ^ ( a["<<x_1-1<<"] & b["<<x_2-1<<"] ) ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            cout<<"     assign mult_laststage_xor"<<fulladder<<" = mult_laststage_cout"<<fulladder-1<<" ^ mult_laststage_and"<<4*fulladder-3<<";"<<endl;
            cout<<"     assign z["<<x_2+fulladder<<"] = mult_laststage_xor"<<fulladder<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
        }
        else
        {
            
            
            //cout<<"     assign mult_laststage_cout"<<fulladder<<" = (mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<") | (mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_laststage"<<"_cout"<<fulladder-1<<") | (mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<");"<<endl;
            cout<<"     assign mult_laststage_and"<<4*fulladder-3<<" = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            cout<<"     assign mult_laststage_and"<<4*fulladder-2<<" = mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            cout<<"     assign mult_laststage_and"<<4*fulladder-1<<" = mult_stage"<<x_2-1<<"_cout"<<fulladder<<" & mult_laststage"<<"_cout"<<fulladder-1<<";"<<endl;
            cout<<"     assign mult_laststage_or"<<fulladder<<" = mult_laststage_and"<<4*fulladder-3<<" | mult_laststage_and"<<4*fulladder-2<<";"<<endl;
            cout<<"     assign mult_laststage_cout"<<fulladder<<" = mult_laststage_or"<<fulladder<<" | mult_laststage_and"<<4*fulladder-1<<";"<<endl;
            //cout<<"     assign z["<<x_2+fulladder<<"] = mult_laststage_cout"<<fulladder-1<<" ^ mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            cout<<"     assign mult_laststage_xor"<<fulladder<<" = mult_laststage_cout"<<fulladder-1<<" ^ mult_stage"<<x_2-1<<"_sum"<<fulladder+1<<";"<<endl;
            cout<<"     assign z["<<x_2+fulladder<<"] = mult_laststage_xor"<<fulladder<<" ^ mult_stage"<<x_2-1<<"_cout"<<fulladder<<";"<<endl;
            
        }
    }

}
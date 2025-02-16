//
//  BenchGen-Shifter.cpp
//  Tools
//
//  Created by Cunxi Yu on 7/25/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#include "BenchGen-Shifter.h"
using namespace std;
//1 bit shift: shift_ctr controls R/L

void BenchGenShifter::mean_max_mux1(int x)
{
    cout<<"    assign mux1_sbar = !comp1_sel;"<<endl;
    for (int i=1; i<=x; i++) {
        cout<<"    assign mux1_and"<<2*i-1<<" = a["<<i-1<<"] & mux1_sbar;"<<endl;
        cout<<"    assign mux1_and"<<2*i<<" = b["<<i-1<<"] & comp1_sel;"<<endl;
        cout<<"    assign mux1_out["<<i-1<<"] = mux1_and"<<2*i-1<<" | mux1_and"<<2*i<<";"<<endl;
    }
}


void BenchGenShifter::Barrelshifter(int x)
{
    cout<<"    assign s_bar = !s"<<endl;
    for (int mux=1; mux<=x; mux++) {
        if (mux!=x) {
            cout<<"    assign and"<<2*mux-1<<"shift_a["<<mux-1<<"] & s_bar;"<<endl;
            cout<<"    assign and"<<2*mux<<"shift_a["<<mux<<"] & s;"<<endl;
        }
        else
        {
            cout<<"    assign and"<<2*mux-1<<"shift_a["<<mux-1<<"] & s_bar;"<<endl;
            cout<<"    assign and"<<2*mux<<"shift_a[0] & s;"<<endl;
        }
    }
}

void RightShift1bit(int x)
{
    cout<<"    assign s = 1'b0;"<<endl;
    cout<<"    assign s_bar = !s;"<<endl;
    for (int mux=1; mux<=x; mux++) {
        if (mux!=x) {
            cout<<"    assign and"<<2*mux-1<<"1'b0"<<mux-1<<" & s_bar;"<<endl;
            cout<<"    assign and"<<2*mux<<"shift_a["<<mux<<"] & s;"<<endl;
        }
        else
        {
            cout<<"    assign and"<<2*mux-1<<"shift_a["<<mux-1<<"] & s_bar;"<<endl;
            cout<<"    assign and"<<2*mux<<"shift_a[0] & s;"<<endl;
        }
    }

}

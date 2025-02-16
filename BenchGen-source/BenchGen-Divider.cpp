#include "BenchGen-Divider.h"

#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

void BenchGenDivider::ArrayNonRestoringDiv(int bit)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Divider_NonRestor";
    int fileint=bit;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename);


    outfile<<"module nonrestoringArrayDiv(x,d,q,r);"<<endl;
    outfile<<"  input ["<<2*bit-2<<":0] x;"<<endl;
    outfile<<"  input ["<<bit-1<<":0] d;"<<endl;
    outfile<<"  output ["<<bit-1<<":0] q;"<<endl;
    outfile<<"  output ["<<bit-1<<":0] r"<<endl;
    outfile<<"    assign inv = !x[0];"<<endl;
    outfile<<"    assign T1 = inv ^ d[0];"<<endl;
    for (int row=1; row<=bit; row++) {
        if (row==1) {
            
        for (int i=1; i<=bit; i++) {
            outfile<<"    assign control_1_"<<i<<" = T1 ^ d["<<i-1<<"];"<<endl;;
            outfile<<"    assign and_1_"<<3*i-2<<" = control_1_"<<i<<" & x["<<i-1<<"];"<<endl;
            if (i!=bit) {
                    outfile<<"    assign and_1_"<<3*i-1<<" = control_1_"<<i<<" & cout_1_"<<i<<";"<<endl;
                    outfile<<"    assign and_1_"<<3*i<<" = x["<<i-1<<"] & cout_1_"<<i<<";"<<endl;
            }
            else
            {
                    outfile<<"    assign and_1_"<<3*i-1<<" = control_1_"<<i<<" & T1 ;"<<endl;
                    outfile<<"    assign and_1_"<<3*i<<" = x["<<i-1<<"] & T1 ;"<<endl;
            }
            
            outfile<<"    assign or_1_"<<i<<" = and_1_"<<3*i-2<<" | and_1_"<<3*i-1<<";"<<endl;
            if (i==1) {
                    outfile<<"    assign q[0] = or_1_"<<i<<" | and_1_"<<3*i<<";"<<endl;
            }
            else
            {
                    outfile<<"    assign cout_1_"<<i-1<<" = or_1_"<<i<<" | and_1_"<<3*i<<";"<<endl;
            }

            outfile<<"    assign xor_1_"<<i<<" = control_1_"<<i<<" ^ x["<<i-1<<"];"<<endl;
            if (i!=bit) {
                    outfile<<"    assign r_1_"<<i-1<<" = xor_1_"<<i<<" ^ cout_1_"<<i<<";"<<endl;
            }
            else
            {
                    outfile<<"    assign r_1_"<<i-1<<" = xor_1_"<<i<<" ^ T1;"<<endl;
            }
            outfile<<endl;
        }
        }
        //row 1
        else if (row!=bit)
        {
            for (int i=1; i<=bit; i++) {
                outfile<<"    assign control_"<<row<<"_"<<i<<" = q["<<row-2<<"] ^ d["<<i-1<<"];"<<endl;;
                if (i!=bit) {
                    outfile<<"    assign and_"<<row<<"_"<<3*i-2<<" = control_"<<row<<"_"<<i<<" & r_"<<row-1<<"_"<<i<<";"<<endl;
                    outfile<<"    assign and_"<<row<<"_"<<3*i-1<<" = control_"<<row<<"_"<<i<<" & cout_"<<row<<"_"<<i<<";"<<endl;
                    outfile<<"    assign and_"<<row<<"_"<<3*i<<" = r_"<<row-1<<"_"<<i<<" & cout_"<<row<<"_"<<i<<";"<<endl;
                }
                else
                {
                    outfile<<"    assign and_"<<row<<"_"<<3*i-2<<" = control_"<<row<<"_"<<i<<" & x["<<i+row-2<<"];"<<endl;
                    outfile<<"    assign and_"<<row<<"_"<<3*i-1<<" = control_"<<row<<"_"<<i<<" & q["<<row-2<<"];"<<endl;
                    outfile<<"    assign and_"<<row<<"_"<<3*i<<" = x["<<i+row-2<<"] & q["<<row-2<<"];"<<endl;
                }
                
                outfile<<"    assign or_"<<row<<"_"<<i<<" = and_"<<row<<"_"<<3*i-2<<" | and_"<<row<<"_"<<3*i-1<<";"<<endl;
                if (i==1) {
                    outfile<<"    assign q["<<row-1<<"] = or_"<<row<<"_"<<i<<" | and_"<<row<<"_"<<3*i<<";"<<endl;
                }
                else
                {
                    outfile<<"    assign cout_"<<row<<"_"<<i-1<<" = or_"<<row<<"_"<<i<<" | and_"<<row<<"_"<<3*i<<";"<<endl;
                }
                if (i==bit) {
                        outfile<<"    assign xor_"<<row<<"_"<<i<<" = control_"<<row<<"_"<<i<<" ^ x["<<i+row-2<<"];"<<endl;
                        outfile<<"    assign r_"<<row<<"_"<<i-1<<" = xor_"<<row<<"_"<<i<<" ^ q["<<row-2<<"];"<<endl;
                }
                else
                {
                        outfile<<"    assign xor_"<<row<<"_"<<i<<" = control_"<<row<<"_"<<i<<" ^ r_"<<row-1<<"_"<<i<<";"<<endl;
                        outfile<<"    assign r_"<<row<<"_"<<i-1<<" = xor_"<<row<<"_"<<i<<" ^ cout_"<<row<<"_"<<i<<";"<<endl;
                }
                outfile<<endl;
            }
        }
        else
        {
            for (int i=1; i<=bit; i++) {
                outfile<<"    assign control_"<<row<<"_"<<i<<" = q["<<row-2<<"] ^ d["<<i-1<<"];"<<endl;;
                if (i!=bit) {
                        outfile<<"    assign and_"<<row<<"_"<<3*i-2<<" = control_"<<row<<"_"<<i<<" & r_"<<row-1<<"_"<<i<<";"<<endl;
                        outfile<<"    assign and_"<<row<<"_"<<3*i-1<<" = control_"<<row<<"_"<<i<<" & cout_"<<row<<"_"<<i<<";"<<endl;
                        outfile<<"    assign and_"<<row<<"_"<<3*i<<" = r_"<<row-1<<"_"<<i<<" & cout_"<<row<<"_"<<i<<";"<<endl;
                }
                else
                {
                        outfile<<"    assign and_"<<row<<"_"<<3*i-2<<" = control_"<<row<<"_"<<i<<" & x["<<i+row-2<<"];"<<endl;
                        outfile<<"    assign and_"<<row<<"_"<<3*i-1<<" = control_"<<row<<"_"<<i<<" & q["<<row-2<<"];"<<endl;
                        outfile<<"    assign and_"<<row<<"_"<<3*i<<" = x["<<i+row-2<<"] & q["<<row-2<<"];"<<endl;
                }
                
                outfile<<"    assign or_"<<row<<"_"<<i<<" = and_"<<row<<"_"<<3*i-2<<" | and_"<<row<<"_"<<3*i-1<<";"<<endl;
                if (i==1) {
                    outfile<<"    assign q["<<row-1<<"] = or_"<<row<<"_"<<i<<" | and_"<<row<<"_"<<3*i<<";"<<endl;
                }
                else
                {
                    outfile<<"    assign cout_"<<row<<"_"<<i-1<<" = or_"<<row<<"_"<<i<<" | and_"<<row<<"_"<<3*i<<";"<<endl;
                }
                if (i==bit) {
                    outfile<<"    assign xor_"<<row<<"_"<<i<<" = control_"<<row<<"_"<<i<<" ^ x["<<i+row-2<<"];"<<endl;
                    outfile<<"    assign r["<<i-1<<"] = xor_"<<row<<"_"<<i<<" ^ q["<<row-2<<"];"<<endl;
                }
                else
                {
                    outfile<<"    assign xor_"<<row<<"_"<<i<<" = control_"<<row<<"_"<<i<<" ^ r_"<<row-1<<"_"<<i<<";"<<endl;
                    outfile<<"    assign r["<<i-1<<"] = xor_"<<row<<"_"<<i<<" ^ cout_"<<row<<"_"<<i<<";"<<endl;
                }
                outfile<<endl;
            }

        }
    }
    outfile<<"endmodule"<<endl;
}

void BenchGenDivider::hierarchicalRestoringDiv(int x)
{
    string location(getcwd(NULL,0));
    string verilogdirectory="/verilogGenerated/";
    location+=verilogdirectory;
    stringstream outfilename;
    string filename="Divider_Restoring";
    int fileint=x;
    outfilename << filename << fileint << "Bits.v";
    string f=outfilename.str();
    string finaloutputfilename;
    finaloutputfilename=location+f;
    //outfile<<finaloutputfilename;
    ofstream outfile(finaloutputfilename);

    outfile<<"module restoringDiv(x,d,q,r);"<<endl;
    outfile<<"  input ["<<2*x<<":1] x;"<<endl;
    outfile<<"  input ["<<x<<":1] d;"<<endl;
    outfile<<"  output ["<<x<<":1] q,r;"<<endl;
    outfile<<"  wire ["<<x<<":1] p;"<<endl;
    outfile<<"  wire ["<<x-1<<":0] ";
    for (int wire=1; wire<=x; wire++) {
        if (wire!=x) {
        outfile<<"c"<<wire<<",s"<<wire<<",";
        }
        else
        {
            outfile<<"c"<<wire;
        }
    }
    outfile<<";"<<endl;
    for (int row=1; row<=x; row++) {
        if (row==1) {
            for (int i=1; i<=x; i++) {
                if(i==1)
                {
                    outfile<<"             CS cs"<<i<<"( x["<<x+row-i+1<<"],d["<<x-i+1<<"],1'b0,p["<<row<<"],s"<<row<<"["<<i-1<<"],c"<<row<<"["<<i-1<<"]);"<<endl;
                }
                else
                {
                    outfile<<"             CS cs"<<i<<"( x["<<x+row-i+1<<"],d["<<x-i+1<<"],c"<<row<<"["<<i-2<<"],p["<<row<<"],s"<<row<<"["<<i-1<<"],c"<<row<<"["<<i-1<<"]);"<<endl;
                }
            }
            outfile<<"             assign q["<<row<<"] = !c"<<row<<"["<<x-1<<"] | x[1] ;"<<endl;
            outfile<<"             assign p["<<row<<"] = !q["<<row<<"] ;"<<endl;
        }
        else if (row!=x)
        {
            for (int i=1; i<=x; i++) {
                if (i==1) {
                    outfile<<"             CS cs"<<x*(row-1)+i<<"( x["<<x+row-i+1<<"],d["<<x-i+1<<"],1'b0,p["<<row<<"],s"<<row<<"["<<i-1<<"],c"<<row<<"["<<i-1<<"]);"<<endl;
                }
                else
                {
                    outfile<<"             CS cs"<<x*(row-1)+i<<"( s"<<row-1<<"["<<i-2<<"],d["<<x-i+1<<"],c"<<row<<"["<<i-2<<"],p["<<row<<"],s"<<row<<"["<<i-1<<"],c"<<row<<"["<<i-1<<"]);"<<endl;
                }
            }
            outfile<<"             assign q["<<row<<"] = !c"<<row<<"["<<x-1<<"] | s"<<row-1<<"["<<x-1<<"] ;"<<endl;
            outfile<<"             assign p["<<row<<"] = !q["<<row<<"] ;"<<endl;
        }
        else
        {
            for (int i=1; i<=x; i++) {
                if (i==1) {
                    outfile<<"             CS cs"<<x*(row-1)+i<<"( x["<<x+row-i+1<<"],d["<<x-i+1<<"],1'b0,p["<<row<<"],r"<<"["<<x-i+1<<"],c"<<row<<"["<<i-1<<"]);"<<endl;
                }
                else
                {
                    outfile<<"             CS cs"<<x*(row-1)+i<<"( s"<<row-1<<"["<<i-2<<"],d["<<x-i+1<<"],c"<<row<<"["<<i-2<<"],p["<<row<<"],r"<<"["<<x-i+1<<"],c"<<row<<"["<<i-1<<"]);"<<endl;
                }
            }
            outfile<<"             assign q["<<row<<"] = !c"<<row<<"["<<x-1<<"] | s"<<row-1<<"["<<x-1<<"] ;"<<endl;
            outfile<<"             assign p["<<row<<"] = !q["<<row<<"] ;"<<endl;
        }
    }
    outfile<<"endmodule"<<endl<<endl;
    outfile<<"module CS(a,d,cin,p,s,cout);\n"
    "   input a,d,cin,p;\n"
    "   output s,cout;\n"
    "   wire s_inside;\n"
    "       assign cout= (!a & d) | (!a & cin) | (d & cin);\n"
    "       assign s_inside=a ^ d ^ cin;\n"
    "       assign s = (p & a) | (!p & s_inside);\n"
    "endmodule"<<endl;
    
}


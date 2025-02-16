//
//  BenchGen-Translate.h
//  Tools
//
//  Created by Cunxi Yu on 7/25/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#ifndef __Tools__BenchGen_Translate__
#define __Tools__BenchGen_Translate__

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class BenchGenTrans {
    
    
public:
    static void Translate(char file[50]);
    static void TranslateToCSF(string s);
    static void TranslatePoly(char file[50]);
    static void TranslateReverse(char file[50]);
    static void NoneReverseTranslate(char s[50]);
    static void TranslateToCSF_TopSig(string s);
    static void NEW_parse_outputfile(string file_in);
    static vector<string> AllVerilogNeed2CSF();
};

#endif /* defined(__Tools__BenchGen_Translate__) */

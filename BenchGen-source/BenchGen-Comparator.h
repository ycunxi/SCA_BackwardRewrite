//
//  BenchGen-Comparator.h
//  Tools
//
//  Created by Cunxi Yu on 7/16/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#ifndef __Tools__BenchGen_Comparator__
#define __Tools__BenchGen_Comparator__

#include <iostream>

class BenchGenComparator{
    
    
public:
    static void comp(int x);
    static void signedadder(int x);
    static void compRTL(int x);
    static void FindMaxNumber(int x);
    static void FindMinNumber(int x);
    static void FindMaxNumberRTL(int x);
    static void FindMinNumberRTL(int x);
    static void FindMeanNumber(int x);
    static void FindMeanNumberRTL(int x);
    static void GenMathModelofComparator(int bit);
};

#endif /* defined(__Tools__BenchGen_Comparator__) */

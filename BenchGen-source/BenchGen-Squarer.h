//
//  BenchGen-Squarer.h
//  Tools
//
//  Created by Cunxi Yu on 7/29/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#ifndef __Tools__BenchGen_Squarer__
#define __Tools__BenchGen_Squarer__

#include <iostream>

class BenchGenSquare {
    
    
public:
    static void datapathAddSquare(int x);
    static void PowThreeSqMultiply(int x);
    static void PowTwoSqMultiplyRTL(int x);
    static void PowThreeSqMultiplyRTL(int x);

    
};

#endif /* defined(__Tools__BenchGen_Squarer__) */

//
//  BenchGen-Matrix.h
//  Tools
//
//  Created by Cunxi Yu on 7/20/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#ifndef __Tools__BenchGen_Matrix__
#define __Tools__BenchGen_Matrix__

#include <iostream>

class BenchGenMatrix {
    
    
public:
    static void MatrixMultiply(int x);
    static void ThreeMultAndAddition(int x);
    static void ThreeMultAndAdditionRTL(int x);
    static void MatrixMultiplyRTL(int x);
};
#endif /* defined(__Tools__BenchGen_Matrix__) */

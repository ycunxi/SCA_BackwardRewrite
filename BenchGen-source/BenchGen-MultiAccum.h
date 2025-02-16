//
//  BenchGen-MultiAccum.h
//  Tools
//
//  Created by Cunxi Yu on 7/14/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#ifndef __Tools__BenchGen_MultiAccum__
#define __Tools__BenchGen_MultiAccum__

#include <iostream>

class BenchGen_MultiAccum{
private:
 
    
public:
    static void MultiplyAccum(int bit);
    static void RTLMultilyAccum(int x);
    static void MacModelGen(int x);
    static void MacModelGen4Clock(int x);
    static void MacModelGen6Clock(int x);

    
};

#endif /* defined(__Tools__BenchGen_MultiAccum__) */

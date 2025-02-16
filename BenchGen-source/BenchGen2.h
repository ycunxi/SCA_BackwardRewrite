//
//  BenchGen2.h
//  Tools
//
//  Created by Cunxi Yu on 7/13/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#ifndef __Tools__BenchGen2__
#define __Tools__BenchGen2__

#include <iostream>


class BenchGen2 {
private:
  //  int bit;
    
public:
    static void RippleCarryAdder(int bit);
    //static void AdderMix(int bit);
    static void MixAddMultiply(int bit1,int bit2);
    static void MixAddMultRTL(int x);
    static void subtracotrTwoComplement(int x);


    
};

#endif /* defined(__Tools__BenchGen2__) */

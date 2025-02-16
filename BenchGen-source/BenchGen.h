//
//  function.h
//  BenchmarkGenerator
//
//  Created by Cunxi Yu on 7/10/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#ifndef BenchGen_h
#define BenchGen_h


class BenchGen
{
    int bit1,bit2;
    
public:
    static void  welcomeTile();
    static void  arbitraryRTLAdder(int x);
    static void  MixhighlevelRTL(int bit1);
    static void  gatelevelbenchADD(int bit1);
    static void  gatelevelAdder(int x);
    static void  EntierMultiplierGen(int bit1,int bit2);
    static void  MultiplierRTL(int x);
    
};


#endif


//
//  BenchGen-DesginCompilerTran.h
//  tranTO-ABC
//
//  Created by Cunxi Yu on 9/1/14.
//  Copyright (c) 2014 Cunxi Yu. All rights reserved.
//

#ifndef __tranTO_ABC__BenchGen_DesginCompilerTran__
#define __tranTO_ABC__BenchGen_DesginCompilerTran__

#include <iostream>

class BenchGenDCtran {
    
    
public:
    static void unitlibtran(char file[50]);
    static void dcVerilogToBlif(char *file);
    static void dcVerilogToBlifToVerilog(char *filename);
};

#endif /* defined(__tranTO_ABC__BenchGen_DesginCompilerTran__) */


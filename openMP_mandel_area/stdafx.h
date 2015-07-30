// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <omp.h>
#define NPOINTS 1000
#define MXITR 1000

void testpoint(struct d_complex c);

struct d_complex{
	double r; 
	double i;
};



// TODO: reference additional headers your program requires here

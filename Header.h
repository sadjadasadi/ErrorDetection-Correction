#pragma once

#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include <conio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;


#define memFileAddr "mem.bin"
#define LmemFileAddr "Lmem.bin"
#define rows 16384  //4 
#define cols 64  //4 


bool create_memory(string addr);
bool read_memory(bool mem[rows][cols], string addr);


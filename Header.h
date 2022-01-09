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


#define MEM_FILE_ADDR "mem.bin"
#define LmemFileAddr "Lmem.bin"
#define ROWS 16384  //4 
#define COLS 64  //4 

#define PARITY_No 3  //number of parity bit
#define CRC_No 33
#define FAULT_No 5    //number of error bit injection



bool create_memory(string addr);
bool read_memory(bool mem[ROWS][COLS], string addr);

float even_parity(bool org_mem[ROWS][COLS], bool CEPB[ROWS][COLS + PARITY_No], bool FEPB[ROWS][COLS + PARITY_No], bool burst);
float odd_parity(bool org_mem[ROWS][COLS], bool COPB[ROWS][COLS + PARITY_No], bool FOPB[ROWS][COLS + PARITY_No], bool burst);
float comb_parity(bool org_mem[ROWS][COLS], bool CCPB[ROWS][COLS + PARITY_No * 2], bool FCPB[ROWS][COLS + PARITY_No * 2], bool burst);
float parity_2d(bool org_mem[ROWS][COLS], bool C_2dPB[ROWS][COLS + PARITY_No * 2], bool F_2dPB[ROWS][COLS + PARITY_No * 2], bool burst);

float single_checksum(bool org_mem[ROWS][COLS], bool CSingleChksum[ROWS + 1][COLS], bool FSingleChksum[ROWS + 1][COLS], bool burst);

bool  fault_inject(int fault_P[][FAULT_No], int rows, int cols, bool burst);

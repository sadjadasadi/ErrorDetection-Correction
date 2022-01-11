#include"Header.h"

int main()
{
	clock_t start = clock();

	// first step you must create memory with random binary number 
	//create_memory(MEM_FILE_ADDR);

	bool mem[ROWS][COLS] = {};
	read_memory(mem, MEM_FILE_ADDR);

	// CPb (Correct Praity bit) FPb (Fault Parity bit)
	
	//bool CPb[ROWS][COLS + PARITY_No] = {};
	//bool FPb[ROWS][COLS + PARITY_No] = {};

	// CPb (Correct Combitional Praity bit) FPb (Fault Combitional Parity bit)
	//bool CCPb[ROWS][COLS + 2 * PARITY_No] = {};
	//bool FCPb[ROWS][COLS + 2 * PARITY_No] = {};

	// CPb (Correct 2D Praity bit) FPb (Fault 2D Parity bit)
	//bool C_2dPb[ROWS][COLS + 2 * PARITY_No] = {};
	//bool F_2dPb[ROWS][COLS + 2 * PARITY_No] = {};

	// CSChkSum (Correct Single CheckSum) FSChkSum (Fault Single CheckSum)
	//bool CSChkSum[ROWS + 1][COLS] = {};
	//bool FSChkSum[ROWS + 1][COLS] = {};

	// CHChkSum (Correct Honneywell CheckSum) FHChkSum (Fault Honneywell CheckSum)
	//bool CHChkSum[ROWS + 2][COLS] = {};
	//bool FHChkSum[ROWS + 2][COLS] = {};

	// CRChkSum (Correct residue CheckSum) FRChkSum (Fault residue CheckSum)
	//bool CRChkSum[ROWS + 1][COLS] = {};
	//bool FRChkSum[ROWS + 1][COLS] = {};

	// CCRCcode (Correct Cyclic Redundancy Check) FCRCcode (Fault Cyclic Redundancy Check)
	//bool CCRCcode[ROWS][COLS + CRC_No - 1] = {};
	//bool FCRCcode[ROWS][COLS + CRC_No - 1] = {};
	// standard polynomial(divisor) { x^32,x^31,x^30,x^29,x^28,x^27,...,x^6,x^5,x^4,x^3,x^2,x^1,x^0}
	//bool divisor[CRC_No] = { 1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,1,0,1,0,1,0,1,1 };
	//bool divisor[CRC_No] = { 1,0,1,1,1,0,1,0,0,0,0,0,1,1,0,1,1,1,0,0,0,1,1,0,0,1,1,0,1,0,1,1,1 };

	// CHammingcode (Correct Hammingcode) FHammingcode (Fault Hammingcode) DCEHammingcode (Detect and Correct Error Hammingcode)
	bool CHammingcode[ROWS][COLS + (COLS / 4 * 3)] = {};
	bool FHammingcode[ROWS][COLS + (COLS / 4 * 3)] = {};
	bool DCEHammingcode[ROWS][COLS + (COLS / 4 * 3)] = {};


	//cout << "------------------------------------------------------------------------------------------\n";
	//cout << "Parity NO: " << PARITY_No  << "|Fault NO: " << FAULT_No << "|Burst: " << false << "|Probability of error detection(percent): " << even_parity(mem, CPb, FPb, false) << endl << endl;
	//cout << "Parity NO: " << PARITY_No  << "|Fault NO: " << FAULT_No << "|Burst:" << true << "|Probability of error detection(percent): " << even_parity(mem, CPb, FPb, true) << endl << endl;
	//cout << "------------------------------------------------------------------------------------------\n";
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst: " << false << "|Probability of error detection(percent): " << odd_parity(mem, CPb, FPb, false) << endl << endl;
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst:" << true << "|Probability of error detection(percent): " << odd_parity(mem, CPb, FPb, true) << endl << endl;

	//cout << "------------------------------------------------------------------------------------------\n";
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst: " << false << "|Probability of error detection(percent): " << comb_parity(mem, CCPb, FCPb, false) << endl << endl;
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst:" << true << "|Probability of error detection(percent): " << comb_parity(mem, CCPb, FCPb, true) << endl << endl;

	//cout << "------------------------------------------------------------------------------------------\n";
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst: " << false << "|Probability of error detection(percent): " << parity_2d(mem, C_2dPb, F_2dPb, false) << endl << endl;
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst:" << true << "|Probability of error detection(percent): " << parity_2d(mem, C_2dPb, F_2dPb, true) << endl << endl;

	//cout << "------------------------------------------------------------------------------------------\n";
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst: " << false << "|Probability of error detection(percent): " << single_checksum(mem, CSChkSum, FSChkSum, false) << endl << endl;
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst:" << true << "|Probability of error detection(percent): " << single_checksum(mem, CSChkSum, FSChkSum, true) << endl << endl;

	//cout << "------------------------------------------------------------------------------------------\n";
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst: " << false << "|Probability of error detection(percent): " << honeywell_checksum(mem, CHChkSum, FHChkSum, false) << endl << endl;
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst:" << true << "|Probability of error detection(percent): " << honeywell_checksum(mem, CHChkSum, FHChkSum, true) << endl << endl;

	//cout << "------------------------------------------------------------------------------------------\n";
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst: " << false << "|Probability of error detection(percent): " << residue_checksum(mem, CRChkSum, FRChkSum, false) << endl << endl;
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst:" << true << "|Probability of error detection(percent): " << residue_checksum(mem, CRChkSum, FRChkSum, true) << endl << endl;

	//cout << "------------------------------------------------------------------------------------------\n";
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst: " << false << "|Probability of error detection(percent): " << cyclic_redundancy_check(mem, divisor, CCRCcode, FCRCcode, false) << endl << endl;
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst:" << true << "|Probability of error detection(percent): " << cyclic_redundancy_check(mem, divisor, CCRCcode, FCRCcode, false) << endl << endl;


	//cout << "------------------------------------------------------------------------------------------\n";
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst: " << false << "|Probability of error detection(percent): " << comb_CRC(mem, divisor, CCRCcode, FCRCcode, false) << endl << endl;
	//cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst:" << true << "|Probability of error detection(percent): " << comb_(mem, divisor, CCRCcode, FCRCcode, false) << endl << endl;

	cout << "------------------------------------------------------------------------------------------\n";
	cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst: " << false << "|Probability of error detection(percent): " << hamming(mem, CHammingcode, FHammingcode, DCEHammingcode, false) << endl << endl;
	cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst:" << true << "|Probability of error detection(percent): " << hamming(mem, CHammingcode, FHammingcode, DCEHammingcode, true) << endl << endl;


	clock_t end = clock();
	cout << "\nElapsed Time : " << (double)(end-start) / CLOCKS_PER_SEC << " second" << "\n\n" << "finish";
	return 0;
}
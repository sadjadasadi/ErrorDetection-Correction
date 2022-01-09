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
	bool CHChkSum[ROWS + 2][COLS] = {};
	bool FHChkSum[ROWS + 2][COLS] = {};

	// CRChkSum (Correct residue CheckSum) FRChkSum (Fault residue CheckSum)
	bool CRChkSum[ROWS + 1][COLS] = {};
	bool FRChkSum[ROWS + 1][COLS] = {};


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

	cout << "------------------------------------------------------------------------------------------\n";
	cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst: " << false << "|Probability of error detection(percent): " << residue_checksum(mem, CRChkSum, FRChkSum, false) << endl << endl;
	cout << "Parity NO: " << PARITY_No << "|Fault NO: " << FAULT_No << "|Burst:" << true << "|Probability of error detection(percent): " << residue_checksum(mem, CRChkSum, FRChkSum, true) << endl << endl;


	clock_t end = clock();
	cout << "\nElapsed Time : " << (double)(end-start) / CLOCKS_PER_SEC << " second" << "\n\n" << "finish";
	return 0;
}
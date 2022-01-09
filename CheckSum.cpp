#include "Header.h"

float single_checksum(bool org_mem[ROWS][COLS], bool CSingleChksum[ROWS + 1][COLS], bool FSingleChksum[ROWS + 1][COLS], bool burst)
{
	//calc single checksum befor error injectin for correct data
	int carry = 0;
	int one = 0;
	bool Checksum[COLS] = {};
	for (int i = COLS - 1; i > -1; i--)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (org_mem[j][i])one++;
		}
		Checksum[i] = (carry + one) % 2;
		carry = (one + carry) / 2;
		one = 0;

		//check!
		//cout << "\n" << Checksum[i] << endl;
	}

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			CSingleChksum[i][j] = org_mem[i][j];
			FSingleChksum[i][j] = org_mem[i][j];
		}
	}

	for (int j = 0; j < COLS; j++)
	{
		CSingleChksum[ROWS][j] = Checksum[j];
		FSingleChksum[ROWS][j] = Checksum[j];
	}

	//check!
	/*for (int i = 0; i < ROWS + 1; i++)
	{
		cout << endl;
		for (int j = 0;j < COLS;j++)
		{
			cout << CSingleChksum[i][j];
		}

	}*/
	cout << "\n >Correct Single Checksum (CSChkSum) Finished\n";
	//=======================================================================================================================
	//error injection into correct data
	int fault_P[ROWS + 1][FAULT_No] = {};
	fault_inject(fault_P, ROWS + 1, COLS, burst);
	for (int i = 0; i < ROWS + 1; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			FSingleChksum[i][fault_P[i][j]] = !(FSingleChksum[i][fault_P[i][j]]);
		}
	}

	//check!
	/*for (int i = 0;i < ROWS + 1;i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			cout << FSingleChksum[i][j];
		}
		cout << endl;
	}*/
	cout << "\n >Fault Single Checksum (FSChkSum) Finished\n";
	//==========================================================================================================================
	
	//calc checksum for faulty data
	bool AChecksum[COLS] = {};
	carry = 0;
	one = 0;

	for (int i = COLS - 1; i > -1; i--)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (FSingleChksum[j][i])one++;
		}
		AChecksum[i] = (carry + one) % 2;
		carry = (one + carry) / 2;
		one = 0;
	}

	//check!
	/*cout << endl;
	for (int j = 0; j < COLS; j++)
	{
		cout << AChecksum[j] << " - " << FSingleChksum[ROWS][j] << " | ";
	}
	cout << endl;*/
	//============================================================================================
	//calc probabily of error detection 

	bool flag = true;
	for (int j = 0; j < COLS; j++)
	{
		if (AChecksum[j] != FSingleChksum[ROWS][j])
		{
			flag = false;
			break;
		}
	}

	if (flag) return 0;
	else return 100;
}

float honeywell_checksum(bool org_mem[ROWS][COLS], bool CHoneywellChkSum[ROWS + 2][COLS], bool FHoneywellChkSum[ROWS + 2][COLS], bool burst)
{
	//calc Honeywell checksum for correct data

	bool mem[ROWS / 2][COLS * 2] = {};
	bool Checksum[COLS * 2] = {};
	for (int i = 0; i < ROWS / 2; i++)
	{
		for (int j = 0; j < 2 * COLS; j++)
		{
			if (j < COLS) mem[i][j] = org_mem[(2 * i) + 1][j];

			else mem[i][j] = org_mem[2 * i][j - COLS];

			//check!
			//cout << mem[i][j];
		}
	}

	int carry = 0;
	int one = 0;

	for (int i = (2 * COLS) - 1; i > -1; i--)
	{
		for (int j = 0; j < ROWS / 2; j++)
		{
			if (mem[j][i])one++;
		}
		Checksum[i] = (carry + one) % 2;
		carry = (one + carry) / 2;
		one = 0;
		//check!
		//cout << "\n" << Checksum[i] << endl;
	}

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			CHoneywellChkSum[i][j] = org_mem[i][j];
			FHoneywellChkSum[i][j] = org_mem[i][j];
		}
	}
	for (int i = ROWS; i < ROWS + 2; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			CHoneywellChkSum[i][j] = Checksum[(i - ROWS) * COLS + j];
			FHoneywellChkSum[i][j] = Checksum[(i - ROWS) * COLS + j];
		}
	}

	//check!
	/*for (int i = 0;i < ROWS + 2;i++)
	{
		cout << endl;
		for (int j = 0;j < COLS;j++)
		{
			cout << CHoneywellChkSum[i][j];
		}
	}*/
	cout << "\n >Correct Honeywell Checksum (CHChkSum) Finished\n";
	//=====================================================================================================================
	//inject error into correct data

	int fault_P[ROWS + 2][FAULT_No] = {};
	fault_inject(fault_P, ROWS + 2, COLS, burst);
	for (int i = 0; i < ROWS + 2; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			FHoneywellChkSum[i][fault_P[i][j]] = !(FHoneywellChkSum[i][fault_P[i][j]]);
		}
	}

	//check!
	/*for (int i = 0;i < ROWS + 2;i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			cout << FHoneywellChkSum[i][j];
		}
		cout << endl;
	}*/
	cout << "\n >Fault Honneywell Checksum (FHChkSum) Finished\n";
	//==========================================================================================================================
	//calc Honeywell for fault data
	bool Fmem[ROWS / 2][COLS * 2] = {};
	bool AChecksum[COLS * 2] = {};
	for (int i = 0; i < ROWS / 2; i++)
	{
		for (int j = 0; j < 2 * COLS; j++)
		{
			if (j < COLS) Fmem[i][j] = FHoneywellChkSum[(2 * i) + 1][j];

			else Fmem[i][j] = FHoneywellChkSum[2 * i][j - COLS];
		}
	}
	carry = 0;
	one = 0;
	for (int i = (2 * COLS) - 1; i > -1; i--)
	{
		for (int j = 0; j < ROWS / 2; j++)
		{
			if (Fmem[j][i])one++;
		}
		AChecksum[i] = (carry + one) % 2;
		carry = (one + carry) / 2;
		one = 0;
	}

	//check!
	/*for (int i = 0;i < (2 * COLS); i++)
	{
		cout << AChecksum[i] << endl;
	}*/

	//============================================================================================
	//calc probability of error detection
	bool flag = true;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (AChecksum[j + COLS * i] != FHoneywellChkSum[ROWS + i][j])
			{
				flag = false;
				break;
			}
		}
		if (!flag) break;
	}
	if (flag) return 0;
	else return 100;
}

float residue_checksum(bool org_mem[ROWS][COLS], bool  CResidueChksum[ROWS + 1][COLS], bool  FResidueChksum[ROWS + 1][COLS], bool burst)
{
	//calc residue checksum for correct data
	
	int carry = 0;
	int one = 0;
	bool  Checksum[COLS] = {};
	for (int i = COLS - 1; i > -1; i--)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (org_mem[j][i])one++;
		}
		Checksum[i] = (carry + one) % 2;
		carry = (one + carry) / 2;
		one = 0;

		//check!
		//cout << "\n" << Checksum[i] << endl;
	}
	while (carry)
	{
		for (int i = COLS - 1; i > -1; i--)
		{
			if (Checksum[i]) one++;
			Checksum[i] = (carry + one) % 2;
			carry = (one + carry) / 2;
			one = 0;
			
			//check!
			//cout << "\n" << Checksum[i] << "---" << carry << endl;
		}
	}

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			CResidueChksum[i][j] = org_mem[i][j];
			FResidueChksum[i][j] = org_mem[i][j];
		}
	}
	for (int j = 0; j < COLS; j++)
	{
		CResidueChksum[ROWS][j] = Checksum[j];
		FResidueChksum[ROWS][j] = Checksum[j];
	}


	//check!
	/*for (int i = 0; i < ROWS + 1; i++)
	{
		cout << endl;
		for (int j = 0;j < COLS;j++)
		{
			cout << CResidueChksum[i][j];
		}
	}*/
	cout << "\n >Correct Residue Checksum (CRChkSum) Finished\n";
	//=======================================================================================================

	//inject error into correct data

	int fault_P[ROWS + 1][FAULT_No] = {};
	fault_inject(fault_P, ROWS + 1, COLS, burst);
	for (int i = 0; i < ROWS + 1; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			FResidueChksum[i][fault_P[i][j]] = !(FResidueChksum[i][fault_P[i][j]]);
		}
	}

	//check!
	//for (int i = 0;i < ROWS + 1;i++)
	//{
	//	for (int j = 0; j < COLS; j++)
	//	{
	//		cout << FResidueChksum[i][j];
	//	}
	//	cout << endl;
	//}
	cout << "\n >Fault Residue Checksum (FRChkSum) Finished\n";

	//==========================================================================================================================
	
	//calc chesum for fault data
	bool AChecksum[COLS] = {};
	carry = 0;
	one = 0;
	for (int i = COLS - 1; i > -1; i--)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (FResidueChksum[j][i])one++;
		}
		AChecksum[i] = (carry + one) % 2;
		carry = (one + carry) / 2;
		one = 0;
	}
	while (carry)
	{
		for (int i = COLS - 1; i > -1; i--)
		{
			if (AChecksum[i]) one++;
			AChecksum[i] = (carry + one) % 2;
			carry = (one + carry) / 2;
			one = 0;
		}
	}

	//check!
	/*cout << endl;
	for (int j = 0; j < COLS; j++)
	{
		cout << AChecksum[j]<<" - "<<FResidueChksum[ROWS][j]<<" | ";
	}*/

	//============================================================================================
	
	//calc probability of error detection
	bool flag = true;
	for (int j = 0; j < COLS; j++)
	{
		if (AChecksum[j] != FResidueChksum[ROWS][j])
		{
			flag = false;
			break;
		}
	}

	if (flag) return 0;
	else return 100;
}


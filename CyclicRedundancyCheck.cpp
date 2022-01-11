#include "Header.h"

float cyclic_redundancy_check(bool org_mem[ROWS][COLS], bool divisor[CRC_No], bool CCRCMEM[ROWS][COLS + CRC_No - 1], bool FCRCMEM[ROWS][COLS + CRC_No - 1], bool burst)
{
	// calc CRC for correct data befor error injection 
	bool aid_divisor[CRC_No] = {};
	bool Remainder[ROWS][CRC_No - 1] = {};

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < CRC_No; j++)
		{
			aid_divisor[j] = org_mem[i][j];
		}
		for (int j = CRC_No; j < COLS + CRC_No; j++)
		{
			if (aid_divisor[0] != 0)
			{
				for (int k = 0; k < CRC_No; k++)
				{
					aid_divisor[k] ^= divisor[k];
				}

			}
			for (int k = 0; k < CRC_No - 1; k++)
			{
				aid_divisor[k] = aid_divisor[k + 1];
			}
			if (j < COLS)
			{
				aid_divisor[CRC_No - 1] = org_mem[i][j];
			}
			else
			{
				aid_divisor[CRC_No - 1] = false;
			}

			//check!

			/*for (int k = 0; k < CRC_No;k++)
			{
				cout << aid_divisor[k];
			}
			cout << endl;*/
		}

		for (int j = 0; j < CRC_No - 1; j++)
		{
			Remainder[i][j] = aid_divisor[j];

			//check!
			//cout << Remainder[i][j];
		}
	}

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS + CRC_No - 1; j++)
		{
			if (j < COLS)
			{
				CCRCMEM[i][j] = org_mem[i][j];
				FCRCMEM[i][j] = org_mem[i][j];

			}
			else
			{
				CCRCMEM[i][j] = Remainder[i][j - COLS];
				FCRCMEM[i][j] = Remainder[i][j - COLS];
			}
		}
	}

	//check!
	/*cout << "\n--------------\n";
	for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + CRC_No - 1; j++)
		{
			cout << CCRCMEM[i][j];
		}
		cout << endl;
	}*/
	cout << "\n >Correct  CRC (Cyclic Redundancy Check) Finished\n";
	//========================================================================================================================================

	// error injection into correct data

	int fault_P[ROWS][FAULT_No] = {};
	fault_inject(fault_P, ROWS, COLS + CRC_No - 1, burst);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			FCRCMEM[i][fault_P[i][j]] = !(FCRCMEM[i][fault_P[i][j]]);
		}
	}

	//check !
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + CRC_No - 1; j++)
		{
			cout << FCRCMEM[i][j];
		}
		cout << endl;
	}*/

	cout << "\n >Fault CRC (Fault Cyclic Redundancy Check) Finished\n";


	//========================================================================================================================================

	//check CRC for correct data, just for checking the alg

	/*for (int i = 0;i < ROWS;i++)
	{
		cout << "\nNo Fault===========\n";
		for (int j = 0;j < CRC_No;j++)
		{
			aid_divisor[j] = CCRCMEM[i][j];
		}
		for (int j = CRC_No; j < COLS + CRC_No; j++)
		{
			if (aid_divisor[0] != 0)
			{
				for (int k = 0;k < CRC_No;k++)
				{
					aid_divisor[k] ^= divisor[k];
				}

			}
			for (int k = 0;k < CRC_No - 1;k++)
			{
				aid_divisor[k] = aid_divisor[k + 1];
			}

			aid_divisor[CRC_No - 1] = CCRCMEM[i][j];

			for (int k = 0; k < CRC_No;k++)
			{
				cout << aid_divisor[k];
			}

			cout << endl;
		}
	}
*/

	//========================================================================================================================================
	//	calc CRC for faulty data
	bool Faid_divisor[CRC_No] = {};
	bool FRemainder[ROWS][CRC_No - 1] = {};

	//cout << "\n----------------------------------------------\n";
	for (int i = 0; i < ROWS; i++)
	{
		//cout << "\nFault ============\n";
		for (int j = 0; j < CRC_No; j++)
		{
			Faid_divisor[j] = FCRCMEM[i][j];
		}
		for (int j = CRC_No; j < COLS + CRC_No; j++)
		{
			if (Faid_divisor[0] != 0)
			{
				for (int k = 0; k < CRC_No; k++)
				{
					Faid_divisor[k] ^= divisor[k];
				}

			}
			for (int k = 0; k < CRC_No - 1; k++)
			{
				Faid_divisor[k] = Faid_divisor[k + 1];
			}


			Faid_divisor[CRC_No - 1] = FCRCMEM[i][j];


			// check!
			/*for (int k = 0; k < CRC_No;k++)
			{
				cout << Faid_divisor[k];
			}*/

		}

		for (int j = 0; j < CRC_No - 1; j++)
		{
			FRemainder[i][j] = Faid_divisor[j];

		}
	}

	//check!
	/*for (int i = 0; i < ROWS;i++)
	{
		cout << endl;
		for (int j = 0;j < CRC_No - 1; j++)
			cout << FRemainder[i][j];
	}*/

	//========================================================================================================================================
	//calc probability of error detection
	
	int counter = 0;
	for (int i = 0; i < ROWS; i++)
	{
		bool flag = false;
		for (int j = 0; j < CRC_No - 1; j++)
		{
			if (FRemainder[i][j] > 0)
			{
				flag = true;
				break;
			}

		}
		if (flag)
			counter++;
	}
	return (counter * 100) / (float)ROWS;
}

float comb_CRC(bool org_mem[ROWS][COLS], bool divisor[CRC_No], bool CCRCMEM[ROWS][COLS + CRC_No - 1], bool FCRCMEM[ROWS][COLS + CRC_No - 1], bool burst)
{
	// calc Cobimtional CRC for correct data 
	bool aid_divisor[CRC_No] = {};
	bool Remainder[ROWS][CRC_No - 1] = {};

	for (int i = 0; i < ROWS; i++)
	{

		for (int j = 0; j < CRC_No; j++)
		{
			aid_divisor[j] = org_mem[i][j];
		}
		for (int j = CRC_No; j < COLS + CRC_No; j++)
		{
			if (aid_divisor[0] != 0)
			{
				for (int k = 0; k < CRC_No; k++)
				{
					aid_divisor[k] ^= divisor[k];
				}

			}
			for (int k = 0; k < CRC_No - 1; k++)
			{
				aid_divisor[k] = aid_divisor[k + 1];
			}
			if (j < COLS)
			{
				aid_divisor[CRC_No - 1] = org_mem[i][j];
			}
			else
			{
				aid_divisor[CRC_No - 1] = false;
			}

			//check!
			/*for (int k = 0; k < CRC_No;k++)
			{
				cout << aid_divisor[k];
			}
			cout << endl;*/
		}

		for (int j = 0; j < CRC_No - 1; j++)
		{
			Remainder[i][j] = aid_divisor[j];
			
			//check!
			//cout << Remainder[i][j];
		}
	}

	// inject reminder into data
	for (int i = 0; i < ROWS; i++)
	{
		int counter = 0;

		for (int j = 0; j < COLS + CRC_No - 1; j++)
		{
			if (!((j + 1) % ((COLS + CRC_No - 1) / (CRC_No - 1))))
			{
				CCRCMEM[i][j] = Remainder[i][counter];
				FCRCMEM[i][j] = Remainder[i][counter];
				counter++;
				//check!
				//cout << "|" << CCRCMEM[i][j] << "|";
			}
			else
			{
				CCRCMEM[i][j] = org_mem[i][j - counter];
				FCRCMEM[i][j] = org_mem[i][j - counter];
				//check!
				//	cout << CCRCMEM[i][j];
			}
		}
	}

	//chekc! 
	//cout << "\n--------------\n";
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + CRC_No - 1; j++)
		{
			cout << CCRCMEM[i][j];
		}
		cout << endl;
	}*/
	cout << "\n >Correct Comb CRC (Correct Combitinal Cyclic Redundancy Check) Finished\n\n";
	//========================================================================================================================================
	
	// inject error into correct data 
	int fault_P[ROWS][FAULT_No] = {};
	fault_inject(fault_P, ROWS, COLS + CRC_No - 1, burst);

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			FCRCMEM[i][fault_P[i][j]] = !(FCRCMEM[i][fault_P[i][j]]);
		}
	}
	
	//check!
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + CRC_No - 1; j++)
		{
			cout << FCRCMEM[i][j];
		}
		cout << endl;
	}*/

	cout << "\n  >Fault Comb CRC (Fault Combitinal Cyclic Redundancy Check) Finished\n";
	

	//========================================================================================================================================
	
	//check Comb CRC for correct data, just for checking the alg

	/*bool CCRCMEM_Parted[ROWS][COLS + CRC_No - 1] = {};
	bool CRemainder[CRC_No - 1] = {};
	for (int i = 0;i < ROWS;i++)
	{
		int counter = 0;
		for (int j = 0; j < COLS + CRC_No - 1;j++)
		{
			if (!((j + 1) % ((COLS + CRC_No - 1) / (CRC_No - 1))))
			{
				CRemainder[counter] = CCRCMEM[i][j];
				counter++;
			}
			else
			{
				CCRCMEM_Parted[i][j - counter] = CCRCMEM[i][j];
			}
		}
		for (int j = 0; j < CRC_No - 1; j++)
		{
			CCRCMEM_Parted[i][j + COLS] = CRemainder[j];
		}
	}
	cout << endl;

	cout << "\nRamain Parted Correct data \n";
	for (int i = 0; i < ROWS;i++)
	{
		cout << endl;
		for (int j = 0;j < COLS + CRC_No - 1;j++)
		{
			cout << CCRCMEM_Parted[i][j];
		}
	}

	for (int i = 0;i < ROWS;i++)
	{
		cout << "\nNo Fault===========\n";
		for (int j = 0;j < CRC_No;j++)
		{
			aid_divisor[j] = CCRCMEM_Parted[i][j];
		}
		for (int j = CRC_No; j < COLS + CRC_No; j++)
		{
			if (aid_divisor[0] != 0)
			{
				for (int k = 0;k < CRC_No;k++)
				{
					aid_divisor[k] ^= divisor[k];
				}

			}
			for (int k = 0;k < CRC_No - 1;k++)
			{
				aid_divisor[k] = aid_divisor[k + 1];
			}
			aid_divisor[CRC_No - 1] = CCRCMEM_Parted[i][j];

			for (int k = 0; k < CRC_No;k++)
			{
				cout << aid_divisor[k];
			}

			cout << endl;
		}
	}
*/
//========================================================================================================================================

	//	calc Combitional CRC for faulty data

	bool Faid_divisor[CRC_No] = {};
	bool FCRCMEM_Parted[ROWS][COLS + CRC_No - 1] = {};
	bool FRemainder[ROWS][CRC_No - 1] = {};
	bool BFRemainder[CRC_No - 1] = {};

	for (int i = 0; i < ROWS; i++)
	{
		int counter = 0;
		for (int j = 0; j < COLS + CRC_No - 1; j++)
		{
			if (!((j + 1) % ((COLS + CRC_No - 1) / (CRC_No - 1))))
			{
				BFRemainder[counter] = FCRCMEM[i][j];
				counter++;
			}
			else
			{
				FCRCMEM_Parted[i][j - counter] = FCRCMEM[i][j];
			}
		}
		for (int j = 0; j < CRC_No - 1; j++)
		{
			FCRCMEM_Parted[i][j + COLS] = BFRemainder[j];
		}
	}

	//check!
	//cout << "\nRamain Parted Fault data \n";
	/*for (int i = 0; i < ROWS;i++)
	{
		cout << endl;
		for (int j = 0;j < COLS + CRC_No - 1;j++)
		{
			cout << FCRCMEM_Parted[i][j];
		}
	}
*/


	for (int i = 0; i < ROWS; i++)
	{


		for (int j = 0; j < CRC_No; j++)
		{
			Faid_divisor[j] = FCRCMEM_Parted[i][j];
		}
		for (int j = CRC_No; j < COLS + CRC_No; j++)
		{
			if (Faid_divisor[0] != 0)
			{
				for (int k = 0; k < CRC_No; k++)
				{
					Faid_divisor[k] ^= divisor[k];
				}

			}
			for (int k = 0; k < CRC_No - 1; k++)
			{
				Faid_divisor[k] = Faid_divisor[k + 1];
			}

			Faid_divisor[CRC_No - 1] = FCRCMEM_Parted[i][j];
			
			//check!
			/*for (int k = 0; k < CRC_No;k++)
			{
				cout << Faid_divisor[k];
			}

			cout << endl;*/
		}

		for (int j = 0; j < CRC_No - 1; j++)
		{
			FRemainder[i][j] = Faid_divisor[j];
		}
	}


	//check!
	/*for (int i = 0; i < ROWS;i++)
	{
		cout << endl;
		for (int j = 0;j < CRC_No - 1; j++)
			cout << FRemainder[i][j];
	}*/
	//========================================================================================================================================
	//calc probability of error detection 
	int counter = 0;
	for (int i = 0; i < ROWS; i++)
	{
		bool flag = false;
		for (int j = 0; j < CRC_No - 1; j++)
		{
			if (FRemainder[i][j] > 0)
			{
				flag = true;
				break;
			}

		}
		if (flag)
			counter++;
	}


	return (counter * 100) / (float)ROWS;
	
}

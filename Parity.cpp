#include "Header.h"

float even_parity(bool org_mem[ROWS][COLS], bool CEPB[ROWS][COLS + PARITY_No], bool FEPB[ROWS][COLS + PARITY_No], bool burst)
{	
	//calc parity befor inject error 

	bool parity[PARITY_No] = {};
	//cout << "\n----Even Parity";
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (!(j % (COLS / PARITY_No)))
			{
				parity[j / (COLS / PARITY_No)] = org_mem[i][j] ^ false;
			}
			else
			{
				parity[j / (COLS / PARITY_No)] ^= org_mem[i][j];
			}

			CEPB[i][j] = org_mem[i][j];
			FEPB[i][j] = org_mem[i][j];
		}
		for (int k = 0; k < PARITY_No; k++)
		{
			CEPB[i][COLS + k] = parity[k];
			FEPB[i][COLS + k] = parity[k];

			//check! 
			//cout << "\n" << parity[k] << endl;
		}
	}

	//check!
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + PARITY_No; j++)
		{
			cout << FEPB[i][j];
		}
		cout << endl;
	}*/
	cout << "  >Correct Even Parity (CEP) Finished\n";
	//======================================================================================================================
	
	// error injection 
	
	int fault_P[ROWS][FAULT_No] = {};
	fault_inject(fault_P, ROWS, COLS + PARITY_No, burst);
	
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			FEPB[i][fault_P[i][j]] = !(FEPB[i][fault_P[i][j]]);
		}
	}

	// check!
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + PARITY_No; j++)
		{
			cout << FEPB[i][j];
		}
		cout << endl;
	}*/
	cout << "  >Fault Even Parity (FEP) Finished\n";
	//======================================================================================================================

	// check parity after error injection 
	bool BFparity[PARITY_No] = {};
	bool AFparity[ROWS][PARITY_No] = {};


	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (!(j % (COLS / PARITY_No)))
			{
				BFparity[j / (COLS / PARITY_No)] = FEPB[i][j] ^ false;
			}
			else
			{
				BFparity[j / (COLS / PARITY_No)] ^= FEPB[i][j];
			}
		}

		for (int k = 0; k < PARITY_No; k++)
		{
			AFparity[i][k] = BFparity[k];
		}
	}
	
	//check!

	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = COLS;j < COLS + PARITY_No;j++)
		{
			cout << AFparity[i][j - COLS] << " | " << FEPB[i][j] << "  -  ";
		}
		cout << endl;
	}*/
	//======================================================================================================================
	
	// calc probability of error detection 
	int counter = 0;
	for (int i = 0; i < ROWS; i++)
	{
		bool flag = false;
		for (int j = COLS; j < COLS + PARITY_No; j++)
		{
			if (AFparity[i][j - COLS] ^ FEPB[i][j])
			{
				flag = true;
				break;
			}
		}

		if (flag)	counter++;
	}
	return (counter * 100 / (float)(ROWS));
}

float odd_parity(bool org_mem[ROWS][COLS], bool COPB[ROWS][COLS + PARITY_No], bool FOPB[ROWS][COLS + PARITY_No], bool burst)
{
	// calc odd parity befor error inject

	bool parity[PARITY_No] = {};

	//cout << "\n----Odd Parity";
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (!(j % (COLS / PARITY_No)))
			{
				parity[j / (COLS / PARITY_No)] = org_mem[i][j] ^ false;
			}
			else
			{
				parity[j / (COLS / PARITY_No)] ^= org_mem[i][j];
			}

			COPB[i][j] = org_mem[i][j];
			FOPB[i][j] = org_mem[i][j];

		}
		for (int k = 0; k < PARITY_No; k++)
		{
			COPB[i][COLS + k] = !parity[k];
			FOPB[i][COLS + k] = !parity[k];
			
			//check!
			//cout << COPB[i][COLS + k];
		}
	}

	//check!

	/*for (int i = 0;i < ROWS;i++)
	{
		cout << endl;
		for (int j = 0;j < COLS + PARITY_No;j++)
		{
			cout << COPB[i][j];
		}

	}*/
	cout << "  >Correct Odd Parity (COP) Finished\n";
	//========================================================================================================================
	
	//inject error to correct data
	int fault_P[ROWS][FAULT_No] = {};
	fault_inject(fault_P, ROWS, COLS + PARITY_No, burst);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			FOPB[i][fault_P[i][j]] = !(FOPB[i][fault_P[i][j]]);
		}
	}

	// check !
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + PARITY_No; j++)
		{
			cout << FOPB[i][j];
		}
		cout << endl;
	}*/
	cout << "  >Fault Odd Parity (FOP) Finished\n";

	//=========================================================================================================================
	
	//calc odd parity after error injection

	bool BFparity[PARITY_No] = {};
	bool AFparity[ROWS][PARITY_No] = {};
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (!(j % (COLS / PARITY_No)))
			{
				BFparity[j / (COLS / PARITY_No)] = FOPB[i][j] ^ false;
			}
			else
			{
				BFparity[j / (COLS / PARITY_No)] ^= FOPB[i][j];
			}
		}
		for (int k = 0; k < PARITY_No; k++)
		{
			AFparity[i][k] = !BFparity[k];
			
			//check!
			//cout << AFparity[i][k];
		}
	}

	//check!
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = COLS;j < COLS + PARITY_No;j++)
		{
			cout << AFparity[i][j - COLS] << " | " << FOPB[i][j] << "  -  ";
		}
		cout << endl;
	}*/
	//====================================================================================================================================
	
	//calc probability of error detection by odd parity on this configure
	int counter = 0;
	for (int i = 0; i < ROWS; i++)
	{
		bool flag = false;
		for (int j = COLS; j < COLS + PARITY_No; j++)
		{
			if (!(!(AFparity[i][j - COLS] ^ FOPB[i][j])))
			{
				flag = true;
				break;
			}
		}
		if (flag)	counter++;
	}
	return (counter * 100 / (float)(ROWS));
}

float comb_parity(bool org_mem[ROWS][COLS], bool CCPB[ROWS][COLS + PARITY_No * 2], bool FCPB[ROWS][COLS + PARITY_No * 2], bool burst)
{
	//calc parity befor error injection

	bool parity[ROWS][PARITY_No * 2] = {};

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (!(j % (COLS / (PARITY_No * 2))))
			{
				parity[i][j / (COLS / (PARITY_No * 2))] = org_mem[i][j] ^ false;
			}
			else
			{
				parity[i][j / (COLS / (PARITY_No * 2))] ^= org_mem[i][j];
			}
		}
		for (int k = 0; k < PARITY_No * 2; k++)
		{
			if (k % 2)
			{
				parity[i][k] = parity[i][k];
			}
			else
			{
				parity[i][k] = !parity[i][k];
			}
			//check!
			//	cout << parity[i][k];
		}
	}

	for (int i = 0; i < ROWS; i++)
	{
		int counter = 0;
		for (int j = 0; j < COLS + PARITY_No * 2; j++)
		{
			if (!((j + 1) % ((COLS + PARITY_No * 2) / (PARITY_No * 2))))
			{
				CCPB[i][j] = parity[i][counter];
				FCPB[i][j] = parity[i][counter];
				counter++;

				//check!
				//cout << "|" << CCPB[i][j] << "|";
			}
			else
			{
				CCPB[i][j] = org_mem[i][j - counter];
				FCPB[i][j] = org_mem[i][j - counter];

				//check!
				//cout << CCPB[i][j];
			}
		}
	}

	cout << "  >Corect Comb Parity (CCP) Finished\n";
	//========================================================================================================================
	
	//error injection into correct data
	int fault_P[ROWS][FAULT_No] = {};
	fault_inject(fault_P, ROWS, COLS + PARITY_No * 2, burst);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			FCPB[i][fault_P[i][j]] = !(FCPB[i][fault_P[i][j]]);
		}
	}

	//check!
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + PARITY_No * 2; j++)
		{
			cout << FCPB[i][j];
		}
		cout << endl;
	}*/
	cout << "  >Fault Comb Parity (FCP) Finished\n";
	//===============================================================================================================================
	
	// calc parity after error injection and then, calc probability of error detection
	bool AFparity[ROWS][PARITY_No * 2] = {};
	int counter = 0;
	for (int i = 0; i < ROWS; i++)
	{
		//cout << endl;
		bool flag = false;
		for (int j = 0; j < COLS + (PARITY_No * 2); j++)
		{
			if (!(j % ((COLS + (PARITY_No * 2)) / (PARITY_No * 2))))
			{
				AFparity[i][j / (((COLS + (PARITY_No * 2)) / (PARITY_No * 2)))] = FCPB[i][j] ^ false;
			}
			else
			{
				AFparity[i][j / (((COLS + (PARITY_No * 2)) / (PARITY_No * 2)))] ^= FCPB[i][j];
			}
		}

		for (int k = 0; k < PARITY_No * 2; k++)
		{
			AFparity[i][k] = AFparity[i][k];
			if (k % 2)
			{

				if (AFparity[i][k])
				{
					flag = true;
					break;
				}
			}
			else
			{

				if (!AFparity[i][k])
				{
					flag = true;
					break;
				}
			}

			//check !
			//cout << AFparity[i][k];
		}

		if (flag) counter++;
	}

	return ((counter * 100) / (float)(ROWS));
}

float parity_2d(bool org_mem[ROWS][COLS], bool C_2dPB[ROWS][COLS + PARITY_No * 2], bool F_2dPB[ROWS][COLS + PARITY_No * 2], bool burst)
{
	//calc parity of correct data befor error injection
	bool col_parity[PARITY_No] = {};
	bool row_parity[ROWS / (COLS / PARITY_No)] = {};
	int row_parity_No = ROWS / (COLS / PARITY_No);
	bool aid_row_parity[ROWS * PARITY_No] = {};
	int counter = 0;

	//cout << "\n----2d Parity";
	for (int i = 0; i < ROWS; i++)
	{

		for (int j = 0; j < COLS; j++)
		{
			if (!(j % (COLS / PARITY_No)))
			{
				col_parity[j / (COLS / PARITY_No)] = org_mem[i][j] ^ false;
			}
			else
			{
				col_parity[j / (COLS / PARITY_No)] ^= org_mem[i][j];
			}
			C_2dPB[i][j] = org_mem[i][j];
			F_2dPB[i][j] = org_mem[i][j];
		}
		for (int k = 0; k < PARITY_No; k++)
		{
			C_2dPB[i][COLS + k] = col_parity[k];
			F_2dPB[i][COLS + k] = col_parity[k];

			//check!
			//cout << col_parity[k];
		}

	}

	//check!
	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (!(j % (ROWS / row_parity_No)))
			{
				row_parity[j / (ROWS / row_parity_No)] = org_mem[j][i] ^ false;
			}
			else
			{
				row_parity[j / (ROWS / row_parity_No)] ^= org_mem[j][i];
			}
		}
		for (int k = 0; k < row_parity_No; k++)
		{
			aid_row_parity[counter] = row_parity[k];
			counter++;
			//check!
			//cout << aid_row_parity[counter];

		}
	}

	counter = 0;
	for (int i = COLS + PARITY_No; i < COLS + PARITY_No + PARITY_No; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			C_2dPB[j][i] = aid_row_parity[counter];
			F_2dPB[j][i] = aid_row_parity[counter];
			counter++;
			//check!
			//cout << C_2dPB[j][i] << " " << aid_row_parity[counter] << " | ";

		}
	}

	//check!
	/*for (int i = 0; i < ROWS; i++)
	{
		cout << endl;
		for (int j = 0;j < COLS + PARITY_No + PARITY_No;j++)
		{
			cout << C_2dPB[i][j];
		}
	}*/

	cout << "  >Correct 2D Parity (C_2dP) Finished\n";
	//======================================================================================================================================= 
	
	//error injection into correct data

	int fault_P[ROWS][FAULT_No] = {};
	fault_inject(fault_P, ROWS, COLS + PARITY_No * 2, burst);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			F_2dPB[i][fault_P[i][j]] = !(F_2dPB[i][fault_P[i][j]]);
		}
	}

	//check!
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + PARITY_No * 2; j++)
		{
			cout << F_2dPB[i][j];
		}
		cout << endl;
	}*/
	cout << "  >Fault 2D Parity (F_2dP) Finished\n";

	//======================================================================================================================================= 
	
	//calc parity after error injection 
	
	bool AF_2dPB[ROWS][PARITY_No * 2] = {};
	bool Acol_parity[PARITY_No] = {};
	bool Arow_parity[ROWS / (COLS / PARITY_No)] = {};
	bool Aaid_row_parity[ROWS * PARITY_No] = {};

	row_parity_No = ROWS / (COLS / PARITY_No);
	counter = 0;

	for (int i = 0; i < ROWS; i++)
	{

		for (int j = 0; j < COLS; j++)
		{
			if (!(j % (COLS / PARITY_No)))
			{
				Acol_parity[j / (COLS / PARITY_No)] = F_2dPB[i][j] ^ false;
			}
			else
			{
				Acol_parity[j / (COLS / PARITY_No)] ^= F_2dPB[i][j];
			}
		}
		for (int k = 0; k < PARITY_No; k++)
		{
			AF_2dPB[i][k] = Acol_parity[k];

			// check!
			//cout << AF_2dPB[i][k];
		}
	}


	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (!(j % (ROWS / row_parity_No)))
			{
				Arow_parity[j / (ROWS / row_parity_No)] = F_2dPB[j][i] ^ false;
			}
			else
			{
				Arow_parity[j / (ROWS / row_parity_No)] ^= F_2dPB[j][i];
			}
		}
		for (int k = 0; k < row_parity_No; k++)
		{
			aid_row_parity[counter] = Arow_parity[k];
			counter++;

			//check!
			//cout << aid_row_parity[counter];

		}
	}

	counter = 0;
	for (int i = COLS + PARITY_No; i < COLS + PARITY_No + PARITY_No; i++)
	{

		for (int j = 0; j < ROWS; j++)
		{
			AF_2dPB[j][i - COLS] = aid_row_parity[counter];
			counter++;

			//check!
			//cout << AF_2dPB[j][i - COLS] << " " << aid_row_parity[counter] << " | ";

		}
	}

	//check!

	//cout << "\n--------\n";
	//for (int i = 0; i < ROWS; i++)
	//{
	//	cout << endl;
	//	for (int j = 0;j < PARITY_No + PARITY_No;j++)
	//	{
	//		cout << AF_2dPB[i][j];
	//	}
	//}

	//=====================================================================================================================================
	//calc probability of error detection 

	int RowCounter = 0;
	int ColCounter = 0;
	bool VerParity[ROWS * PARITY_No] = {};
	bool HorParity[ROWS * PARITY_No] = {};
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = COLS; j < COLS + 2 * PARITY_No; j++)
		{
			//check!
			//cout << AF_2dPB[i][j - COLS] << " |F" << F_2dPB[i][j] << " - ";
			if (j < (COLS + PARITY_No))
			{
				HorParity[ColCounter] = AF_2dPB[i][j - COLS] ^ F_2dPB[i][j];
				ColCounter++;

			}
			else
			{
				VerParity[RowCounter] = AF_2dPB[i][j - COLS] ^ F_2dPB[i][j];
				RowCounter++;
			}
		}
	}

	//check!
	//	cout << "\n======================\n";
		/*for (int i = 0; i < ROWS * PARITY_No; i++)
		{
			cout << HorParity[i] << endl;
		}
		cout << "\nhor parity\n";*/
		/*for (int i = 0; i < ROWS*PARITY_No; i++)
		{
			cout << VerParity[i] << endl;
		}
		cout << "\nver parity\n";
	*/

	counter = 0;
	int Dimension = COLS / PARITY_No;

	for (int i = 0; i < ROWS; i++)
	{
		bool flag = false;
		for (int j = 0; j < PARITY_No; j++)
		{
			if (HorParity[i * PARITY_No + j] == 1)
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			for (int j = 0; j < Dimension; j++)
			{
				for (int k = 0; k < Dimension; k++)
				{
					if (VerParity[j + k * Dimension * row_parity_No] == 1)
					{
						flag = true;
						break;
					}
				}

				if (flag)	break;
			}
		}
		if (flag)counter++;
	}

	return (counter * 100 / (float)(ROWS));
}


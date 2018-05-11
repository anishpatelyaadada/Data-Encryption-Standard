#include "Encryption.h"
#include <cstring>
#include <string>
#include <cstdlib>
#include<iostream>
#include<fstream>
using namespace std;
//outputFile.open("C:\\Users\\kings\\Desktop\\data.txt", ios::app);

Encryption::Encryption()
{
	outputFile.open("C:\\Users\\kings\\Desktop\\data.txt", ios::app);

}

// convert the key to 64 bit and send to parity function to drop the key
void Encryption::InitialKey_to_Binary(char initial_key[16]) {
	//outputFile.open("C:\\Users\\kings\\Desktop\\data.txt",ios::app);
	outputFile << "------------------------------------------------------------------------\n";
	outputFile << "Anish Patel.\n";
	outputFile << "Project 2:- DES\n";
	outputFile << "------------------------------------------------------------------------\n";
	outputFile << "Key and Datas\n";
	outputFile << "------------------------------------------------------------------------\n";
	outputFile << "Key = Security\n";
	outputFile << "Key in Hexa - Decimal = 5345435552495459\n";
	outputFile << "Text = I Like Computer Class.\n";
	outputFile << "Above text is divided into three block.\n";
	outputFile << "Text 1 Block = I Like Com\n";
	outputFile << "Text 1 Hexa-Decimal = 494c494b45434f4d\n";
	outputFile << "Text 2 Block = puter Cla\n";
	outputFile << "Text 2 Hexa-Decimal = 5055544552434c41\n";
	outputFile << "Text 3 Block = ss\n";
	outputFile << "Text 3 Hexa-Decimal = 5353000000000000\n";
	outputFile << "------------------------------------------------------------------------\n";

	int initialKeytoBinary[64];
	int c=0;
	outputFile << "Key in Binary.\n";
	for (int i = 0; i < 16; i++) {
		string binaryValueOfHex =  convert_hex_to_binary(initial_key[i]);
		//outpuFIle << initial_key[i] << " = " << binaryValueOfHex << endl;

		for (int j = 0; j < 4; j++) {
			
			initialKeytoBinary[c + j] = stoi(binaryValueOfHex.substr(j, 1));
			outputFile << initialKeytoBinary[c + j];
			//outpuFIle << c + j << " = " << initialKeytoBinary[c + j]  << endl;
		}
		c = c + 4;
	}
	outputFile << endl;
	outputFile << "------------------------------------------------------------------------\n";

	parity_drop(initialKeytoBinary);
	outputFile << endl;
	//outputFile.close();
}

// function to drop parity key from the the 64 bit and make it 56 bit
void Encryption::parity_drop(int originalKeyInBinary[64]) {
	int parityDropKey[56];
	int parityKey_C[28], parityKey_D[28];
	int PC_1_Table[56] = { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,
	3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4 };

	outputFile << "Parity Drop Key.\n";
	int j = 28;
	outputFile << "C0                            D0\n";
	for (int i = 0; i < 56; i++) {
		parityDropKey[i] = originalKeyInBinary[PC_1_Table[i] - 1];
		if (i < 28) {
			parityKey_C[i] = originalKeyInBinary[PC_1_Table[i] - 1];
			//outputFile << i << " = " << parityKey_C[i] << endl;
			outputFile << parityKey_C[i];
		}
		if (i > 27) {
			if (i == 28)
				outputFile << "  ";

			parityKey_D[i - 28] = originalKeyInBinary[PC_1_Table[i] - 1];
			//outputFile << i << " = " << parityKey_D[i - 28] << endl;

			outputFile << parityKey_D[i - 28];
		}
	}
	outputFile << endl;
	outputFile << "------------------------------------------------------------------------\n";

	generate_16_parity_drop(parityKey_C, parityKey_D);
}

//generate 16 parity drop pair key by using following logic 
// round:- 1,2,9,16 - one bit shift
// round:- others - two bits shift
void Encryption::generate_16_parity_drop(int parityKey_C[28], int parityKey_D[28]) {
	int parityKey_16_C[16][28], parityKey_16_D[16][28];
	
	//	outputFile << "round:-1, 2, 9, 16 - one bit shift.\n";
		//outputFile << "round:- others - two bits shift.\n";
		// this will generate 16 keys of 56bit with shifting which explain above and then send the data to this function "generete_16_keys"
	
	// parity drop for C
	outputFile << "All possible C & D Combination.\n";
	for (int i = 0; i < 16; i++) {
		outputFile << "C" << i + 1 << " = ";
		for (int j = 0; j < 28; j++) {

			if (i == 0) {
				//below if statement will shit only one bit
				if (i == 0 || i == 1 || i == 8 || i == 15) {
					if (j < 27) {
						parityKey_16_C[i][j] = parityKey_C[j + 1];
						outputFile << parityKey_16_C[i][j];
					}
					else {
						parityKey_16_C[i][j] = parityKey_C[0];
						outputFile << parityKey_16_C[i][j];
					}
				}//below else statement will shit only two bit
				else {
					if (j < 26) {
						parityKey_16_C[i][j] = parityKey_C[j + 2];
						outputFile << parityKey_16_C[i][j];
					}
					else if (j == 27) {
						parityKey_16_C[i][j] = parityKey_C[1];
						outputFile << parityKey_16_C[i][j];
					}
					else{
						parityKey_16_C[i][j] = parityKey_C[0];
						outputFile << parityKey_16_C[i][j];
					}
				}
			}
			else {
				//below if statement will shit only one bit
				if (i == 0 || i == 1 || i == 8 || i == 15) {
					if (j < 27) {
						parityKey_16_C[i][j] = parityKey_16_C[i - 1][j + 1];
						outputFile << parityKey_16_C[i][j];
					}
					else {
						parityKey_16_C[i][j] = parityKey_16_C[i - 1][0];
						outputFile << parityKey_16_C[i][j];
					}
				}//below else statement will shit only two bit
				else {
					if (j < 26) {
						parityKey_16_C[i][j] = parityKey_16_C[i - 1][j + 2];
						outputFile << parityKey_16_C[i][j];
					}
					else if (j == 27) {
						parityKey_16_C[i][j] = parityKey_16_C[i - 1][1];
						outputFile << parityKey_16_C[i][j];
					}
					else {
						parityKey_16_C[i][j] = parityKey_16_C[i - 1][0];
						outputFile << parityKey_16_C[i][j];
					}
				}
			}
		}		
		outputFile << endl;
	}
	outputFile << endl;
	//parity drop for D
	for (int i = 0; i < 16; i++) {
		outputFile << "D" << i + 1 << " = ";
		for (int j = 0; j < 28; j++) {

			if (i == 0) {
				//below if statement will shit only one bit
				if (i == 0 || i == 1 || i == 8 || i == 15) {
					if (j < 27) {
						parityKey_16_D[i][j] = parityKey_D[j + 1];
						outputFile << parityKey_16_D[i][j];
					}
					else {
						parityKey_16_D[i][j] = parityKey_D[0];
						outputFile << parityKey_16_D[i][j];
					}
				}//below else statement will shit only two bit
				else {
					if (j < 26) {
						parityKey_16_D[i][j] = parityKey_D[j + 2];
						outputFile << parityKey_16_D[i][j];
					}
					else if (j == 27) {
						parityKey_16_D[i][j] = parityKey_D[1];
						outputFile << parityKey_16_D[i][j];
					}
					else {
						parityKey_16_D[i][j] = parityKey_D[0];
						outputFile << parityKey_16_D[i][j];
					}
				}
			}
			else {
				//below if statement will shit only one bit
				if (i == 0 || i == 1 || i == 8 || i == 15) {
					if (j < 27) {
						parityKey_16_D[i][j] = parityKey_16_D[i - 1][j + 1];
						outputFile << parityKey_16_D[i][j];
					}
					else {
						parityKey_16_D[i][j] = parityKey_16_D[i - 1][0];
						outputFile << parityKey_16_D[i][j];
					}
				}//below else statement will shit only two bit
				else {
					if (j < 26) {
						parityKey_16_D[i][j] = parityKey_16_D[i - 1][j + 2];
						outputFile << parityKey_16_D[i][j];
					}
					else if (j == 27) {
						parityKey_16_D[i][j] = parityKey_16_D[i - 1][1];
						outputFile << parityKey_16_D[i][j];
					}
					else {
						parityKey_16_D[i][j] = parityKey_16_D[i - 1][0];
						outputFile << parityKey_16_D[i][j];
					}
				}
			}
		}
		outputFile << endl;
	}
	outputFile << "------------------------------------------------------------------------\n";
	generete_16_keys(parityKey_16_C, parityKey_16_D);
}

// generate all final 16 keys 
void Encryption::generete_16_keys(int key_C[16][28], int key_D[16][28]) {
	int dumyKeyCombine[16][56];
	int finalCombineKey[16][48];
	int PC_2[48] = { 14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32 };
	outputFile  << "Combine Key of C and D.\n";
	for (int j = 0; j < 16; j++) {
		outputFile << "Combine " << j + 1 << " = ";
		for (int i = 0; i < 56; i++) {
			if (i < 28) {
				dumyKeyCombine[j][i] = key_C[j][i];
				outputFile << dumyKeyCombine[j][i];
			}
			else {
				dumyKeyCombine[j][i] = key_D[j][i - 28];
				outputFile << dumyKeyCombine[j][i];
			}
		}
		outputFile << endl;
		//outputFile << "------------------------------------------------------------------------\n";

	}
	outputFile << "------------------------------------------------------------------------\n";

	//final key of 48bit
	outputFile << "Final key for each Round.\n";
	for (int j = 0; j < 16; j++) {
		outputFile << "K" << j + 1 << " = ";
		for (int i = 0; i < 48; i++) {
			finalCombineKey[j][i] = dumyKeyCombine[j][PC_2[i]-1];
			final_key_16[j][i] = finalCombineKey[j][i];
			outputFile << finalCombineKey[j][i]; 
			if ((i == 5 || i==11 || i==17||i==23||i==29||i==35||i==41||i==47))
				outputFile << " ";
		}
		outputFile << endl;
	}
	outputFile << "------------------------------------------------------------------------\n";
	outputFile.close();
}

// convert text to binary
void Encryption::InitialText_to_Binary(char initial_key[16]) {
	outputFile.open("C:\\Users\\kings\\Desktop\\data.txt", ios::app);

	int initialKeytoBinary[64];
	int c = 0;
	outputFile << "Text in Binary.\n";
	for (int i = 0; i < 16; i++) {
		string binaryValueOfHex = convert_hex_to_binary(initial_key[i]);
		//outputFile << initial_key[i] << " = " << binaryValueOfHex << endl;

		for (int j = 0; j < 4; j++) {

			initialKeytoBinary[c + j] = stoi(binaryValueOfHex.substr(j, 1));
			outputFile << initialKeytoBinary[c + j];
			//outputFile << c + j << " = " << initialKeytoBinary[c + j]  << endl;
		}
		c = c + 4;
	}
	outputFile << endl;
	outputFile << "------------------------------------------------------------------------\n";

	initial_permutation(initialKeytoBinary);
	
}


// initial permutation of 64bit character
void Encryption::initial_permutation(int dataToPermute[]) {
	int permutationTable[64] = { 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,
 40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7 };

	int leftBlockInitial[32];
	int rightBlockInitial[32];

	
	outputFile << "Left block , Right Block " << endl;
	
	for (int i = 0; i < 64; i++) {
		if (i < 32) {
			leftBlockInitial[i] = dataToPermute[permutationTable[i]-1];
			outputFile << leftBlockInitial[i];
			//outputFile << leftBlockInitial[i];
		}
		else{
			if (i == 32)
				outputFile << " ";
			rightBlockInitial[i-32] = dataToPermute[permutationTable[i]-1];
			outputFile << rightBlockInitial[i - 32];
		}
	}
	outputFile << endl;
	outputFile << "------------------------------------------------------------------------\n";

	expansion_P_Box(leftBlockInitial,rightBlockInitial);
	outputFile.close();
}

// expansion P box to convert the 32 bit into 48 bit
void Encryption::expansion_P_Box(int leftBlockData[], int rightBlockData[]) {
	int expansionTable[48] = { 32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1 };
	int permutation_straight_P_Box[32] = { 16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25 };
	int rightBlockExpansion[16][48];
	int RightBlockData_for_FinalPermutation[16][32];
	int LeftBlockData_for_FinalPermutation[16][32];
	char hexadecimal;

	int rightXOR[48];
	//outputFile << "Expansion P Box" << endl << endl;
	for (int j = 0; j < 16; j++) {
		//	outputFile << "XOR " << j + 1 << " = ";
			//XOR operation of 48 bit text and 48 bit key
		for (int i = 0; i < 48; i++) {
			if (j == 0) {
				rightBlockExpansion[j][i] = rightBlockData[expansionTable[i] - 1];
				//outputFile << rightBlockExpansion[j][i];

				if ((rightBlockExpansion[j][i] + final_key_16[j][i]) == 0) {
					rightXOR[i] = 0;
				}
				else if ((rightBlockExpansion[j][i] + final_key_16[j][i]) == 1) {
					rightXOR[i] = 1;
				}
				else /* if ((rightBlockExpansion[j][i] + final_key_16[j][i]) == 2)*/ {
					rightXOR[i] = 0;
				}
				//outputFile << rightXOR[i];
			}
			else {
				rightBlockExpansion[j][i] = RightBlockData_for_FinalPermutation[j - 1][expansionTable[i] - 1];
				//outputFile << rightBlockExpansion[j][i];

				if ((rightBlockExpansion[j][i] + final_key_16[j][i]) == 0) {
					rightXOR[i] = 0;
				}
				else if ((rightBlockExpansion[j][i] + final_key_16[j][i]) == 1) {
					rightXOR[i] = 1;
				}
				else /* if ((rightBlockExpansion[j][i] + final_key_16[j][i]) == 2)*/ {
					rightXOR[i] = 0;
				}
				//outputFile << rightXOR[i];
			}

		}
		// here i need to copy left block data
		// and convert the 48 bit to 32bit using s box
		S_Box_Value(rightXOR);
		//outputFile << "final right Block = ";
		for (int a = 0; a < 32; a++) {
			finalRightBlock_Operation[a] = finalRightBlock[permutation_straight_P_Box[a] - 1];
			//outputFile << finalRightBlock_Operation[a];
		}
		//	outputFile << endl;
			//outputFile << "RightBlockData_for_FinalPermutation = ";
		for (int b = 0; b < 32; b++) {
			if (j == 0) {
				if ((leftBlockData[b] + finalRightBlock_Operation[b]) == 0) {
					RightBlockData_for_FinalPermutation[j][b] = 0;
				}
				else if ((leftBlockData[b] + finalRightBlock_Operation[b]) == 1) {
					RightBlockData_for_FinalPermutation[j][b] = 1;
				}
				else {
					RightBlockData_for_FinalPermutation[j][b] = 0;
				}
				//outputFile << RightBlockData_for_FinalPermutation[j][b];
				//outputFile << "Final Block " << i + 1 << " = " << finalRightBlock[i] << endl;
				LeftBlockData_for_FinalPermutation[j][b] = rightBlockData[b];
			}
			else {
				if ((LeftBlockData_for_FinalPermutation[j - 1][b] + finalRightBlock_Operation[b]) == 0) {
					RightBlockData_for_FinalPermutation[j][b] = 0;
				}
				else if ((LeftBlockData_for_FinalPermutation[j - 1][b] + finalRightBlock_Operation[b]) == 1) {
					RightBlockData_for_FinalPermutation[j][b] = 1;
				}
				else {
					RightBlockData_for_FinalPermutation[j][b] = 0;
				}
				//	outputFile << RightBlockData_for_FinalPermutation[j][b];
				LeftBlockData_for_FinalPermutation[j][b] = RightBlockData_for_FinalPermutation[j - 1][b];
			}
			if (j == 15) {
				LeftBlockData_for_FinalPermutation[15][b] = RightBlockData_for_FinalPermutation[15][b];
				RightBlockData_for_FinalPermutation[15][b] = RightBlockData_for_FinalPermutation[14][b];
			}
		}
		//outputFile << endl << endl;
	}

	// display the result of all rounds
	for (int j = 0; j < 16; j++) {
		outputFile << "Round " << j + 1 << " Binary = ";
		for (int i = 0; i < 64; i++) {
			if (i < 32) {
				outputFile << LeftBlockData_for_FinalPermutation[j][i];
			}
			else {
				if (i == 32)
					outputFile << " ";
				outputFile << RightBlockData_for_FinalPermutation[j][i - 32];
			}
		}
		outputFile << endl << "Hexa-Decimal   = ";
		// convert the binary text to hexadecimal
		for (int i = 0; i < 64; i++) {
			if (i == 3 || i == 7 || i == 11 || i == 15 || i == 19 || i == 23 || i == 27 || i == 31) {
				hexadecimal = binary_hexadecimal(LeftBlockData_for_FinalPermutation[j][i - 3], LeftBlockData_for_FinalPermutation[j][i - 2], LeftBlockData_for_FinalPermutation[j][i - 1], LeftBlockData_for_FinalPermutation[j][i]);
				outputFile << hexadecimal;
			}
			else {
				if (i == 32)
					outputFile << "                         ";

				if (i == 35 || i == 39 || i == 43 || i == 47 || i == 51 || i == 55 || i == 59 || i == 63) {
					if (j != 15) {
						hexadecimal = binary_hexadecimal(RightBlockData_for_FinalPermutation[j][i - 3], RightBlockData_for_FinalPermutation[j][i - 2], RightBlockData_for_FinalPermutation[j][i - 1], RightBlockData_for_FinalPermutation[j][i]);
						outputFile << hexadecimal;
					}
					if (j == 15) {
						hexadecimal = binary_hexadecimal(RightBlockData_for_FinalPermutation[14][i - 3], RightBlockData_for_FinalPermutation[14][i - 2], RightBlockData_for_FinalPermutation[14][i - 1], RightBlockData_for_FinalPermutation[14][i]);
						outputFile << hexadecimal;

					}
				}
			}

		}
		outputFile << endl;
	}
	outputFile << "------------------------------------------------------------------------\n";
	final_Permutation(RightBlockData_for_FinalPermutation, LeftBlockData_for_FinalPermutation);
}


//select S Box, row and column to find the value of S box at specific location
void Encryption::S_Box_Value(int rightXOR[48]) {
	int row, column;
	int j = 1, decimalValueOfSBox;
	int dumyFinalData[4];
	int counter = 0, a = 0;
	bool checkWhileLoop = false;
	bool flag = false;

	//finalRightBlock[i] = 0;
	for (int i = 0; i < 48; i = i + 6) {
		dumyFinalData[0] = 0;
		dumyFinalData[1] = 0;
		dumyFinalData[2] = 0;
		dumyFinalData[3] = 0;
		/*first and last bit*/
		if (rightXOR[i] == 0 && rightXOR[i + 5] == 0)
			row = 0;
		else if (rightXOR[i] == 0 && rightXOR[i + 5] == 1)
			row = 1;
		else if (rightXOR[i] == 1 && rightXOR[i + 5] == 0)
			row = 2;
		else if (rightXOR[i] == 1 && rightXOR[i + 5] == 1)
			row = 3;

		/*remaining bit*/

		if (rightXOR[i + 1] == 0 && rightXOR[i + 2] == 0 && rightXOR[i + 3] == 0 && rightXOR[i + 4] == 0)
			column = 0;
		else if (rightXOR[i + 1] == 0 && rightXOR[i + 2] == 0 && rightXOR[i + 3] == 0 && rightXOR[i + 4] == 1)/*2*/
			column = 1;
		else if (rightXOR[i + 1] == 0 && rightXOR[i + 2] == 0 && rightXOR[i + 3] == 1 && rightXOR[i + 4] == 0)/*3*/
			column = 2;
		else if (rightXOR[i + 1] == 0 && rightXOR[i + 2] == 0 && rightXOR[i + 3] == 1 && rightXOR[i + 4] == 1)/*4*/
			column = 3;
		else if (rightXOR[i + 1] == 0 && rightXOR[i + 2] == 1 && rightXOR[i + 3] == 0 && rightXOR[i + 4] == 0)/*5*/
			column = 4;
		else if (rightXOR[i + 1] == 0 && rightXOR[i + 2] == 1 && rightXOR[i + 3] == 0 && rightXOR[i + 4] == 1)/*6*/
			column = 5;
		else if (rightXOR[i + 1] == 0 && rightXOR[i + 2] == 1 && rightXOR[i + 3] == 1 && rightXOR[i + 4] == 0)/*7*/
			column = 6;
		else if (rightXOR[i + 1] == 0 && rightXOR[i + 2] == 1 && rightXOR[i + 3] == 1 && rightXOR[i + 4] == 1)/*8*/
			column = 7;
		else if (rightXOR[i + 1] == 1 && rightXOR[i + 2] == 0 && rightXOR[i + 3] == 0 && rightXOR[i + 4] == 0)/*9*/
			column = 8;
		else if (rightXOR[i + 1] == 1 && rightXOR[i + 2] == 0 && rightXOR[i + 3] == 0 && rightXOR[i + 4] == 1)/*10*/
			column = 9;
		else if (rightXOR[i + 1] == 1 && rightXOR[i + 2] == 0 && rightXOR[i + 3] == 1 && rightXOR[i + 4] == 0)/*11*/
			column = 10;
		else if (rightXOR[i + 1] == 1 && rightXOR[i + 2] == 0 && rightXOR[i + 3] == 1 && rightXOR[i + 4] == 1)/*12*/
			column = 11;
		else if (rightXOR[i + 1] == 1 && rightXOR[i + 2] == 1 && rightXOR[i + 3] == 0 && rightXOR[i + 4] == 0)/*13*/
			column = 12;
		else if (rightXOR[i + 1] == 1 && rightXOR[i + 2] == 1 && rightXOR[i + 3] == 0 && rightXOR[i + 4] == 1)/*14*/
			column = 13;
		else if (rightXOR[i + 1] == 1 && rightXOR[i + 2] == 1 && rightXOR[i + 3] == 1 && rightXOR[i + 4] == 0)/*15*/
			column = 14;
		else if (rightXOR[i + 1] == 1 && rightXOR[i + 2] == 1 && rightXOR[i + 3] == 1 && rightXOR[i + 4] == 1)/*15*/
			column = 15;

		decimalValueOfSBox = list_of_S_Boxes(j, row, column);
		//outputFile << "\nS Box " << j << ",Row = " << row << ", Col = " << column << ", Value = " << decimalValueOfSBox << ", ";

		j++; // to update the value of S Boxes
		//outputFile << ", Straight PBox.\n";

		if (decimalValueOfSBox == 0) {
			checkWhileLoop = true;
			flag = false;
		}
		else {
			dumyFinalData[0] = 0;
			dumyFinalData[1] = 0;
			dumyFinalData[2] = 0;
			dumyFinalData[3] = 0;
			while (decimalValueOfSBox != 0)
			{
				flag = true;
				dumyFinalData[counter] = decimalValueOfSBox % 2;
				decimalValueOfSBox = decimalValueOfSBox / 2;
				//outputFile << dumyFinalData[counter];
				checkWhileLoop = false;
				counter++;
				//	outputFile << "counter " << counter << ", Value = " << dumyFinalData[counter] << endl;
			}
		}

		if (checkWhileLoop == true && counter == 0) {
			finalRightBlock[a] = dumyFinalData[3];
			finalRightBlock[a + 1] = dumyFinalData[2];
			finalRightBlock[a + 2] = dumyFinalData[1];
			finalRightBlock[a + 3] = dumyFinalData[0];
		//	outputFile << finalRightBlock[a] << finalRightBlock[a + 1] << finalRightBlock[a + 2] << finalRightBlock[a + 3] << endl;
			a = a + 4;
			//outputFile << "a-0 = " << a << endl;
		}
		else {
			finalRightBlock[a] = dumyFinalData[3];
			finalRightBlock[a + 1] = dumyFinalData[2];
			finalRightBlock[a + 2] = dumyFinalData[1];
			finalRightBlock[a + 3] = dumyFinalData[0];
			//outputFile << finalRightBlock[a] << finalRightBlock[a + 1] << finalRightBlock[a + 2] << finalRightBlock[a + 3] << endl;
			counter = 0;
			a = a + 4;
			//	outputFile << "a = " << a << endl;
			dumyFinalData[0] = 0;
			dumyFinalData[1] = 0;
			dumyFinalData[2] = 0;
			dumyFinalData[3] = 0;
		}
		counter = 0;
	}
	a = 0;
	//outputFile << endl;
}

//final permutation to get the encrypted text
void Encryption::final_Permutation(int RightBlockData_for_FinalPermutation[][32], int LeftBlockData_for_FinalPermutation[][32]) {
	int finalPermuataionTable[64] = {40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,
	35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};
	int FinalPermuatation[64];
	int combineBlock[64];
	char hexadecimal;
	//outputFile << "Before final permutation.\n";
	for (int i = 0; i < 64; i++) {
		if (i < 32) {
			combineBlock[i] = LeftBlockData_for_FinalPermutation[15][i];
		}
		else {
			combineBlock[i] = RightBlockData_for_FinalPermutation[15][i-32];
		}
	}
	outputFile << "Cipher text in Binary.\n";
	for (int i = 0; i < 64; i++) {
		FinalPermuatation[i] = combineBlock[finalPermuataionTable[i] - 1];
		outputFile << FinalPermuatation[i];
	}
	outputFile << endl << "Hexa-Decimal     =  ";
	for (int i = 0; i < 64; i++) {
		if (i == 3 || i == 7 || i == 11 || i == 15 || i == 19 || i == 23 || i == 27 || i == 31 || i == 35 || i == 39 || i == 43 || i == 47 || i == 51 || i == 55 || i == 59 || i == 63) {
			hexadecimal = binary_hexadecimal(FinalPermuatation[i - 3], FinalPermuatation[i - 2], FinalPermuatation[i - 1], FinalPermuatation[i]);
			outputFile << hexadecimal;
		}
	}
	cout << endl;
	outputFile << "\n------------------------------------------------------------------------\n";
	outputFile << "------------------------------------------------------------------------\n";
	outputFile << "------------------------------------------------------------------------\n";
	outputFile.close();
}

//list of S Boxes
int Encryption::list_of_S_Boxes(int selectBox, int row, int column) {
	switch (selectBox)
	{
	case 1:
	{
		int S1[4][16] = { {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} };
		return_S_Box_Value = S1[row][column];
		return return_S_Box_Value;
	}
		break;
	case 2:
	{
		int S2[4][16] = { {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9} };
		return_S_Box_Value = S2[row][column];
		return return_S_Box_Value;
	}
		break;
	case 3:
	{
		int S3[4][16] = { {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
		{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12} };
		return_S_Box_Value = S3[row][column];
		return return_S_Box_Value;
	}
		break;
	case 4: {
		int S4[4][16] = { {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14} };
		return_S_Box_Value = S4[row][column];
		return return_S_Box_Value;
	}
		break;
	case 5: {
		int S5[4][16] = { {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3} };
		return_S_Box_Value = S5[row][column];
		return return_S_Box_Value;
	}
		break;
	case 6: {
		int S6[4][16] = { {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13} };
		return_S_Box_Value = S6[row][column];
		return return_S_Box_Value;
	}
		break;
	case 7: {
		int S7[4][16] = { {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12} };
		return_S_Box_Value = S7[row][column];
		return return_S_Box_Value;
	}
		break;
	case 8: {
		int S8[4][16] = { {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11} };
		return_S_Box_Value = S8[row][column];
		return return_S_Box_Value;
	}
		break;
	default: {
		outputFile << "Incorrect selection of S Box.\n";
		return 0; 
	}
		break;
	}
}
// convert decimal to binary

int Encryption::convert_decimal_to_binary(int data) {
	switch (data)
	{
	case 0:
		return 0000;
		break;
	case 1:
		return 0001;
		break;
	case 2:
		return 0010;
		break;
	case 3:
		return 0011;
		break;
	case 4:
		return 0100;
		break;
	case 5:
		return 0101;
		break;
	case 6:
		return 0110;
		break;
	case 7:
		return 0111;
		break;
	case 8:
		return 1000;
		break;
	case 9:
		return 1001;
		break;
	case 10:
		return 1010;
		break;
	case 11:
		return 1011;
		break;
	case 12:
		return 1100;
		break;
	case 13:
		return 1101;
		break;
	case 14:
		return 1110;
		break;
	case 15:
		return 1111;
		break;
	default: {
		outputFile << "Incorrect Selection.\n";
		return 0;
	}
		break;
	}
}

char Encryption::binary_hexadecimal(int a, int b, int c, int d) {
	if (a == 0 && b == 0 && c == 0 && d == 0)
		return '0';
	else if (a == 0 && b == 0 && c == 0 && d == 1)
		return '1';
	else if (a == 0 && b == 0 && c == 1 && d == 0)
		return '2';
	else if (a == 0 && b == 0 && c == 1 && d == 1)
		return '3';
	else if (a == 0 && b == 1 && c == 0 && d == 0)
		return '4';
	else if (a == 0 && b == 1 && c == 0 && d == 1)
		return '5';
	else if (a == 0 && b == 1 && c == 1 && d == 0)
		return '6';
	else if (a == 0 && b == 1 && c == 1 && d == 1)
		return '7';
	else if (a == 1 && b == 0 && c == 0 && d == 0)
		return '8';
	else if (a == 1 && b == 0 && c == 0 && d == 1)
		return '9';
	else if (a == 1 && b == 0 && c == 1 && d == 0)
		return 'A';
	else if (a == 1 && b == 0 && c == 1 && d == 1)
		return 'B';
	else if (a == 1 && b == 1 && c == 0 && d == 0)
		return 'C';
	else if (a == 1 && b == 1 && c == 0 && d == 1)
		return 'D';
	else if (a == 1 && b == 1 && c == 1 && d == 0)
		return 'E';
	else if (a == 1 && b == 1 && c == 1 && d == 1)
		return 'F';
	else
		return 'g';
}
// convert the hexadecimal into binary
string Encryption::convert_hex_to_binary(char value) {
	switch (value)
	{
	case'0':
		return "0000";
		break;
	case'1':
		return "0001";
		break;
	case'2':
		return "0010";
		break;
	case'3':
		return "0011";
		break;
	case'4':
		return "0100";
		break;
	case'5':
		return "0101";
		break;
	case'6':
		return "0110";
		break;
	case'7':
		return "0111";
		break;
	case'8':
		return "1000";
		break;
	case'9':
		return "1001";
		break;
	case'a':
		return "1010";
		break;
	case'b':
		return "1011";
		break;
	case'c':
		return "1100";
		break;
	case'd':
		return"1101";
		break;
	case'e':
		return "1110";
		break;
	case'f':
		return "1111";
		break;
	default:
		outputFile << "Incorrect Input!\n";
		return 0;
		break;
	}
}
Encryption::~Encryption()
{

}

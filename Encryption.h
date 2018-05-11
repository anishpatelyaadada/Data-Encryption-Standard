#pragma once
#include <cstring>
#include <string>
#include <cstdlib>
#include<iostream>
#include<fstream>
using namespace std;
class Encryption
{
private:
	int final_key_16[16][48];
	int return_S_Box_Value;
	int finalRightBlock[32];
	int finalRightBlock_Operation[32];
	ofstream outputFile;
public:
	string filePath = "C:\\Users\\kings\\Desktop\\data.txt";
	

	Encryption();
	// below function are to generate the key
	void InitialKey_to_Binary(char[]);
	string convert_hex_to_binary(char);
	void parity_drop(int[]);
	void generate_16_parity_drop(int[], int[]);
	void generete_16_keys(int[][28], int[][28]);

	// below text are to permute text using key and generate final cipher text
	void InitialText_to_Binary(char[]);
	void initial_permutation(int[]);
	void expansion_P_Box(int[], int[]);
	void S_Box_Value(int[]);
	int list_of_S_Boxes(int, int, int);
	int convert_decimal_to_binary(int);
	void final_Permutation(int[][32], int[][32]);
	char binary_hexadecimal(int, int, int, int);
	~Encryption();
};


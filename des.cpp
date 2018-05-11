#include<iostream>
#include<fstream>
#include "Encryption.h"
using namespace std;

int main() {
	Encryption();
	Encryption data;
	/*ofstream outpuFile;
	outpuFile.open(data.filePath,ios::app);
	outpuFile << "Anish Patel.\n";
	outpuFile << "Project 2:- DES\n";
	outpuFile << "------------------------------------------------------------------------\n";
	outpuFile << "Key and Datas\n";
	outpuFile << "------------------------------------------------------------------------\n";
	outpuFile << "Key = Security\n";
	outpuFile << "Key in Hexa - Decimal = 5345435552495459\n";
	outpuFile << "Text = I Like Computer Class.\n";
	outpuFile << "Above text is divided into three block.\n";
	outpuFile << "Text 1 Block = I Like Com\n";
	outpuFile << "Text 1 Hexa-Decimal = 494c494b45434f4d\n";
	outpuFile << "Text 2 Block = puter Cla\n";
	outpuFile << "Text 2 Hexa-Decimal = 5055544552434c41\n";
	outpuFile << "Text 3 Block = ss\n";
	outpuFile << "Text 3 Hexa-Decimal = 5353000000000000\n";

	outpuFile << "------------------------------------------------------------------------\n";*/
	// key = security - into hexadecimal
	char initial_key[16] = { '5','3','4','5','4','3','5','5','5','2','4','9','5','4','5','9' };
	// plain text into hexadecimal
	char initial_plaintext_1[16] = { '4','9','4','c','4','9','4','b','4','5','4','3','4','f','4','d' };
	char initial_plaintext_2[16] = { '5','0','5','5','5','4','4','5','5','2','4','3','4','c','4','1' };
	char initial_plaintext_3[16] = { '5','3','5','3','0','0', '0','0','0','0','0','0','0','0','0','0'};

	//char initial_key[16] = { '1','3','3','4','5','7','7','9','9','b','b','c','d','f','f','1' };
	// plain text into hexadecimal
	//char initial_plaintext_1[16] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
	
	data.InitialKey_to_Binary(initial_key);
	
	data.InitialText_to_Binary(initial_plaintext_1);	
	data.InitialText_to_Binary(initial_plaintext_2);	
	data.InitialText_to_Binary(initial_plaintext_3);

	system("pause");	
	return 0;
}
// wav to hex converter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;


char aaahex(int n) {
	switch (n)
	{
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	case 10: return 'a';
	case 11: return 'b';
	case 12: return 'c';
	case 13: return 'd';
	case 14: return 'e';
	case 15: return 'f';
	default:
		return 'k';
	};
}

int main()
{
	int n = 2*32000;
	int m = 0;
	char next = 'a';
	//setlocale(LC_ALL, "rus");
	// char a[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	string path = "C:\\Users\\Gosha\\Downloads\\VK audio\\WWRYH.wav";

	ifstream filein(path, ios::binary | ios::in);
	ofstream fileout(path += "second.inc");
	if (filein.is_open())
		cout << "ok" << endl;
	else
	{
		cout << "not ok\n" << endl;
		cin.get();
		return -1;
	}
	if (fileout.is_open())
		cout << "ok" << endl;
	else
	{
		cout << "not ok\n" << endl;
		cin.get();
		return -1;
	}
	
	//char* buffer = new char[n + 1];
	//buffer[n] = 0;
	//
	////FILE *fpin;
	////FILE *fpout;
	////fpin = fopen("C:\\Users\\Gosha\\Downloads\\VK audio\\8kACDC Recovered - Highway to Hell.wav", "r");
	////
	////if (fpin) fclose(fpin);
	////fputs("  ", fpout);
	////fpout = fopen("C:\\Users\\Gosha\\Downloads\\VK audio\\8kACDC Recovered - Highway to Hell.wav", "wb");
	//file.read(buffer, n);
	//file.close();
	//fileout << "sound: "<<std::endl;
	//for (int j = 0; j < strlen(buffer) / 16 ; j++){
	//	fileout << ".db   ";
	//	for (int i = 0; i < 16; i++) {
	//		fileout << "0x";			
	//		fileout << a[buffer[16 * j + i] / 16] << a[buffer[16 * j + i] % 16] << " ";
	//	}
	//	fileout << std::endl;
	//}
	//if (strlen(buffer) % 16) {
	//	fileout << ".db   ";
	//	for (int i = 0; i < strlen(buffer) % 16; i++) {
	//		fileout << "0x";
	//		fileout << a[buffer[strlen(buffer) / 16 + i] / 16] << a[buffer[strlen(buffer) / 16 + i] % 16] << " ";
	//		/*fileout << "0x";
	//		fileout << hex << buffer[strlen(buffer) / 16 + i] << " ";
	//		cout << hex << buffer[strlen(buffer) / 16 + i] << " ";*/
	//	}
	//	fileout << std::endl;
	//}

	fileout << "sound: " << std::endl;

	/*do
	{
		do
		{
			do
			{
				do
				{
					filein.get(next);
				} while (next!='d');
				filein.get(next);
			} while (next != 'a');
			filein.get(next);
		} while (next != 't');
		filein.get(next);
	} while (next != 'a');*/

	do
	{
		//if (!(m % 16)) { fileout << std::endl << ".db   "; };

		filein.get(next);
		if (next == ' ') {
			fileout << ", 0x";
			filein.get(next);
		}
		else {
			if (next == '\r') {
				fileout << "\n.db   0x";
				filein.get(next);
			}
		}

		fileout << next;

		//fileout << "0x" 
		/*	fileout<< aaahex((int) next / 16) << aaahex((int) next % 16);

		if ((m % 16) - 15) {
			fileout << ", ";
		};*/

		cout << next;
		m++;
	} while (/*(!filein.eof())&&*/(m<n));

	fileout << std::endl << "soundend: " << std::endl;

	fileout.flush();
	fileout.close();

	cout <<"     nda " << m;

	system("pause");
	return 0;
}

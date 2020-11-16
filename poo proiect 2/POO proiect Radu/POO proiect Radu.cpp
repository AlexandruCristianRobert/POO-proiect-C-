
// sala de fitness

/*					programarea activitatilor cu un instructor
					instructor se identifica dupa :
													id
													nume
													vector dinamic de programari

													o programare contine
																		informatii despre participant
																		data programarii
																		durata in ore a sedintei.

				Sa se calculeze
								gradul de incarcare a salii per sedinta.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string.h>
#include<iomanip>
#include<string>
using namespace std;
class Instructor
{
private:
	char* nume_instructor;
	int* programari;								//pointer catre vector
	int lungime_vector;
	int nextIndex;							//urmatoarea valoare limita
	int li;
	int id_instructor;

public:

	Instructor(int* fprogramari, const char* fnume_instructor = "Anonim") :programari(fprogramari)
	{
		programari = new int[10];
		for (int i = 0;i < 5;i++)
			programari[i] = 0;
		lungime_vector = 5;
		nextIndex = 0;
		li = strlen(fnume_instructor);
		nume_instructor = new char[li + 1];
		strcpy(nume_instructor, fnume_instructor);
		static int id = 0;
		id_instructor = id++;

	}

	Instructor(Instructor& ob) :programari(ob.programari)
	{
		programari = new int[5];
		for (int i = 0;i < 5;i++)
			programari[i] = 0;
		li = strlen(ob.nume_instructor);
		nume_instructor = new char[li + 1];
		strcpy(nume_instructor, ob.nume_instructor);
		static int id = 0;
		id_instructor = id++;

	}
	void Afisare()
	{
		cout << "Intrusctorul " << nume_instructor << " cu id-ul:" << id_instructor << " are urmatoarele programari:" << endl;
		cout << "Nr participanti:" << setw(20) << "Data sedinta" << setw(35) << "Durata sedinta(ore)" << endl;

		for (int i = 0;i < lungime_vector;i = i + 5)
		{
			cout << programari[i] << setw(25) << programari[i + 1] << "." << programari[i + 2] << "." << programari[i + 3] << setw(25) << programari[i + 4] << endl;
		}
		cout << endl;
	}

	void Grad_Ocupare(int n)
	{
		float procent, numarParticipanti, numarMaxim = n;
		cout << endl;
		for (int i = 0;i < lungime_vector;i = i + 5)
		{
			numarParticipanti = programari[i];
			procent = numarParticipanti / numarMaxim * 100;
			
			if (numarParticipanti>numarMaxim)
			{
				cout << "Sala este supra-aglomerata!" << endl;
			}
			else
				if (numarParticipanti == numarMaxim)
				{
					cout << "Sala este plina in timpul acestei sedinte" << endl;
				}
				else
					cout << "In timpul sedintei, sala este ocupata in proportie de " << setprecision(4) << procent << " la suta";
		}
		cout << endl;
	}

	void set_nume(const char* nume)
	{
		if (li < strlen(nume))
		{
			li = strlen(nume);
			delete[] nume_instructor;
			nume_instructor = new char[li + 1];
		}
		strcpy(nume_instructor, nume);
	}

	char* get_nume()
	{
		return nume_instructor;
	}

	int& operator[](int index)
	{
		int* programariNoi;  // pointer catre vectorul nou
		if (index >= lungime_vector)
		{
			programariNoi = new int[index + 5];
			for (int i = 0;i < nextIndex;i++)
				programariNoi[i] = programari[i];
			for (int j = nextIndex;j < index + 5;j++)	//initializam restul
				programariNoi[j] = 0;
			lungime_vector = index + 5;		//lungimea creste
			delete[] programari;				//stergem vectorul nou
			programari = programariNoi;			//alocam nou vector
		}
		if (index > nextIndex)							//setam next index dupa index
			nextIndex = index + 1;
		return *(programari + index);         // referinta catre element
	}
	void AdaugareValoare(int val)
	{
		int* programariNoi;
		if (nextIndex == lungime_vector)
		{
			lungime_vector = lungime_vector + 5;
			programariNoi = new int[lungime_vector];
			for (int i = 0;i < nextIndex;i++)
				programariNoi[i] = programari[i];
			for (int j = nextIndex;j < lungime_vector;j++)
				programariNoi[j] = 0;
			delete[] programari;
			programari = programariNoi;
		}
		programari[nextIndex++] = val;
	}
	int lungime()
	{
		return lungime_vector;
	}
	~Instructor()
	{
		delete[] nume_instructor;

		delete[] programari;
	}

};
int main()
{
	/*
															Instructiuni!!

Se creaza Instructorul sub forma de: Instructor nume({},"nume instructor");

se adauga valori  folosint functia AdaugareValoare
Din 5 in 5 5 pentru a rula corect programul in ordinea : nr participanti, data(3 inputs), durata

Pentru calculul procentului se  apeleaza functia Grad_Ocupare(MaximPersoane);

	*/
	int  MaximPersoane,nrParticipanti,data[3],nrOre;
	cout << "Introdu numarul maxim de persoane ce pot fi in sala:" << endl;
	cin >> MaximPersoane;
	int continuare=1;

	Instructor s1({ }, "ionel");
	while (continuare==1)
	{
		cout << "Introdu numarul de participanti: ";
		cin >> nrParticipanti;
		cout << endl;
		s1.AdaugareValoare(nrParticipanti);
		cout << "Introdu data la care o sa fie sedinta: "<<endl;
		cout << "Ziua:";
		cin>>data[0];
		cout << endl << "Luna:";
		cin >> data[1];
		cout << endl << "Anul:";
		cin >> data[2];
		s1.AdaugareValoare(data[0]);
		s1.AdaugareValoare(data[1]);
		s1.AdaugareValoare(data[2]);
		cout << endl << "Introdu durata sedintei:";
		cin >> nrOre;
		s1.AdaugareValoare(nrOre);
		cout << endl << "Vrei sa mai introduci o sedinta?"<<endl<<"Daca da, scrie 1"<<endl;
		cin >> continuare;
		cout << endl;
	}

	s1.Afisare();
	s1.Grad_Ocupare(MaximPersoane);
	cout << endl; // pentru a arata mai frumos

	//Instructor s2({}, "Raducu");
	//s2.AdaugareValoare(9);
	//s2.AdaugareValoare(11);
	//s2.AdaugareValoare(11);
	//s2.AdaugareValoare(2022);
	//s2.AdaugareValoare(21);
	//s2.Afisare();
	//s2.Grad_Ocupare(MaximPersoane);


}

#include<iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <sstream>
using namespace std;

int total; 
string cuvant[6];
int a[6];
string solutie;
string definitii[6];
int nivel = 1;
void extrage_random(string nume_fisier, int &index_global)
{
    ifstream f(nume_fisier.c_str());
    if (!f.is_open()) {
        cout << "Eroare la deschiderea fisierului: " << nume_fisier << endl;
        exit(1);
    }

    const int MAX = 100;
    string cuv[MAX];
    int lung[MAX];
    string def[MAX];

    int n = 0;
    string line;

    while (getline(f, line) && n < MAX) {
   
        stringstream ss(line);
        getline(ss, cuv[n], ':');
        lung[n] = cuv[n].length();
        getline(ss, def[n]);
        n++;
    }
    f.close();
    if (n > 0) {
        for (int i = 0; i < 2; i++) {
            int r = rand() % n;
            cuvant[index_global] = cuv[r];
            a[index_global] = lung[r];
            definitii[index_global] = def[r];
            index_global++;
        }
    }
}

void incarca_toate()
{
    srand(time(NULL));

    int index = 0;

    extrage_random("easy.txt", index);
    extrage_random("medium.txt", index);
    extrage_random("hard.txt", index);
}

void regulament()
{
	cout<< "		Bine ati venit la 'Jocul cuvintelor!' "<< endl;
	cout<< " Regulament:  "<< endl;
	cout<< "1.Utilizatorul trebuie sa ghiceasca cuvintele."<< endl;
	cout<< "2.Ficare cuvant va avea o definitie si veti putea cumpara litere. Fiecare litera va costa 100 lei, iar daca gresiti un cuvant de 3 ori se va scadea suma din total."<< endl;
	cout<< "3.Vom avea 3 nivele de dificulate . Un nivel are 2 cuvinte"<< endl;
	cout<< " Succes!!!!"<<endl;
	cout<<endl;
}

void etapa()
{
	cout<<endl;
	if( nivel == 1 || nivel ==2)
		cout<<"			     NIVEL USOR"<<endl;
	else if( nivel == 3 || nivel ==4)
		cout<<"			     NIVEL MEDIU"<<endl;
	else cout<<"			     NIVEL GREU"<<endl;
	cout<<"			Nivelul "<<nivel << ": cuvant de "<< a[nivel - 1] << " litere"<< endl;
	cout<<endl;
	cout<<"Definitia:"<< endl;
	cout<< definitii[nivel-1] <<endl;
	int cifra = a[nivel-1] ;
	cout<<"*";
	solutie = '*';
	for(int i = 1; i< cifra; i++)
		{
			cout<<"*";
			solutie += '*';
		}
		
	cout<<endl;
	
	
}

void litera()
{
	string cuvant_cautat = cuvant[nivel -1];
	bool x = 0;
	char alfabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
	                          'h', 'i', 'j', 'k', 'l', 'm', 'n', 
	                          'o', 'p', 'q', 'r', 's', 't', 'u',
	                          'v', 'w', 'x', 'y', 'z' };
	for(int i = 0; i < 26 ; i++)
		{
			for(int j = 0; j < cuvant_cautat.length(); j++)
				if(alfabet[i] == cuvant_cautat[j] && solutie[j] != alfabet[i]) 
				{
					x =1;
					solutie[j] = alfabet[i];
				}
				
			if(x) break;		
		}
	cout<< solutie <<endl;
}

void rezolvare()
{
	string citire;
	bool ok=1;
	int bani = a[nivel-1] * 100;
	int nr_incercari = 3;
	while(ok)
	{
		cout<< "Poti sa ceri o litera(tasteaza '*') sau sa dai solutia."<< endl;
		cin>> citire;
		if(citire == cuvant[nivel-1]) break;
		if(nr_incercari)
		{	
			if(citire.length()>=1 && citire != "*") nr_incercari --;
				else if(citire == "*") 
						{
							bani = bani - 100;
							litera();
							
						}
						else nr_incercari --;
		}
		else 
		{
			total = total - bani;
			cout<<"Ai incercat de 3 ori. Din pacate ai gresit cuvantul! "<<endl;
			cout<<" Cuvantul era "<< cuvant[nivel-1]<<"."<< endl;
			cout<< "--------------------------------"<<endl;
			cout<<"Punctaj: "<< total<<endl;
			return;
		}
			
	}
	total = total + bani;
	cout<< "--------------------------------"<<endl;
	cout<<"Punctaj: "<< total<<endl;
}


void final()
{
	cout<< "--------------------------------"<<endl;
	cout<< "		FELICITARI!!!"<< endl;
	cout<< "--------------------------------"<<endl;
	cout<< "Total : " << total<< endl;
}
int main()
{
	char raspuns;
	incarca_toate();
	regulament();
	cout<<"Esti pregatit? y/n"<< endl;
	cin>> raspuns;
	
	if(raspuns == 'n') return 0;
	
	for (int i = 0; i<=5 ; i++)
	{
		
		etapa();
		rezolvare(); 
		nivel ++;
	}
	final();
}

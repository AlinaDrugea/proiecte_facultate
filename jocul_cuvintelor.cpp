#include<iostream>
#include <string>
#include <cctype>
using namespace std;

int total; 
string cuvant[] = {"luna", 
				   "punte",
				   "striga",
				   "inginer",
				   "document",
				   "misterios",
				   "caracterul"};
int a[] = {4,5,6,7,8,9,10};
string solutie;
string definitii[]= {"Satelitul natural al Pamantului ",
					 "Legatura intre doua lumi, fie ea peste apa sau in imaginatie",
					 "A emite un sunet puternic pentru a atrage atentia intr-un mod intentionat",
					 "Persoana care concepe si organizeaza sisteme complexe, transformand ideile in structuri functionale",
					 "Inregistrare ce pastreaza informatii pentru analiza sau referinta ulterioara",
					 "Care ascunde informatii sau intentii, greu de inteles",
					 "Ansamblul trasaturilor interioare"};
int nivel = 1;

void regulament()
{
	cout<< "		Bine ati venit la 'Jocul cuvintelor!' "<< endl;
	cout<< " Regulament:  "<< endl;
	cout<< "1.Utilizatorul trebuie sa ghiceasca cuvintele. Aceste cuvinte sunt de dificultati medii."<< endl;
	cout<< "2.Ficare cuvant va avea o definitie si veti putea cumpara litere. Fiecare litera va costa 100 lei, iar daca gresiti un cuvant de 3 ori se va scadea suma din total."<< endl;
	cout<< "3.Vom avea mai multe nivele de la cuvinte de 4 litere pana la 10 litere."<< endl;
	cout<< " Succes!!!!"<<endl;
	cout<<endl;
}

void etapa()
{
	cout<<endl;
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
	int nr_incercari = 2;
	while(ok)
	{
		cout<< "Poti sa ceri o litera(tasteaza '*') sau sa dai solutia."<< endl;
		cin>> citire;
		if(citire == cuvant[nivel-1]) break;
		if(nr_incercari)
		{	
			if(citire.length()>1) nr_incercari --;
				else if(citire == "*") 
						{
							bani -= 100;
							litera();
							
						}
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
	
	regulament();
	cout<<"Esti pregatit? y/n"<< endl;
	cin>> raspuns;
	
	if(raspuns == 'n') return 0;
	
	for (int i = 4; i<=10 ; i++)
	{
		
		etapa();
		rezolvare(); 
		nivel ++;
	}
	final();
}

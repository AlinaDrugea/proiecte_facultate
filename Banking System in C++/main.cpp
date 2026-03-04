#include <iostream>
#include <fstream>
#include "account.h"
#include <cstdlib>
#include <sstream> 
#include <ctime>
#include "checking_account.h"
#include "savings_account.h"
using namespace std;

ofstream f("conturi.txt", ios::app);
ifstream fin("conturi.txt");

string genereazaCod(int lungime);
int cauta__iban(string iban_cautat);
int meniu ();
void cauta_cont(string cnp_cautat);
int main() {
	srand(time(NULL));
	string nr_bancar;
    int opt;
    int tip_cont;
    string cnp;
   
	opt = meniu();    
    while (opt!=0)    
    {
    	
    	if (opt == 1)
	    {
		cout<<" Introduceti Codul Numerit Personal ";
		cin>> cnp;
		cout<< "Ce tip de cont bancar doriti?"<< endl;
		cout<< "1.Cont curent"<< endl;
		cout<< "2.Cont economii"<< endl;
		cout<< "3.Cont curent cu descoperire de cont "<< endl;
		cin>> tip_cont;
		
		
		if (tip_cont == 1 )
		{
			nr_bancar = genereazaCod(10);
			Account A(nr_bancar, 100);
			cout<< A.get_balanta()<<"lei  "<< A.get_cont();
			f<<cnp;
			f<< " ";
			f<< A.get_cont()<< " "<<A.get_balanta() ;
			f<< " Cont curent"<<endl;
		}
		else if(tip_cont == 2)
		{
			nr_bancar = genereazaCod(10);
			savings_account A(nr_bancar, 100);
			cout<< A.get_balanta()<<"lei  "<< A.get_cont();
			f<<cnp;
			f<< " ";
			f<< A.get_cont()<< " "<<A.get_balanta() ;
			f<<" Cont economii"<<endl;
		}
			
		else{
			nr_bancar = genereazaCod(10);
			checking_account A(nr_bancar, 100,10000);
			cout<< A.get_balanta()<<"lei  "<< A.get_cont();
			f<<cnp;
			f<< " ";
			f<< A.get_cont()<< " "<<A.get_balanta() ;
			f<<" Cont curent cu descoperire de cont"<< A.get_lim()<<endl;
		
		}
			
		}
		if(opt == 2){
		cout<<" Introduceti Codul Numerit Personal ";
		cin>> cnp;
		cauta_cont(cnp);
		
		
		}
		if(opt == 3){
		cout<<" Introduceti Contul in care doriti sa depuneti : "<< endl;
		cin>>nr_bancar;
		
		   
		        
				
				
			
		}
		opt = meniu();
		
	}

    

    return 0;
}
string genereazaCod(int lungime)
{ 
	string caractere = "0123456789"; 
	string rezultat = "RO"; 
	for (int i = 2; i < lungime; i++) 
		{ rezultat += caractere[rand() % caractere.size()]; } 
	return rezultat;
}
int meniu ()
{
	int opt;
	    cout << "\n=== MENIU BANCA ===\n";
        cout << "1. Creeaza cont\n";
        cout << "2. Afiseaza conturi\n";
        cout << "3. Depozitare\n";
        cout << "4. Retragere\n";
        cout << "5. Aplica dobanda\n";
        cout << "0. Iesire\n";
        cout << "Optiune: ";
        cin>> opt;
    return opt;    
}

void cauta_cont(string cnp_cautat)
{
    ifstream f("conturi.txt");
    if(!f.is_open()){
        cout << "Eroare la deschiderea fisierului!" << endl; 
        return;
    }

    string line;
    bool gasit = false;
    bool antet_afisat = false;

    while(getline(f, line)) {
        stringstream ss(line);
        string cnp_file, iban_file, balanta_file, tip_cont_file;

        
        getline(ss, cnp_file, ' ');
        getline(ss, iban_file, ' ');
        getline(ss, balanta_file, ' ');
        getline(ss, tip_cont_file); 

        if(cnp_file == cnp_cautat) {
            if(!antet_afisat){
                cout << "CNP           numar_cont sold        tip " << endl;
                antet_afisat = true;
            }
            cout << cnp_file << " " << iban_file << " " << balanta_file << "lei " << tip_cont_file << endl;
            gasit = true;
        }
    }

    if(!gasit)
        cout << "Nu exista conturi pentru acest CNP.\n";
}
int cauta__iban(string iban_cautat)
{
    ifstream f("conturi.txt");
    if(!f.is_open()){
        cout << "Eroare la deschiderea fisierului!" << endl; 
        return;
    }

    string line;
    bool gasit = false;
	int balanta; 
    while(getline(f, line)) {
        stringstream ss(line);
        string cnp_file, iban_file, balanta_file, tip_cont_file;

        
        getline(ss, cnp_file, ' ');
        getline(ss, iban_file, ' ');
        getline(ss, balanta_file, ' ');
        getline(ss, tip_cont_file); 

        if(iban_file == iban_cautat) {
        	int a = 1;
           	for(int i = 0 ; i< strlen(balanta_file);i++)
           	{
           		balanta += (balanta_file[i]-'0')*a;
			   }
			   
            gasit = true;
            
        }
    }

    if(!gasit)
        return 0;
    return balanta;
    
}


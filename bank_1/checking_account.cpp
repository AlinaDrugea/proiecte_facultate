#include <string>
#include <iostream>
#include "checking_account.h"
#include "account.h"

checking_account::  checking_account(string nr, double sum, double lim):Account(nr,sum){
	limita = lim;
}

void checking_account:: retragere(double sum)
{
	if (sum+sum*2/100 >limita+balanta ) cout<< "Ai trecut limita"<<endl;
	else
	{
		sum = sum +sum*2/100;
		cout<<" Permisa retragerea"<<endl;
		cout<<" Comision "<< sum*2/100 << endl;
	}
	balanta -= 	limita;
}

void checking_account:: afisare(){
	cout<< " Contul dumneavoastra cu numarul "<< numar_cont << " are soldul "<< balanta<< endl;
	cout<< " Limita "<< limita<< endl;
	
}

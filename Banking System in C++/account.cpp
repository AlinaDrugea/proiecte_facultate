#include <string>
#include <iostream>
#include "account.h"
Account::Account (string nr, double sum){
	balanta= sum;
	numar_cont = nr;
	
}

Account::~Account() {}
void Account:: depozitare(double sum){
	balanta = balanta +sum;
	
	
}
void Account:: retragere(double sum){
	balanta = balanta -sum;
	
}
void Account:: afisare(){
	cout<< " Contul dumneavoastra cu numarul "<< numar_cont << " are soldul "<< balanta<< endl;
}

double Account:: get_balanta(){
	return balanta;
	
}
string Account:: get_cont(){
	return numar_cont;
	
}

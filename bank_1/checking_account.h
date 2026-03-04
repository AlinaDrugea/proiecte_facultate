#pragma once
#include <string>
#include <iostream>
#include "account.h"
class checking_account: public Account{
	double limita;
	public:
		
		checking_account(string nr, double sum, double lim);
	    void retragere(double sum);
		void afisare();
		double get_lim(){ return limita;}
	
};

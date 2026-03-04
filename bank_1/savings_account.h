  #pragma once
  #include <string>
  #include <iostream>
  #include "account.h"
 class savings_account:public Account{
 	private:
 		
 		int dobanda;
 	public:
 		savings_account(string nr, double sum) : Account(nr, sum), dobanda(0) {}
 		void adauga_dobanda();
 		void afisare();
 		int get_dobanda() {return dobanda;}
 		
 	
 };

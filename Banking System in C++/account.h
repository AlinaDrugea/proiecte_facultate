#pragma once
#include <string>
#include <iostream>
 using namespace std;
 class Account{
 	protected:
	 	double balanta ;
	 	string numar_cont;
	 	
 	public:
 		 
 		Account(string nr, double sum);
 		virtual ~Account();
 		virtual void depozitare(double sum);
 		virtual void retragere(double sum);
 		virtual void afisare();
 		double get_balanta();
 		string get_cont();
 	
 };

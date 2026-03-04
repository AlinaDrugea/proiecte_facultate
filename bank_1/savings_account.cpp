
#include <string>
#include <iostream>
#include "account.h"
#include "savings_account.h"

void savings_account:: adauga_dobanda(){
	if(balanta>30000 ) 
	{
		dobanda =balanta*2/100;
		balanta += dobanda;
	}
		
}
void savings_account:: afisare(){
	
	cout<< " Contul dumneavoastra cu numarul "<< numar_cont << " are soldul "<< balanta<< endl;
	cout<< "S-a adaugat dobanda "<<dobanda<< endl;
	
	
}

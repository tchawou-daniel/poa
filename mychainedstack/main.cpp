#include <iostream>
#include "mychainedstack.h"
using namespace std;

// Main de test simple
int main()
{
	// Banner
 	cout << "Mychainedstack - test" << endl;

	// Instanciation de la classe dérivée
	Mychainedstack _cs;

	// Reference à la baseclass (polymorphisme)
	Mystack& cs = _cs; 

    ///pop pile vide
    int pop_pil_vide = cs.pop();
    cout << "la pile vide renvoi :" << pop_pil_vide << "\n\n";
	
	// Push
    cout << "la taille 0 est "<< cs.size()<< "\n";
	cs.push(1);
    cout << "la taille 1 est "<< cs.size() << "\n";
	cs.push(2);
    cout << "la taille 2 est "<< cs.size()<<"\n";
	cs.push(3);
    cout << "la taille 3 est "<< cs.size()<<"\n";
   	//cs.push(4);
    //cout << "la taille 4 est "<< cs.size()<<"\n";


	// Pop
	int p;
	p = cs.pop();
    cout << p << endl;
	p = cs.pop();
	cout << p << endl;	
    cout << "\n\n" << "After two pop we have :" << cs.size() <<"\n";


	// Opérateur %
	int q;
	q = cs % 2;
    cout << "\n\n" << "After the operator% we have : ";
	cout << "The q value is :"<< q << "\n\n";
    
    cs.print();

    int res_operator=cs.operator%(1);
    cout << "Res operator :" << res_operator<<"\n\n";
	// Clear
	//cs.clear();


  	return 0;
}

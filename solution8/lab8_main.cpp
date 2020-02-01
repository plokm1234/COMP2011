#include <iostream>
#include "lab8.h"
using namespace std;

//global variable definition
Registry regis;

int main(){
	//initialization for regis
	regis.num=0;
	for (int i=0; i<MAX_REGISTRY_NUM; i++)
		regis.p[i] = nullptr;

	//build the family tree for Harry Potter
	cout << "-------------------------------------" << endl;
	cout<<"Build the family tree for Harry Potter!"<<endl;
	cout << "-------------------------------------" << endl << endl;

	cout << "Create grandparents:" << endl;
	createPerson("Arthur Weasley", male, Wizardkind, 68);
	createPerson("Molly Prewett", female, Wizardkind, 67);
	createPerson("James Potter", male, Wizardkind, 59);
	createPerson("Lily Evans", female, Wizardkind, 59);
	createPerson("Mr. Granger", male, Muggle, 60);
	createPerson("Mrs. Granger", female, Muggle, 58);
	// create a person that already exists
	createPerson("Mrs. Granger", female, Muggle, 58);

	cout << endl;
	getMarried("Arthur Weasley", "Molly Prewett");
	getMarried("James Potter", "Lily Evans");
	// marry a person who is already married
	getMarried("Mr. Granger", "Lily Evans");
	// marry a person who doesn't exist
	getMarried("Lord Voldemort", "Mrs. Granger");
	getMarried("Mr. Granger", "Mrs. Granger");


	cout << endl;
	cout << "Create parents:" << endl;
	createPerson("Bill Weasley", male, Wizardkind, 49);
	createPerson("Charlie Weasley", male, Wizardkind, 47);
	createPerson("Percy Weasley", male, Wizardkind, 43);
	createPerson("Fred Weasley", male, Wizardkind, 41);
	createPerson("George Weasley", male, Wizardkind, 41);
	createPerson("Ronald Weasley", male, Wizardkind, 39);
	createPerson("Ginny Weasley", female, Wizardkind, 38);
	createPerson("Hermione Granger", female, Wizardkind, 40);
	createPerson("Harry Potter", male, Wizardkind, 39);


	cout << endl;
	addKid("Arthur Weasley", "Molly Prewett", "Bill Weasley");
	addKid("Arthur Weasley", "Molly Prewett", "Charlie Weasley");
	addKid("Arthur Weasley", "Molly Prewett", "Percy Weasley");
	addKid("Arthur Weasley", "Molly Prewett", "Fred Weasley");
	addKid("Arthur Weasley", "Molly Prewett", "George Weasley");
	addKid("Arthur Weasley", "Molly Prewett", "Ronald Weasley");
	addKid("Arthur Weasley", "Molly Prewett", "Ginny Weasley");
	addKid("James Potter", "Lily Evans", "Harry Potter");
	// the kid has already been added
	addKid("James Potter", "Lily Evans", "Ronald Weasley");
	addKid("Mr. Granger", "Mrs. Granger", "Hermione Granger");

	cout << endl;
	getMarried("Ronald Weasley", "Hermione Granger");
	getMarried("Harry Potter", "Ginny Weasley");

	cout << endl;
	cout << "Create children:" << endl;
	createPerson("Rose Weasley", female, Wizardkind, 14);
	createPerson("Hugo Weasley", male, Wizardkind, 11);
	createPerson("James Potter Jr", male, Wizardkind, 14);
	createPerson("Albus Potter", male, Wizardkind, 13);
	createPerson("Lily Potter", female, Wizardkind, 11);

	cout << endl;
	addKid("Ronald Weasley", "Hermione Granger", "Rose Weasley");
	addKid("Ronald Weasley", "Hermione Granger", "Hugo Weasley");
	addKid("Harry Potter", "Ginny Weasley", "James Potter Jr");
	addKid("Harry Potter", "Ginny Weasley", "Albus Potter");
	addKid("Harry Potter", "Ginny Weasley", "Lily Potter");


	cout << endl <<"-----------" << endl;
	cout<<"Start tesing"<<endl;
	cout << "----------" << endl << endl;

	cout<<"Print the Lily Potter's parents."<<endl;
	printParents("Lily Potter");

	cout<<endl;
	cout << "Print all kids of Arthur Weasley." << endl;
	printKids("Arthur Weasley");

	cout<<endl;
	cout << "Optional task:" << endl;
	cout << endl;
	printGrandParents("Lily Potter");

	cout << "Print all descendents of Arthur Weasley." << endl;
	printAllDescendents(searchPerson("Arthur Weasley"));


	// free dynamically allocated memory
	cout <<"-----------" << endl;
	cout<<"Clean memory"<<endl;
	cout << "----------" << endl << endl;
	for (int i = 0; i < regis.num; i++)
		delete regis.p[i];  //to delete each Person struct pointed by the array.

}

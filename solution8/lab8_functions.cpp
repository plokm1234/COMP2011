#include <iostream>
#include <cstring>
#include "lab8.h"
using namespace std;

// global variable declaration
extern Registry regis;

// helper function for internal usage
Person* searchPerson(const char name[MAX_NAME_LENGTH]) {
	for (int i = 0; i < regis.num; i++)
		if (strncmp(regis.p[i]->name, name, MAX_NAME_LENGTH) == 0)
			return regis.p[i];
	return nullptr;
}

void printPerson(const Person* p, int tab){
	for (int i = 0; i < tab; i++)
		cout << '\t';
	if (p == nullptr){
		cout << "Error:"  << "No such person!" << endl;
		return;
	}

	cout << "Name: " << p->name
			<< ", Sex: " << ((p->sex == male)? "Male" : "Female")
			<< ", Identity: " << ((p->identity == Wizardkind)? "Wizardkind" : "Muggle")
			<< ", Age: " << p->age << endl;
}

// Task 1
// create a new Person object and add him/her to registry
// relationship pointers (e.g. father, mother, spouse, all kids) are nullptr
// return pointer to the person
// Fail to create if registry is full, or the person with same name already in registry
// return nullptr in this case
Person* createPerson(const char name[MAX_NAME_LENGTH], const SEX sex, const IDENTITY identity, int age) {
	if (regis.num >= MAX_REGISTRY_NUM){
		cout << "Error:"  << "Registry is full already! Can't create a new person." << endl;
		return nullptr;
	}
	if (searchPerson(name)){
		cout << "Error: "  << name << "already exist in the registry." << endl;
		return nullptr;
	}

	Person* newPerson = new Person;
	strncpy(newPerson->name,  name, MAX_NAME_LENGTH);
	newPerson->age = age;
	newPerson->sex = sex;
	newPerson->identity = identity;
	newPerson->father = nullptr;
	newPerson->mother = nullptr;
	newPerson->spouse = nullptr;
	for (int i = 0; i < MAX_KID_NUM; i++)
		newPerson->kid[i] = nullptr;
	regis.p[regis.num++] = newPerson;

	cout << name << " is created and added to registry." << endl;
	return newPerson;
}
// Task 2
// setup spouse pointer for both husband and wife
// bigamy is not allowed
// can't marry to a person who doesn't exist in registry
bool getMarried(const char male[MAX_NAME_LENGTH],
		const char female[MAX_NAME_LENGTH]) {
	Person* groom = searchPerson(male);
	Person* bride = searchPerson(female);
	if (groom == nullptr){
		cout << "Error: "  << "Groom does not exist in registry!" << endl;
		return false;
	}
	if (bride == nullptr){
		cout << "Error: "  << "Bride does not exist in registry!" << endl;
		return false;
	}

	bool bigamy = false;
	if (groom->spouse != nullptr) {
		cout << "Error: "  << "The groom is married!" << endl;
		bigamy = true;
	}
	if (bride->spouse != nullptr) {
		cout << "Error: "  << "The bride is married!" << endl;
		bigamy = true;
	}
	if (bigamy) //same-sex marriage is not checked
		return false;

	groom->spouse = bride;
	bride->spouse = groom;
	cout << "Congratulations, " << male << " and " << female
			<< " are married." << endl;
	return true;
}

// Task 3
// setup pointer(s) in kid[] for both mother and father
// setup mother/father pointer for the kid
// can't add the kid if he/she already added or the kid array is full
// Assumption for simplicity:
// father/mother/kid already exist in registry
// No single parent
// No divorce (that is, kid array for a couple should be the same
bool addKid(const char father_name[MAX_NAME_LENGTH],
		const char mother_name[MAX_NAME_LENGTH],
		const char kid_name[MAX_NAME_LENGTH]) {
	Person* kid = searchPerson(kid_name);
	Person* father = searchPerson(father_name);
	Person* mother = searchPerson(mother_name);

	if (kid->mother != nullptr || kid->father != nullptr) {
		cout << "Error: "  << "Kid " << kid_name << "is already added!" << endl;
		return false;
	}

	int i;
	for (i=0; i<MAX_KID_NUM; i++){
		if (father->kid[i] == nullptr)
			break;
	}
	if (i == MAX_KID_NUM) {
		cout << "Error: "  << father_name << " has too many children!" << endl;
		return false;
	}

	father->kid[i] = kid;
	mother->kid[i] = kid;
	kid->mother = mother;
	kid->father = father;
	cout << "Successfully add kid " << kid_name << " to parents " << father_name << " and " << mother_name  << "."<< endl;
	return true;
}

// Task 4
// print information of all kids
void printKids(const char name[MAX_NAME_LENGTH]){
	Person* p = searchPerson(name);
	if (p == nullptr) {
		cout << "Error: "  << "Can't find " << name << "in registry, fail to print!" << endl;
		return;
	}
	cout << "Kids of " << p->name << ":"<< endl;
	for (int i=0; i<MAX_KID_NUM; i++){
		if (p->kid[i] == nullptr)
			break;
		else
			printPerson(p->kid[i]);
	}
}

// Task 5
// print information of parents
void printParents(const char name[MAX_NAME_LENGTH]) {
	Person* p = searchPerson(name);
	if (p == nullptr) {
		cout << "Error: "  << "Can't find " << name << "in registry, fail to print!" << endl;
		return;
	}
	cout << "Parents of " << p->name << ":"<< endl;
	cout << "Mother: " << endl;
	printPerson(p->mother);
	cout << "Father: " << endl;
	printPerson(p->father);
}

// Optional
// print information of grandparents
void printGrandParents(const char name[MAX_NAME_LENGTH]) {
	Person* p = searchPerson(name);
	if (p == nullptr) {
		cout << "Error: "  << "Can't find " << name << "in registry, fail to print!" << endl;
		return;
	}
	cout << "Grandparents of " << p->name << ":"<< endl;
	if (p->mother != nullptr){
		cout  << "Maternal grandfather: " << endl;
		printPerson(p->mother->father);
		cout  << "Maternal grandmother: " << endl;
		printPerson(p->mother->mother);
	}
	else{
		cout << "Maternal grandparents: no record!" << endl;
	}
	if (p->father != nullptr){
		cout  << "Paternal grandfather: " << endl;
		printPerson(p->father->father);

		cout  << "Paternal grandmother: " << endl;
		printPerson(p->father->mother);
	}
	else{
		cout << "Paternal grandparents: no record!" << endl;
	}
}

// Optional
// print information of all descendents
// hint recursion
void printAllDescendents(const Person* p, int level) {
	if (p == nullptr && level == 0) {
		cout << "Error: "  << "Can't find in registry, fail to print!" << endl;
	}
	if (p == nullptr) {
		return;
	}
	for (int i=0; i<level; i++)
		cout << '\t';
	printPerson(p, level);
	for (int i = 0; i < MAX_KID_NUM; i++){
		if (p->kid[i] != nullptr)
			printAllDescendents(p->kid[i], level + 1);
	}
}

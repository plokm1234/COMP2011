// global constant
const int MAX_NAME_LENGTH = 30;
const int MAX_REGISTRY_NUM = 100;
const int MAX_KID_NUM = 10;

// user-defined data types
enum SEX{male, female};
enum IDENTITY{Wizardkind, Muggle};

struct Person {
	SEX sex;
	IDENTITY identity;
	char name[MAX_NAME_LENGTH];
	int age;
	Person* spouse;  // nullptr if single
	Person* mother;
	Person* father;
	Person* kid[MAX_KID_NUM]; // nullptr if no kid
};

//collection of all persons in family tree
struct Registry{
	int num;
	Person* p[MAX_REGISTRY_NUM];
};

// function declaration

// helper function, internal usage
// search a person with given name in registry, and return its pointer.
Person* searchPerson(const char name[MAX_NAME_LENGTH]);
// print full information of a person
void printPerson(const Person* p, int tab = 0);

// create a Person object, add him/her to registry
Person* createPerson(const char name[MAX_NAME_LENGTH], const SEX sex, const IDENTITY identity, int age);
// setup spouse pointer for both husband and wife
bool getMarried(const char male[MAX_NAME_LENGTH], const char female[MAX_NAME_LENGTH]);
// setup parent/kid pointers
bool addKid(const char father_name[MAX_NAME_LENGTH],
		const char mother_name[MAX_NAME_LENGTH],
		const char kid_name[MAX_NAME_LENGTH]);
// print info of parents/kids/grandparents
void printParents(const char name[MAX_NAME_LENGTH]);
void printKids(const char name[MAX_NAME_LENGTH]);
void printGrandParents(const char name[MAX_NAME_LENGTH]);
//print info of all descendants
//hint: recursion
void printAllDescendents(const Person* p, int level=0);

#include <cmath>
#include <ctime>
#include <iostream>
#include <climits>
#include <cstdlib>

#include "lab6.h"

using namespace std;

// Utility functions
int euclidean_distance(const Point& p1, const Point& p2) {
	float x_diff = p1.x - p2.x;
	float y_diff = p1.y - p2.y;

	return ceil(sqrt(x_diff * x_diff + y_diff * y_diff));
}

void print_location(const Point& location) {
	cout << "Location: (" << location.x << ", " << location.y << ")" << endl;
}

/* functions for fuel */

void init_fuelprice(int fuelprice[][NUM_FUEL_TYPES]) {
	// i=0 Caltex; i=1 Esso; i=2 Sinopec; i=3 Shell
	// j=0 Premium; j=1 Regular; j=2 Diesel
	for (int i = 0; i < NUM_OF_BRANDS; i++)
		for (int j = 0; j < NUM_FUEL_TYPES; j++)
            switch (j) {
                case Premium:
                    fuelprice[i][j] = 19 + (rand() % 5 - 2);
                    break;
                case Regular:
                    fuelprice[i][j] = 18 + (rand() % 5 - 2);
                    break;
                case Diesel:
                    fuelprice[i][j] = 14 + (rand() % 5 - 2);
                    break;
            }
}


void print_fuelprices(const int fuelprice[][NUM_FUEL_TYPES]) {
    cout << endl;
	cout << "===================" << endl;
	cout << "Today's fuel prices" << endl;
	cout << "===================" << endl;
	for (int i = 0; i < NUM_OF_BRANDS; i++) {
		cout << brandname[static_cast<Brand>(i)];
        cout << endl;
        
		for (int j = 0; j < NUM_FUEL_TYPES; j++) {
            cout << '\t';
			cout << fueltype[static_cast<FuelType>(j)];
			cout << ": " << fuelprice[i][j] << endl;
		}
	}
}

/* functions for gas stations */

// FUNCTION 1
/**
   TODO: Initialize an array of GasStations.
   Each gas station is initialized with random brand, and a random location in 2D area.
 **/

void init_gas_stations(GasStation stations[], int num_of_stations) {

for(int i=0;i<NUM_OF_STATIONS;i++){
	stations[i].brand=Brand(rand()%NUM_OF_BRANDS);
	stations[i].location.x=rand()%(X_RANGE+1);
	stations[i].location.y=rand()%(Y_RANGE+1);	
}
}

// FUNCTION 2
/**
   TODO: print brand and location information of a given gas station.
   Feel free to decide the output formats as long as it is readable.
 **/
void print_a_gas_station(const GasStation& gs) {
	cout.width(13);cout<<" Brand: ";
	cout.width(22);cout<<brandname[gs.brand];
	cout.width(20);print_location(gs.location);

}

// FUNCTION 3
/**
   TODO: print brand and location information of all gas stations.
   Feel free to decide the output formats as long as it is readable.
 **/
void print_gas_stations(const GasStation stations[], int num_of_stations) {

	cout<<endl<<"============"<<endl<<"Gas Stations"<<endl<<"============"<<endl;
for(int i =0;i<NUM_OF_STATIONS;i++){
	cout<<"#"<<i<<" Brand: ";
	cout.width(10);cout<<left<<brandname[stations[i].brand];
	cout.width(10);print_location(stations[i].location);
}
}


/* functions for car */

// FUNCTION 4
/**
   TODO: Initialize a car.
   The car is initialized with random location in 2D area.
   Its tank capacity is FULL_TANK.
   Its remain fuel is a random number in [0, FULL_TANK - 1].
   It uses a random kind of fuel.
 **/
void init_car(Car& car) {

car.fueltype=FuelType(rand()%NUM_FUEL_TYPES);
car.location.x=rand()%(X_RANGE+1);
car.location.y=rand()%(Y_RANGE+1);
car.remainfuel=rand()%FULL_TANK;
car.tankcapacity=FULL_TANK;

}

// FUNCTION 5
/**
   TODO: Print car information, i.e. location, tank capacity, type of fuel used, remaining fuel.
   Feel free to decide the output formats as long as it is readable.
 **/
void print_car(const Car& car) {

cout<<endl<<"========"<<endl<<"Lab6 Car"<<endl<<"========"<<endl;
print_location(car.location);
cout.width(13);cout<<left<<"Fuel: ";
cout.width(10);cout<<fueltype[car.fueltype];
cout<<endl;
cout.width(13);cout<<left<<"Tank capacity: ";
cout.width(3);cout<<car.tankcapacity<<endl;
cout.width(13);cout<<left<<"Remain fuel: ";
cout.width(5);cout<<car.remainfuel<<endl;
}

// FUNCTION 6
/**
   TODO: Find all gas stations that the car can reach with gasoline left in the tank.
   For example, if the car has 20 litres of gasoline left,
   assuming gasoline consumption is GAS_PER_KM (which is 1) litre per km,
   the car can only reach gas stations within distance 20.
   The car will consume more gasoline when drive towards the gas station.
   When the car reaches the gas station, it will add gasoline to full tank.

   For each gas station reachable, print its distance to the car location, gasoline to be added, and total gasoline cost
   Feel free to decide the output formats as long as it is readable.

   The function should return the index of gas station, with minimum gasoline cost.
   If the car can't reach any gas station, return -1.
 **/

int choose_station(const GasStation stations[], int num_of_stations,
		const int fuelprice[][NUM_FUEL_TYPES], const Car& car) {
cout<<endl<<"==========================="<<endl<<"Gas stations can be reached"<<endl<<"==========================="<<endl;
int a[NUM_OF_STATIONS]={};
for(int i=0;i<NUM_OF_STATIONS;i++){

if(car.remainfuel>=euclidean_distance(stations[i].location,car.location)*GAS_PER_KM)
{
	cout.width(5);cout<<right;cout<<"#"<<i;
	cout.width(15);cout<<" Brand: ";
	cout.width(22);cout<<right;cout<<brandname[stations[i].brand];
	cout.width(20);print_location(stations[i].location);

	cout<<"dist: ";cout.width(7);cout<<left<<euclidean_distance(stations[i].location,car.location);

	cout.width(7);cout<<right;cout<<"gas to add: "<<car.tankcapacity-car.remainfuel+GAS_PER_KM*euclidean_distance(stations[i].location,car.location)<<"L";

	cout.width(14);cout<<"price:"<<fuelprice[stations[i].brand][car.fueltype];

	cout.width(16);cout<<"total: "<<fuelprice[stations[i].brand][car.fueltype]*(car.tankcapacity-car.remainfuel+GAS_PER_KM*euclidean_distance(stations[i].location,car.location))<<endl<<endl;

a[i]=fuelprice[stations[i].brand][car.fueltype]*(car.tankcapacity-car.remainfuel+GAS_PER_KM*euclidean_distance(stations[i].location,car.location));
}

}
int index=12;
int min;
for(int i=0;i<NUM_OF_STATIONS;i++){if(a[i]>0){min=a[i];index=i;break;}}
//cout<<min<<","<<index;
for(int i=0;i<NUM_OF_STATIONS;i++){if(a[i]>0 && a[i]<min){min=a[i];index=i;}}

if(index!=12){return index;}

/*cout<<a[0]<<"|"<<a[1]<<"|"<<a[2]<<"|"<<a[3]<<"|"<<a[4]<<"|"<<a[5]<<"|"<<a[6]<<"|"<<a[7]<<"|"<<a[8]<<"|"<<a[9];*/
return -1;

}

/* Driver program to test all functions */
int main() {
	srand(time(0));

	// set imaginary fuel prices
	int fuelprice[NUM_OF_BRANDS][NUM_FUEL_TYPES];
	init_fuelprice(fuelprice);
	print_fuelprices(fuelprice);

	// create gas stations at random locations

	GasStation stations[NUM_OF_STATIONS];
	init_gas_stations(stations, NUM_OF_STATIONS);
	print_gas_stations(stations, NUM_OF_STATIONS);

	// car information
	Car lab6car;
	init_car(lab6car);
	print_car(lab6car);

	// choose gas station
	int idx = choose_station(stations, NUM_OF_STATIONS, fuelprice, lab6car);
	if (idx == -1) {
		cout << "No feasible solution" << endl;
	}
	else {
		cout << endl << "Best choice:" << endl;
		cout << "#" << idx << '\t';
		print_a_gas_station(stations[idx]);
	}
}
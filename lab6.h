/* Global constant */
const int NUM_OF_BRANDS = 4; // Fuel companies
const int NUM_FUEL_TYPES = 3; // Fuel types
const int NUM_OF_STATIONS = 10; // Number of gas stations
const int GAS_PER_KM = 1; // Gasoline consumption: 1 litre per km

const int X_RANGE = 50; // 2D area size
const int Y_RANGE = 50;

const int FULL_TANK = 40; // Fuel tank capacity

/* enum */
enum FuelType {Premium, Regular, Diesel};
enum Brand {Caltex, Sinopec, Esso, Shell}; //updated

/* for printing */
const char brandname[][10] = { "Caltex", "Sinopec", "Esso", "Shell"};
const char fueltype[][10] = { "Premium", "Regular", "Diesel"};

/* user-defined struct */
struct Point { //for simplicity, integer coordinates are used
	int x;
	int y;
};

struct Car {
	FuelType fueltype;
	int tankcapacity;
	int remainfuel;
	Point location;
};

struct GasStation {
	Brand brand;
	Point location;
};
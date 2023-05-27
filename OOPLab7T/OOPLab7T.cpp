// OOPLab7T.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <clocale>

int main()
{
    setlocale(LC_CTYPE, "ukr");
    std::cout << "Лабораторна робота №7  \n";
    std::cout << "Автоматизована система ...  \n";
    
    #include <string>
#include <vector>
#include <iostream>

// Forward declarations of the Car and Trip classes
class Car;
class Trip;

class Driver {
public:
    std::string name;
    bool is_available = true; // initialize is_available to true
    bool is_on_duty = false; // initialize is_on_duty to false
    bool needs_repair;
    std::string car_type;
    int num_completed_trips;
    int num_uncompleted_trips;
    int num_trips_since_last_repair;

    // constructor
    Driver() : is_available(false), needs_repair(false), num_completed_trips(0),
        num_uncompleted_trips(0), num_trips_since_last_repair(0) {}

    void requestRepair();
    // ... other properties and methods as needed
};


class Car {
public:
    std::string car_type; // type of the car
    std::string license_plate; // license plate of the car
    bool is_available; // indicates if the car is available for use
    bool needs_repair; // indicates if the car needs repair
    std::string checkCondition(); // added return type
    // ... other properties and methods as needed
    std::string condition; // added member variable
};

class Trip {
public:
    std::string origin;
    std::string destination;
    Driver driver;
    Car car;
    bool is_completed; // indicates if the trip is completed
    // ... other properties and methods as needed
};

class Dispatch {
public:
    std::vector<Driver> drivers;
    std::vector<Car> cars;
    std::vector<Trip> trips;

    void assignTrip(Trip trip);
    void suspendDriver(Driver driver);
    void addDriver(Driver driver);
    void addCar(Car car);
    void removeDriver(Driver driver);
    void removeCar(Car car);
    void printAllTrips();
    // ... other properties and methods as needed
};

void Dispatch::assignTrip(Trip trip) {
    // find an available driver and car that can complete the trip
    for (Driver& driver : drivers) {
        if (driver.is_available && driver.car_type == trip.car.car_type && !driver.needs_repair) {
            for (Car& car : cars) {
                if (car.is_available && car.car_type == trip.car.car_type && !car.needs_repair) {
                    // assign the trip to the driver and car
                    driver.is_available = false;
                    driver.is_on_duty = true;
                    car.is_available = false;
                    trip.driver = driver;
                    trip.car = car;
                    trips.push_back(trip);
                    return;
                }
            }
        }
    }
}

void Driver::requestRepair() {
    needs_repair = true;
    num_trips_since_last_repair = 0;
}

void Dispatch::suspendDriver(Driver driver) {
    // find the driver and mark them as unavailable and off duty
    for (Driver& d : drivers) {
        if (d.name == driver.name) {
            d.is_available = false;
            d.is_on_duty = false;
            return;
        }
    }
}

void Dispatch::addDriver(Driver driver) {
    drivers.push_back(driver);
}

void Dispatch::addCar(Car car) {
    cars.push_back(car);
}

void Dispatch::removeDriver(Driver driver) {
    for (int i = 0; i < drivers.size(); i++) {
        if (drivers[i].name == driver.name) {
            drivers.erase(drivers.begin() + i);
            return;
        }
    }
}

void Dispatch::removeCar(Car car) {
    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].license_plate == car.license_plate) {
            cars.erase(cars.begin() + i);
            return;
        }
    }
}

void Dispatch::printAllTrips() {
    std::cout << "All Trips:" << std::endl;
    for (const Trip& trip : trips) {
        std::cout << "Driver: " << trip.driver.name << ", Car: " << trip.car.license_plate
            << ", From: " << trip.origin << ", To: " << trip.destination
            << ", Completed: " << (trip.is_completed ? "Yes" : "No") << std::endl;
    }
}

int main() {
    Dispatch dispatch;

    // create drivers
    Driver john;
    john.name = "John";
    john.is_available = true;
    john.is_on_duty = false;
    john.needs_repair = false;
    john.car_type = "Sedan";
    john.num_completed_trips = 0;
    john.num_uncompleted_trips = 0;
    john.num_trips_since_last_repair = 0;

    Driver mary;
    mary.name = "Mary";
    mary.is_available = true;
    mary.is_on_duty = false;
    mary.needs_repair = false;
    mary.car_type = "SUV";
    mary.num_completed_trips = 0;
    mary.num_uncompleted_trips = 0;
    mary.num_trips_since_last_repair = 0;

    // create cars
    Car sedan1;
    sedan1.car_type = "Sedan";
    sedan1.license_plate = "ABC123";
    sedan1.is_available = true;
    sedan1.needs_repair = false;
    sedan1.condition = "Good";

    Car suv1;
    suv1.car_type = "SUV";
    suv1.license_plate = "XYZ789";
    suv1.is_available = true;
    suv1.needs_repair = false;
    suv1.condition = "Excellent";

    // add drivers and cars to dispatch
    dispatch.addDriver(john);
    dispatch.addDriver(mary);
    dispatch.addCar(sedan1);
    dispatch.addCar(suv1);

    // create trips
    Trip trip1;
    trip1.origin = "Home";
    trip1.destination = "Airport";
    trip1.is_completed = false;
    trip1.driver = john;
    trip1.car = sedan1;

    Trip trip2;
    trip2.origin = "Office";
    trip2.destination = "Restaurant";
    trip2.is_completed = true;
    trip2.driver = mary;
    trip2.car = suv1;

    // assign the trips
    dispatch.assignTrip(trip1);
    dispatch.assignTrip(trip2);

    // print all trips
    dispatch.printAllTrips();

    // create a new trip with different values
    Trip trip3;
    trip3.origin = "City Center";
    trip3.destination = "Museum";
    trip3.is_completed = false;

    Driver alex;
    alex.name = "Alex";
    alex.is_available = true;
    alex.is_on_duty = false;
    alex.needs_repair = false;
    alex.car_type = "Sedan";
    alex.num_completed_trips = 0;
    alex.num_uncompleted_trips = 0;
    alex.num_trips_since_last_repair = 0;

    Car sedan2;
    sedan2.car_type = "Sedan";
    sedan2.license_plate = "DEF456";
    sedan2.is_available = true;
    sedan2.needs_repair = false;
    sedan2.condition = "Good";

    trip3.driver = alex;
    trip3.car = sedan2;

    // assign the trip
    dispatch.assignTrip(trip3);

    // print all trips
    dispatch.printAllTrips();

    // remove a driver and a car
    dispatch.removeDriver(john);
    dispatch.removeCar(sedan1);

    // print all trips after removal
    dispatch.printAllTrips();

    return 0;
}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

#include <string>

class Vehicle {
  public:
    std::string regNumber;
    Vehicle(std::string regNumber);
};

class ParkingSpace {
  public:
    Vehicle* occupant;
    ParkingSpace();
    void recordEntry(Vehicle* vehicle);
    void recordExit();
};

class CarPark {
  public:
    std::string name;
    int capacity;
    CarPark(int capacity, std::string name);
    int getVacancies();
    ParkingSpace* getParkingSpace(int id);
  private:
    ParkingSpace* spaces;
};
#include <string>
#include <exception> 

class Vehicle {
  public:
    std::string regNumber;
    Vehicle(std::string regNumber);
};

class ParkingSpace {
  public:
    Vehicle* occupant;
    ParkingSpace();
};

class AlreadyOccupiedException : public std::exception {
  public:
    Vehicle* vehicle;
    std::string carParkName;
    int spaceId;
    AlreadyOccupiedException(std::string carParkName, int spaceId, Vehicle* vehicle);
    const char* what() const throw() override;
};

class CarPark {
  public:
    std::string name;
    int capacity;
    CarPark(int capacity, std::string name);
    int getVacancies();
    bool isVacant(int spaceId);
    Vehicle* getOccupant(int spaceId);
    void park(Vehicle* vehicle, int spaceId);
    void unpark(int spaceId);
  private:
    ParkingSpace* spaces;
};
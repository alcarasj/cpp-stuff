#include <parking.h>
#include <string>

Vehicle::Vehicle(std::string regNumber) {
  this->regNumber = regNumber;
}

ParkingSpace::ParkingSpace() {
  this->occupant = nullptr;
}

AlreadyOccupiedException::AlreadyOccupiedException(std::string carParkName, int space, Vehicle* vehicle) {
  this->carParkName = carParkName;
  this->spaceId = spaceId;
  this->vehicle = vehicle;
}

const char* AlreadyOccupiedException::what() const throw() {
  return std::string("Vehicle with reg number " + this->vehicle->regNumber + " tried to park at space " + std::to_string(this->spaceId) + " in \"" + this->carParkName + "\" car park but it is occupied!").c_str();
}

CarPark::CarPark(int capacity, std::string name) {
  this->name = name;
  this->capacity = capacity;
  this->spaces = new ParkingSpace[capacity];
}

int CarPark::getVacancies() {
  int result = 0;
  for (int i = 0; i < this->capacity; i++) {
    if (this->spaces[i].occupant == nullptr) {
      result++;
    }
  }
  return result;
}

bool CarPark::isVacant(int spaceId) {
  return this->getOccupant(spaceId) == nullptr;
}

Vehicle* CarPark::getOccupant(int spaceId) {
  return this->spaces[spaceId].occupant;
}
    
void CarPark::park(Vehicle* vehicle, int spaceId) {
  if (this->spaces[spaceId].occupant != nullptr) {
    throw AlreadyOccupiedException(this->name, spaceId, vehicle);
  }
  this->spaces[spaceId].occupant = vehicle;
}

void CarPark::unpark(int spaceId) {
  Vehicle* vehiclePtr = this->spaces[spaceId].occupant;
  delete vehiclePtr;
  this->spaces[spaceId].occupant = nullptr;
}
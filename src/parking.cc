#include <parking.h>
#include <string>

Vehicle::Vehicle(std::string regNumber) {
  this->regNumber = regNumber;
}

ParkingSpace::ParkingSpace() {
  this->occupant = nullptr;
}

AlreadyOccupiedException::AlreadyOccupiedException() {}

const char* AlreadyOccupiedException::what() const throw() {
  return "This space is already occupied!";
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
  this->spaces[spaceId].occupant = vehicle;
}

void CarPark::unpark(int spaceId) {
  Vehicle* vehiclePtr = this->spaces[spaceId].occupant;
  delete vehiclePtr;
  this->spaces[spaceId].occupant = nullptr;
}
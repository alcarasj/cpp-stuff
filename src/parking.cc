#include <parking.h>
#include <string>

Vehicle::Vehicle(std::string regNumber) {
  this->regNumber = regNumber;
}

ParkingSpace::ParkingSpace() {
  this->occupant = nullptr;
}

void ParkingSpace::recordEntry(Vehicle* vehicle) {
  this->occupant = vehicle;
}

void ParkingSpace::recordExit() {
  this->occupant = nullptr;
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
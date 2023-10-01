#include <gtest/gtest.h>
#include <parking.h>
#include <string>

TEST(ParkingTest, TestOneCarEntryAndExit) {
  const int testCapacity = 250;
  const std::string testName("Test Car Park");
  CarPark testCarPark(testCapacity, testName);

  EXPECT_EQ(testName, testCarPark.name);
  EXPECT_EQ(testCapacity, testCarPark.capacity);
  EXPECT_EQ(testCapacity, testCarPark.getVacancies());

  const std::string testRegNum("09-D-12345");
  Vehicle* testCar = new Vehicle(testRegNum);
  const int testSpaceId = std::rand() % testCarPark.capacity;
  ParkingSpace* spacePtr = testCarPark.getParkingSpace(testSpaceId);
  spacePtr->recordEntry(testCar);

  EXPECT_EQ(testRegNum, testCarPark.getParkingSpace(testSpaceId)->occupant->regNumber);
  EXPECT_EQ(testRegNum, testCarPark.getParkingSpace(testSpaceId)->occupant->regNumber);
  EXPECT_EQ(testCapacity - 1, testCarPark.getVacancies());
  
  spacePtr = testCarPark.getParkingSpace(testSpaceId);
  spacePtr->recordExit();

  EXPECT_EQ(nullptr, testCarPark.getParkingSpace(testSpaceId)->occupant);
  EXPECT_EQ(testCapacity, testCarPark.getVacancies());
}
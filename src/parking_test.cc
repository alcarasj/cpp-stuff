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
  EXPECT_TRUE(testCarPark.isVacant(testSpaceId));
  EXPECT_EQ(nullptr, testCarPark.getOccupant(testSpaceId));

  testCarPark.park(testCar, testSpaceId);

  EXPECT_FALSE(testCarPark.isVacant(testSpaceId));
  EXPECT_EQ(testRegNum, testCarPark.getOccupant(testSpaceId)->regNumber);
  EXPECT_EQ(testCapacity - 1, testCarPark.getVacancies());
  
  testCarPark.unpark(testSpaceId);

  EXPECT_EQ(nullptr, testCarPark.getOccupant(testSpaceId));
  EXPECT_EQ(testCapacity, testCarPark.getVacancies());
}
#include <gtest/gtest.h>
#include <parking.h>
#include <string>

TEST(ParkingTest, TestOneCarEntryAndExit) {
  const int testCapacity = 250;
  const std::string testName("Test Car Park");
  CarPark testCarPark(testCapacity, testName);

  // Assert that the newly-created CarPark has the correct attributes.
  ASSERT_EQ(testName, testCarPark.name);
  ASSERT_EQ(testCapacity, testCarPark.capacity);
  ASSERT_EQ(testCapacity, testCarPark.getVacancies());

  // Create a Vehicle, and park and unpark at some random valid ParkingSpace.
  const std::string testRegNum("09-D-12345");
  Vehicle* testCar = new Vehicle(testRegNum);
  const int testSpaceId = std::rand() % testCarPark.capacity;
  ASSERT_TRUE(testCarPark.isVacant(testSpaceId));
  ASSERT_EQ(nullptr, testCarPark.getOccupant(testSpaceId));

  testCarPark.park(testCar, testSpaceId);

  ASSERT_FALSE(testCarPark.isVacant(testSpaceId));
  ASSERT_EQ(testRegNum, testCarPark.getOccupant(testSpaceId)->regNumber);
  ASSERT_EQ(testCapacity - 1, testCarPark.getVacancies());
  
  testCarPark.unpark(testSpaceId);

  ASSERT_EQ(nullptr, testCarPark.getOccupant(testSpaceId));
  ASSERT_EQ(testCapacity, testCarPark.getVacancies());
}

TEST(ParkingTest, TestOccupiedParkingSpace) {
  const int testCapacity = 1;
  const std::string testName("Test Occupied Parking Space");
  CarPark testCarPark(testCapacity, testName);

  // Assert that the newly-created CarPark has the correct attributes.
  ASSERT_EQ(testName, testCarPark.name);
  ASSERT_EQ(testCapacity, testCarPark.capacity);
  ASSERT_EQ(testCapacity, testCarPark.getVacancies());

  // Create a Vehicle, and park and unpark at some random valid ParkingSpace.
  const std::string testRegNum("00-WD-54321");
  Vehicle* testCar = new Vehicle(testRegNum);
  const int testSpaceId = std::rand() % testCarPark.capacity;
  ASSERT_TRUE(testCarPark.isVacant(testSpaceId));
  ASSERT_EQ(nullptr, testCarPark.getOccupant(testSpaceId));

  testCarPark.park(testCar, testSpaceId);

  ASSERT_FALSE(testCarPark.isVacant(testSpaceId));
  ASSERT_EQ(testRegNum, testCarPark.getOccupant(testSpaceId)->regNumber);
  ASSERT_EQ(0, testCarPark.getVacancies());

  // Should throw error if another car tries to park at an occupied space.
  const std::string anotherTestRegNum("96-D-420");
  Vehicle* anotherTestCar = new Vehicle(anotherTestRegNum);
  ASSERT_THROW(testCarPark.park(testCar, testSpaceId), AlreadyOccupiedException);

  // The first vehicle should still remain there.
  ASSERT_FALSE(testCarPark.isVacant(testSpaceId));
  ASSERT_EQ(testRegNum, testCarPark.getOccupant(testSpaceId)->regNumber);
  ASSERT_EQ(0, testCarPark.getVacancies());
}
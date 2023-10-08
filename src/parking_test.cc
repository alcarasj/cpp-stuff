#include <gtest/gtest.h>
#include <parking.h>
#include <string>
#include <thread>

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

  // Ensure that the space is vacant.
  const int testSpaceId = std::rand() % testCarPark.capacity;
  ASSERT_TRUE(testCarPark.isVacant(testSpaceId));
  ASSERT_EQ(nullptr, testCarPark.getOccupant(testSpaceId));

  // Create a Vehicle, then park and unpark.
  const std::string testRegNum("00-WD-54321");
  Vehicle* testCar = new Vehicle(testRegNum);

  testCarPark.park(testCar, testSpaceId);

  ASSERT_FALSE(testCarPark.isVacant(testSpaceId));
  ASSERT_EQ(testRegNum, testCarPark.getOccupant(testSpaceId)->regNumber);
  ASSERT_EQ(0, testCarPark.getVacancies());

  // Should throw error if another car tries to park at an occupied space.
  const std::string anotherTestRegNum("96-D-420");
  Vehicle* anotherTestCar = new Vehicle(anotherTestRegNum);
  ASSERT_THROW(testCarPark.park(anotherTestCar, testSpaceId), AlreadyOccupiedException);

  // The first vehicle should still remain there.
  ASSERT_FALSE(testCarPark.isVacant(testSpaceId));
  ASSERT_EQ(testRegNum, testCarPark.getOccupant(testSpaceId)->regNumber);
  ASSERT_EQ(0, testCarPark.getVacancies());
}

TEST(ParkingTest, TestMultipleCarsRaceForOneParkingSpace) {
  const int testCapacity = 1;
  const std::string testName("Test Multiple Cars Race For One Parking Space");
  CarPark testCarPark(testCapacity, testName);

  // Assert that the newly-created CarPark has the correct attributes.
  ASSERT_EQ(testName, testCarPark.name);
  ASSERT_EQ(testCapacity, testCarPark.capacity);
  ASSERT_EQ(testCapacity, testCarPark.getVacancies());

  // Ensure that the space is vacant.
  const int testSpaceId = std::rand() % testCarPark.capacity;
  ASSERT_TRUE(testCarPark.isVacant(testSpaceId));
  ASSERT_EQ(nullptr, testCarPark.getOccupant(testSpaceId));

  // Create 500 threads that each create a Vehicle that attempts to park at the parking space.
  // One vehicle should be able park, the rest should be unable to park and throw exception.
  const int numberOfThreads = 500;
  int exceptionsThrown = 0;
  std::vector<std::thread> threads;
  for (int i = 0; i < numberOfThreads; i++) {
    auto vehicleThread = [](CarPark* carPark, int spaceId, std::string vehicleRegNumber, int* exceptionsThrownPtr) {
      Vehicle* testCar = new Vehicle(vehicleRegNumber);
      try {
        carPark->park(testCar, spaceId);
      } catch (const AlreadyOccupiedException& e) {
        (*exceptionsThrownPtr)++;
      }
    };
    std::string testRegNum("99-C-63" + std::to_string(i));
    threads.push_back(std::thread(vehicleThread, &testCarPark, testSpaceId, testRegNum, &exceptionsThrown));
  }

  for (auto &thread : threads) {
    thread.join();
  }

  ASSERT_EQ(numberOfThreads - 1, exceptionsThrown);
  ASSERT_FALSE(testCarPark.isVacant(testSpaceId));
  ASSERT_NE(nullptr, testCarPark.getOccupant(testSpaceId));
  ASSERT_EQ(0, testCarPark.getVacancies());
  ASSERT_EQ("99-C-63", testCarPark.getOccupant(testSpaceId)->regNumber.substr(0, 7));
}
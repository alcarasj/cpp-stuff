#include <gtest/gtest.h>
#include <parking.h>
#include <string>

TEST(ParkingTest, TestFullFlow) {
  const int testCapacity = 250;
  const std::string testName("Test Car Park");
  CarPark testCarPark(testCapacity, testName);

  EXPECT_EQ(testName, testCarPark.name);
  EXPECT_EQ(testCapacity, testCarPark.capacity);
  EXPECT_EQ(testCapacity, testCarPark.getVacancies());
}
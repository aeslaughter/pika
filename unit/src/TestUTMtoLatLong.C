#include "gtest/gtest.h"
#include "utm_to_latlong.h"

TEST(UTMCoordinate, constructor)
{
  UTMCoordinate coord(504076.71, 4817139.95, 12);
  EXPECT_EQ(coord.easting, 504076.71);
  EXPECT_EQ(coord.northing, 4817139.95);
  EXPECT_EQ(coord.zone, static_cast<unsigned int>(12));
  EXPECT_EQ(coord.hemisphere, UTMCoordinate::Hemisphere::NORTH);

  UTMCoordinate coord2(504076.71, 4817139.95, 12, UTMCoordinate::Hemisphere::SOUTH);
  EXPECT_EQ(coord2.hemisphere, UTMCoordinate::Hemisphere::SOUTH);
}

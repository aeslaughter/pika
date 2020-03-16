#include "gtest/gtest.h"
#include "Coordinates.h"

using namespace PikaUtils::Coordinates;

TEST(UTM, constructor)
{
  UTM coord(504076.71, 4817139.95, 12);
  EXPECT_EQ(coord.easting, 504076.71);
  EXPECT_EQ(coord.northing, 4817139.95);
  EXPECT_EQ(coord.zone, static_cast<unsigned int>(12));
  EXPECT_EQ(coord.hemisphere, UTM::Hemisphere::NORTH);

  UTM coord2(504076.71, 4817139.95, 12, UTM::Hemisphere::SOUTH);
  EXPECT_EQ(coord2.hemisphere, UTM::Hemisphere::SOUTH);
}

TEST(WGS84, constructor)
{
  WGS84 coord(43.507179, -110.949567);
  EXPECT_EQ(coord.latitude.deg(), 43.507179);
  EXPECT_EQ(coord.longitude.deg(), -110.949567);
}

TEST(convert, UTMtoWGS84)
{
  WGS84 coord = convert(UTM(504076.71, 4817139.95, 12));
  EXPECT_EQ(coord.latitude.deg(), 43.507179);
  EXPECT_EQ(coord.longitude.deg(), -110.949567);
}

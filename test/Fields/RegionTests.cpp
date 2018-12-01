#include <catch2/catch.hpp>
#include "Tracing/Region.h"
#include "GenericTypes.h"

TEST_CASE("Region constructor + getMin() + getMax() tests", "[region]")
{
  SECTION("Empty region")
  {
    CityGen::Region region({});

    CHECK(region.getVertices().size() == 0);
  }

  SECTION("Region boundaries")
  {
    CityGen::Region region({ {-1.0f, 2.0f}, {1.0f, 1.0f}, {2.0f, 2.0f}, {5.4f, 5.4f}, {5.5f, 5.3f} });

	CHECK(region.getMin() == CityGen::Vector{ -1.0f, 1.0f });
	CHECK(region.getMax() == CityGen::Vector{ 5.5f, 5.4f });

    CHECK(region.getVertices().size() == 5);
  }
}

TEST_CASE("Region flip tests", "[region]")
{
  SECTION("Flipped region")
  {
    CityGen::Vector A{2.2f, 2.2f};
    CityGen::Vector B{1.1f, 1.1f};
    CityGen::Vector C{0.0f, 0.0f};

    CityGen::Region regionA({ A, B, C });
    CityGen::Region regionB({ C, B, A });

    regionA.flip();

    CHECK(regionA.getVertices()[0] == regionB.getVertices()[0]);
    CHECK(regionA.getVertices()[1] == regionB.getVertices()[1]);
    CHECK(regionA.getVertices()[2] == regionB.getVertices()[2]);
  }

  SECTION("Region flipped twice should be equal to initial region")
  {
    CityGen::Vector A{ 2.2f, 2.2f };
    CityGen::Vector B{ 1.1f, 1.1f };
    CityGen::Vector C{ 0.0f, 0.0f };

    CityGen::Region region({ A, B, C });

    region.flip();
    region.flip();

    CHECK(region.getVertices()[0] == A);
    CHECK(region.getVertices()[1] == B);
    CHECK(region.getVertices()[2] == C);
  }
}

TEST_CASE("Region isClockwise tests", "[region]")
{
  SECTION("Clockwise region", "[region]") 
  {
    CityGen::Region region({ {0,0}, {1,0}, {1,1}, {0,1} });

    CHECK(region.isClockwise());
  }
}

TEST_CASE("Region points tests")
{
  SECTION("Region contains appropriate points")
  {
    CityGen::Region region({ {0,0}, {1,0}, {1,1}, {0,1} });

    CHECK(region.containsPoint({ 0,0 }));
    CHECK(region.containsPoint({ 1,1 }));
  }
}
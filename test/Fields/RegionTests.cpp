#include <catch2/catch.hpp>
#include "Tracing/Region.h"
#include "GenericTypes.h"

TEST_CASE("Region constructor + getMin() + getMax() tests", "[region]")
{
  SECTION("Regions must be empty")
  {
  CityGen::Region region({});

    REQUIRE(region.getVertices().size() == 0);
  }

  SECTION("max value must be = (5.5f, 5.4f) and min must be = (-1.0f, 1)")
  {
    CityGen::Region region({ {-1.0f, 2}, {1, 1}, {2, 2}, {5.4f, 5.4f}, {5.5f, 5.3f} });

    CHECK(region.getMax().x == 5.5f);
    REQUIRE(region.getMax().y == 5.4f);

    REQUIRE(region.getMin().x == -1.0f);
    REQUIRE(region.getMin().y == 1);

    REQUIRE(region.getVertices().size() == 5);
  }
}

TEST_CASE("Region flip tests", "[region]")
{
  SECTION("Region [(2.2f, 2.2f), (1.1f, 1.1f), (0,0)] must be flipped to [(0,0), (1.1f, 1.1f), (2.2f, 2.2f)]")
  {
    CityGen::Vector A{2.2f, 2.2f};
    CityGen::Vector B{1.1f, 1.1f};
    CityGen::Vector C{0, 0};

    CityGen::Region regionA({ A, B, C });
    CityGen::Region regionB({ C, B, A });

    regionA.flip();

    REQUIRE(regionA.getVertices()[0] == regionB.getVertices()[0]);
    REQUIRE(regionA.getVertices()[1] == regionB.getVertices()[1]);
    REQUIRE(regionA.getVertices()[2] == regionB.getVertices()[2]);
  }

  SECTION("Region [(2.2f, 2.2f), (1.1f, 1.1f), (0,0)] must be flipped twice")
  {
    CityGen::Vector A{ 2.2f, 2.2f };
    CityGen::Vector B{ 1.1f, 1.1f };
    CityGen::Vector C{ 0, 0 };

    CityGen::Region region({ A, B, C });

    region.flip();
    region.flip();

    REQUIRE(region.getVertices()[0] == A);
    REQUIRE(region.getVertices()[1] == B);
    REQUIRE(region.getVertices()[2] == C);
  }
}

TEST_CASE("Region isClockwise tests", "[region]")
{
  SECTION("Region [(0,0), (1,0), (1,1), (0,1)] must be clockwise", "[region]") 
  {
    CityGen::Region region({ {0,0}, {1,0}, {1,1}, {0, 1} });

    REQUIRE(region.isClockwise());
  }
}
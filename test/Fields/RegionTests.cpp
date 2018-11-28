#include <catch2/catch.hpp>
#include "Tracing/Region.h"
#include "GenericTypes.h"
#include <iostream>

TEST_CASE("Region constructor + getMin() + getMax() tests", "[region]")
{
  SECTION("_vectices must be empty")
  {
    std::vector<CityGen::Vector> vector;
    CityGen::Region region(vector);

    REQUIRE(region.getVertices().size() == 0);
  }

  SECTION("max value must be = (5.5f, 5.5f) and min must be = (0, 0)")
  {
    CityGen::Region region({ {0,0}, {1,1}, {2,2}, {5.4f, 5.4f}, {5.5f, 5.5f} });

    REQUIRE(region.getMax().x == 5.5f);
    REQUIRE(region.getMax().y == 5.5f);

    REQUIRE(region.getMin().x == 0);
    REQUIRE(region.getMin().y == 0);

    REQUIRE(region.getVertices().size() == 5);
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
  SECTION("Region [(0,0), (1,1)] must be flipped to [(1,1), (0,0)]")
  {
    CityGen::Vector A, B;

    A.x = A.y = 0;
    B.x = B.y = 1;

    CityGen::Region region({ A, B });

    region.flip();

    REQUIRE(region.getVertices()[0] == B);
    REQUIRE(region.getVertices()[1] == A);
  }

  SECTION("Region [(2.2f, 2.2f), (1.1f, 1.1f), (0,0)] must be flipped to [(0,0), (1.1f, 1.1f), (2.2f, 2.2f)]")
  {
    CityGen::Vector A, B, C;

    A.x = A.y = 2.2f;
    B.x = B.y = 1.1f;
    C.x = C.y = 0;

    CityGen::Region region({ A, B, C });

    region.flip();

    REQUIRE(region.getVertices()[0] == C);
    REQUIRE(region.getVertices()[1] == B);
    REQUIRE(region.getVertices()[2] == A);
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
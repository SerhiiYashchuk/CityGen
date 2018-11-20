#include "GenericTypes.h"
#include <catch2/catch.hpp>

inline float vectorLength(float x, float y)
{
  return std::sqrt(x * x + y * y);
}

TEST_CASE("Vector lenght", "[vector]")
{
  CityGen::Vector vector;

  SECTION("Coordinates [0,0]")
  {
    vector.x = 0;
    vector.y = 0;

    REQUIRE(vector.length() == 0);
  }

  SECTION("Coordinates [1,1]")
  {
    vector.x = 1;
    vector.y = 1;

    REQUIRE(vector.length() > 0);
  }

  SECTION("Coordinates x == y [-1,-1]")
  {
    vector.x = -1;
    vector.y = -1;

    REQUIRE(vector.length() > 0);
  }

  SECTION("Coordinates [i,j] length")
  {
    for (int i = -5; i < 5; i++)
    {
      vector.x = static_cast<float>(i);
      for (int j = -5; j < 5; j++)
      {
        vector.y = static_cast<float>(j);

        REQUIRE(vector.length() == vectorLength(static_cast<float>(i), static_cast<float>(j)));
    }
    }

  }
}

TEST_CASE("Vectors equality", "[vector]")
{
  CityGen::Vector A;
  CityGen::Vector B;

  SECTION("0 == 0")
  {
    A.x = B.x = 0;
    A.y = B.y = 0;

    REQUIRE(A == B);
  }

  SECTION("0.99 == 0.99")
  {
    A.x = B.x = 0.99f;
    A.y = B.y = 0.99f;

    REQUIRE(A == B);
  }
  
  SECTION("-0.99 == -0.99")
  {
    A.x = B.x = -0.99f;
    A.y = B.y = -0.99f;

    REQUIRE(A == B);
  }

  SECTION("0 == 0; 0.99 == 0.99")
  {
    A.x = B.x = 0;
    A.y = B.y = 0.99f;

    REQUIRE(A == B);
  }

}

TEST_CASE("Vectors inequality", "[vector]")
{
  CityGen::Vector A;
  CityGen::Vector B;

  SECTION("0 != 0.99")
  {
    A.x = A.y = 0;
    B.x = B.y = 0.99f;

    REQUIRE(A != B);
  }

  SECTION("-0.99 != 0.99")
  {
    A.x = A.y = -0.99f;
    B.x = B.y = 0.99f;

    REQUIRE(A != B);
  }

  SECTION("0 != 0.99; 0.99 != 0")
  {
    A.x = 0;
    B.x = 0.99f;

    A.y = 0.99f;
    B.y = 0;

    REQUIRE(A != B);
  }
}

TEST_CASE("Vectors coordinates addition", "[vector]")
{
  CityGen::Vector A;
  CityGen::Vector B;

  SECTION("[0,0] + [0,0] must be = [0,0]")
  {
    A.x = B.x = 0;
    A.y = B.y = 0;

    CityGen::Vector tmp = A + B;
    REQUIRE(tmp.x == 0);
    REQUIRE(tmp.y == 0);
  }

  SECTION("[1,1] + [1,1] must be = [2,2]")
  {
    A.x = B.x = 1;
    A.y = B.y = 1;

    CityGen::Vector tmp = A + B;
    REQUIRE(tmp.x == 2);
    REQUIRE(tmp.y == 2);
  }

  SECTION("[-1,-1] + [1,1] must be = [0,0]")
  {
    A.x = A.y = -1;
    B.x = B.y = 1;

    CityGen::Vector tmp = A + B;
    REQUIRE(tmp.x == 0);
    REQUIRE(tmp.y == 0);
  }
}

TEST_CASE("Vectors coordinates subtraction", "[vector]")
{
  CityGen::Vector A;
  CityGen::Vector B;

  SECTION("[0,0] - [0,0] must be = [0,0]")
  {
    A.x = B.x = 0;
    A.y = B.y = 0;

    CityGen::Vector tmp = A - B;
    REQUIRE(tmp.x == 0);
    REQUIRE(tmp.y == 0);
  }

  SECTION("[1,1] - [1,1] must be = [0,0]")
  {
    A.x = B.x = 1;
    A.y = B.y = 1;

    CityGen::Vector tmp = A - B;
    REQUIRE(tmp.x == 0);
    REQUIRE(tmp.y == 0);
  }

  SECTION("[-1,-1] - [1,1] must be = [-2,-2]")
  {
    A.x = A.y = -1;
    B.x = B.y = 1;

    CityGen::Vector tmp = A - B;
    REQUIRE(tmp.x == -2);
    REQUIRE(tmp.y == -2);
  }

  SECTION("[1,1] - [-1,-1] must be = [2,2]")
  {
    A.x = A.y = 1;
    B.x = B.y = -1;

    CityGen::Vector tmp = A - B;
    REQUIRE(tmp.x == 2);
    REQUIRE(tmp.y == 2);
  }
}

TEST_CASE("Vectors coordinates multiplication", "[vector]")
{
  CityGen::Vector A;
  CityGen::Vector B;

  SECTION("[0,0] * [0,0] must be = [0,0]")
  {
    A.x = B.x = 0;
    A.y = B.y = 0;

    CityGen::Vector tmp = A * B;
    REQUIRE(tmp.x == 0);
    REQUIRE(tmp.y == 0);
  }

  SECTION("[0,0] * [1,1] must be = [0,0]")
  {
    A.x = A.y = 0;
    B.x = B.y = 1;

    CityGen::Vector tmp = A * B;
    REQUIRE(tmp.x == 0);
    REQUIRE(tmp.y == 0);
  }

  SECTION("[1,1] * [1,1] must be = [1,1]")
  {
    A.x = B.x = 1;
    A.y = B.y = 1;

    CityGen::Vector tmp = A * B;
    REQUIRE(tmp.x == 1);
    REQUIRE(tmp.y == 1);
  }

  SECTION("[-1,-1] * [1,1] must be = [-1,-1]")
  {
    A.x = A.y = -1;
    B.x = B.y = 1;

    CityGen::Vector tmp = A * B;
    REQUIRE(tmp.x == -1);
    REQUIRE(tmp.y == -1);
  }

  SECTION("[-1,-1] * [-1,-1] must be = [1,1]")
  {
    A.x = A.y = -1;
    B.x = B.y = -1;

    CityGen::Vector tmp = A * B;
    REQUIRE(tmp.x == 1);
    REQUIRE(tmp.y == 1);
  }
}

TEST_CASE("Vectors coordinates division", "[vector]")
{
  CityGen::Vector A;
  CityGen::Vector B;

  SECTION("[0,0] / [1,1] must be = [0,0]")
  {
    A.x = A.y = 0;
    B.x = B.y = 1;

    CityGen::Vector tmp = A / B;
    REQUIRE(tmp.x == 0);
    REQUIRE(tmp.y == 0);
  }

  SECTION("[1,1] / [1,1] must be = [1,1]")
  {
    A.x = A.y = 1;
    B.x = B.y = 1;

    CityGen::Vector tmp = A / B;
    REQUIRE(tmp.x == 1);
    REQUIRE(tmp.y == 1);
  }
}

TEST_CASE("Vectors coordinate += operation", "[vector]")
{
  CityGen::Vector A;
  CityGen::Vector B;

  SECTION("[0,0] += [0,0] must be = [0,0]")
  {
    A.x = A.y = 0;
    B.x = B.y = 0;

    A += B;
    REQUIRE(A.x == 0);
    REQUIRE(A.y == 0);
  }

  SECTION("[0,0] += [1,1] must be = [1,1]")
  {
    A.x = A.y = 0;
    B.x = B.y = 1;

    A += B;

    REQUIRE(A.x == 1);
    REQUIRE(A.y == 1);
  }
}

TEST_CASE("Vectors coordinate -= operation", "[vector]")
{
  CityGen::Vector A;
  CityGen::Vector B;

  SECTION("[0,0] -= [0,0] must be = [0,0]")
  {
    A.x = A.y = 0;
    B.x = B.y = 0;

    A -= B;

    REQUIRE(A.x == 0);
    REQUIRE(A.y == 0);
  }

  SECTION("[0,0] -= [1,1] must be = [-1,-1]")
  {
    A.x = A.y = 0;
    B.x = B.y = 1;

    A -= B;

    REQUIRE(A.x == -1);
    REQUIRE(A.y == -1);
  }

  SECTION("[1,1] -= [1,1] must be = [0,0]")
  {
    A.x = A.y = 1;
    B.x = B.y = 1;

    A -= B;

    REQUIRE(A.x == 0);
    REQUIRE(A.y == 0);
  }
}

TEST_CASE("Vectors coordinate *= operation", "[vector]")
{
  CityGen::Vector A;
  CityGen::Vector B;

  SECTION("[0,0] *= [0,0] must be = [0,0]")
  {
    A.x = A.y = 0;
    B.x = B.y = 0;

    A *= B;

    REQUIRE(A.x == 0);
    REQUIRE(A.y == 0);
  }

  SECTION("[0,0] *= [1,1] must be = [0,0]")
  {
    A.x = A.y = 0;
    B.x = B.y = 1;

    A *= B;

    REQUIRE(A.x == 0);
    REQUIRE(A.y == 0);
  }

  SECTION("[1,1] *= [1,1] must be = [1,1]")
  {
    A.x = A.y = 1;
    B.x = B.y = 1;

    A *= B;

    REQUIRE(A.x == 1);
    REQUIRE(A.y == 1);
  }
}

TEST_CASE("Vectors coordinate /= operation", "[vector]")
{
  CityGen::Vector A;
  CityGen::Vector B;

  SECTION("[0,0] /= [1,1] must be = [0,0]")
  {
    A.x = A.y = 0;
    B.x = B.y = 1;

    A /= B;

    REQUIRE(A.x == 0);
    REQUIRE(A.y == 0);
  }

  SECTION("[1,1] /= [1,1] must be = [1,1]")
  {
    A.x = A.y = 1;
    B.x = B.y = 1;

    A /= B;

    REQUIRE(A.x == 1);
    REQUIRE(A.y == 1);
  }
}

TEST_CASE("Vector scalar multiplacation", "[vector]")
{
  CityGen::Vector vector;

  SECTION("[0,0] * 0 must be = [0,0]")
  {
    vector.x = vector.y = 0;

    vector = vector * 0;

    CityGen::Vector tmp;
    tmp.x = tmp.y = 0;

    REQUIRE(vector == tmp);
  }

  SECTION("[0,0] * 1 must be = [0,0]")
  {
    vector.x = vector.y = 0;

    vector = vector * 1;

    CityGen::Vector tmp;
    tmp.x = tmp.y = 0;

    REQUIRE(vector == tmp);
  }

  SECTION("[1,1] * 0 must be = [0,0]")
  {
    vector.x = vector.y = 1;

    vector = vector * 0;

    CityGen::Vector tmp;
    tmp.x = tmp.y = 0;

  REQUIRE(vector == tmp);
  }

  SECTION("[1,1] * 1 must be = [1,1]")
  {
    vector.x = vector.y = 1;

    vector = vector * 1;

    CityGen::Vector tmp;
    tmp.x = tmp.y = 1;

    REQUIRE(vector == tmp);
  }
}

TEST_CASE("Vector scalar division", "[vector]")
{
  CityGen::Vector vector;

  SECTION("[0,0] / 1 must be = [0,0]")
  {
    vector.x = vector.y = 0;

    vector = vector / 1;

    CityGen::Vector tmp;
    tmp.x = tmp.y = 0;

  REQUIRE(vector == tmp);
  }

  SECTION("[1,1] / 1 must be = [1,1]")
  {
    vector.x = vector.y = 1;

    vector = vector / 1;

    CityGen::Vector tmp;
    tmp.x = tmp.y = 1;

  REQUIRE(vector == tmp);
  }
}

TEST_CASE("Vector scalar *= operation", "[vector]")
{
  CityGen::Vector vector;

  SECTION("[0,0] *= 0 must be = [0,0]")
  {
    vector.x = vector.y = 0;

    vector *= 0;

    CityGen::Vector tmp;
    tmp.x = tmp.y = 0;

    REQUIRE(vector == tmp);
  }

  SECTION("[0,0] *= 1 must be = [0,0]")
  {
    vector.x = vector.y = 0;

    vector *= 1;

    CityGen::Vector tmp;
    tmp.x = tmp.y = 0;

    REQUIRE(vector == tmp);
  }

  SECTION("[1,1] *= 0 must be = [0,0]")
  {
    vector.x = vector.y = 1;

    vector *= 0;

    CityGen::Vector tmp;
    tmp.x = tmp.y = 0;

    REQUIRE(vector == tmp);
  }

  SECTION("[1,1] *= 1 must be = [1,1]")
  {
    vector.x = vector.y = 1;

    vector *= 1;

    CityGen::Vector tmp;
    tmp.x = tmp.y = 1;

    REQUIRE(vector == tmp);
  }

}

TEST_CASE("Vector scalar /= operation", "[vector]")
{
  CityGen::Vector vector;

  SECTION("[0,0] /= 1 must be = [0,0]")
  {
    vector.x = vector.y = 0;

    vector /= 1;

    CityGen::Vector tmp;
    tmp.x = tmp.y = 0;

    REQUIRE(vector == tmp);
  }

  SECTION("[1,1] /= 1 must be = [1,1]")
  {
    vector.x = vector.y = 1;

    vector /= 1;

    CityGen::Vector tmp;
    tmp.x = tmp.y = 1;

    REQUIRE(vector == tmp);
  }
}

TEST_CASE("Vectors dot product", "[vector]")
{
  CityGen::Vector A;
  CityGen::Vector B;

  SECTION("([0,0],[0,0]) must be = 0")
  {
    A.x = A.y = B.x = B.y = 0;
    REQUIRE(CityGen::Utils::dotProduct(A, B) == 0);
  }

  SECTION("([1,1],[0,0]) must be = 0")
  {
    A.x = A.y = 1;
    B.x = B.y = 0;
    
    REQUIRE(CityGen::Utils::dotProduct(A, B) == 0);
  }

  SECTION("([1,1],[1,1]) must be = 2")
  {
    A.x = A.y = 1;
    B.x = B.y = 1;

    REQUIRE(CityGen::Utils::dotProduct(A, B) == 2);
  }
}
#define CATCH_CONFIG_MAIN

#include "GenericTypes.h"
#include "catch.hpp"



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
		A.x = B.x = 0.99;
		A.y = B.y = 0.99;

		REQUIRE(A == B);
	}
	
	SECTION("-0.99 == -0.99")
	{
		A.x = B.x = -0.99;
		A.y = B.y = -0.99;

		REQUIRE(A == B);
	}

	SECTION("0 == 0; 0.99 == 0.99")
	{
		A.x = B.x = 0;
		A.y = B.y = 0.99;

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
		B.x = B.y = 0.99;

		REQUIRE(A != B);
	}

	SECTION("-0.99 != 0.99")
	{
		A.x = A.y = -0.99;
		B.x = B.y = 0.99;

		REQUIRE(A != B);
	}

	SECTION("0 != 0.99; 0.99 != 0")
	{
		A.x = 0;
		B.x = 0.99;

		A.y = 0.99;
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

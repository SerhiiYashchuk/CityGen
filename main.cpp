#include "GeometricTree.h"
#include <iostream>

using namespace CityGen;

template<typename T>
void printElements(const std::vector<T> &container)
{
  for (const auto &element : container)
  {
    std::cout << element << " ";
  }

  std::cout << '\n';
}

int main(int /*argc*/, char const * /*argv[]*/)
{
  using Data = int;
  const Rect overallArea = { 0, 0, 100, 100 }; // Working area
  const std::size_t threshold = 10; // Maximum number of elements in one sub-region
  const std::size_t maxDepth = 100; // Maximum number of divisions

  /*
    When the QuadTree is empty its depth equals 1. It means that new elements will be placed
    together in one container and they will belong to the top region. As soon as the number of
    elements in one region exceeds the level's threshold, the region will be divided into 4
    equal sub-regions and all elements will be distributed between them. This process may continue
    for each region unless that region's depth exceeds the maximum depth of the tree.

    You don't have to deal with this stuff but it may be useful for your understanding.
  */
  
  Utils::QuadTree<Data> gTree(overallArea, threshold, maxDepth);

  /*
    We will put 4 elements into 4 different quadrants.

    +-----+-----+
    |  1  |  2  |
    +-----+-----+
    |  3  |  4  |
    +-----+-----+
  */

  const Rect quadrant1 = { 0, 0, 50, 50 };
  const Rect quadrant2 = { 51, 0, 100, 50 };
  const Rect quadrant3 = { 0, 51, 50, 100 };
  const Rect quadrant4 = { 51, 51, 100, 100 };

  // Currently we have to use the same type for position and bounds. We will change it soon.
  gTree.insert({ 25, 25, 25, 25 }, 1);
  gTree.insert({ 75, 25, 75, 25 }, 2);
  gTree.insert({ 25, 75, 25, 75 }, 3);
  gTree.insert({ 75, 75, 75, 75 }, 4);

  // Lets get all elements from the tree.
  printElements(gTree.getItemsInBounds(overallArea));

  // Now lets get elements from each individual quadrant.
  printElements(gTree.getItemsInBounds(quadrant1));
  printElements(gTree.getItemsInBounds(quadrant2));
  printElements(gTree.getItemsInBounds(quadrant3));
  printElements(gTree.getItemsInBounds(quadrant4));

  // Lets experiment with bounds.
  printElements(gTree.getItemsInBounds({ 0, 0, 100, 50 })); // Should be 1 and 2
  printElements(gTree.getItemsInBounds({ 51, 0, 100, 100 })); // Should be 2 and 4
}

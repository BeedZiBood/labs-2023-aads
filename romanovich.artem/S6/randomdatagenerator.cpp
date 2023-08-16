#include <random>
#include "randomdatagenerator.h"
std::vector< int > romanovich::generateRandomData(size_t size, int min, int max)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector< int > data(size);
  std::uniform_int_distribution< int > dist(min, max);
  for (size_t i = 0; i < size; i++)
  {
    data[i] = dist(gen);
  }
  return data;
}
std::vector< float > romanovich::generateRandomData(size_t size, float min, float max)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector< float > data(size);
  std::uniform_real_distribution< float > dist(min, max);
  for (size_t i = 0; i < size; i++)
  {
    data[i] = dist(gen);
  }
  return data;
}

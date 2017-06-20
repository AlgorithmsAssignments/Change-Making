#include "Test.h"
#include <iostream>
using namespace std;

int sum(std::vector<int> v)
{
  int sum = 0;
  for (unsigned int i = 0; i < v.size(); i++) {
    sum += v[i];
  }

  return sum;
}

vector<int> makeChangeRecursive(vector<int> sorted_coins, int amount, std::vector<int> answer, int lastIndex)
{
  //unsigned int lastIndex = sorted_coins.size() - 1;
  if(lastIndex < 0)
    return answer;
  int currCoin = sorted_coins[lastIndex];
  // cout<<"Checking with index: "<<lastIndex<<endl;
  if(currCoin <= amount)
  {
    // cout<<"Less than"<<endl;
    answer.push_back(currCoin);
    amount -= currCoin;
    answer = makeChangeRecursive(sorted_coins, amount, answer, lastIndex);
  }else
  {
    // cout<<"Didn't find"<<endl;
    answer = makeChangeRecursive(sorted_coins, amount, answer, lastIndex - 1);
  }

  return answer;
}

vector<int> makeChange(vector<int> sorted_coins, int amount)
{
  vector<int> answer;

  answer = makeChangeRecursive(sorted_coins, amount, answer, sorted_coins.size() - 1);
  cout<<endl<<"Returned"<<endl<<endl;
  return answer;
}

int main ()
{
    test();
    return 0;
}

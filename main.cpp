#include "Test.h"
#include <iostream>
#include <map>
using namespace std;
//GREEDY
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

vector<int> makeChangeGreedy(vector<int> sorted_coins, int amount)
{
  vector<int> answer;

  answer = makeChangeRecursive(sorted_coins, amount, answer, sorted_coins.size() - 1);
  cout<<endl<<"Returned"<<endl<<endl;
  return answer;
}
//GREEDY END


//DYNAMIC HELP
map< int, map<int, int> > memo;

int countSolutionsRecursive(vector<int> coins, int amount)
{
  if(amount == 0)
    return 1;

  if(amount < 0)
    return 0;

  if(coins.size() == 0 && amount > 0)
    return 0;

  vector<int> coins_wo_last = coins;
  coins_wo_last.pop_back();
  if(
    memo.find(coins.size()) == memo.end() ||
    memo[coins.size()].find(amount) == memo[coins.size()].end()
    )
  {
    memo[coins.size()][amount] = countSolutionsRecursive(coins_wo_last, amount)
      + countSolutionsRecursive(coins, amount - coins[coins.size()-1]);
  }

  return memo[coins.size()][amount];
}

int countSolutions(vector<int> coins, int amount)
{
  memo.clear();
  return countSolutionsRecursive(coins, amount);
}

//DYNAMIC HELP END

//DYNAMIC TEST


vector<int> makeChange(vector<int> sorted_coins, int amount)
{
  vector<int> answer;
  cout<<"Vec size: "<<sorted_coins.size()<<endl;
  cout<<"Solutions possible: "<<countSolutions(sorted_coins, amount)<<endl;

  return answer;
}

//DYNAMIC TEST END

int main ()
{
    test();
    return 0;
}

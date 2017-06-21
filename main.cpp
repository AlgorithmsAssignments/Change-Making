#include "Test.h"
#include <map>
#include <limits>
#include <iostream>
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

int countSolutionsRecursive(vector<int> coins, int amount, int minNumOfCoinsNeeded, vector<int>* answer)
{
  if(amount == 0)
  {
    if(answer->size() == minNumOfCoinsNeeded)
    {
      cout<<endl<<endl<<"FOUND MINIMUM!"<<endl<<endl;
    }
    return 1;
  }

  if(amount < 0)
  {
    answer->pop_back();
    return 0;
  }

  if(coins.size() == 0 && amount > 0)
  {
    return 0;
  }
  vector<int> coins_wo_last = coins;
  coins_wo_last.pop_back();
  if(
    memo.find(coins.size()) == memo.end() ||
    memo[coins.size()].find(amount) == memo[coins.size()].end()
    )
  {
    int coinToRemove = coins[coins.size()-1];
    answer->push_back(coinToRemove);
    vector<int> checkVec;
    checkVec.push_back(coinToRemove);
    memo[coins.size()][amount] = countSolutionsRecursive(coins_wo_last, amount, minNumOfCoinsNeeded, answer)
      + countSolutionsRecursive(coins, amount - coinToRemove, minNumOfCoinsNeeded, &checkVec);
  }

  return memo[coins.size()][amount];
}

int countSolutions(vector<int> coins, int amount, int minNumOfCoinsNeeded, vector<int>* answer)
{
  memo.clear();
  return countSolutionsRecursive(coins, amount, minNumOfCoinsNeeded, answer);
}

//DYNAMIC HELP END

//DYNAMIC TEST

//MIN coins
//FROM: http://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/
int minCoins(vector<int> coins, int m, int V, std::vector<int>* answer)
{
   // base case
   if (V == 0) return 0;

   // Initialize result
   int res = std::numeric_limits<int>::max();
   int THE_MAX = res;
   // Try every coin that has smaller value than V
   for (int i = 0; i < m; i++)
   {
     if (coins[i] <= V)
     {
         int sub_res = minCoins(coins, m, V - coins[i], answer);
         // result can minimized
         if (sub_res != THE_MAX && sub_res + 1 < res)
         {
           answer->push_back(coins[i]);
           res = sub_res + 1;
         }else{
           answer->pop_back();
         }
     }
   }
   return res;
}
//MIN END

vector<int> makeChange(vector<int> sorted_coins, int amount)
{
  vector<int> answer;
  cout<<"Vec size: "<<sorted_coins.size()<<endl;
  vector<int> dummy;
  int minNumOfCoinsNeeded = minCoins(sorted_coins, sorted_coins.size(), amount, &dummy);
  cout<<"Min coins needed: "<<minNumOfCoinsNeeded<<endl;
  cout<<"Solutions possible: "<<countSolutions(sorted_coins, amount, minNumOfCoinsNeeded, &answer)<<endl<<endl;
  cout<<"Answer has size:"<<answer.size()<<endl ;
  for(int i = 0; i < answer.size(); ++i)
  {
    cout<<"I: "<<answer[i]<<endl;
  }
  cout<<endl<<endl;
  return answer;
}

//DYNAMIC TEST END

int main ()
{
    test();
    return 0;
}

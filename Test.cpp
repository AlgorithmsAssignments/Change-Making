#include "Test.h"

int _getSum(vector<int> vec)
{
    int sum=0;
    for(int i=0;i<vec.size();i++)
    {
        sum+=vec[i];
    }
    return sum;
}

bool _contains(vector<int> container, vector<int> contained)
{
    for(int i=0;i<container.size();i++)
    {
        bool flag = false;
        for(int j=0;j<contained.size();j++)
        {
            if(container[i]==contained[j])
            {
                flag = true;
                break;
            }
        }
        if(!flag)
            return false;
    }
    return true;
}

void test()
{
    static const int arr[] = {1, 5, 10, 20};
    vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    vector<int> res1 = makeChange(vec, 36);

    static const int arr2[] = {1, 4, 5, 15, 20};
    vector<int> vec2 (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
    vector<int> res2 = makeChange(vec2, 23);

    if(_getSum(res1) == 36
       && _contains(res1, vec)
       && _getSum(res2) == 23
       && _contains(res2, vec2)
       )
    {
        cout<<"Test: Pass"<<endl;
    }else
    {
        cout<<"Test: Fail"<<endl;
    }

}

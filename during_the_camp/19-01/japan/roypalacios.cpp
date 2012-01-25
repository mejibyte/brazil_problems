#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <queue>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

long long want;
bool done;

int popcount(long long x)
{
	int ans = 0;
	while(x)
	{
		ans++;
		x = x & (x-1);
	}
	return ans;
}

vector <string> ans;

string tos(int n)
{
	stringstream os;
	os<<n;
	return os.str();
}

void backtrack(long long mask, int steps)
{
	if(done) return;
	
	int need = popcount(want & (~mask));
	
	if(need == 0)
	{
		done = 1;
		return;
	}
	else if(need <= steps)
	{
		// shift
		for(int i=1; i<=42; i++)
		{
			if(mask & (1LL<<i))
			{
				int j = i<<1, k=1;
				while(j <= 42)
				{
					long long nmask = mask | (1LL<<j);
					
					if(done) break;
					if(nmask != mask) backtrack(nmask, steps-1);
					if(done) ans.push_back(tos(i) + "<<" + tos(k));
					
					k++;
					j<<=1;
				}
			}
		}

		// add & substract
		for(int i=1; i<=42; i++)
		{
			if(mask & (1LL<<i))
			{
				for(int j=1; j<i; j++)
				{
					if(mask & (1LL<<j))
					{
						int a = i + j;
						if(a <= 42)
						{
							long long nmask = mask | (1LL<<a);
							if(nmask != mask)
							{
								if(done) break;
								backtrack(nmask, steps-1);
								if(done) ans.push_back(tos(i) + "+" + tos(j));
							}
						}
						int b = i - j;
						if(b >= 1)
						{
							long long nmask = mask | (1LL<<b);
							if(nmask != mask)
							{
								if(done) break;
								backtrack(nmask, steps-1);
								if(done) ans.push_back(tos(i) + "-" + tos(j));
							}
						}
					}
				}
			}
		}
	}
}

int main()
{
    #ifndef LOCAL
    	freopen("japan.in", "r", stdin);
    	freopen("japan.out", "w", stdout);
    #endif
	
	int n;
	while(cin>>n)
	{
		want = 0;
		for(int i=0; i<n; i++)
		{
			int tmp;
			cin>>tmp;
			
			want |= (1LL<<tmp);
		}
		
		done = 0;
		ans.clear();
		
		for(int steps=0; steps<100; steps++)
		{
			backtrack(1LL<<1, steps);
			if(done)
			{
				cout<<steps<<endl;
				for(int i=(int)ans.size()-1; i>=0; i--)
					cout<<ans[i]<<endl;
				break;
			}
		}
	}
	
	return 0;
}

using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

long double distSqr (int x0, int y0, int x1, int y1){
	return (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1);
}

int main(){
	#ifndef LOCAL
	freopen("circles.in", "r", stdin);
	freopen("circles.out", "w", stdout);
	#endif
	
    int cases;
    scanf("%d", &cases);
    while (cases--){
		int x0, y0, r0, x1, y1, r1;
		scanf("%d %d %d %d %d %d", &x0, &y0, &r0, &x1, &y1, &r1);
		
		//printf("%d %d %d %d %d %d: ", x0, y0, r0, x1, y1, r1);
        
		if (x0 == x1 and y0 == y1){
			if (r0 == r1) printf("I can't count them - too many points :(\n");
			else printf("There are no points!!!\n");
			if (cases > 0) puts("");
			continue;
		}
		assert(x1 != x0 or y1 != y0);
		
		double dx = x0 - x1;
		double dy = y0 - y1;
		if (y0 != y1){
			double m = -dx / dy;
			double d = (1.0 * r1 * r1 - r0 * r0 - dx * dx - dy * dy) / (2.0 * dy);
			
			double a = m * m + 1;
			double b = 2 * m * d;
			double c = d * d - r0 * r0;
			
            D(a); D(b); D(c);
			
			double root = b * b - 4 * a * c;
			
			if (cmp(root, 0) < 0){
				//No solutions
				printf("There are no points!!!\n");
			}
			if (cmp(root, 0) == 0){
				//One solution
				printf("There are only 1 of them....\n");
				double x = -b / (2.0 * a);
				double y = m * x + d;
				printf("%.6lf %.6lf\n", x + x0, y + y0);
			}
			if (cmp(root, 0) > 0){
				//Two solutions
				printf("There are only 2 of them....\n");
				double x1 = (-b + sqrt(root)) / (2.0 * a);
				double y1 = m * x1 + d;
				double x2 = (-b - sqrt(root)) / (2.0 * a);
				double y2 = m * x2 + d;
				
				vector <pair < double, double> > p;
				p.push_back(make_pair(x1, y1));
				p.push_back(make_pair(x2, y2));
				sort(p.begin(), p.end());
				
				printf("%.6lf %.6lf\n", p[0].first + x0, p[0].second + y0);
				printf("%.6lf %.6lf\n", p[1].first + x0, p[1].second + y0);
			}		
		} else {
			double m = -dy / dx;
			double d = (1.0 * r1 * r1 - r0 * r0 - dx * dx - dy * dy) / (2.0 * dx);
			
			double a = m * m + 1;
			double b = 2 * m * d;
			double c = d * d - r0 * r0;
			
			double root = b * b - 4 * a * c;
			
			if (cmp(root, 0) < 0){
				//No solutions
				printf("There are no points!!!\n");
			}
			if (cmp(root, 0) == 0){
				//One solution
				printf("There are only 1 of them....\n");
				double y = -b / (2.0 * a); 
				double x = m * y + d;
				printf("%.06lf %.06lf\n", x + x0, y + y0);
			}
			if (cmp(root, 0) > 0){
				//Two solutions
				printf("There are only 2 of them....\n");
				double y1 = (-b + sqrt(root)) / (2.0 * a);
				double x1 = m * y1 + d;
				double y2 = (-b - sqrt(root)) / (2.0 * a);
				double x2 = m * y2 + d;
				
				vector <pair < double, double> > p;
				p.push_back(make_pair(x1, y1));
				p.push_back(make_pair(x2, y2));
				sort(p.begin(), p.end());
				
				printf("%.06lf %.06lf\n", p[0].first + x0, p[0].second + y0);
				printf("%.06lf %.06lf\n", p[1].first + x0, p[1].second + y0);
			}		    
		}		
		if (cases > 0) puts("");		
	}
    
    return 0;
}

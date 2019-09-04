//Run by entering 2 commands: g++ -o name name.cpp then, ./name

/*
--------PLANNING--------
points cases:
1. (x1<x2) & (y1<y2)
2. (x1<x2) & (y1>y2)
3. (x1>x2) & (y1<y2)
4. (x1>x2) & (y1>y2)

2&3  1&4 same

https://www.easycalculation.com/analytical/learn-triangle-incenter.php

1) get lines to work-> get triangle to work
2) calculate incenter and radius
3) calculate circmcenter and radius
4) draw incircle and circumcircle
5) draw euler line between incenter and circumcenter

*/
int matrix[100][100] = {{0}};
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <math.h>
using namespace std;

//redo line1, line2 , b_alg !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



void b_alg(int r1, int c1, int r2, int c2) {
        if(abs(c2-c1) < abs(r2-r1)) {
                if(r1 > r2) {
			        int dx = r1 - r2;
			        int dy = c1 - c2;
			        if(c1 < c2) { dy = c2-c1;}
			        
			        int e = 2*dy - dx;
			        int y = c2;

			        for(int x = r2; x < r1; x++) {
			                matrix[x][y] = 1;
			                if(e > 0) {
			                		if(c1-c2 < 0) { y = y-2; }
			                        y = y + 1;
			                        e = e - 2*dx;
			                }
			                e = e + 2*dy;
			        }


                }
                else {
				        int dx = r2 - r1;
				        int dy = c2 - c1;
				        if(c2 < c1) { dy = c1-c2;}
				        
				        int e = 2*dy - dx;
				        int y = c1;

				        for(int x = r1; x < r2; x++) {
				                matrix[x][y] = 1;
				                if(e > 0) {
				                		if(c2-c1 < 0) { y = y-2; }
				                        y = y + 1;
				                        e = e - 2*dx;
				                }
				                e = e + 2*dy;
				        }
                }
        }       
        else {
                if(c1 > c2) {
				        int dx = r1 - r2;
				        if(r1 < r2) { dx = r2 - r1; }
				        int dy = c1 - c2;

				        
				        int e = 2*dx - dy;
				        int x = r2;

				        for(int y = c2; y < c1; y++) {
				                matrix[x][y] = 1;
				                if(e > 0) {
				                		if(r1<r2) { x = x-2; }
				                        x = x + 1;
				                        e = e - 2*dy;
				                }
				                e = e + 2*dx;
				        }
				}
                
                else {
			        int dx = r2 - r1;
			        if(r2 < r1) { dx = r1 - r2; }
			        int dy = c2 - c1;

			        
			        int e = 2*dx - dy;
			        int x = r1;

			        for(int y = c1; y < c2; y++) {
			                matrix[x][y] = 1;
			                if(e > 0) {
			                		if(r2<r1) { x = x-2; }
			                        x = x + 1;
			                        e = e - 2*dy;
			                }
			                e = e + 2*dx;
			        }

                }
        }

        //return out;
}
void circle(int r, int cx, int cy) {
		int m[100][100] = {{0}};
        int x, y, xmax, y2, y2_new, ty;
        xmax = (int) (r * 0.70710678); // maximum x at radius/sqrt(2)
        y = r;
        y2 = y * y;
        ty = (2 * y) - 1; 
        y2_new = y2;
        for (x = 0; x <= xmax; x++) {
                if ((y2 - y2_new) >= ty) {
                        y2 -= ty;
                        y -= 1;
                        ty -= 2;
                }
                if(cx+x < 100 && cy+y < 100) { m[cx+x][cy+y] = 1; }
        		if(cx-x > 0 && cy+y < 100) { m[cx-x][cy+y] = 1; }
        		if(cx+x < 100 && cy-y > 0) { m[cx+x][cy-y] = 1; }
        		if(cx-x > 0 && cy-y > 0) { m[cx-x][cy-y] = 1; }
        
        		if(cx+y < 100 && cy+x < 100) { m[cx+y][cy+x] = 1; }
        		if(cx-y > 0 && cy+x < 100) { m[cx-y][cy+x] = 1; }
        		if(cx+y < 100 && cy-x > 0) { m[cx+y][cy-x] = 1; }
        		if(cx-y > 0 && cy-x > 0) { m[cx-y][cy-x] = 1; }
                y2_new -= (2 * x) - 3;
        }
 
        for(int i = 0; i < 100; i++) {
                for(int j = 0; j<100; j++) {
                        if(m[i][j] == 1){matrix[i][j] = 1;}
                        
                }
        }
}






int main(void) {
        srand (time(NULL));
        int r1 = rand()%100;
        int c1 = rand()%100;

        int r2 = rand()%100;
        int c2 = rand()%100;

        while(abs(r2-r1) == 0  ) {
        	r2 = rand()%100;
        }

        while(abs(c2-c1) == 0 ) {
        	c2 = rand()%100;
        }

        int r3 = rand()%100;
        int c3 = rand()%100;

        while(abs(r3-r1) == 0 || abs(r3-r2) == 0 ) {
        	r2 = rand()%100;
        }

        while(abs(c3-c1) == 0 || abs(c3-c2) == 0 ) {
        	c2 = rand()%100;
        }
        

        b_alg(r1, c1, r2, c2);
        b_alg(r2, c2, r3, c3);
        b_alg(r3, c3, r1, c1);

        double dist12 = sqrt(pow(r2-r1, 2)+pow(c2-c1, 2));
        double dist23 = sqrt(pow(r3-r2, 2)+pow(c3-c2, 2));
        double dist31 = sqrt(pow(r3-r1, 2)+pow(c3-c1, 2));  
        double p = dist12+dist23+dist31;
        
        int incx = (r1*dist23+r2*dist31+r3*dist12)/p;
        int incy = (c1*dist23+c2*dist31+c3*dist12)/p; 

        double s = .5*p;
        double r = sqrt(((s-dist12)*(s-dist23)*(s-dist31))/s);
        double R = (dist12*dist23*dist31)/(4*r*s);

        circle(r, incx, incy);


        double a_1 = (c2-c1)/(r2-r1);
		double a_2 = (c3-c2)/(r3-r2);

		double b_1 = a_1 * .5 * (r1+r2);
		double b_2 = a_2 * .5 * (r2+r3);

		double c_1 = .5 * (c1+c2);
		double c_2 = .5 * (c2+c3);

		int ccx = (b_2 + c_2 - b_1 - c_1)/(a_2 - a_1);
		int ccy = -1 * a_2 * ccx + b_2 + c_2;

		circle(R, ccx, ccy);

		
		b_alg(incx, incy, ccx, ccy);

        ofstream file;
        file.open("o1.ppm");

        file << "P3 300 100 1";
        for(int i = 0; i < 100; i++) {
                for(int j = 0; j<100; j++) {
                        if(matrix[i][j] == 1){file<<"111";}
                        else{file<< "000";}
                }
                file << "\n";
        }
        

        
        file.close();
        return 0;
}
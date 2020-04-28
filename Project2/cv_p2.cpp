int matrix[100][100] = {{0}};

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <math.h>
#include <sstream>

using namespace std;


bool inTriangle(int ax, int ay, int bx, int by, int cx, int cy, int px, int py) {
	int c_prod1[2] = {(bx-ax)*(py-ay), -1*(by-ay)*(px-ax)};
	int c_prod2[2] = {(bx-ax)*(cy-ay), -1*(by-ay)*(cx-ax)};

	int dot_prod = c_prod1[0]*c_prod2[0] + c_prod1[1]*c_prod2[1];

	if(dot_prod < 0) {return false;}
	return true;

}

double distance(int ix, int iy, int jx, int jy) {
    double res = pow(jx-ix,2)+ pow(jy-iy,2);
    return sqrt(res);

}

int b_alg(int r1, int c1, int r2, int c2) {
    if(abs(c2-c1) > abs(r2-r1)) {
        if(c1 > c2) {
            int dr = r1 - r2;
            if(r1 < r2) { dr = r2 - r1; }
            int dc = c1 - c2;    
            int e = 2*dr - dc;
            int r = r2;

            for(int c = c2; c < c1; c++) {
                matrix[r][c] = 1;
                if(e > 0) {
                    if(r1<r2) { r = r-2; }
                    r = r + 1;
                    e = e - 2*dc;
                }
                e = e + 2*dr;
            }
        }   
                
        else {
            int dr = r2 - r1;
            if(r2 < r1) { dr = r1 - r2; }
            int dc = c2 - c1;
            int e = 2*dr - dc;
            int r = r1;

            for(int c = c1; c < c2; c++) {
                matrix[r][c] = 1;
                if(e > 0) {
                    if(r2<r1) { r = r-2; }
                    r = r + 1;
                    e = e - 2*dc;
                }
                e = e + 2*dr;
            }

        } 
                
    }       
    else {
                
        
        if(r1 > r2) {
            int dr = r1 - r2;
            int dc = c1 - c2;
            if(c1 < c2) { dc = c2-c1;}
                        
            int e = 2*dc - dr;
            int c = c2;

            for(int r = r2; r < r1; r++) {
                matrix[r][c] = 1;
                if(e > 0) {
                    if(c1-c2 < 0) { c = c-2; }
                    c = c + 1;
                    e = e - 2*dr;
                }
                e = e + 2*dc;
            }


        }
        else {
            int dr = r2 - r1;
            int dc = c2 - c1;
            if(c2 < c1) { dc = c1-c2;}
                            
            int e = 2*dc - dr;
            int c = c1;

            for(int r = r1; r < r2; r++) {
                matrix[r][c] = 1;
                if(e > 0) {
                    if(c2-c1 < 0) { c = c-2; }
                    c = c + 1;
                    e = e - 2*dr;
                }
                e = e + 2*dc;
            }
        }

    }
}
int main(int argc, char* argv[]) {
	srand (time(NULL));
//get number of points
	stringstream str;
    str << argv[1];
    static int num_pts;
    str >> num_pts;

    cout << num_pts;

    int* x_pts = new int[num_pts];
    int* y_pts = new int[num_pts];

    for(int i = 0; i < num_pts; i++) {
    	int x1 = rand()%100;
        int y1 = rand()%100;

        x_pts[i] = x1;
        y_pts[i] = y1;
    }

    int new_np = num_pts;
    int* in = new int[num_pts];
    for(int i = 0; i < 10; i++) {

    	int one = rand()%num_pts;
    	while( in[one] <0) {
    		one = rand()%num_pts;
    	}
        int two = rand()%num_pts;

        while(abs(two-one) == 0 || in[two] <0 ) {
        	two = rand()%num_pts;
        }

        int three = rand()%num_pts;

        while(abs(three-one) == 0 || abs(three-two) == 0 || in[three] <0) {
        	three = rand()%num_pts;
        }

        for(int j = 0; j < num_pts; j++) {
        	if(j != one && j != two && j != three && in[j] >=0) {
		        bool c12 = inTriangle(x_pts[one], y_pts[one], x_pts[two], y_pts[two], x_pts[three], y_pts[three], x_pts[j], y_pts[j]);
		        bool c23 = inTriangle(x_pts[two], y_pts[two], x_pts[three], y_pts[three], x_pts[one], y_pts[one], x_pts[j], y_pts[j]);
		        bool c31 = inTriangle(x_pts[three], y_pts[three], x_pts[one], y_pts[one], x_pts[two], y_pts[two], x_pts[j], y_pts[j]);

		        if(c12 && c23 && c31) {
		        	if(in[j] > -1) { 
                        cout << x_pts[i] << " " << y_pts[i] << " " << in[i] << "\n";
                        new_np = new_np-1; 
                    }

		        	in[j] = -1; 

		        	
		        }
		    }
		}
    }

    int* x_bord = new int[new_np+1];
    int* y_bord = new int[new_np+1];
    int counter = 0;
    for(int i = 0; i < num_pts; i++) {
    	if(in[i] >= 0) {
            if(counter == 0) {
                x_bord[new_np] = x_pts[i];
                y_bord[new_np] = y_pts[i];
            }
    		matrix[x_pts[i]][y_pts[i]] = 1;
            x_bord[counter] = x_pts[i];
            y_bord[counter++] = y_pts[i];

    	}
    	else {matrix[x_pts[i]][y_pts[i]] = 2;}
    }





     while(1) {
        bool b = true;
        for(int i = 0; i < new_np; i++) {
            for(int j = 0; j < new_np; j++) {
                if(i >= j) {
                    continue;
                }
                if(distance(x_bord[i], y_bord[i], x_bord[i+1], y_bord[i+1]) + distance(x_bord[j], y_bord[j], x_bord[j+1], y_bord[j+1]) > distance(x_bord[i], y_bord[i], x_bord[j], y_bord[j]) + distance(x_bord[i+1], y_bord[i+1], x_bord[j+1], y_bord[j+1])) {
                    b = false;

                    int tempx = x_bord[j];
                    int tempy = y_bord[j];

                    x_bord[j] = x_bord[i+1];
                    y_bord[j] = y_bord[i+1];

                    x_bord[i+1] = tempx;
                    y_bord[i+1] = tempy;

                }
            }
        }


        if(b) {
            break;
        }
     }

     for(int i = 0; i < new_np; i++) {
        b_alg(x_bord[i], y_bord[i], x_bord[i+1], y_bord[i+1]);
     }


     for(int i = 0; i < 100; i++) {
        for(int j = 0; j<100; j++) {
            if(matrix[i][j] == 1){ cout << "O"; }
            else if(matrix[i][j] == 2){ cout << "*"; }
            else { cout << "-"; }
                        
        }
        cout << "\n";
    }

    cout << new_np;
    delete[] x_pts;
    delete[] y_pts;

	return 0;
}
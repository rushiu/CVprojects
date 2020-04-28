int matrix[100][100] = {{0}};

int mx = 0;
int my = 0;

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <math.h>
#include <sstream>

using namespace std;

double distance(int ix, int iy, int jx, int jy) {
    double res = pow(jx-ix,2)+ pow(jy-iy,2);
    return sqrt(res);

}
void b_alg(int r1, int c1, int r2, int c2) {
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






int* bf(int num_pts) {
    srand (time(NULL));
    int* x_pts = new int[num_pts];
    int* y_pts = new int[num_pts];

    for(int i = 0; i < num_pts; i++) {
        int x1 = rand()%100;
        int y1 = rand()%100;

        x_pts[i] = x1;
        y_pts[i] = y1;
    matrix[x1][y1] = 1;
    }

    double dbest = 1000.0;
    int bx1 = 0;
    int by1 = 0;

    int bx2 = 0;
    int by2 = 0;

    for(int i = 0; i < num_pts; i++) {
        for(int j = i+1; j < num_pts; j++) {
            if(distance(x_pts[i], y_pts[i], x_pts[j], y_pts[j]) < dbest) {
                dbest = distance(x_pts[i], y_pts[i], x_pts[j], y_pts[j]);
                bx1 = x_pts[i];
                by1 = y_pts[i];

                bx2 = x_pts[j];
                by2 = y_pts[j];
            }

        }
    }
    int* ret = new int[4];
    ret[0] = bx1;
    ret[1] = by1;

    ret[2] = bx2;
    ret[3] = by2;
    //cout << "Brute Force: " << dbest << "\n";
    return ret;

}


int main(int argc, char* argv[]) {   

            clock_t start, stop;

        start = clock();

        int* ans = bf(30);
        cout << ans[0]; 
        cout << "\n"; 
        
        cout << ans[1]; 
        cout << "\n"; 
        
        cout << ans[2]; 
        cout << "\n"; 
        
        cout << ans[3]; 
        cout << "\n"; 

        stop = clock();
        double pass = (double(stop) - double(start)); 
        pass = pass/ CLOCKS_PER_SEC;

        cout << "BF: Time taken for " << 30 << " Points: " << pass << " seconds. \n";
        start = clock();

    b_alg(ans[0], ans[1], ans[2], ans[3]);

    ofstream file;
    file.open("t5.ppm");
    file << "P3 100 100 1 \n";
        for(int i = 0; i < 100; i++) {
                for(int j = 0; j<100; j++) {
                        if(matrix[i][j] == 1){file<<"0 0 0 ";}
                        else{file<< "1 1 1 ";}
                }
                file << "\n";
        }

        for(int i = 0; i < 100; i++) {
                for(int j = 0; j<100; j++) {
                        if(matrix[i][j] == 1){cout<<"1";}
                        else{cout<< "-";}
                }
                cout << "\n";
        }



    return 0;
}
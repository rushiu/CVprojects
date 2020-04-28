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

double best_dist(int a[], int b[], int len) {

    if(len == 3) {
        double d01 = distance(a[0], b[0], a[1], b[1]);
        double d12 = distance(a[1], b[1], a[2], b[2]);
        double d02 = distance(a[0], b[0], a[2], b[2]);

        if(d01 <= d12 && d01 <= d02) {
            return d01;
        }
        if(d12 <= d02 && d12 <= d01) {
            return d12;
        }
        return d02;

    }
    if(len == 2) {
        return distance(a[0], b[0], a[1], b[1]);
    }
    if(len > 3) {
        int new_len = len/2;
        int* new_a_1st;
        int* new_a_2nd;
        int* new_b_1st;
        int* new_b_2nd;

        if(len % 2 != 0) {
            new_a_1st = new int[new_len];
            new_a_2nd = new int[new_len+1];

            new_b_1st = new int[new_len];
            new_b_2nd = new int[new_len+1];
        }

        else {
            new_a_1st = new int[new_len];
            new_a_2nd = new int[new_len];

            new_b_1st = new int[new_len];
            new_b_2nd = new int[new_len];
        }

        for(int i = 0; i < new_len; i++) {
            new_a_1st[i] = a[i];
            new_b_1st[i] = b[i];
        }
        for(int j = new_len; j < len; j++) {
            new_a_2nd[j-new_len] = a[j];
            new_b_2nd[j-new_len] = b[j];
        }
        double error = distance(a[new_len-1], b[new_len-1], a[new_len], b[new_len]);

        double n1 = best_dist(new_a_1st, new_b_1st, new_len);

        double n2;
        if(len % 2 != 0) {
            n2 = best_dist(new_a_2nd, new_b_2nd, new_len+1);
        }
        else {
            n2 = best_dist(new_a_2nd, new_b_2nd, new_len);
        }

        if(n1 < n2 && n1 < error) { 
            return n1;
        }
        if(n2 < n1 && n2 < error) {
            return n2;
        }
        return error;


    }


}



int bf(int num_pts) {
    srand (time(NULL));
    int* x_pts = new int[num_pts];
    int* y_pts = new int[num_pts];

    for(int i = 0; i < num_pts; i++) {
        int x1 = rand()%100;
        int y1 = rand()%100;

        x_pts[i] = x1;
        y_pts[i] = y1;
    }

    double dbest = 1000.0;
    for(int i = 0; i < num_pts; i++) {
        for(int j = i+1; j < num_pts; j++) {
            if(distance(x_pts[i], y_pts[i], x_pts[j], y_pts[j]) < dbest) {
                dbest = distance(x_pts[i], y_pts[i], x_pts[j], y_pts[j]);
            }

        }
    }
    //cout << "Brute Force: " << dbest << "\n";

}

int recur(int num_pts) {
    srand (time(NULL));
    int* x_pts = new int[num_pts];
    int* y_pts = new int[num_pts];

    for(int i = 0; i < num_pts; i++) {
        int x1 = rand()%100;
        int y1 = rand()%100;

        x_pts[i] = x1;
        y_pts[i] = y1;
    }

    for(int i = 0; i < num_pts; i++) {
        int min_x_index = i;
        for(int j = i; j < num_pts; j++) {
            if(x_pts[j] < x_pts[min_x_index]) {
                min_x_index = j;
            }
        }

        int tempx = x_pts[min_x_index];
        int tempy = y_pts[min_x_index];

        x_pts[min_x_index] = x_pts[i];
        y_pts[min_x_index] = y_pts[i];

        x_pts[i] = tempx;
        y_pts[i] = tempy;

    }

    double bd = best_dist(x_pts, y_pts, num_pts);   
    //cout << "Recursive Approach: "<<bd << "\n"; 


    return 0;
}


int main(int argc, char* argv[]) {   

    int* test = new int[9];
    test[0] = 10;
    test[1] = 100;
    test[2] = 200;
    test[3] = 300;
    test[4] = 400;
    test[5] = 500;
    test[6] = 600;
    test[7] = 700;
    test[8] = 750;

    for(int i = 0; i < 9; i++) {
        clock_t start, stop;

        /*start = clock();

        bf(test[i]);

        stop = clock();
        double pass = (double(stop) - double(start)); 
        pass = pass/ CLOCKS_PER_SEC;

        cout << "BF: Time taken for " << test[i] << " Points: " << pass << " seconds. \n";
*/
        start = clock();

        recur(test[i]);

        stop = clock();
        double pass = (double(stop) - double(start)); 
        pass = pass/ CLOCKS_PER_SEC;

        cout << " RECUR: Time taken for " << test[i] << " Points: " << pass << " seconds. \n";
    }
    return 0;
}

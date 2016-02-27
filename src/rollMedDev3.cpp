#include <Rcpp.h>
using namespace Rcpp;
#include <vector>
using namespace std;

class Window { 
private:
    vector<double> currentArray;
    vector<int> order;
    int k, midVal, lowest, highest;
    
    void swapValues(int v1, int v2) {
        currentArray[v1] = currentArray[v1] + currentArray[v2];
        currentArray[v2] = currentArray[v1] - currentArray[v2];
        currentArray[v1] = currentArray[v1] - currentArray[v2];
        order[v1] = order[v1] + order[v2];
        order[v2] = order[v1] - order[v2];
        order[v1] = order[v1] - order[v2];
    }
    
    void sortDown(int j) {
        while (j > 0 && currentArray[j] < currentArray[j-1]) {
            swapValues(j, j - 1);
            j--;
        }
    }
    
    void sortUp(int j) {
        while(j < (k - 1) && currentArray[j] > currentArray[j + 1]) {
            swapValues(j, j + 1);
            j++;
        }
    }

public:
    Window(vector<double> firstK) {
        k = firstK.size();
        midVal = (k - 1) / 2;
        currentArray = firstK;
        order.reserve(k);
        for(int i = 0; i < k; i++) {
            order[i] = i;
        }
        lowest = 0;
        highest = k - 1;
    }
    
    double addValue(double v) {
        int l = 0;
        while(order[l] > lowest) l++;
        currentArray[l] = v;
        order[l] = ++highest;
        lowest++;
        if(l > 0 && v < currentArray[l - 1]) sortDown(l);
        if(l < (k - 1) && v > currentArray[l + 1]) sortUp(l);
        return currentArray[midVal];
    }
    
    double initialSort() {
        for(int i = 0; i < k; i++) {
            sortDown(i);
        }
        return currentArray[midVal];
    }
};

// [[Rcpp::export]]
NumericVector rollingMedian3(NumericVector v, int k) {
    vector<double> firstK (k); 
    NumericVector out(v.size());
    for(int i = 0; i < k; i++) firstK[i] = v[i];
    Window w(firstK);
    int oi = 0;
    out[oi++] = w.initialSort();
    while(oi < ((k+1)/2)) out[oi++] = out[0];
    for(int j = k; j < v.size(); j++) out[oi++] = w.addValue(v[j]);
    double last = out[oi-1];
    while(oi < v.size()) out[oi++] = last;
    return out;
}
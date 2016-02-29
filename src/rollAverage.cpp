#include <Rcpp.h>
using namespace Rcpp;
#include <vector>
using namespace std;

class RollingAveWindow {
private:
    RollingAveWindow();
protected:
    int k, lowest;
    vector<double> currentArray;
    vector<int> order;
    RollingAveWindow(vector<double> firstK) {
        k = firstK.size();
        currentArray = firstK;
        order.reserve(k);
        for(int i = 0; i < k; i++) {
            order[i] = i;
        }
        lowest = 0;
    }
};

class RollingMeanWindow: public RollingAveWindow {
private:
    double sum;
public:
    RollingMeanWindow(vector<double> a) : RollingAveWindow(a) {}
    double initialValue() {
        sum = 0;
        for(int i = 0; i < k; i++) {
            sum += currentArray[i];
        }
        return sum / k;
    }
    double addValue(double v){
        sum += (v - currentArray[lowest]);
        currentArray[lowest] = v;
        if(lowest == (k-1)) {
            lowest = 0;
        } else{
            lowest++;
        }
        return sum / k;
    }
};

class RollingMedianWindow: public RollingAveWindow {
private:
    int midVal, highest;
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
    RollingMedianWindow(vector<double> a) : RollingAveWindow(a) {}
    double initialValue() {
        midVal = (k - 1) / 2;
        highest = k - 1;
        for(int i = 0; i < k; i++) {
            sortDown(i);
        }
        return currentArray[midVal];
    }
    double addValue(double v){
        int l = 0;
        while(order[l] > lowest) l++;
        currentArray[l] = v;
        order[l] = ++highest;
        lowest++;
        if(l > 0 && v < currentArray[l - 1]) sortDown(l);
        if(l < (k - 1) && v > currentArray[l + 1]) sortUp(l);
        return currentArray[midVal];
    }
};



// [[Rcpp::export]]
NumericVector rollingMeanRaw(NumericVector v, int k) {
    vector<double> firstK (k);
    NumericVector out(v.size() - (k-1) ) ;
    for(int i = 0; i < k; i++) firstK[i] = v[i];
    RollingMeanWindow w(firstK);
    int oi = 0;
    out[oi++] = w.initialValue();
    for(int j = k; j < v.size(); j++) out[oi++] = w.addValue(v[j]);
    return out;
}

// [[Rcpp::export]]
NumericVector rollingMedianRaw(NumericVector v, int k) {
    vector<double> firstK (k);
    NumericVector out(v.size() - (k-1));
    for(int i = 0; i < k; i++) firstK[i] = v[i];
    RollingMedianWindow w(firstK);
    int oi = 0;
    out[oi++] = w.initialValue();
    for(int j = k; j < v.size(); j++) out[oi++] = w.addValue(v[j]);
    return out;
}

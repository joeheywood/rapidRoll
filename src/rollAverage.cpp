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
        //midVal = (k - 1) / 2;
        currentArray = firstK;
        order.reserve(k);
        for(int i = 0; i < k; i++) {
            order[i] = i;
        }
        lowest = 0;
    }

    //double addValue(double v);
    //double initialValue();
public:

};


class RollingMeanWindow: public RollingAveWindow {
private:
    double sum;
public:
    RollingMeanWindow(vector<double> a) : RollingAveWindow(a) {}
    double initialValue(); 
    double addValue(double v);
};

class RollingMedianWindow: public RollingAveWindow {
private:
    int midVal, highest;
public:
    RollingMedianWindow(vector<double> a) : RollingAveWindow(a) {}
    double initialValue();
    double addValue(double v);
};



double RollingMeanWindow::initialValue() {
    sum = 0;
    for(int i = 0; i < k; i++) {
        sum += currentArray[i];
    }
    return sum / k;
}

double RollingMeanWindow::addValue(double v) {
    sum += (v - currentArray[lowest]);
    currentArray[lowest] = v;
    if(lowest == (k-1)) {
        lowest = 0;
    } else{
        lowest++;
    }
    return sum / k;
}


// [[Rcpp::export]]
NumericVector rollingMeanRawX(NumericVector v, int k) {
    vector<double> firstK (k);
    NumericVector out(v.size() - (k-1) ) ;
    for(int i = 0; i < k; i++) firstK[i] = v[i];
    RollingMeanWindow w(firstK);
    int oi = 0;
    out[oi++] = w.initialValue();
    for(int j = k; j < v.size(); j++) out[oi++] = w.addValue(v[j]);
    return out;
}

//NumericVector rollingMedianRaw(NumericVector v, int k) {
//    vector<double> firstK (k);
//    NumericVector out(v.size() - (k-1) ) ;
//    for(int i = 0; i < k; i++) firstK[i] = v[i];
//    RollingMedianWindow w(firstK);
//    int oi = 0;
//    out[oi++] = w.initialValue();
//    for(int j = k; j < v.size(); j++) out[oi++] = w.addValue(v[j]);
//    return out;
//}

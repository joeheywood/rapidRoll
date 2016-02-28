

#include <vector>
using namespace std;

#ifndef RollingAveWindow
#define RollingAveWindow

class RollingAveWindow {
protected:
    int k, lowest;
    vector<double> currentArray;
    vector<int> order;

public:
    RollingAveWindow(vector<double> firstK) {
        k = firstK.size();
        //midVal = (k - 1) / 2;
        currentArray = firstK;
        order.reserve(k);
        for(int i = 0; i < k; i++) {
            order[i] = i;
        }
        lowest = 0;
        //highest = k - 1;
    }
};


class RollingMeanWindow: public RollingAveWindow {
private:
    double sum;
public:
    RollingMeanWindow(vector<double> a) : RollingAveWindow(a) {}
};

class RollingMedianWindow: public RollingAveWindow {
private:
    int midVal, highest;
public:
    RollingMedianWindow(vector<double> a) : RollingAveWindow(a) {}
};

#endif

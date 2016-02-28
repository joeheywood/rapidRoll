// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// rollingMedianRaw
NumericVector rollingMedianRaw(NumericVector v, int k);
RcppExport SEXP rapidRoll_rollingMedianRaw(SEXP vSEXP, SEXP kSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< NumericVector >::type v(vSEXP);
    Rcpp::traits::input_parameter< int >::type k(kSEXP);
    __result = Rcpp::wrap(rollingMedianRaw(v, k));
    return __result;
END_RCPP
}

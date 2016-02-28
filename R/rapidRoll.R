################################################################################
## Main functions
################################################################################

rapidRollMean <- function(unrolled, winSize = 3, pad = "NA", keyVals = NULL) {

}


rapidRollMedian <- function(unrolled, winSize = 3, pad = "none", keyVals = NULL) {
    rw <- rollingMedianRaw(unrolled, winSize)
    if(pad == "none") {
        rw <- rw
    } else if(is.numeric(pad)) {
        rw <- c(rep(pad, (k-1)/2), rw, rep(pad, (k-1)/2))
    } else if(pad == "na") {
        rw <- c(rep(NA, (k-1)/2), rw, rep(NA, (k-1)/2))
    } else if(pad == "firstLast") {
        rw <- c(rep(rw[1], (k-1)/2), rw, rep(rw[length(rw)], (k-1)/2))
    }
    if(is.null(keyVals)){
        rw
    } else {
        if(length(keyVals == length(rw))){
            data.frame(key = keyVals, value = rw)
        } else {
            data.frame(key = keyVals, value = rw)
        }

    }
}

# rollingMax, rollingMin..?


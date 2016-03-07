################################################################################
## Main functions
################################################################################

rapidRollMean <- function(unrolled, winSize = 3, pad = "none") {
    rollingAveRaw(unrolled, 3, "mean")
}

rapidRollMedian <- function(unrolled, winSize = 3, pad = "none") {
    rollingAveRaw(unrolled, 3, "median")
}

rapidRollToDF <- function(unrDF, col, rrFun = rapidRollMean, winSize = 3,
                          pad = "none", align = "centre") {
    print(paste0("Col: ", col, " | ", is.numeric(col)))
    newColName <- paste0(ifelse(is.numeric(col), colnames(unrDF)[col], col),
                         "_rolled")
    unrDF[,newColName] <- setPadding(rrFun(unrDF[, col], winSize), pad, align,
                                     winSize)
    unrDF

}

setPadding <- function(x, pad, align, winSize) {
    padSize = (winSize - 1) / 2
    if(pad == "none"){
        x <- c(rep(NA, padSize), x, rep(NA, padSize))
    } else if(is.numeric(pad)) {
        if(length(pad) == 1) pad[2] <- pad[1]
        x <- c(rep(pad[1], padSize), x, rep(pad[2], padSize))
    } else if(pad == "topTail") {
        x <- c(rep(x[1], padSize), x, rep(x[length(x)], padSize))
    }
    x
}


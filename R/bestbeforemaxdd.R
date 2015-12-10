bestbeforemaxdd <- function(x, threshold, dir = 1){
    if (any(is.na(x))) stop(sQuote("x"), " must not be NULL!");
    len <- length(x)
    cret <- .C ("bestbeforemaxdd",
                as.double(x),
                as.int(len),
                as.double(threshold),
                as.int(dir),
                ret = double(len)
                )
    ret <- cret$ret
    ret
}

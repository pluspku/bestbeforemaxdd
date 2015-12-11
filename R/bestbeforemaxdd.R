#' Function to calculate the difference before meet the first max drawdown
#'
#' @useDynLib bestbeforemaxdd
#' @param x data series, should be a vector
#' @param threshold the threshold to determine max drawdown
#' @param long is long or short?
#' @keywords maxdd
#' @export
#' @examples
#' bestbeforemaxdd()

bestbeforemaxdd <- function(x, threshold, long = TRUE){
    if (any(is.na(x))) stop(sQuote("x"), " must not be NULL!");
    len <- length(x)
    cret <- .C ("bestbeforemaxdd",
                as.double(x),
                as.integer(len),
                as.double(threshold),
                as.integer(long),
                ret = integer(len)
                )
    ret <- cret$ret + 1
    ret
}

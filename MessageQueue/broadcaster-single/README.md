# SPSC\_ Using the circular queue

## Performance

* Using sequence consistense memory order everywhere 981ns
* Using sequence acquire-release memory order 480ns
* Using set the head and tail pointer in two side of the queue 451ns

## Note

You have to make sure that the queue is always empty! Or the calculation of performance may be wrong

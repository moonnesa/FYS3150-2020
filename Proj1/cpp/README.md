Project 1.

Main program /cpp/main.cpp

On ubuntu, compiled with g++ test.cpp -o test -DARMA_DONT_USE_WRAPPER -lopenblas -llapack

Called by ./proj1 inputfilename

input.cfg is an example of an input file. The program sets some default values if it doesn't find the correct tags. The input file is commented with #.
  
The input can then be altered depending on the desired configuration, e.g. skip x,u(x) output for runs where you just need the error and time measurements.

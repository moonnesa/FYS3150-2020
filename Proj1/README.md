Project 1.

Main program /cpp/main.cpp
On ubuntu, compiled with g++ -o proj1 main.cpp -DARMA_DONT_USE_WRAPPER -lopenblas -llapack


Called by ./proj1 inputfilename

input.cfg is an example of an input file. The program sets some default values if it doesn't find the correct tags. The input file is commented with #.

Input and output files in respectively data/cfg and data/out, as well as some plots in data/

The results are generated using python/runs_and_plots.py

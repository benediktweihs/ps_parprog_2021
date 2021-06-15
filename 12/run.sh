#!/bin/bash
# if python does not contain all necessary packages run (requires conda):
# conda env create -f ./data/environment.yml
# conda activate environment
echo "--------------------"
echo "Compilaton:"
echo "--------------------"
make
echo "--------------------"
echo "Solve ode with common orbit as analytical solution"
echo "--------------------"
./analytically_stable
echo "--------------------"
echo "Generate gif"
echo "--------------------"
python ./data/plot.py
echo "--------------------"
echo "Run main"
echo "--------------------"

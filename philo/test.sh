#!/bin/bash

clear

echo "# ======================================================================="
echo "# PHILOSOPHERS"
echo "# ======================================================================="

echo
echo "# ERROR OUTPUTS"
echo "# ======================================================================="

echo
echo "./philo humberto doisberto tresberto quatroberto cincoberto"
./philo humberto doisberto tresberto quatroberto cincoberto
echo "./philo 1 2 tresberto 4 5"
./philo 1 2 tresberto 4 5
echo "./philo 1berto 2 3 4"
./philo 1berto 2 3 4
echo "./philo 1 2 3 4 cincoberto"
./philo 1 2 3 4 cincoberto

echo
echo "# SUCCESS OUTPUTS"
echo "# ======================================================================="
echo "./philo 1 2 3 4"
./philo 5 2 3 4

echo
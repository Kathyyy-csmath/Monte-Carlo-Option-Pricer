# Monte-Carlo-Option-Pricer

A C++ project for option pricing with Monte Carlo simulation, enhanced with:

✅ Real historical data from Yahoo Finance (via Python yfinance)

✅ Support for European options (call & put)

✅ Greeks (Delta, Gamma, Vega) estimation via both Black–Scholes closed form and Monte Carlo

✅ Barrier options (Up-and-Out, Up-and-In, Down-and-Out, Down-and-In)

✅ Visualization of simulated asset paths and terminal distributions


📂 Project Structure
#include

Random Number Generator.h
PathSimulator.h
Option.h
MonteCarloPricer.h
Statistics.h
#src

RandomNumberGenerator.cpp
PathSimulator.cpp
Option.cpp
MonteCarloPricer.cpp
Statistics.cpp
main.cpp
#CMakeLists.txt


⚙️ Build & Run
1. Fetch real market data
I use yfinance to download 1-year daily data for AAPL:

📌
This project was built as part of my CV/portfolio to showcase quantitative finance and C++ skills.

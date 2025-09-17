import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os


if os.path.exists("AAPL.csv"):
    print("Using local AAPL.csv")
    data = pd.read_csv("AAPL.csv")
else:
    import yfinance as yf
    print("Downloading data from Yahoo Finance...")
    ticker = "AAPL"
    data = yf.download(ticker, period="1y")
    data.to_csv("AAPL.csv")


if "Adj Close" in data.columns:
    prices = data["Adj Close"].dropna().values
else:
    prices = data["Close"].dropna().values

print("Prices length:", len(prices))


returns = np.diff(np.log(prices))
sigma = np.std(returns) * np.sqrt(252)

if np.isnan(sigma) or sigma <= 0:
    print("⚠️ Sigma invalid, fallback to 0.2")
    sigma = 0.2

print("Final Sigma:", sigma)


def monte_carlo_option_price(S0, K, r, sigma, T, n_simulations, steps=100):
    dt = T / steps
    prices = []
    for _ in range(n_simulations):
        S = S0
        for _ in range(steps):
            z = np.random.normal()
            S *= np.exp((r - 0.5 * sigma**2) * dt + sigma * np.sqrt(dt) * z)
        prices.append(max(S - K, 0))
    return np.exp(-r * T) * np.mean(prices)

def plot_convergence():
    S0, K, r, T = prices[-1], prices[-1], 0.05, 1.0
    n_paths = [100, 500, 1000, 5000, 10000, 20000]
    mc_prices = []

    for n in n_paths:
        price = monte_carlo_option_price(S0, K, r, sigma, T, n)
        mc_prices.append(price)

    plt.figure(figsize=(8, 5), dpi=120)
    plt.plot(n_paths, mc_prices, marker="o", linestyle="-", color="blue", label="MC Price")
    plt.xlabel("Number of Monte Carlo Simulations", fontsize=12)
    plt.ylabel("Option Price", fontsize=12)
    plt.title(f"Monte Carlo Convergence (AAPL, σ={sigma:.2f})", fontsize=14)
    plt.legend()
    plt.grid(True, linestyle="--", alpha=0.6)
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    plot_convergence()
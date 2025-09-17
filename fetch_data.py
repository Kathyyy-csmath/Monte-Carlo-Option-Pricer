import yfinance as yf

ticker = yf.Ticker("AAPL")
data = ticker.history(period="1y")
data.to_csv("AAPL.csv")
print("Saved AAPL.csv")
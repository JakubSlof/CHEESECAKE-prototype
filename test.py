import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# Data
y = np.array([40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140])
x = np.array([203, 239, 264, 283, 295, 305, 314, 319, 325, 329, 335])

# Definice exponenciální funkce
def exponential_func(x, a, b, c):
    return a * np.exp(b * x) + c

# Proložení křivky
params, covariance = curve_fit(exponential_func, x, y, p0=[1, 0.01, 0])
a, b, c = params

# Vytvoření hodnot pro hladkou křivku
x_fit = np.linspace(min(x), max(x), 300)
y_fit = exponential_func(x_fit, a, b, c)

# Vytvoření grafu
plt.figure(figsize=(12, 8))
plt.scatter(x, y, color='blue', s=80, label='Naměřená data', zorder=5)
plt.plot(x_fit, y_fit, color='red', linewidth=3, label='Exponenciální fit')

# Popisky os a titulky
plt.xlabel('Hodnoty x', fontsize=14)
plt.ylabel('Hodnoty y', fontsize=14)
plt.title('Exponenciální proložení dat', fontsize=16, fontweight='bold')

# Mřížka a legenda
plt.grid(True, alpha=0.3, linestyle='--')
plt.legend(fontsize=12)

# Zobrazení rovnice v grafu
equation_text = f'$y = {a:.2e} \\cdot e^{{{b:.6f} \\cdot x}} + {c:.2f}$'
plt.annotate(equation_text, xy=(0.05, 0.8), xycoords='axes fraction', 
            fontsize=14, bbox=dict(boxstyle="round,pad=0.5", fc="lightyellow", alpha=0.8))

# Upravíme vzhled grafu
plt.xlim(min(x)-10, max(x)+10)
plt.ylim(min(y)-10, max(y)+10)

# Zvýrazníme osy
plt.axhline(y=0, color='k', linestyle='-', alpha=0.3)
plt.axvline(x=0, color='k', linestyle='-', alpha=0.3)

plt.tight_layout()
plt.show()

# Výpis předpisu funkce
print(f"Předpis exponenciální funkce:")
print(f"y = {a:.6e} * e^({b:.8f} * x) + {c:.6f}")
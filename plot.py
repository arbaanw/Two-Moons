import matplotlib.pyplot as plt
import numpy as np

plt.style.use('_mpl-gallery')

# make data
t = np.linspace(0, np.pi, 100)
x = np.cos(t)
y = np.sin(t)
x2 = 1 - np.cos(t)
y2 = -1*np.sin(t) + 0.5

# plot
fig, ax = plt.subplots()

ax.plot(x, y, linewidth=2.0)
ax.plot(x2, y2, 'x', markeredgewidth=2)

plt.show()

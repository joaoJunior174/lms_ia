# import matplotlib as mpl
# mpl.use('Agg')
# import matplotlib.pyplot as plt
# from random import randint
# import numpy as np
# from mpl_toolkits import mplot3d

#alpswater
# Create the vectors X and Y
# x = np.array(range(50))
# y1 = x*1.90178 + 155.296;
# y2 = x*1.90101 + 155.381;
# y3 = -0.0223769*x**2 + x*3.0476 + 140.827;

# plt.scatter([20.79,20.79,22.4,22.67,23.15,23.35,23.89,
# 23.99,
# 24.02,
# 24.01,
# 25.14,
# 26.57,
# 28.49,
# 27.76,
# 29.04,
# 29.88,
# 30.06], [194.5,
# 194.3,
# 197.9,
# 198.4,
# 199.4,
# 199.9,
# 200.9,
# 201.1,
# 201.4,
# 201.3,
# 203.6,
# 204.6,
# 209.5,
# 208.6,
# 210.7,
# 211.9,
# 212.2])

# plt.title('alpswater')
# plt.xlim(20,31)
# plt.ylim(194,213)

# plt.plot(x,y1,label='normal')
# plt.plot(x,y2,label='weighted')
# plt.plot(x,y3,label='quadratic')

# plt.xlabel('x axis')
# plt.ylabel('y axis')

# plt.grid(alpha=.1,linestyle='--')

# plt.legend()
  
# plt.savefig('alpswater.png')

#US-Census
# x = np.array(range(2010))
# y1 = x*2.0253 - 3783.95;
# y2 = x*2.00994- 3753.89;
# y3 = 0.00949051*x**2 - x*34.9877 + 32294.2;

# plt.scatter([1900,
# 1910,
# 1920,
# 1930,
# 1940,
# 1950,
# 1960,
# 1970,
# 1980,
# 1990,
# 2000
# ], [75.995,
# 91.972,
# 105.711,
# 123.203,
# 131.669,
# 150.697,
# 179.323,
# 203.212,
# 226.505,
# 249.633,
# 281.422
# ])


# Create the plot
# plt.plot(x,y1,label='normal')
# plt.plot(x,y2,label='weighted')
# plt.plot(x,y3,label='quadratic')

# Add a title
# plt.title('US-Census')

# Add X and y Label
# plt.xlabel('x axis')
# plt.ylabel('y axis')

# plt.xlim(1890,2010)
# plt.ylim(60,300)

# Add a grid
# plt.grid(alpha=.1,linestyle='--')

# plt.legend()
  
# plt.savefig('US-Census.png')

# def f(x, y):
#     return 1.28348*y + 4.03689*x + 37.3792


# x = np.linspace(0, 4, 10)
# y = np.linspace(0, 20, 10)

# X, Y = np.meshgrid(x, y)
# Z = f(X, Y)

# fig = plt.figure()
# ax = plt.axes(projection='3d')
# ax.contour3D(X, Y, Z, 50, cmap='viridis')
# ax.set_xlabel('x')
# ax.set_ylabel('y')
# ax.set_zlabel('z');
# plt.savefig('books_attend_grade.png')
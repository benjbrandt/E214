import numpy as np
import scipy as sp
import matplotlib as mpl
mpl.use("pdf")
from matplotlib import pyplot as plt 
from uncertainties import ufloat
import uncertainties.unumpy as unp
from scipy.optimize import curve_fit
from scipy import integrate
import math



x,y=np.genfromtxt('Test.txt', unpack=True)


def f(x, a, b):
    return  a*x+b

params, covariance_matrix = curve_fit(f, x, y)
errors = np.sqrt(np.diag(covariance_matrix))
print('a =', ufloat(params[0],errors[0]))
print('b =', ufloat(params[1],errors[1]))
x_plot = np.linspace(0,10,num= 10000)

plt.plot(x_plot,f(x_plot,params[0],params[1]),'r',label='Fit')
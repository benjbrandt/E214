from matplotlib import pyplot as plt 
import numpy as np 
from scipy.optimize import curve_fit

# range 30-55
m = [75,78,79,80,81,82,85]
pt_half = [40.17, 41.77, 42.20, 42.77, 43.44, 43.78, 45.47]
pt_half_err = [0.05, 0.05 ,0.05 ,0.05 ,0.05, 0.05, 0.06]


def f(x,a,b):
    return a * x + b

popt, pcov = curve_fit(f,pt_half,m)
t = np.linspace(40,47,1000)
plt.plot(t, f(t,*popt), 'r', label='fit_30-55')

plt.errorbar(pt_half, m, xerr=pt_half_err,  fmt='o', markersize=2, color='k', capsize=2, label='Range 30-55')

#print(popt)
#print(pcov)

m_real = popt[0] * 43.35 + popt[1]
print('M_w_30-55 =',m_real)
plt.xlabel(r'$p_T$ [GeV]')
plt.ylabel(r'$M_W$ [GeV]')
plt.grid()
plt.legend()

m_z = popt[0] * 48.97 + popt[1]
print('m_z_30-55=', m_z)

# range (27 to 55)
pt_27_55 = [40.29,41.84,42.31,42.88,43.54,43.89,45.49]
pt_err_27_55 = [0.05,0.05,0.04,0.05,0.06,0.06,0.06]
plt.errorbar(pt_27_55, m, xerr=pt_err_27_55,  fmt='o', markersize=2, color='k', capsize=2, label='Range 27-55')

popt_27_55, pcov_27_55 = curve_fit(f,pt_27_55,m)

plt.plot(t, f(t,*popt_27_55), 'r', label='fit_27-55')

mw_27_55 = popt_27_55[0] * 43.45 + popt_27_55[1]
mz_27_55 = popt_27_55[0] * 49.07 + popt_27_55[1]

print('')
print('mw_27_55 =', mw_27_55)
print('mz_27_55 =', mz_27_55)


# range (32 to 55)
pt_32_55 = [40.14,41.76,42.14,42.7,43.38,43.72,45.41]
pt_err_32_55 = [0.05,0.08,0.06,0.05,0.06,0.05,0.05]
plt.errorbar(pt_32_55, m, xerr=pt_err_32_55,  fmt='o', markersize=2, color='k', capsize=2, label='Range 32-55')

popt_32_55, pcov_32_55 = curve_fit(f,pt_32_55,m)

plt.plot(t, f(t,*popt_32_55), 'r', label='fit_32-55')

mw_32_55 = popt_32_55[0] * 43.24 + popt_32_55[1]
mz_32_55 = popt_32_55[0] * 48.95 + popt_32_55[1]

print('')
print('mw_32_55 =', mw_32_55)
print('mz_32_55 =', mz_32_55)


plt.savefig('linear_fit.pdf')
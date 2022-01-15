import math
import sympy as sp

m = 5 * (10**(-5))  # [kg/s]
Stk_50 = 0.49
Width = 0.00056  # [m]
N_n = 1
P_in = 101325  # [Pa]
rho_in = 1.2  # [kg/m^3]
rho_particle = 1000  # [kg/m^3]
gamma = 1.4
Mass = 28.97  # [kg/kmol]
R_u = 8.314  # [kJ/kmol*K]
T_in = 300  # [K]
d_p = 130 * (10 ** (-9))  # [m]

# Stage 1

Area = 3.14 * (Width**2) / 4  # [m^2]
P_out = 0  # [Pa]
Err = 1


# Stage 2

P_out = P_out + 1  # [Pa]

# Cubic Eq. Solver

a = ((m) / (rho_in * Area * N_n)) * ((P_in) / (P_out)) * (0.0016593)
b = 1
c = - ((m) / (rho_in * Area * N_n)) * ((P_in) / (P_out))

   
V_1 = ((-b) + (((b ** 2) - (4 * a * c)) ** (0.5))) / (2 * (a))  # [m/s]

# Stage 3

rho_out = (rho_in) * (P_out/P_in) ** (1/1.4)  # [kg/m^3]

V_2 = (2 * (P_in-P_out) / (rho_out)) ** (0.5)  # [m/s]

# Stage 4

Err = abs(V_1-V_2)

# Stage 5

V_out = V_1
c_p = 1.0045

T_out = (T_in - (((V_out) ** (2)) / ((2) * (c_p))))
mu = 1.8 * (10 ** (-5)) * ((T_out / T_in) ** (3 / 2)) * (T_in + 120/T_out + 120)

# Stage 6

C_c = 1 + ((1 / (1000 * P_out * d_p)) * (15.6 + 7 * math.exp(-59 * P_out * d_p)))
d_50 = math.sqrt((9 * mu * Width * Stk_50) / (rho_particle * V_out * C_c))  # [m]

# Stage 7

print("d_50 = %s m" %d_50)
print("P_out = %s Pa" %P_out)
print("V_nozzle = %s m/s" %V_out)
print("T_nozzle = %s K" %T_out)
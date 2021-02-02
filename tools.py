from control import tf, pade
from numpy import arctan, deg2rad, random, rad2deg, sqrt, tan


def angle_of_attack(x):
    aoa = rad2deg(arctan(x[2] / x[0]))
    return aoa


def angle_of_sideslip(x):
    v = sqrt(x[0] ** 2 + x[1] ** 2 + x[2] ** 2)
    aos = rad2deg(arctan(x[1] / v))
    return aos


def dynamic_pressure(rho, x):
    v = speed(x)
    q = 0.5 * rho * v ** 2
    return q


def flight_path_angle(x):
    theta = rad2deg(x[4])
    alpha = angle_of_attack(x)
    gamma = theta - alpha
    return gamma


def lead_lag(t_lead, t_lag):
    comp = tf([t_lead, 1], [t_lag, 1])
    return comp


def pade_model(tau, n=1):
    approx = pade(tau, n)
    approx = tf(approx[0], approx[1])
    return approx


def speed(x):
    v = sqrt(x[0]**2+x[1]**2+x[2]**2)
    return v


def uvw(v, alpha, beta):
    vb = v * tan(deg2rad(beta))
    w_u = tan(deg2rad(alpha))
    ub = sqrt((v**2 - vb**2) / (1 + w_u**2))
    wb = w_u * ub
    return [ub, vb, wb]


def unit_noise():
    noise = (1 - 2 * random.rand())
    return noise

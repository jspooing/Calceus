import random

def L_testcase():
    L_p1 = random.randrange(40, 50)+random.random()
    L_p2 = random.randrange(40, 60)+random.random()
    L_p3 = random.randrange(40, 60)+random.random()
    L_p4 = random.randrange(40, 60)+random.random()
    L_p5 = random.randrange(50, 70)+random.random()

    L_press=[L_p1, L_p2, L_p3, L_p4, L_p5]

    return L_press

def R_testcase():

    R_p1 = random.randrange(40, 50)+random.random()
    R_p2 = random.randrange(40, 60)+random.random()
    R_p3 = random.randrange(40, 60)+random.random()
    R_p4 = random.randrange(40, 60)+random.random()
    R_p5 = random.randrange(50, 70)+random.random()

    R_press = [R_p1, R_p2, R_p3, R_p4, R_p5]

    return R_press

def gyro():
    degree = random.randrange(-25, 40)+random.random()

    return degree

def accel():
    w_speed = random.randrange(0, 2) + random.random()

    return w_speed

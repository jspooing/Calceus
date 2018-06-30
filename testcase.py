import random

def L_testcase():
    # 왼발 압력점 테스트
    L_p1 = random.randrange(40,50)+random.random()
    L_p2 = random.randrange(40,60)+random.random()
    L_p3 = random.randrange(40,60)+random.random()
    L_p4 = random.randrange(40, 60)+random.random()
    L_p5 = random.randrange(50, 70)+random.random()

    L_press=[L_p1, L_p2, L_p3, L_p4, L_p5]

    return L_press

def R_testcase():

    # 오른발 압력점 테스트
    R_p1 = random.randrange(40, 50)+random.random()
    R_p2 = random.randrange(40, 60)+random.random()
    R_p3 = random.randrange(40, 60)+random.random()
    R_p4 = random.randrange(40, 60)+random.random()
    R_p5 = random.randrange(50, 70)+random.random()

    R_press = [R_p1, R_p2, R_p3, R_p4, R_p5]

    return R_press

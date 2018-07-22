import matplotlib
matplotlib.use('Agg')
from testcase import L_testcase as lt
from testcase import R_testcase as rt
import numpy as np
import matplotlib.pyplot as plt
from testcase import gyro, accel

def run():
    loc_LFlist = []
    loc_RFlist = []
    tmp_l = [0,0,0,0,0]
    tmp_r = [0,0,0,0,0]
    tstIndex = 10

    for i in range(1, tstIndex):
        loc_LFlist.append(lt())
        loc_RFlist.append(rt())

    try:
        for i in range(0, 5):
            for j in range(0, len(loc_LFlist)):
                tmp_l[i]+=loc_LFlist[j][i]
                tmp_r[i]+=loc_RFlist[j][i]
    except:
        pass


    print("=======================")
    print("Success to analysis.")
    print("=======================")

    for i in range(0, len(tmp_l)):
        tmp_l[i]/=tstIndex
        tmp_r[i]/=tstIndex


    out_l = []
    out_r = []

    for tmp_ls in range(0, len(tmp_l)):
        out_l.append(int(tmp_l[tmp_ls]))
    for tmp_rs in range(0, len(tmp_r)):
        out_r.append(int(tmp_r[tmp_rs]))

    f = open('value.txt', 'w')
    f.write(' '.join(str(out_l)))
    f.write(' '.join(str(out_r)))
    f.close()

    return tmp_l+tmp_r

def visualize(pressure):
    type=['LF1', 'LF2', 'LF3', 'LF4', 'LF5',
          'RF1', 'RF2', 'RF3', 'RL4', 'RF5']
    data=pressure

    fig = plt.figure(figsize=(8, 5))
    ax = fig.add_subplot(111)

    pos = np.arange(10)
    rects = plt.bar(pos, data, align='center', width=0.5, color='#819FF7')
    plt.xticks(pos, type)

    for i, rect in enumerate(rects):
        ax.text(rect.get_x() + rect.get_width() / 2.0, 1.01 * rect.get_height(), str(int(data[i])) + '%',
                ha='center')

    plt.ylabel('Pressure Value')
    plt.xlabel('The pressure of Foot')
    plt.savefig('/home/chc/web/fserver/myapp/static/result.png')

def check_habit():
    data=gyro()

    if data < -19.9:
        res = 'High Arch Foot type.'
        return res

    elif -19.9<=data<31.93:
        res = 'Normal Arch Foot type.'
        return res

    elif data >= 31.93:
        res = 'Flat Foot type.'
        return res

def check_speed():    
    data = accel()
    if 0.5<data<1.3:
        return 'You have a Normal walking speed'
    elif 0<data<=0.5:
        return 'You have a faster walking speed than average'
    elif data>=1.3:
        return 'You have a slower walking speed than average'

def contents(data):
    info1 = '''Your walk test is as follows. '''+'\n'
    info=""
    for i in range(0, 5):
        info+=("Left Foot P"+str(i)+" : "+str(int(data[i]))+'\n')
    for i in range(0, 5):
        info+=("Right Foot P"+str(i)+" : "+str(int(data[i+5]))+'\n')

    
    varOfLfoot = data[0] +data[1] +data[2] +data[3] +data[4]
    varOfRfoot = data[5] +data[6] +data[7] +data[8] +data[9]

    if varOfRfoot > varOfLfoot:
        bal = 'Also, The weight is biased to the right foot.'
    else:
        bal = 'Also, The weight is biased to the left foot.'


    sub0 = check_speed()
    sub1 = ', and the type of foot is '+check_habit()+'\n'
    sub2 = 'Now, You can get your own fit shoes!'+'\n'

    result=info1+'\n'+info+'\n'+sub0+sub1+bal+'\n'+sub2

    out_text=open('/home/chc/calceus/datastream/content.txt', 'w')
    out_text.write(result)
    out_text.close()

def execute(data):
    visualize(data)
    contents(data)

# Execute
execute(run())

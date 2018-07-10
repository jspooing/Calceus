import matplotlib
matplotlib.use('Agg')
from testcase import L_testcase as lt
from testcase import R_testcase as rt
import numpy as np
import matplotlib.pyplot as plt

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

    for i in range(0, len(tmp_l)):
        tmp_l[i]/=tstIndex
        tmp_r[i]/=tstIndex


    out_l = []
    out_r = []

    for tmp_ls in range(0, len(tmp_l)):
        out_l.append(int(tmp_l[tmp_ls]))
    for tmp_rs in range(0, len(tmp_r)):
        out_r.append(int(tmp_r[tmp_rs]))

    print(out_l + out_r)

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
    plt.savefig('/home/chc/calceus/web/fserver/myapp/static/result.png')


def contents(data):
    info1 = '''Your result ~~~ '''+'\n'
    info=""
    for i in range(0, 5):
        info+=("Left Foot P"+str(i)+" : "+str(int(data[i]))+'\n')
    for i in range(0, 5):
        info+=("Right Foot P"+str(i)+" : "+str(int(data[i+5]))+'\n')

    result=info1+info
    out_text=open('/home/chc/calceus/datastream/content.txt', 'w')
    out_text.write(result)
    out_text.close()

def execute(data):
	visualize(data)
	contents(data)

# Execute
execute(run())

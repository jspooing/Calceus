from testcase import L_testcase as lt
from testcase import R_testcase as rt
import matplotlib.pyplot as plt
import numpy as np

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

    print(loc_LFlist)
    print(loc_RFlist)

    print("=======================")

    for i in range(0, len(tmp_l)):
        tmp_l[i]/=tstIndex
        tmp_r[i]/=tstIndex

    print("Average of LFoot : ", tmp_l)
    print("Average of RFoot : ", tmp_r)

    return tmp_l+tmp_r

def visualize(pressure):
    type=['LFoot1', 'LFoot2', 'LFoot3', 'LFoot4', 'LFoot5',
          'RFoot1', 'RFoot2', 'RFoot3', 'RLFoot4', 'RFoot5']
    data=pressure

    fig = plt.figure(figsize=(8, 4))
    ax = fig.add_subplot(111)

    pos = np.arange(10)
    rects = plt.bar(pos, data, align='center', width=0.5)
    plt.xticks(pos, type)

    for i, rect in enumerate(rects):
        ax.text(rect.get_x() + rect.get_width() / 2.0, 0.95 * rect.get_height(), str(int(data[i])) + '%',
                ha='center')

    plt.ylabel('Pressure Value')
    plt.xlabel('The pressure of Foot')
    plt.show()
    plt.savefig('result.png')


visualize(run())

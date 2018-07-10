import matplotlib.pyplot as plt
import numpy as np

def run():
    # File Input
    streamf=open('/home/chc/calceus/datastream/stream.txt', 'r')
    data = [int(num) for num in streamf.read().split()]
    streamf.close()

    #print(len(data))
    #print(data)

    # The List as a stack for press value
    tmp_l = [0, 0, 0, 0, 0]
    tmp_r = [0, 0, 0, 0, 0]
    IndexOfData = len(data) / 10

    for j in range(0, int(len(data)/10)):
        for i in range(0, 5):
            tmp_l[i]+=data[i+(j*10)]
            tmp_r[i]+=data[i+((j*10)+5)]

    #print(tmp_l, tmp_r)
    print("=======================")

    for i in range(0, len(tmp_l)):
        tmp_l[i]/=IndexOfData
        tmp_r[i]/=IndexOfData

    #print("Average of LFoot : ", tmp_l)
    #print("Average of RFoot : ", tmp_r)

    out_l=[]
    out_r=[]

    for tmp_ls in range(0,len(tmp_l)):
       out_l.append(int(tmp_l[tmp_ls]))
    for tmp_rs in range(0,len(tmp_r)):
       out_r.append(int(tmp_r[tmp_rs]))

    print(out_l+out_r)

    f=open('/home/chc/calceus/datastream/value.txt', 'w')
    f.write(' '.join(str(out_l)))
    f.write(' '.join(str(out_r)))
    f.close()

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
    plt.savefig('result.png')

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


# Execute
visualize(run())
contents(run())

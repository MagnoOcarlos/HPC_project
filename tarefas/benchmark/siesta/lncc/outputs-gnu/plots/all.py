import matplotlib.pyplot as plt 
import numpy as np 
import pandas as pd 


df_I = pd.read_csv("../optI_time.txt", header=None)
df_II = pd.read_csv("../optII_time.txt", header=None)

df_nopt = pd.read_csv("../nopt_time.txt", header=None)

fig = plt.figure(figsize=(8,6))

x=np.arange(0,4,1)


axes = fig.add_axes([0.1,0.1,0.8,0.8])
axes2 = fig.add_axes([0.4,0.5,0.4,0.3])

axes.plot(x,df_I,color='y', ls='-.', marker='o',markersize=8, label="OPT I")
axes.plot(x,df_II,color='b', ls='-.', marker='o',markersize=8, label="OPT II")
axes.plot(x,df_nopt, color='r', ls='-.', marker='o', markersize=8, label="No OPT")
axes.set_xlabel('OX')
axes.set_ylabel("Time (s)")
axes.set_title("All Flag's Set ")
axes.legend(loc='lower left')

axes.arrow(x=2, y=570, dx=0, dy=100, width=.05, facecolor='red', length_includes_head=True, head_width=0.2, head_length=23)
axes.set_xticks(x)


axes2.set_xticks([0,1,2,3])
axes2.set_xlim([0.80,3.3])
axes2.set_ylim([375,550])
axes2.grid(True,which="both",ls="-")
axes2.plot(x,df_nopt, color='r', ls='-.', marker='o', markersize=8)
axes2.plot(x,df_I,color='y', ls='-.', marker='o',markersize=8, label="OPT I")
axes2.plot(x,df_II,color='b', ls='-.', marker='o',markersize=8, label="OPT II")
axes2.set_xlabel('OX')
axes2.set_ylabel("Time (s)")
axes2.set_title("Zoom ")



plt.savefig("all.pdf",dpi=300)

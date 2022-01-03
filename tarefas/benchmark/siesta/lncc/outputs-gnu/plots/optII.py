import matplotlib.pyplot as plt 
import numpy as np 
import pandas as pd 


df = pd.read_csv("../optII_time.txt", header=None)
df_nopt = pd.read_csv("../nopt_time.txt", header=None)

fig = plt.figure(figsize=(8,6))

x=np.arange(0,4,1)


axes = fig.add_axes([0.1,0.1,0.8,0.8])

axes.plot(x,df,color='b', ls='-.', marker='o',markersize=8, label ="OPT II")
axes.set_xlabel('OX')
axes.set_ylabel("Time (s)")
axes.set_title("Benchmark Time versus OX flags with opmization (OPT II) ")


axes.plot(x,df_nopt, color='r', ls='-.', marker='o', markersize=8, label="No OPT")
axes.legend(loc="lower left")
axes.set_xticks(x)


plt.savefig("optII.pdf",dpi=300)

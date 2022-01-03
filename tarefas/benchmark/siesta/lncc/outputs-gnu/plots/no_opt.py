import matplotlib.pyplot as plt 
import numpy as np 
import pandas as pd 


df =pd.read_csv("../nopt_time.txt", header=None)

fig = plt.figure(figsize=(8,6))

x=np.arange(0,4,1)


axes= fig.add_axes([0.1,0.1,0.8,0.8])


axes.plot(x,df,color='r', ls='-.', marker='o',markersize=8)
axes.set_xlabel('OX')
axes.set_ylabel("Time (s)")
axes.set_title("Benchmark Time versus OX flags without any opmization")
axes.set_xticks(x)
plt.savefig("no_opt.pdf",dpi=300)

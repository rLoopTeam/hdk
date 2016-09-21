import plotly
from plotly.graph_objs import Scatter, Layout
import pandas as pd
import numpy as np
import sys

if len(sys.argv) == 1:
  print("please enter file to plot")
  sys.exit()

df = pd.read_csv(sys.argv[1],error_bad_lines=False)
df.head()

plotly.offline.plot({
    "data": [Scatter(y=df["Time"],name='Time')
    		,Scatter(y=df["Yaw"],name='Yaw')
    		,Scatter(y=df["RPM"],name='RPM')
            ,Scatter(y=df["Laser1"],name='Laser1')
            ,Scatter(y=df["Laser2"],name='Laser2')
            ,Scatter(y=df["Laser3"],name='Laser3')
            ],
    "layout": Layout(title="RPM Incrementing")
})
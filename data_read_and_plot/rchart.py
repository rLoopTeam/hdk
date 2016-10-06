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
    "data": [
             Scatter(y=df["Laser1mm"],name='Laser1mm')
            ,Scatter(y=df["Laser2mm"],name='Laser2mm')
            ,Scatter(y=df["Laser3mm"],name='Laser3mm')
            ,Scatter(y=df["Ritch"],name='Ritch')
            ,Scatter(y=df["Roll"],name='Roll')
            ,Scatter(y=df["PWM"],name='PWM')
            ],
    "layout": Layout(title="RPM Incrementing")
})
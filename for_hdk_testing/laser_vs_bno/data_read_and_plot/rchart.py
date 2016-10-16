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
             Scatter(y=df["BNO_Pitch"],name='BNO_Pitch')
            ,Scatter(y=df["BNO_Roll"],name='BNO_Roll')
            ,Scatter(y=df["Laser_Pitch"],name='Laser_Pitch')
            ,Scatter(y=df["Laser_Roll"],name='Laser_Roll')
            ],
    "layout": Layout(title="Comparison of BNO055 and Laser Orientation")
})
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
    "data": [Scatter(y=df["X"],name='X')
            ,Scatter(y=df["Y"],name='Y')
            ,Scatter(y=df["Z"],name='Z')
            ],
    "layout": Layout(title="Accelerometer")
})
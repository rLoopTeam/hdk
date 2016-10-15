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
             Scatter(y=df["Target_Height"],name='Target_Height')
            ,Scatter(y=df["Laser_Pin1"],name='Laser_Pin1')
            ,Scatter(y=df["Laser_Pin2"],name='Laser_Pin2')
            ,Scatter(y=df["Laser_Pin3"],name='Laser_Pin3')
            ,Scatter(y=df["H1_Height"],name='H1_Height')
            ,Scatter(y=df["H2_Height"],name='H2_Height')
            ,Scatter(y=df["H3_Height"],name='H3_Height')
            ,Scatter(y=df["H4_Height"],name='H4_Height')
            ,Scatter(y=df["H1_PWM"],name='H1_PWM')
            ,Scatter(y=df["H2_PWM"],name='H2_PWM')
            ,Scatter(y=df["H3_PWM"],name='H3_PWM')
            ,Scatter(y=df["H4_PWM"],name='H4_PWM')
            ,Scatter(y=df["H1_Adjusted_PWM"],name='H1_Adjusted_PWM')
            ,Scatter(y=df["H2_Adjusted_PWM"],name='H2_Adjusted_PWM')
            ,Scatter(y=df["H3_Adjusted_PWM"],name='H3_Adjusted_PWM')
            ,Scatter(y=df["H4_Adjusted_PWM"],name='H4_Adjusted_PWM')
            ],
    "layout": Layout(title="RPM Incrementing")
})

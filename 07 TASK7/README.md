# TASK7 - Writeup

## Description

![Alt text](img/1.png)

## Solution

For this task we are provided with `Music.wav` file ,, the first thing i did is analyzing the the file in `Sonic Visualizer`
and we got our first half of the flag `Securinets{S0m3_4udi0_g4m3s`

![Alt text](img/2.png)

while looking for the other half of i discovered a hidden morse code inside the file ,, so i combined `sox` and `multimon-ng` to decode the data and get the other half `_H4V3_FUN}`

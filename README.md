# Smart-Calendar-Clock:open_mouth:

This project is one part of Open-Innovation-1(开放性创新实践) for Chongxin Collage(崇新学堂), School of Information Science and Engineering, Shandong university. I'm happy to provide my solution on how to establish and create a smart bluetooth calendar based on STC89C52 single-chip.

It is a simple but meaningful system design project about sensors, single-chip and IOT. If you are interested, please refer to [report.pdf](https://github.com/genglinWang/Smart-Calendar-Clock/blob/main/Report.pdf) for more details, and feel free to contact me, discuss about the project and pick faults:dizzy_face:.

## System Overview
<img decoding="async" src="https://github.com/genglinWang/Smart-Calendar-Clock/blob/main/docs/img/demo.jpg" width="60%">

## Demo: Displaying time, temperature and humidity
<img decoding="async" src="https://github.com/genglinWang/Smart-Calendar-Clock/blob/main/docs/img/demo1.jpg" width="60%">

# To-do list

## Basic
- [x] Display Current year, month, day, hour, minute and second 
- [x] Set year, month, day, hour, minute, second via button matrix
- [x] Set and display AM and PM
- [x] Display Chinese lunar year, month, day and Chinese 24 solar terms
- [x] Set alarm clock time and alarm clock music
- [x] Detect and display temperature and humidity
## Advanced
- [x] Select alarm clock music (using TF card to store music data)
- [x] Mobile phones connect to the system through Bluetooth, and APP can complete the basic settings above
- [x] Get online weather forecast by mobile phone APP, then transmit and display the weather on LCD
- [x] Fire detection and alarm via text message

# Hardware

## Sensors and Modules
* DHT11: Temperature and humidity
* MQ-2: Smoke concentration
* JQ8900-16P: Music player
* LCD12864: Liquid Crystal Display
* TTS: Text-to-speech
* HC-05: Bluetooth

## Schematic
<img decoding="async" src="https://github.com/genglinWang/Smart-Calendar-Clock/blob/main/docs/img/Schematic.jpg" width="70%">
The schematic is designed by https://lceda.cn/. It can help developers find the proper schematics and corresponding PCB Packages of their favourite sensors and modules.

My schematic was selected and shown in the teaching PowerPoint of Open-Innovation-1 in 2023 Spring.:relieved::heart:

## PCB Layout
<img decoding="async" src="https://github.com/genglinWang/Smart-Calendar-Clock/blob/main/docs/img/PCBup.jpg" width="70%">
<img decoding="async" src="https://github.com/genglinWang/Smart-Calendar-Clock/blob/main/docs/img/PCBdown.jpg" width="70%">
All PCB layouts are developped by Altium-Desinger.

# Software
You can refer to [src](https://github.com/genglinWang/Smart-Calendar-Clock/tree/main/src) for drivers of sensors and modules. All the source code is developped by keil.

# APP
You can refer to [Appinventor](https://github.com/genglinWang/Smart-Calendar-Clock/tree/main/Appinventor) for .aia file in App inventor, which is a graphic app programming website.


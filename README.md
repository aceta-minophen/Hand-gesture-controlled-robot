# Makeshift Gimbal Project

A small robot which works by monitoring the tilt of hands and moves as you want it to. It has applications in controlling quadcopters the same way as UGVs for security and surveillance purposes, along with medical applications which involves easy control and handling of wheelchairs.

![image](https://user-images.githubusercontent.com/87569188/150358096-27945690-cfa7-4990-a9bd-7f27bb25a14a.png)


> A short documentation for this can be found in the [Electronic Wings Website](https://www.electronicwings.com/users/SukriteeSharma/projects/1763/hand-gesture-controlled-robot). It was built for a competition conducted by Electroni Wings along with Mouser Electronics in the month of December, _2021_.


# Project Architecture 📝
This project works in **3 main parts**: 

1. **Hand Module**: Retrieves and records the data of the tilt of the hand.
2. **Communication Module**: Transmits data from the hand module and receives it on the 2WD module.
3. **2WD Module**: Interprets the received data from the hand module and acts on it to change the speed and direction of the 2 wheeler robot.

```
**MPU6050** --------------I2C Comm--------------> **Arduino1 (Hand module)** --------------SPI Comm--------------> **NodeMCU1 (Hand module)** --------------Wi-Fi--------------> **NodeMCU2 (2WD module)** --------------I2C Comm --------------> **Arduino2 (2WD module)** --------------> **L298N H-bridge motor driver**`
```

# Components Used 🧮
Before starting on this project, make sure to go through this checklist:

| Component  | Amount  | Utility |
|---| :-: |---|
| Arduino Uno | x2 | Microcontroller |
| MPU6050 Accelerometer & Gyroscope | x1 | Tilt sensing |
| NodeMCU ESP8266 Board | x2 | WiFi Module |
| L298N Dual H-Bridge Motor Driver | x1 | Controlling 2 motors |
| DC Motors (9V/12V) | x2 | For driving 2 rear wheels |
|Lithium Polymer Battery 11.1V | x1 | Power supply with desired current output |


# The Setup 🛠️
## 1. Hand Module 🧤
### Components 🧮
1. **MPU6050**: Used for measure angle (tilt of hand)
2. **Arduino Uno (1)**: Acts as in intermediate to fetch and process the values of angles and sends them to the NodeMCU Wi-Fi module via SPI Communication Protocol
3. **NodeMCU (1)**: Receives the angle values

### Schematics 🏗️

![image](https://user-images.githubusercontent.com/87569188/150363184-6a032708-aa62-42cb-ac70-8a7a0edab293.png)
> Connect the MPU6050 to Arduino as shown for **I2C communication**. I2C is the serial communication protocol done using only 2 wires.

---
![image](https://user-images.githubusercontent.com/87569188/150363313-9b8d8ddd-74fc-48c4-aae8-8cbe8f7522ae.png)
> Connect the NodeMCU to Arduino as shown for **SPI communication**. SPI is the Serial communication protocol done using 4 wires. Arduino is assigned as the Slave and NodeMCU as the Master.

## 2. Communication Module 🌐
### Components 🧮
1. **NodeMCU (1)**: This is the server NodedMCU. Transmits the angle values over Wi-Fi.
2. **NodeMCU (2)**: This is the client NodeMCU. It receives the angle values.

## 3. The 2 Wheeler Robot Car 🚙
### Components 🧮
1. **NodeMCU (2)**: Sends the received angle values to the Arduino via I2C protocol.
2. **Arduino (2)**: Processes the values obtained and it is programmed such that:
   - When the tilt is forward the car speeds ahead
   - With backward tilt, it slows down
   - With left tilt, the car turns left
   - With right tilt, the car turns right
3. **Motor driver**: It is used to control and vary the speeds of the 2 motors in the robot by following the data received from the Arduino.

### Schematics 🏗️
![image](https://user-images.githubusercontent.com/87569188/150366839-d9dfc235-9c93-4024-a268-57cfeef1b6f6.png)
> Connect the NodeMCU to Arduino as shown for **I2C Communication**. I2C protocol was used to send data from the NodeMCU to the Arduino. The NodeMCU was assigned as the Master and Arduino as the Slave.

---
![image](https://user-images.githubusercontent.com/87569188/150367093-a15d6812-e65a-4392-8412-7eb30db38692.png)
> Connect the motor driver to the Arduino as shown.

# Code 💻
## Hand Module 🧤
The codes for Arduino and NodeMCU for the hand module are given [here](https://github.com/aceta-minophen/Hand-gesture-controlled-robot/tree/main/Hand%20Module).
## 2 Wheeler Robot Car 🚙
The codes for Arduino and NodeMCU for the 2 Wheeler Robot Car are given [here](https://github.com/aceta-minophen/Hand-gesture-controlled-robot/tree/main/2WD).

# Hand Module 
## Architecture
**MPU6050** ---Sending Angle Values via I2C---> **Arduino Uno** ---Sending angle values via SPI---> **ESP8266**
## Circuit Schematics
![image](https://user-images.githubusercontent.com/87569188/145699862-6a5dc43a-9191-4095-9a4b-975f0192e391.png)
> SPI communication between NodeMCU and Arduino with NodeMCU as _Master_ and Arduino as _Slave_.

![image](https://user-images.githubusercontent.com/87569188/145699908-a373acbe-1215-476e-93fe-74ba2a6c9bb6.png)
> I2C communication between Arduino Uno and MPU6050


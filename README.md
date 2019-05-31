# Hardware:
`CPU`: STM32 F103C8T6<br>
`Oscillator`: 8 MHz<br>

`OLED`:<br>
>GND ----> GND<br>
>VCC ----> 3.3V<br>
>SCL ----> PB9<br>
>SDA ----> PB10<br>
>RES ----> PB11<br>
>DC  ----> PB12<br>
>CS  ----> PB13<br>
>FSO ----> PB14<br>
>CS2 ----> PB15<br>

# Software:
* Basic delay function using systick;<br>
* Debug port using USART1(GPIOA_9: TX; GPIOA_10: RX);<br>

# IDE:
Keil uVersion5.<br>
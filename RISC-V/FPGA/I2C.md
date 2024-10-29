I²C（Inter-Integrated Circuit）是一种用于设备间短距离通信的同步串行通信协议，由飞利浦（现为NXP）开发，常用于嵌入式系统和电路板上的设备之间的数据传输。I²C协议特别适合将多个从设备连接到单一的主设备，常见于传感器、显示器、EEPROM等外围设备。

I²C的主要特性

	1.	双线制通信：
	•	SDA（数据线）：用于传输数据的双向信号线。
	•	SCL（时钟线）：主设备提供的时钟信号，控制数据传输速率。
	2.	主从架构：
	•	I²C采用主从架构，其中主设备负责生成时钟信号，并控制数据传输的启动和停止。
	•	多个从设备可以连接到总线上，每个设备通过一个唯一的7位或10位地址标识。主设备可以通过地址指定要通信的从设备。
	3.	数据传输与确认机制：
	•	I²C通信以“帧”为单位，包含起始位、地址位、数据位和停止位。在传输过程中，从设备在每个字节传输完成后返回一个“确认位”（ACK），确保数据正确传递。
	4.	支持多主设备：
	•	I²C总线上可以有多个主设备，但在同一时刻只有一个主设备可以进行通信，防止总线冲突。

应用场景

I²C广泛用于电子设备中的低速外围设备通信，例如温度传感器、时钟、EEPROM、液晶显示器等，尤其适合需要控制多设备的嵌入式系统。I²C的简单性和低成本使其成为电路板内部设备通信的常见选择。
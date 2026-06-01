# MORSE CODE SYSTEM USING STM32

# Description
    This project is an embedded system implementation using the STM32 microcontroller to demonstrate UART-based serial communication combined with Morse code generation.The system receives characters from a PC terminal application via UART. The received data is processed in real time by the microcontroller and converted into Morse code representation.The Morse code is displayed in two forms: Visual output using onboard LED and Textual representation sent back through UART

This project is developed using bare-metal programming (register-level coding) without using HAL or CubeMX libraries, providing deeper understanding of microcontroller architecture, peripheral configuration, and low-level embedded system design.

# Hardware used
   STM32F103C8T6 (Blue Pill) microcontroller
   USB-TO-TTL Converter provide UART communication
   STLINK V2 for microcontroller
   Power bank 

# SOftware used
   STMCube IDE
   RealTerm for UART

# Pin connections
USB-TTL and STM32 

USB-TTL Module	          STM32 Blue Pill

TX	                      PA3 (USART2_RX)
RX	                      PA2 (USART2_TX)
GND	                      GND

STM32 AND ST-LINK

ST-LINK               STM32
SWDIO	              SWDIO	
SWCLK	              SWCLK	
GND	                  GND	
3.3V	              3.3V	
RST / NRST	          NRST

Power 5v using power bank

# Methodology
   The implementation follows a structured embedded system workflow:
1. System Initialization
Enable clock for GPIOA, GPIOC, and USART2 peripherals.
Configure USART2 pins:
PA2 → TX (Alternate function push-pull)
PA3 → RX (Input floating)
Configure PC13 as output for LED control.

2. UART Configuration
USART2 is initialized for asynchronous serial communication.
Baud rate is set to 9600 bps for reliable communication with USB-to-TTL converter.
UART is configured for:
8-bit data frame
No parity
1 stop bit

3. Data Reception
The system continuously waits for input from the serial terminal.
Each received character is read from the USART data register.
Lowercase characters are converted to uppercase for uniform processing.

4. Morse Code Encoding
Each character is mapped to its corresponding Morse pattern.
A dot (.) is represented by a short LED blink.
A dash (-) is represented by a long LED blink.
Inter-symbol and inter-character delays are used to maintain proper Morse timing.

5. Output Generation
LED Output: Onboard LED (PC13) blinks according to Morse sequence.
UART Output: Corresponding Morse code pattern is transmitted back to the PC terminal for verification.

6. Continuous Operation
The system runs in an infinite loop.
Continuously receives, processes, and transmits data in real time.

# Conclusion
    This project successfully demonstrates a real-time embedded communication system using the STM32 Blue Pill microcontroller.It integrates UART serial communication with Morse code encoding, providing both visual (LED) and textual (UART) outputs. Through this implementation, a strong understanding of bare-metal embedded programming, peripheral configuration, and real-time signal handling was achieved.
    The project also highlights the importance of:
               Accurate timing control in embedded systems
               Proper UART configuration and debugging
               Low-level hardware register programming
    Overall, this system serves as a strong foundation for more advanced embedded applications such as signal analyzers, communication decoders, and IoT-based control systems

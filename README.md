# Digital-Code-Lock

Nowadays people focus more on keeping valuable possessions at home owing to the pandemic. In such cases, there must be a secure environment to keep everything safe. A Password based Door Security System serves the purpose. The system comprises a number keypad, 16X2 LCD and they are connected to the 8 bit microcontroller AT89C51. This is one of the popular Microcontrollers. It has 40 pins and there are 32 input/output lines. The microcontroller has a program memory of 4 Kilobytes. The microcontroller continuously monitor the keypad and if somebody enters the password it will check the entered password with the password which was stored in the memory and if it they are same then the microcontroller will switch on the corresponding device.  The system will allow the person who knows the password and it will not allow who don't know the password and the system will also show the persons who try to break the protection barrier. 
 
The AT89C51 is an age old 8-bit microcontroller from the Atmel family. It works with the popular 8051 architecture and hence is used by most beginners till date. It is a 40 pin IC package with 4 kilobytes flash memory. It has four ports and all together provides 32 Programmable GPIO pins. It does not have in-built ADC module and supports only USART communication. Although it can be interfaced with external ADC IC like the ADC084 or the ADC0808. Atmel microcontroller can be programmed with different software's that is available in the market. Arduino, Keil uVision are the most used platforms to name a few. If you are planning on serious programming and expansion with community support then Keil is recommended. In order to program the Atmel microcontroller we will need an IDE (Integrated Development Environment), where the programming takes place. A compiler, where our program gets converted into MCU readable form called HEX files. An IPE (Integrated Programming Environment), which is used to dump our hex file into our MCUs 

Algorithm: 
 
  1. START 
  2. initialise led, keypad 
  3. clear lod             
  4. print "Enter Password" on led             
  5. get 4 digit password using matrix keypad 
  6. if input "2940" then 
      6.1 print "Locker Open" 
      6.2 relay switch is on 
      6.3 if next input is „*‟ 
          6.3.1 go to step 4  
  7. else   
      7.1 print “Wrong Password”  
      7.2 go to step 4 if count is not 3 and input is „*‟   
      7.3 if count is 3    
          7.3.1 alarm buzzes    
          7.3.2 keypad and lcd turned off  
  
8 if input is „#‟   
      8.1 go to step 2 
9 STOP 
 
 

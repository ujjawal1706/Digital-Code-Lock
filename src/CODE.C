#include<stdio.h>
#include<reg51.h>
#include<stdlib.h>
#include<string.h>
void cmdwr(void);                             //LCD command write sub routine                   
void datwr(void);                              //LCD data write sub routine
void delay(void);                               //Delay function
void check(void);                              //Password check function
void answ(void);                               //Trial and result analysis function
void asterisk(void);                           //Asterisk key input function
void debounce_delay(void);               //Keypad debounce delay functiom
void trl_chk(void);                           //trial Check function
void init(void);                                 //system initialization
sbit en=P3^2;                              
sbit rs=P3^0;
sbit rw=P3^1;
sbit relay=P3^4;
sbit alarm=P3^7;
code unsigned char msg[14]="Enter Password";
code unsigned char open_msg[11]="Locker Open";
code unsigned char lock_msg[14]="Wrong Password";
code unsigned char array1[5]={0x38,0x0f,0x06,0x01,0x80};
code unsigned char array2[5]={0xc0,0xc0,0xc1,0xc2,0xc3};
unsigned data passwd[5]={0,2,9,4,0};           //Locker password initial '0'is dummy
unsigned data digit[5];
unsigned char i,p,k,l,m,n,f,y;
int count=0,num=0,trial=0;          //initializing count,trial and num to zero
void main()
{
 relay=0;                                 //turning relay off
 alarm=0;                               //turning alarm off
 while(1)
  {
    P2=0xf7;                         //Initialization key scan
    i=(P2&0xf0);
     {
      if(i==0xe0)
       {
         init();
         goto LOOP;
        }
      }
   }
LOOP:while(1)                        //Entire key scan starts
{
  P2=0xfe;
  i=(P2&0xf0);
  {
    if(i==0xe0)
     {
       debounce_delay();         //Delay to over come keypad bounce
       count++;                     //incrementing count
       asterisk();
       digit[count]=1;           //Setting key value
       check();
       answ();  
      } 
    else if(i==0xd0)
      {
       debounce_delay();
       count++;
       asterisk();
       digit[count]=2;
       check();
       answ();
      }
    else if(i==0xb0)
      {
       debounce_delay();
       count++;
       asterisk();
       digit[count]=3;
       check();
       answ();
      } 
   }
  P2=0xfd;
  i=(P2&0xf0);
  {
    if(i==0xe0)
      {
       debounce_delay();
       count++;
       asterisk();
       digit[count]=4;
       check();
       answ();
      }
    else if(i==0xd0)
      {
       debounce_delay();
       count++;
       asterisk();
       digit[count]=5;
       check();
       answ();
      }
    else if(i==0xb0)
      {
       debounce_delay();
       count++; 
       asterisk();
       digit[count]=6;
       check();
       answ();
      }
  }
  P2=0xfb;
  i=(P2&0xf0);
   {
    if(i==0xe0)
     {
      debounce_delay();
      count++;
      asterisk();
      digit[count]=7;
      check();
      answ();
     }
    else if(i==0xd0)
     {
      debounce_delay();
      count++;
      asterisk();
      digit[count]=8;
      check();
      answ();
     }
    else if(i==0xb0)
     {
      debounce_delay();
      count++;
      asterisk();
      digit[count]=9;
      check();
      answ();
     }
  }
  P2=0xf7;
  i=(P2&0xf0); 
   {
   if(i==0xe0)
    {
      debounce_delay();
      for(p=0;p<=4;p++)
       {                                          
        P1=array1[p];
        cmdwr();
        delay();
       }
      for(m=0;m<=13;m++)
       {
        P1=msg[m];                      //Enter password message display
        datwr();
        delay();
       }
     P1=0x3c;
     cmdwr();
     delay();
     P1=0xc0;
     cmdwr();
     delay();
     count=num=0;
    }
   else if(i==0xd0)
    {
     debounce_delay();
     count++;
     asterisk();
     digit[count]=0;
     check();
     answ();
    }
  else if(i==0xb0)
    {
     debounce_delay();
     relay=0;
     num=count=0;
     P1=0x08;
     cmdwr();
     delay();
    }
   }
  }
 }
void datwr()
 {
  rs=1;rw=0;en=1;delay();en=0;            //steps to send data to lcd
 }
void cmdwr()
 {
  rs=0;rw=0;en=1;delay();en=0;          //steps to send command to lcd
 }
void delay()                                       //software delay
 {    
  for(k=1;k<200;k++);
   {
    for(l=1;l<=200;l++);
   }
 }
void check()
 {
  switch(count)
   {
   case 1:if(digit[count]==passwd[count])
           {
            num=num+1;
           }
           break;
  case 2:if(digit[count]==passwd[count])
          {
           num=num+1;
          }
           break;
  case 3:if(digit[count]==passwd[count])
         {
          num=num+1;
         }
          break;
  case 4:if(digit[count]==passwd[count])
         {
          num=num+1;
         }
         break;
       }
}
void answ()
 {
 if(count==4)                                       //Checking count
  {
  if(num==4)                                       //Checking "num" value to verify password 
     {
      relay=1;
      for(p=0;p<=4;p++)
       {
        P1=array1[p];
        cmdwr();
        delay();
       }
      for(f=0;f<=10;f++)
       {
        P1=open_msg[f];                   //Locker open msg
        datwr();
        delay();
       }
      count=num=0;
      trial=0;
      while(1)
       {
        P2=0xf7;
        i=(P2&0xf0);
         {
          if(i==0xe0)
           {
            init();
            break;
           }
          else if(i==0xb0)
           {
            debounce_delay();               
            relay=0; 
            num=count=0;
            P1=0x01;
            cmdwr();
            delay();
            P1=0x02;
            cmdwr();
            delay();
           }
         }
       }
      }
  else 
   {
    relay=0;
    for(p=0;p<=4;p++)
     {                                                                           
      P1=array1[p];
      cmdwr();
      delay();
     }
    for(n=0;n<=13;n++)
     {
      P1=lock_msg[n];                               //Locker closed message
      datwr();
      delay();
     }
    trial++;
    trl_chk();
    while(1)
     {
      P2=0xf7;
      i=(P2&0xf0);
     {
      if(i==0xe0)
       {
        init();
        break;
       }
     }
   }
  }
 }
}
void asterisk()                             //Subroutine to display "*" in LCD
 {
  P1=array2[count];
  cmdwr(); 
  P1=0x2a;
  datwr();
 }
void debounce_delay()                  //Debounce Delay generation using timers
 {
  for(y=0;y<=4;y++)
   {
    TMOD=0x01;
    TH0=0x3C;
    TL0=0xB0;
    TR0=1;
    while(TF0==0);
    TR0=0;
    TF0=0;
   }
 }
void trl_chk()                          //Function to check trials
 {
  if(trial>2)                            //Verifying number of trials
   {
    P2=0x00;
    while(1)
     {
      alarm=1;
     }
   }
 }
void init()                            //Function to initialize system
 {
  debounce_delay();
  for(p=0;p<=4;p++) 
   {                           
    P1=array1[p];
    cmdwr();
    delay();
   }
  for(m=0;m<=13;m++)
   {
    P1=msg[m];
    datwr();
    delay();
   }
   P1=0x3c;
   cmdwr();
   delay(); 
   P1=0xc0;
   cmdwr();
   delay();
   count=num=0;
 }

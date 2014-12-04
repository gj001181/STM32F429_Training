#include "main.h"


static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}

void RCC_Configuration(void)
{
      /* --------------------------- System Clocks Configuration -----------------*/
      /* GPIOA clock enable */
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
}
 
/**************************************************************************************/
 
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*-------------------------- GPIO Configuration for Push Button ----------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD ;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG , ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);





}
 
/**************************************************************************************/
 
void LED_Initialization(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG , ENABLE); //LED3/4 GPIO Port

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

  
}

void LED3_On(void){

  GPIO_SetBits(GPIOG,GPIO_Pin_13);

}

void LED3_Off(void){

  GPIO_ResetBits(GPIOG,GPIO_Pin_13);

}

void LED4_On(void){

  GPIO_SetBits(GPIOG,GPIO_Pin_14);

}

void LED4_Off(void){

  GPIO_ResetBits(GPIOG,GPIO_Pin_14);

}

void LED3_Toggle(void){


  GPIO_ToggleBits(GPIOG,GPIO_Pin_13);

}

void LED4_Toggle(void){


  GPIO_ToggleBits(GPIOG,GPIO_Pin_14);

}

uint8_t PushButton_Read(void){

    return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);

}
/**************************************************************************************/
int main(void)
{
    uint32_t a=1000;
    uint32_t b=20000;
    uint32_t c=0;
    RCC_Configuration();
    GPIO_Configuration();
    LED_Initialization();


    while(1)
    {
      if(PushButton_Read())
      {
       
       c=c+1;
       

       if(c==4)
        c=1;
       
       
       Delay_1us(300000);
      } 
     

     
      if(c==1)
      {
        a=1000;
      }

      if(c==2)
      {
        a=1500;
      }  

      if(c==3)
      {
        a=2000;
      }
        

    GPIO_SetBits(GPIOE, GPIO_Pin_8);
    Delay_1us(a);
    GPIO_ResetBits(GPIOE, GPIO_Pin_8);
    Delay_1us(b-a);
     


     
      if(c==1)
      {
        a=1500;
      }

      if(c==2)
      {
        a=2000;
      }  

      if(c==3)
      {
        a=1000;
      }
        

    GPIO_SetBits(GPIOG, GPIO_Pin_1);
    Delay_1us(a);
    GPIO_ResetBits(GPIOG, GPIO_Pin_1);
    Delay_1us(b-a);
     


     
      if(c==1)
      {
        a=2000;
      }

      if(c==2)
      {
        a=1000;
      }  

      if(c==3)
      {
        a=1500;
      }
        

    GPIO_SetBits(GPIOE, GPIO_Pin_10);
    Delay_1us(a);
    GPIO_ResetBits(GPIOE, GPIO_Pin_10);
    Delay_1us(b-a);
     
    


    }
    
   

}


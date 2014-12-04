
#include "main.h"

void Delay_1us(uint32_t nCnt_1us)
{
  uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 45; nCnt != 0; nCnt--);
}

void USART1_IRQHandler(void);


void RCC_Configuration(void)
{
      /* --------------------------- System Clocks Configuration -----------------*/
      /* USART1 clock enable */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
      /* GPIOA clock enable */
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
}
 
/**************************************************************************************/
 
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*-------------------------- GPIO Configuration ----------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Connect USART pins to AF */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);   // USART1_TX
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);  // USART1_RX
}
 
/**************************************************************************************/
 
void LED_Initialization(void){

  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG , ENABLE); //LED3/4 GPIO Port

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;  // LED is connected to PG13/PG14
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

}

void LED3_Toggle(void){


  GPIOG->ODR ^= GPIO_Pin_13;

}

void LED4_Toggle(void){


  GPIOG->ODR ^= GPIO_Pin_14;
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


void USART1_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;

    /* USARTx configuration ------------------------------------------------------*/
    /* USARTx configured as follow:
     *  - BaudRate = 57600 baud
     *  - Word Length = 8 Bits
     *  - One Stop Bit
     *  - No parity
     *  - Hardware flow control disabled (RTS and CTS signals)
     *  - Receive and transmit enabled
     */
    USART_InitStructure.USART_BaudRate = 57600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);

    USART_ClearFlag(USART1, USART_FLAG_TC);

    USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /* NVIC Initialization */
    NVIC_InitTypeDef NVIC_InitStruct = {
      .NVIC_IRQChannel = USART1_IRQn,
      .NVIC_IRQChannelPreemptionPriority = 0,
      .NVIC_IRQChannelSubPriority = 0,
      .NVIC_IRQChannelCmd = ENABLE
    };
    NVIC_Init(&NVIC_InitStruct);

}

void USART1_puts(char* s)
{
    while(*s) {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, *s);
        s++;
    }
}
int i;
char b[5];
char a;
int c;
int d;

/**************************************************************************************/
int main(void)
{
    RCC_Configuration();
    GPIO_Configuration();
    USART1_Configuration();
    LED_Initialization();
    
   
    while(1)
    {
        if(b[i]=='a'){
          if(b[i+1]=='b'){
            if(b[i+2]=='c'){
              if(b[i+3]=='3'){
                if(b[i+4]=='o'){
                  c=1;
                  LED3_On();
                }
              }
            }
          }
        }

        if(b[i]=='a'){
          if(b[i+1]=='b'){
            if(b[i+2]=='c'){
              if(b[i+3]=='3'){
                if(b[i+4]=='f'){
                  c=0;
                  LED3_Off();
                }
              }
            }
          }
         }

        if(b[i]=='a'){
          if(b[i+1]=='b'){
            if(b[i+2]=='c'){
              if(b[i+3]=='4'){
                if(b[i+4]=='o'){
                  d=1;
                  LED4_On();
                }
              }
            }
          }
         }
        
        if(b[i]=='a'){
          if(b[i+1]=='b'){
            if(b[i+2]=='c'){
              if(b[i+3]=='4'){
                if(b[i+4]=='f'){
                  d=0;
                  LED4_Off();
                
                }
              }
            }
          }
        }

        if(b[i]=='d'){
          if(b[i+1]=='e'){
            if(b[i+2]=='f'){
              if(b[i+3]=='3'){
                  
                  LED3_Toggle();
                  if(d==1){
                    LED4_On();
                  }

                  }
                  


              }
            }
          }
        

        if(b[i]=='d'){
          if(b[i+1]=='e'){
            if(b[i+2]=='f'){
              if(b[i+3]=='4'){
                  
                  LED4_Toggle();
                  if(c==1){
                    LED3_On();
                  }
                
                  }


                  



              }
            }
          }
        

   }
    

}


void USART1_IRQHandler(void)
{
  
  if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
    uart1_data = USART_ReceiveData(USART1);
    USART_SendData(USART1, uart1_data);
    a = USART_ReceiveData(USART1);
    b[i]=b[i+1];
    b[i+1]=b[i+2];
    b[i+2]=b[i+3];
    b[i+3]=b[i+4];
    b[i+4]=a;
  }

}
#include "main.h"

static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}

void DrawThickCircle(uint32_t x,uint32_t y,uint32_t radius, uint32_t thickness){


    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DrawFullCircle(x, y, radius);
    LCD_SetColors(LCD_COLOR_WHITE-1,LCD_COLOR_WHITE);
    LCD_DrawFullCircle(x, y, radius-thickness);


}


void RCC_Configuration(void)
{
      /* --------------------------- System Clocks Configuration -----------------*/
      /* USART1 clock enable */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
      /* GPIOA clock enable */
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
}

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


void ADC_Initialization(void)
{
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;

  /* Enable ADC3, DMA2 and GPIO clocks ****************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

  /* Configure ADC3 Channel7 pin as analog input ******************************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                     // No external trigger is connected
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;                  // ADC clock prescaler
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;      // No DMA (polling mode)
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;  
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC3 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                       // Resolution 12 bits
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;                                // Use single channel 
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                           // Continue conversion
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                       // Data bits shifted to right hand side (Low)
  ADC_InitStructure.ADC_NbrOfConversion = 1;                                   // Convert only once
  ADC_Init(ADC3, &ADC_InitStructure);

  /* ADC3 regular channel7 configuration *************************************/
  ADC_RegularChannelConfig(ADC3, ADC_Channel_13, 1, ADC_SampleTime_3Cycles);

  /* Enable ADC3 */
  ADC_Cmd(ADC3, ENABLE);


  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);

  /* Configure ADC3 Channel7 pin as analog input ******************************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                     // No external trigger is connected
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;                  // ADC clock prescaler
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;      // No DMA (polling mode)
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;  
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC3 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                       // Resolution 12 bits
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;                                // Use single channel 
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                           // Continue conversion
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                       // Data bits shifted to right hand side (Low)
  ADC_InitStructure.ADC_NbrOfConversion = 1;                                   // Convert only once
  ADC_Init(ADC2, &ADC_InitStructure);

  /* ADC3 regular channel7 configuration *************************************/
  ADC_RegularChannelConfig(ADC2, ADC_Channel_14, 1, ADC_SampleTime_3Cycles);

  /* Enable ADC3 */
  ADC_Cmd(ADC2, ENABLE);

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  /* Configure ADC3 Channel7 pin as analog input ******************************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                     // No external trigger is connected
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;                  // ADC clock prescaler
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;      // No DMA (polling mode)
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;  
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC3 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                       // Resolution 12 bits
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;                                // Use single channel 
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                           // Continue conversion
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                       // Data bits shifted to right hand side (Low)
  ADC_InitStructure.ADC_NbrOfConversion = 1;                                   // Convert only once
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC3 regular channel7 configuration *************************************/
  ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 1, ADC_SampleTime_3Cycles);

  /* Enable ADC3 */
  ADC_Cmd(ADC1, ENABLE);
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
}

void USART1_puts(char* s)
{
    while(*s) {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, *s);
        s++;
    }
}


uint8_t buff_transmit[100];
uint16_t adc_dataX=0,adc_dataY=0,adc_dataZ=0;
int i=0;
float voltageX =0.0f,voltageY =0.0f,voltageZ =0.0f;
float AccX =0.0f,AccY =0.0f,AccZ =0.0f;
const float alpha = 0.03;
double fXg = 0;
double fYg = 0;
double fZg = 0;
double pitch = 0;
double roll = 0;



int main(void)
{

  
    RCC_Configuration();
    GPIO_Configuration();
    USART1_Configuration();
    ADC_Initialization();
  uint8_t colorR =0 ,colorG =0 ,colorB =0 ;
  uint8_t colorR_dir =0 ,colorG_dir =0 ,colorB_dir =0 ;
  char lcd_text_buff[100];


  /* LCD initialization */
  LCD_Init();
  
  /* LCD Layer initialization */
  LCD_LayerInit();
    
  LCD_SetLayer(LCD_FOREGROUND_LAYER);
  LCD_SetColorKeying(0xFFFFFF);

  /* Need to reload */
  LTDC_ReloadConfig(LTDC_IMReload);

  /* Enable the LTDC */
  LTDC_Cmd(ENABLE);
  
  /* Set LCD foreground layer */

  /* Clear the LCD */ 
  LCD_Clear(LCD_COLOR_WHITE);
  LCD_SetFont(&Font16x24);

  LCD_SetLayer(LCD_BACKGROUND_LAYER);
  LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE);

  LCD_DisplayStringLine(LINE(1), (uint8_t*)" LCD text print example ");
  LCD_DisplayStringLine(LINE(2), (uint8_t*)" Ming6842 @ github");

    LCD_SetLayer(LCD_FOREGROUND_LAYER);

    LCD_SetColors(LCD_COLOR_WHITE,LCD_COLOR_WHITE);
    LCD_DrawFullRect(0,0,240,320);

    LCD_Clear(LCD_COLOR_WHITE);

#define X_MIDDLE 120
#define Y_MIDDLE 180

    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DrawUniLine(X_MIDDLE+75, Y_MIDDLE-75  , X_MIDDLE-75, Y_MIDDLE+75);
    LCD_DrawUniLine(X_MIDDLE+75, Y_MIDDLE-75-1, X_MIDDLE-75, Y_MIDDLE+75-1);
    LCD_DrawUniLine(X_MIDDLE+75, Y_MIDDLE-75+1, X_MIDDLE-75, Y_MIDDLE+75+1);

    LCD_DrawUniLine(X_MIDDLE-75, Y_MIDDLE-75  , X_MIDDLE+75, Y_MIDDLE+75);
    LCD_DrawUniLine(X_MIDDLE-75, Y_MIDDLE-75-1, X_MIDDLE+75, Y_MIDDLE+75-1);
    LCD_DrawUniLine(X_MIDDLE-75, Y_MIDDLE-75+1, X_MIDDLE+75, Y_MIDDLE+75+1);


    LCD_DrawFullRect(X_MIDDLE-60,Y_MIDDLE-5,120,10);
    LCD_DrawFullRect(X_MIDDLE-5,Y_MIDDLE-60,10,120);


    DrawThickCircle(X_MIDDLE,Y_MIDDLE,30,7);

    DrawThickCircle(X_MIDDLE+60,Y_MIDDLE,22,   5);
    DrawThickCircle(X_MIDDLE-60,Y_MIDDLE,22,   5);
    DrawThickCircle(X_MIDDLE   ,Y_MIDDLE+60,22,5);
    DrawThickCircle(X_MIDDLE   ,Y_MIDDLE-60,22,5);

    DrawThickCircle(X_MIDDLE+75,Y_MIDDLE+75,32,5);
    DrawThickCircle(X_MIDDLE-75,Y_MIDDLE-75,32,5);
    DrawThickCircle(X_MIDDLE+75,Y_MIDDLE-75,32,5);
    DrawThickCircle(X_MIDDLE-75,Y_MIDDLE+75,32,5);

    LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);

    LCD_DisplayStringLine(LINE(1), (uint8_t*)"     Ce-91     ");

  LCD_SetLayer(LCD_BACKGROUND_LAYER);
  ADC_SoftwareStartConv(ADC1);
  ADC_SoftwareStartConv(ADC2);
  ADC_SoftwareStartConv(ADC3);
  while (1)
  {
  LCD_SetLayer(LCD_FOREGROUND_LAYER);
  LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
  adc_dataX = ADC_GetConversionValue(ADC1);
  adc_dataY = ADC_GetConversionValue(ADC2);
  adc_dataZ = ADC_GetConversionValue(ADC3);
  voltageX = (float)adc_dataX*3.3f/4095.0f;
  voltageY = (float)adc_dataY*3.3f/4095.0f;
  voltageZ = (float)adc_dataZ*3.3f/4095.0f;
  AccX = ((float)voltageX-2.08)/0.38;
  AccY = ((float)voltageY-2.80)/0.165;
  AccZ = ((float)voltageZ-1.33)/0.63;
  fXg = AccX * alpha + (fXg * (1.0 - alpha));
  fYg = AccY * alpha + (fYg * (1.0 - alpha));
  fZg = AccZ * alpha + (fZg * (1.0 - alpha));
  roll  = (atan2(-fYg, fZg)*180.0)/3.14159;
  pitch = (atan2(fXg, sqrt(fYg*fYg + fZg*fZg))*180.0)/3.14159;
  sprintf((char *)buff_transmit, "ADCDataX = %d\r\n",adc_dataX);
  LCD_DisplayStringLine(LINE(2), (uint8_t*) (char *)buff_transmit );
  sprintf((char *)buff_transmit, "ADCDataY = %d\r\n",adc_dataY);
  LCD_DisplayStringLine(LINE(3), (uint8_t*) (char *)buff_transmit );
  sprintf((char *)buff_transmit, "ADCDataZ = %d\r\n",adc_dataZ);
  LCD_DisplayStringLine(LINE(4), (uint8_t*) (char *)buff_transmit );
  sprintf((char *)buff_transmit, "VoltageX = %fV\r\n",voltageX);
  LCD_DisplayStringLine(LINE(5), (uint8_t*) (char *)buff_transmit );
  sprintf((char *)buff_transmit, "VoltageY = %fV\r\n",voltageY);
  LCD_DisplayStringLine(LINE(6), (uint8_t*) (char *)buff_transmit );
  sprintf((char *)buff_transmit, "VoltageZ = %fV\r\n",voltageZ);
  LCD_DisplayStringLine(LINE(7), (uint8_t*) (char *)buff_transmit );
  sprintf((char *)buff_transmit, "AccX = %fg\r\n",AccX);
  LCD_DisplayStringLine(LINE(8), (uint8_t*) (char *)buff_transmit );
  sprintf((char *)buff_transmit, "AccY = %fg\r\n",AccY);
  LCD_DisplayStringLine(LINE(9), (uint8_t*) (char *)buff_transmit );
  sprintf((char *)buff_transmit, "AccZ = %fg\r\n",AccZ);
  LCD_DisplayStringLine(LINE(10), (uint8_t*) (char *)buff_transmit );
  sprintf((char *)buff_transmit, "Roll = %f\r\n",roll);
  LCD_DisplayStringLine(LINE(11), (uint8_t*) (char *)buff_transmit );
  sprintf((char *)buff_transmit, "Pitch = %f\r\n",pitch);
  LCD_DisplayStringLine(LINE(12), (uint8_t*) (char *)buff_transmit );

          for (i=0;i<50;i++){

            buff_transmit[i]=0;
          }
  

  LCD_SetLayer(LCD_BACKGROUND_LAYER);
    if(colorR_dir){

          colorR += 1;

      if(colorR > 250) colorR_dir=0;
      
    }else{

      colorR -= 1;

      if(colorR<20) colorR_dir=1;
    }

    if(colorG_dir){

          colorG += 2;

      if(colorG > 250) colorG_dir=0;
      
    }else{

      colorG -= 2;

      if(colorG<25) colorG_dir=1;
    }

    if(colorB_dir){

          colorB += 3;

      if(colorB > 250) colorB_dir=0;
      
    }else{

      colorB -= 3;

      if(colorB<25) colorB_dir=1;
    }

    LCD_SetColors(ASSEMBLE_RGB(colorR, colorG, colorB),LCD_COLOR_BLACK);
    LCD_DrawFullRect(0,0,240,320);

    //Delay_1us(150000);

  }
  
}


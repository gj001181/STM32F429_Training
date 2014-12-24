#include "main.h"

static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}

void SPI_Initialization(void){

  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI5, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(SPI5);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  /* SPI baudrate is set to 5.6 MHz (PCLK2/SPI_BaudRatePrescaler = 90/16 = 5.625 MHz)  */

  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI5, &SPI_InitStructure);

  /* Enable SPI4  */
  SPI_Cmd(SPI5, ENABLE);
  
  /* Configure GPIO PIN for Chip select */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  
  GPIO_PinAFConfig(GPIOF, GPIO_PinSource7, GPIO_AF_SPI5);
  GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_SPI5);
  GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_SPI5);

  /* Configure GPIO PIN for SPI4 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);


}

int main(void)
{

  char lcd_text_main[100];
  // uint8_t buff_transmit[100];
  uint8_t receivedData=0;
  uint8_t Xl,Xh,Yl,Yh,Zl,Zh;

    

    lcd_init();
    lcd_drawBackground(20,60,250);
    lcd_drawBGPersimmon(20, 60, 250);
    LCD_SetColors(LCD_COLOR_WHITE-1,LCD_COLOR_WHITE);

    LCD_SetFont(&Font8x12); 

    terminalBufferInitilization();
    SPI_Initialization();


    //FIFO

    // GPIO_ResetBits(GPIOC, GPIO_Pin_1);
      
    // SPI_I2S_SendData(SPI5,0x2e);
    // while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
    // while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
    // receivedData=SPI_I2S_ReceiveData(SPI5);
      
    // SPI_I2S_SendData(SPI5,0x00);
    // while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
    // while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
    // receivedData=SPI_I2S_ReceiveData(SPI5);

    // GPIO_SetBits(GPIOC, GPIO_Pin_1);

    // GPIO_ResetBits(GPIOC, GPIO_Pin_1);
      
    // SPI_I2S_SendData(SPI5,0xae);
    // while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
    // while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
    // receivedData=SPI_I2S_ReceiveData(SPI5);
      
    // SPI_I2S_SendData(SPI5,0xff);
    // while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
    // while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
    // receivedData=SPI_I2S_ReceiveData(SPI5);

    // GPIO_SetBits(GPIOC, GPIO_Pin_1);

    //20H
    GPIO_ResetBits(GPIOC, GPIO_Pin_1);
      
    SPI_I2S_SendData(SPI5,0x20);
    while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
    while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
    receivedData=SPI_I2S_ReceiveData(SPI5);
      
    SPI_I2S_SendData(SPI5,0x0f);
    while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
    while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
    receivedData=SPI_I2S_ReceiveData(SPI5);

    GPIO_SetBits(GPIOC, GPIO_Pin_1);

    GPIO_ResetBits(GPIOC, GPIO_Pin_1);
      
    SPI_I2S_SendData(SPI5,0xa0);
    while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
    while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
    receivedData=SPI_I2S_ReceiveData(SPI5);
      
    SPI_I2S_SendData(SPI5,0xff);
    while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
    while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
    receivedData=SPI_I2S_ReceiveData(SPI5);

    GPIO_SetBits(GPIOC, GPIO_Pin_1);
    








    while(1){

      GPIO_ResetBits(GPIOC, GPIO_Pin_1);
      
      SPI_I2S_SendData(SPI5,0xa8);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI5);
      
      SPI_I2S_SendData(SPI5,0xff);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI5);

      Xl=receivedData;

      GPIO_SetBits(GPIOC, GPIO_Pin_1);

      GPIO_ResetBits(GPIOC, GPIO_Pin_1);
      
      SPI_I2S_SendData(SPI5,0xa9);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI5);
      
      SPI_I2S_SendData(SPI5,0xff);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI5);

      Xh=receivedData;

      GPIO_SetBits(GPIOC, GPIO_Pin_1);

      GPIO_ResetBits(GPIOC, GPIO_Pin_1);
      
      SPI_I2S_SendData(SPI5,0xaa);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI5);
      
      SPI_I2S_SendData(SPI5,0xff);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI5);

      Yl=receivedData;

      GPIO_SetBits(GPIOC, GPIO_Pin_1);

      GPIO_ResetBits(GPIOC, GPIO_Pin_1);
      
      SPI_I2S_SendData(SPI5,0xab);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI5);
      
      SPI_I2S_SendData(SPI5,0xff);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI5);

      Yh=receivedData;

      GPIO_SetBits(GPIOC, GPIO_Pin_1);

      GPIO_ResetBits(GPIOC, GPIO_Pin_1);
      
      SPI_I2S_SendData(SPI5,0xac);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI5);
      
      SPI_I2S_SendData(SPI5,0xff);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI5);

      Zl=receivedData;

      GPIO_SetBits(GPIOC, GPIO_Pin_1);

      GPIO_ResetBits(GPIOC, GPIO_Pin_1);
      
      SPI_I2S_SendData(SPI5,0xad);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI5);
      
      SPI_I2S_SendData(SPI5,0xff);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);
      while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI5);

      Zh=receivedData;

      GPIO_SetBits(GPIOC, GPIO_Pin_1);

      short X,Y,Z;
      X=Xh*256+Xl;
      Y=Yh*256+Yl;
      Z=Zh*256+Zl;

      if(X>32767)
        {X=X-65535;}
      if(Y>32767)
        {Y=Y-65535;}
      if(Z>32767)
        {Z=Z-65535;}

      sprintf(lcd_text_main,"XL : %d \n", Xl); terminalWrite(lcd_text_main);
      sprintf(lcd_text_main,"XH : %d \n", Xh); terminalWrite(lcd_text_main);
      sprintf(lcd_text_main,"YL : %d \n", Yl); terminalWrite(lcd_text_main); 
      sprintf(lcd_text_main,"YH : %d \n", Yh); terminalWrite(lcd_text_main);
      sprintf(lcd_text_main,"ZL : %d \n", Zl); terminalWrite(lcd_text_main);
      sprintf(lcd_text_main,"ZH : %d \n", Zh); terminalWrite(lcd_text_main);
      sprintf(lcd_text_main,"X : %d \n", X); terminalWrite(lcd_text_main);
      sprintf(lcd_text_main,"Y : %d \n", Y); terminalWrite(lcd_text_main);
      sprintf(lcd_text_main,"Z : %d \n", Z); terminalWrite(lcd_text_main); 
      sprintf(lcd_text_main,"\n"); terminalWrite(lcd_text_main);
      sprintf(lcd_text_main,"\n"); terminalWrite(lcd_text_main);
      sprintf(lcd_text_main,"\n"); terminalWrite(lcd_text_main);



      
      
      
    
      

      
      // sprintf((char *)buff_transmit, "XL = %d\r\n",Xl);
      // LCD_DisplayStringLine(LINE(5), (uint8_t*) (char *)buff_transmit );
      // sprintf((char *)buff_transmit, "XH = %d\r\n",Xh);
      // LCD_DisplayStringLine(LINE(6), (uint8_t*) (char *)buff_transmit );
      // sprintf((char *)buff_transmit, "YL = %d\r\n",Yl);
      // LCD_DisplayStringLine(LINE(7), (uint8_t*) (char *)buff_transmit );
      // sprintf((char *)buff_transmit, "YH = %d\r\n",Yh);
      // LCD_DisplayStringLine(LINE(8), (uint8_t*) (char *)buff_transmit );
      // sprintf((char *)buff_transmit, "ZL = %d\r\n",Zl);
      // LCD_DisplayStringLine(LINE(9), (uint8_t*) (char *)buff_transmit );
      // sprintf((char *)buff_transmit, "ZH = %d\r\n",Zh);
      // LCD_DisplayStringLine(LINE(10), (uint8_t*) (char *)buff_transmit );


      // SPI_I2S_SendData(SPI5,0x04);
      // while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET);

      // while (SPI_I2S_GetFlagStatus(SPI5, SPI_FLAG_RXNE) == RESET);
      // receivedData=SPI_I2S_ReceiveData(SPI5);
      

      // sprintf(lcd_text_main,"receivedData : %x    \n", receivedData); terminalWrite(lcd_text_main); 
   
      Delay_1us(800000);

    }
  
}


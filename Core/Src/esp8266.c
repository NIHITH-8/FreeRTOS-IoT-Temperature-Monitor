#include "esp8266.h"
#include <string.h>
#include <stdio.h>
#include "lcd.h"

extern UART_HandleTypeDef huart6;
extern float temp;
extern volatile float g_temperature;
char buffer[200];
char str[120];

void ESP_init(void)
{
    // ---------------- AT TEST ----------------
    HAL_UART_Transmit(&huart6, (uint8_t*)"AT\r\n", 4, 1000);
    HAL_UART_Receive(&huart6, (uint8_t*)buffer, sizeof(buffer)-1, 2000);

    if(strstr(buffer,"OK")==NULL)
    {
    	scmd(0x01);
        string("AT FAIL");
        return;
    }
    scmd(0x01);
    string("AT OK");

    // ---------------- RESET ----------------
    memset(buffer, 0, sizeof(buffer));
    HAL_UART_Transmit(&huart6, (uint8_t*)"AT+RST\r\n", 8, 1000);
    HAL_UART_Receive(&huart6, (uint8_t*)buffer, sizeof(buffer)-1, 8000);

    if(strstr(buffer,"ready")==NULL && strstr(buffer,"OK")==NULL)
    {
    	scmd(0x01);
        string("RST FAIL");
        return;
    }
    scmd(0x01);
    string("RST OK");
    HAL_Delay(500);

    // ---------------- MODE ----------------
    memset(buffer, 0, sizeof(buffer));

    HAL_UART_Transmit(&huart6,
                      (uint8_t*)"AT+CWMODE=3\r\n",
                      strlen("AT+CWMODE=3\r\n"),
                      1000);

    HAL_UART_Receive(&huart6,
                      (uint8_t*)buffer,
                      sizeof(buffer)-1,
                      3000);

    // debug safe check
    if(strstr(buffer,"OK") || strstr(buffer,"CWMODE"))
    {
    	scmd(0x01);
        string("MODE OK");
    }
    else
    {
    	scmd(0x01);
        string("MODE FAIL");
        return;
    }
    // ---------------- WIFI ----------------
    memset(buffer, 0, sizeof(buffer));
    HAL_UART_Transmit(&huart6,
        (uint8_t*)"AT+CWJAP=\"Mywifi\",\"88888888\"\r\n",
        strlen("AT+CWJAP=\"Mywifi\",\"88888888\"\r\n"),
        1000);

    HAL_UART_Receive(&huart6, (uint8_t*)buffer, sizeof(buffer)-1, 12000);

    if(strstr(buffer,"WIFI CONNECTED")==NULL && strstr(buffer,"OK")==NULL)
    {
    	scmd(0x01);
        string("WIFI FAIL");
        return;
    }
    scmd(0x01);
    string("WIFI OK");
    // ---------------- IP ----------------
    memset(buffer, 0, sizeof(buffer));
    HAL_UART_Transmit(&huart6, (uint8_t*)"AT+CIFSR\r\n", 10, 1000);
    HAL_UART_Receive(&huart6, (uint8_t*)buffer, sizeof(buffer)-1, 3000);

    if(strstr(buffer,"STAIP")==NULL)
    {
    	scmd(0x01);
        string("IP FAIL");
        return;
    }
    scmd(0x01);
    string("IP OK");

    // ---------------- SINGLE MODE ----------------
    HAL_UART_Transmit(&huart6, (uint8_t*)"AT+CIPMUX=0\r\n", 13, 1000);
    HAL_UART_Receive(&huart6, (uint8_t*)buffer, sizeof(buffer)-1, 2000);
}










void AT_configs(void)
{
    int len;

    memset(buffer, 0, sizeof(buffer));

    // ---------------- CIP START TCP ----------------
    memset(buffer, 0, sizeof(buffer));

    HAL_UART_Transmit(&huart6,
        (uint8_t*)"AT+CIPSTART=\"TCP\",\"142.93.218.33\",80\r\n",
        strlen("AT+CIPSTART=\"TCP\",\"142.93.218.33\",80\r\n"),
        1000);

    HAL_UART_Receive(&huart6, (uint8_t*)buffer, sizeof(buffer)-1, 1000);

    if(strstr(buffer,"OK")==NULL && strstr(buffer,"CONNECT")==NULL)
    {
    	scmd(0x01);
        string("TCP FAIL");
        return;
    }

    // ---------------- HTTP ----------------

    sprintf(str,"GET /page.php?temp=%d&hum=1&dev=1\r\n",(int)g_temperature);

    len = strlen(str);
//------------------CIP_SEND------------------
    sprintf(buffer,"AT+CIPSEND=%d\r\n",len);

    HAL_UART_Transmit(&huart6,(uint8_t*)buffer,strlen(buffer),1000);
    HAL_UART_Receive(&huart6,(uint8_t*)buffer,sizeof(buffer)-1,1000);

    if(strchr(buffer,'>')==NULL)
    {
    	scmd(0x01);
        string("CIPSEND FAIL");
        return;
    }

    HAL_UART_Transmit(&huart6,(uint8_t*)str,strlen(str),1000);
    HAL_UART_Receive(&huart6,(uint8_t*)buffer,sizeof(buffer)-1,2000);

    if(strstr(buffer,"SEND OK")==NULL && strstr(buffer,"OK")==NULL)
    {
    	scmd(0x01);
        string("HTTP FAIL");
        return;
    }

    // ---------------- CIP CLOSE ----------------
    HAL_UART_Transmit(&huart6,(uint8_t*)"AT+CIPCLOSE\r\n",13,1000);
    HAL_UART_Receive(&huart6,(uint8_t*)buffer,sizeof(buffer)-1,1000);
    scmd(0x01);
    string("DONE");
}

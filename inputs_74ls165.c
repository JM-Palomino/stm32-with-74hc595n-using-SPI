
#include "inputs_74ls165.h"
#include "tim.h"
#include "gpio.h"


int Bit(int pinLeer){
    int valorBit;
    // Pulso de carga paralela, guarda estado de las entradas
    HAL_GPIO_WritePin(GPIOA, CargarDatos, GPIO_PIN_RESET);//CargarDatos=0
        DelayMicro(10);
    HAL_GPIO_WritePin(GPIOA, CargarDatos, GPIO_PIN_SET);//CargarDatos=1
       DelayMicro(10);
 
    // Lee el valor de bits de la salida QH del 74HC165
     for(int i = 0; i < pinLeer; i++) 
     {
        valorBit = HAL_GPIO_ReadPin(GPIOB, Dato); // leer el pin deseado
          HAL_GPIO_WritePin(GPIOA, Clock, GPIO_PIN_SET);//Clock=1
           DelayMicro(10);
         HAL_GPIO_WritePin(GPIOA, Clock, GPIO_PIN_RESET);//Clock=0 
          DelayMicro(10);
     }
    return(valorBit);
}

int Byte(void){
	
	int value_byte=0;
	  for(int i = 0; i < 8; i++) 
     {
		  value_byte |= (Bit(i+1) << i); 
     }
		return(value_byte); 
}

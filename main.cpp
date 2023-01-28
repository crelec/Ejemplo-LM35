#include "mbed.h"

//static BufferedSerial serial_port(USBTX, USBRX);
static BufferedSerial serial_port(PA_2, PA_3);
//static BufferedSerial serial_port(PA_9, PA_10); //PA_10=D2=UART1_RX  PA_9=D8=UART1_TX "Uso bluetooth"

AnalogIn pinMedido(PA_0); //PA_0=A0

char mensaje[40]={0};
int dato_Entero=0;
int dato_decimal=0;

//Prototipo de función
void medirAnalogo(void);
void Decimal_Entero(float decimal);

//Hilos
Thread hilo_medirAnalogo;

int main()
{
serial_port.write("Hola.!  Arranque del programa.\n\r",32);
hilo_medirAnalogo.start(medirAnalogo);
    while (true) {
        
    }
}

void medirAnalogo(void)
{
    int datoADC;
    float datoMedido;
    
    while(true)
    {
    datoADC=pinMedido.read_u16();// lectura del voltaje como entero corto sin signo entre 0x0 y 0xFFFF
    sprintf(mensaje,"ADC: %d\n\r",datoADC);
    serial_port.write(mensaje,12);
    datoMedido=(datoADC*0.0050354); // ojo conversión a temperatura
    Decimal_Entero(datoMedido);
    sprintf(mensaje,"Temp: %d.%d\n\r",dato_Entero,dato_decimal);
    serial_port.write(mensaje,14);
    ThisThread::sleep_for(3000ms);
    }
}

//funcion decimal entero
void Decimal_Entero(float decimal){
    dato_Entero=int(decimal);
    dato_decimal=(decimal-int(decimal))*1000;
}

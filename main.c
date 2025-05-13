#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>

//////////////////////////////////////////////////////////////////////////////
// Display //

/*
    PD0: Saída : Segmento a
    PD1: Saída : Segmento b
    PD2: Saída : Segmento c
    PD3: Saída : Segmento d
    PD4: Saída : Segmento e
    PD5: Saída : Segmento f
    PD6: Saída : Segmento g
    PD7: Saída : Segmento p
    PB0: Saída : Dezena
    PB1: Saída : Unidade
*/

char digitos7seg[16] = {    0x3F, 0x06, 0x5B, 0x4F, 
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F, 0x77, 0x7C, 
                            0x39, 0x5E, 0x79, 0x71  };

void disp7seg_init(void)
{
    // Configuração das I/Os
    DDRD = 0xFF;
    DDRD |= (1<<0); // Unidade
    DDRD |= (1<<1); // Dezena
}
void disp7seg( unsigned char d)
{
    PORTD = digitos7seg[d];
    PORTB |= (1<<0);    // Dz <- 1
    PORTB &= ~(1<<1);   // Un <- 1 
}
void digitos7seg_un( unsigned char d)
{
    PORTB &= ~(1<<1);
    PORTD = digitos7seg[d];
    PORTB |= (1<<0);
}
void disp7seg_dz( unsigned char d)
{
    PORTB &= ~(1<<0);
    PORTD = digitos7seg[d];
    PORTB |= (1<<1);
}

//////////////////////////////////////////////////////////////////////////////
// Programa Principal //

int main (void)
{
    char i = 0;
    long t = 0;
    disp7seg_init();

    while( 1 )
    {
        if(t % 2)
        {
            disp7seg_dz( (i / 10) % 10);
        }
        else
        {
            disp7seg_un( i % 10);
        }

        _delay_ms(1);
        ++t;
        if( (t%250) == 0)
        {
            i++;
            if( i >=100)
                i = 0;
        }
    }
}
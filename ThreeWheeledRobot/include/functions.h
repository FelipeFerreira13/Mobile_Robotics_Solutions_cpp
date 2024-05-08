#ifndef INCLUDE
#define INCLUDE

#include "VMXPi.h"
#include <sys/syscall.h>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>  /* printf() */
#include <string.h> /* memcpy() */
#include <inttypes.h>

#include "math.h"


inline VMXPi *vmx_ptr;

enum pin_state { HIGH = 1, LOW = 0 };

// void analogWrite( int pin, int value);
// void digitalWrite( int pin, int value);
void delay( uint32_t ms );
void delayMicroseconds( uint32_t us );
uint32_t millis( );
long map(long x, long in_min, long in_max, long out_min, long out_max);
double max( double x, double y );
int max( int x, int y );
double min( double x, double y );
int min( int x, int y );
void piMode( int pin, int mode);



class Serial{
    public:
        Serial(){}
        ~Serial(){}
        void print( string word ){
            printf(word.c_str());
        }
        void print( double word ){
            printf("%f", word);
        }
        void print( int word ){
            printf("%d", word);
        }
        void print( uint32_t word ){
            printf("%d", word);
        }
        void println( string word ){
            printf(word.c_str());
            printf("\n");
        }
        void println( double word ){
            printf("%f", word);
            printf("\n");
        }
        void println( int word ){
            printf("%d", word);
            printf("\n");
        }
        void println( uint32_t word ){
            printf("%d", word);
            printf("\n");
        }
        void begin(  int baudrate ){}
};

#endif
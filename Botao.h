#ifndef _BOTAOH_
#define _BOTAOH_

#include "Arduino.h"
class Botao{
  private:
    int _pin;
    int _tempo = 500;
    boolean _estado = LOW;
    unsigned long int _tempoAnterior = 0;
  public:
    Botao(int pin);
    void test_Botao();   
};
#endif
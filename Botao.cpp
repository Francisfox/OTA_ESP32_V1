#include "Botao.h"
Botao::Botao(int pin){ 
  _pin = pin;
  pinMode(_pin, OUTPUT); 
}
void Botao::test_Botao(){
  if(millis() - _tempoAnterior >= _tempo){
    _tempoAnterior = millis();
    digitalWrite(_pin, _estado);
    _estado = !_estado;
  }
}
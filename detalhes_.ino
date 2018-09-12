void ligar(){
    digitalWrite(12, 1);
    digitalWrite(11, 1);
    //delay(10);
}
void desligar(){
    digitalWrite(12, 0);
    digitalWrite(11, 0);
  
}
void led_E(){
    digitalWrite(12, 1);
   // delay(10);
}
void led_D(){
    digitalWrite(11, 1);
    //delay(10);
}

void buzzer(){
    digitalWrite(10, 1);
    delay(1000);
    digitalWrite(10, 0);
    
}

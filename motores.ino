void atras(int pwm){
  analogWrite(pos1, 0);
  analogWrite(neg1, pwm);

  analogWrite(pos2, 0);
  analogWrite(neg2, pwm);
  
}
void frente(int pwm) {

  analogWrite(pos1, pwm);
  analogWrite(neg1, 0);

  analogWrite(pos2, pwm);
  analogWrite(neg2, 0);
}
void direi(int pwm){
  analogWrite(pos1, 0);
  analogWrite(neg1, pwm+30);

  analogWrite(pos2, pwm);
  analogWrite(neg2, 0);

}
void esquerda(int pwm) {

  analogWrite(pos1, pwm);
  analogWrite(neg1, 0);

  analogWrite(pos2, 0);
  analogWrite(neg2, pwm);

}
void esque(int pwm){
  
  analogWrite(pos1, pwm);
  analogWrite(neg1, 0);

  analogWrite(pos2, 0);
  analogWrite(neg2, pwm+30);

}
void direita(int pwm) {

  analogWrite(pos1, 0);
  analogWrite(neg1, pwm);

  analogWrite(pos2, pwm);
  analogWrite(neg2, 0);
}


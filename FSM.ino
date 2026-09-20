//Pinos
const int pinoBotao = 2;
const int pinoLed = 13;

//Estados da FSM
enum EstadoBotao{IDLE,DEBOUNCE,ATIVO};
EstadoBotao estado = IDLE;
const unsigned long TEMPO_DEBOUNCE = 50; // ms

unsigned long tInicioDebounce = 0;
bool ledLigado = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinoBotao, INPUT_PULLUP);
  pinMode(pinoLed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool pressionado = (digitalRead(pinoBotao) == LOW);

  switch (estado) {
  case IDLE:
    if(pressionado){
      tInicioDebounce = millis();
      estado = DEBOUNCE;

    }break;
  case DEBOUNCE:
    if(!pressionado){
      estado = IDLE;
    }else if(millis() - tInicioDebounce >= TEMPO_DEBOUNCE){
      ledLigado = !ledLigado;
      digitalWrite(pinoLed, ledLigado);
      estado = ATIVO;
    }
    break;
  case ATIVO:
    if(!pressionado){
      estado = IDLE;
    }
    break;
  }
}

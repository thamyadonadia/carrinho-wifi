// importação da biblioteca que contém as funções para os servo motor
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Configuração da rede do ESP (para o modo AP)
const char* ssid = "ESP8266";
const char* password = "senha123";

IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 100, 1);
IPAddress subnet(255, 255, 255, 0);
ESP8266WebServer server(80);

//Funções criadas
void processaComando(char comando);
void handle_OnConnect();
void handle_frente();
void handle_tras();
void handle_parar();
void handle_esquerda();
void handle_direita();
void handle_meio();
void handle_NotFound();

String SendHTML();

// definição de constantes que serão usadas ao longo do código
#define velocidadeMotor 1023   //Varia proporcionalmente entre 0 e 1023
#define esquerda 2 
#define direita 165
#define meio 90
#define pinoServo D6
#define motorCC_ENB D7
#define motorCC_IN3 D1
#define motorCC_IN4 D2

// Variável para controle serial, usada para testes
char comando;

// Objeto para controlar o servo
Servo motorServo;

void setup() {
  
  Serial.begin(115200);
  
  // Configuração dos pinos
  pinMode(motorCC_ENB, OUTPUT);
  pinMode(motorCC_IN3, OUTPUT);
  pinMode(motorCC_IN4, OUTPUT);
  
  // Motores desligados 
  digitalWrite(motorCC_IN3, LOW);
  digitalWrite(motorCC_IN4, LOW);

  // Configuração do servo motor
  motorServo.attach(pinoServo);
  motorServo.write(meio);

  //Configuração do ESP como AP
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);

  // Configura as requisições HTTP
  server.on("/", HTTP_GET, handle_OnConnect);
  server.on("/f", HTTP_GET, handle_frente);
  server.on("/t", HTTP_GET, handle_tras);
  server.on("/p", HTTP_GET, handle_parar);
  server.on("/e", HTTP_GET, handle_esquerda);
  server.on("/d", HTTP_GET, handle_direita);
  server.on("/m", HTTP_GET, handle_meio);
  server.onNotFound(handle_NotFound);

  //Inicializa o servidor
  server.begin();
  Serial.println("ESP8266 car server started.");

  // Define a velocidade do motor
  analogWrite(motorCC_ENB, velocidadeMotor);
}

void loop() {
  //Possibilidade de controle serial
  if(Serial.available() > 0){
    processaComando(Serial.read());
  }

  //Monitora as requisições
  server.handleClient();
  server.send(200, "text/html", SendHTML());
}

//Função chamada quando um dispositivo se conectar ao ESP
void handle_OnConnect() {
  processaComando('p');
  Serial.println("Client connected");
  server.send(200, "text/html", SendHTML());
}


//Funções chamadas de acordo com as diferentes requisições
void handle_frente(){
  processaComando('f');
  server.send(200, "text/html", SendHTML());
}

void handle_tras(){
  processaComando('t');
  server.send(200, "text/html", SendHTML());
}

void handle_parar(){
  processaComando('p');
  server.send(200, "text/html", SendHTML());
}

void handle_esquerda(){
  processaComando('e');
  server.send(200, "text/html", SendHTML());
}

void handle_direita(){
  processaComando('d');
  server.send(200, "text/html", SendHTML());
}

void handle_meio(){
  processaComando('m');
  server.send(200, "text/html", SendHTML());
}



// Função chamada ao requisitar um endereço inexistente
void handle_NotFound(){
  server.send(200, "text/html", "Not Found");
}

//Função para manipular os motores de acordo com o comendo
void processaComando(char comando){
  Serial.println("COMANDO:");
  Serial.println(comando);

  switch (comando){
    //Motor de tração ligado (frente)
    case 'f':
      digitalWrite(motorCC_IN3, HIGH);
      digitalWrite(motorCC_IN4, LOW);
      Serial.print("FRENTE");
      break;

    //Motor de tração ligado (trás)
    case 't':
      digitalWrite(motorCC_IN3, LOW);
      digitalWrite(motorCC_IN4, HIGH);
      Serial.print("TRÁS");
      break;

    //Motor de tração desligado
    case 'p':
      digitalWrite(motorCC_IN3, LOW);
      digitalWrite(motorCC_IN4, LOW);
      Serial.print("PARAR");
      break;

    //Mudar a direção (direita)
    case 'd':
      motorServo.write(direita);
      Serial.print("DIRETA");
      break;

    //Mudar a direção (esquerda)
    case 'e':
      motorServo.write(esquerda); 
      Serial.print("ESQUERDA");
      break;

    //Mudar a direção (meio)
    case 'm':
      Serial.print("MEIO");
      motorServo.write(meio);
      break;

    default:
      return;
  }
  return;
}

// Função que retorna o texto HTML da página
String SendHTML(){
  String html = "<!DOCTYPE html>";
  html += "<html>\n";
  html += "<head>\n";
  html += "<title>ESP8266 WiFi Car</title>\n";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  html += "<style>\n";
  html += "body {\n";
  html += "background-color: #121212;\n";
  html += "}\n";
  html += "h1 {\n";
  html += "color: #67db7b ;\n";
  html += "text-align: center  ;\n";
  html += "}\n";
  html += "h2 {\n";
  html += "color: #ffffff;\n";
  html += "text-align: center;\n";
  html += "}\n";
  html += "input{\n";
  html += "width: 15vw;\n";
  html += "height: 15vw;\n";
  html += "margin: 10px;\n";
  html += "color: #121212;\n";
  html += "background-color: #67db7b;\n";
  html += "}\n";
  html += "#controls {\n";
  html += "padding:50px 0;\n";
  html += "justify-content:space-between;\n";
  html += "display: flex;\n";
  html += "flex-direction: row;\n";
  html += "}\n";
  html += "#left_controls{\n";
  html += "margin: auto;\n";
  html += "display: flex;\n";
  html += "flex-direction: column;\n";
  html += "}\n";
  html += "#right_controls{\n";
  html += "margin: auto;\n";
  html += "width: auto;\n";
  html += "display: flex;\n";
  html += "flex-direction: row;\n";
  html += "}\n";
  html += "</style>\n";
  html += "</head>\n";
  html += "<body>\n";
  html += "<header>\n";
  html += "<h1>Gambiarra-mobile</h1>\n";
  html += "<h2>Dirija com moderação</h2>\n";
  html += "<br>\n";
  html += "</header>\n";
  html += "<div id=\"controls\">\n";
  html += "<form method=\"GET\" id=\"left_controls\">\n";
  html += "<input type=\"button\" value=\"/\\\" onclick=\"window.location.href='/f'\">\n";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"O\" onclick=\"window.location.href='/p'\">\n";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"\\/\" onclick=\"window.location.href='/t'\">\n";
  html += "<br><br>\n";
  html += "</form>\n";
  html += "<div id=\"right_controls\">\n";
  html += "<input type=\"button\" value=\"<-\" onclick=\"window.location.href='/e'\">\n";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"O\" onclick=\"window.location.href='/m'\">\n";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"->\" onclick=\"window.location.href='/d'\">\n";
  html += "<br><br>\n";
  html += "</div>\n";
  html += "</div>\n";
  html += "</body>\n";
  html += "</html>\n";

  return html;
}

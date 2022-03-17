# Carrinho controlado via Wi-Fi
> Alunos: Afonso Salvador de Magalhães, Diogo Delazare Brandão e Thamya Vieira Hashimoto Donadia 
Mostra Projeto Integrador em Computação I - 2021.2
Universidade Federal do Espírito Santo (UFES) 

## Descrição do projeto 


## Materiais utilizados 
**1. Componentes para a montagem física**
   - Módulo Wi-Fi ESP8266
   - Driver Ponte H L298N
   - 1x Motor DC/CC
   - 1x Servo motor 
   - Protoboard 
   - Jumpers
   - Conector de bateria 9V
   - Estrutura de um carrinho de brinquedo 

**2. Softwares**
   - Arduino IDE
    
## Hardware - Montagem do circuito 
**1. Esquemático e explicação das conexões**  
: Aqui temos as conexões realizadas para montar o carrinho. O motor CC/DC é conectado ao driver e utilizado para movimentar o carrinho para frente ou para trás. Os pinos de input (IN1, IN2, IN3, IN4) do driver são conectados a um pino digital do ESP e utilizados para determinar a direção de movimento do motor CC/DC. Já os pinos ENABLE (ENA, ENB) são conectados a pinos PWM do ESP para controlar a velocidade de rotação do motor. Por outro lado, o servo motor foi conectado a um pino PWM do ESP, de modo que é possível controlar a angulação de rotação do motor. (TERMINAR)

| Driver | L298N |  
|--------|-------|  


**2. Montagem física**  
   O sistema foi montado por cima da base do chassi de um antigo carrinho de brinquedo, aproveitando seus eixos de roda e seu interruptor para desligá-lo. O motor DC é colocado na parte de trás do carrinho e conectado ao eixo traseiro, já o servo motor é responsável pela movimentação direcional do eixo dianteiro. O motor DC está conectado diretamente ao Driver Ponte H, que recebe as ordens do ESP pelos pinos IN3, IN4 e ENB.(TERMINAR)


## Software - Explicação do código  
   A priori, foi necessário configurar a IDE do Arduino para programar o ESP8266

**1. Código para controlar os motores**  
   No início do código, foram definidas constantes para nomear os pinos que estão conectados o servo motor e o motor CC/DC, a velocidade de atuação do motor e a angulação de giro do servo. Após isso, temos os comandos do ESP para Driver, a fim de controlar o motor CC/DC. Para isso foi utilizada uma tabela lógica que define o sinal digital dos pinos IN3 e IN4, de modo que o carrinho se movimente para frente, para trás ou fique parado. As permutações utilizadas no código e seus resultados são demonstrados a seguir. Além disso, foi definida uma velocidade padrão para a movimentação do carrinho.  

|  IN3  |  IN4  | Resultado |
|-------|-------|-----------|
| High  |  Low  | Frente    |
|  Low  |  High | Trás      |
|  Low  |  Low  | Parado

   Para fazer o carrinho virar para um lado ou outro, foi utilizada a biblioteca Servo.h para controlar o servo motor. Desse modo, foi definida uma angulação base para ele virar para um lado e o oposto para virar para o outro lado. Por fim, utilizou-se a função da própria biblioteca para aplicar a angulação de giro no servo motor.

**2. Conexão Wi-Fi**  







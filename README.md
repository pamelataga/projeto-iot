# projeto-iot

#1º Passo: Montar

##itens necessários
#Para o sensor e atuador:
1 - Placa ESP8266
1 - protoboard 400 pontos
1 - cabo USB padrão 

#Para o sensor: 
1 - Sensor DTH 22
3 - Jumpers macho-fêmea

#Para o atuador: 
1 - Led (qualquer cor)
1 - jumper macho-macho
1 - jumper macho-fêmea
1 - resistor 220 ohms

Imagem de como deve ficar a montagem com os itens acima: 

![prototipo](https://user-images.githubusercontent.com/43140253/144505461-c46f26b0-fbda-437b-b5ac-10c6b657297e.jpeg)

#2º Passo: Programar

##Códigos-fonte
Na pasta programação tem 3 códigos:
- "liga_desliga_led_teste" = teste para testar se a montagem do led esta funcionando corretamente 
- "temperatura_com_mqtt_funcionando" = apenas a programação que exibe a temperatura e humidade com o protocolo mqtt funcionando corretamente
- "codigo_completo" = programação completa do projeto

- Para o funcionamento dos códigos é necessário ter a IDE Arduino instalada em seu computador, baixar as bibliotecas: "PubSubClient". "ESP8266WiFi" e "DHT" e ir em "Ferramentas" -> "Porta" -> Selecionar a porta "COM5". 

#3º Passo: Configurar o Aplicativo

##Aplicativo
- Baixar o app: Mqtt Dashboar - IoT and Node-RED controller (sistema android)

#Fazer a configuração do servidor broker: 
- Clicar no Botão +; 
- Preencher os campos nome do servidor = "Nome livre para o seu projeto", Address = "mqtt.eclipseprojects.io", Port = "1883", selecionar a opção QOS1 e clicar no ícone salvar.

#Criar os botões para as funções do projeto
- Clicar no Botão +;

Temperatura:  
- Escolher o botão "text"; 
- Preencher os campos: Nome do Bloco = "Temperatura", tópico para inscrever = "lab/temp", Desabilitar a opção "habilitar publicação" (Caso esteja selecionada), personalizar o ícone com imagem e cor conforme tua preferencia e clicar no botão salvar;  

Humidade:  
- Escolher o botão "text"; 
- Preencher os campos: Nome do Bloco = "Humidade", tópico para inscrever = "lab/humid", Desabilitar a opção "habilitar publicação" (Caso esteja selecionada), personalizar o ícone com imagem e cor conforme tua preferencia e clicar no botão salvar;  

Temperatura:  
- Escolher o botão "button"; 
- Preencher os campos: Nome do Bloco = "Led", tópico para publicar = "casa/sala", personalizar o ícone com imagem e cor conforme tua preferencia e clicar no botão salvar;  

#Pronto! seu projeto já está funcionando


#Breve explicação do funcionamento:
O sensor DHT22 faz as leituras, através do MQTT Broker Eclipse, faz o método publish e se comunica com o app Mqtt Dashboard. 

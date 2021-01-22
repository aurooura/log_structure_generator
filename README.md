# log_structure_generator

Para usar o codigo, basta clonar no terminal.
Digitar cd log_structure_generator(entrar na pasta) e digitar:
make str_proc 

O arquivo para gerar as estruturas segue o seguinte:


[MODELO] [NOME]
[FUNCAO]
[TIPO0] [VARIAVEL0]
[TIPO1] [VARIAVEL1]
.
.
.
[TIPON] [VARIAVELN]

Exemplo:
EKF_21 EKFL
SelectVelPosFusion2
float velPosObs[0]
float velPosObs[1]
float velPosObs[2]
float velPosObs[3]
float velPosObs[4]
float velPosObs[5]
float gpsDataDelayed.sensor_idx
float fuseVelData
float fusePosData

Para utilizar basta digitar no terminal dentro da pasta:
./str_proc <arquivo_de_entrada >arquivo_de_saida.txt
Desta forma, as estruturas estarao em arquivo_de_saida.txt



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
END

[MODELO] [NOME]
[FUNCAO]
[TIPO0] [VARIAVEL0]
[TIPO1] [VARIAVEL1]
.
.
.
[TIPON] [VARIAVELN]
END

[MODELO] [NOME]
[FUNCAO]
[TIPO0] [VARIAVEL0]
[TIPO1] [VARIAVEL1]
.
.
.
[TIPON] [VARIAVELN]
END


Exemplo:
CP01 CP01
CovariancePrediction01

float P[0][0];
float P[0][1];
float P[0][2];
float P[0][3];
float P[0][4];
float P[0][5];
float P[0][6];
float P[0][7];
float P[0][8];
float P[0][9];
float P[0][10];
float P[0][11];
float P[0][12];
float P[0][13];
float P[0][14];
END
CP02 CP02
CovariancePrediction02
float stateStruct.gyro.scale.z;
float stateStruct.accel.zbias;
float stateStruct.velocity.z;
float imuDataDelayed.delAngDT;
float inhibitMagStates;
float inhibitWindStates;
float hgtRate;
float expectGndEffectTakeoff;
float stateIndexLim;
float dtEkfAvg;
END
CP03 CP03
CovariancePrediction03
float P[19][19];
float P[19][20];
float P[19][21];
float P[19][22];
float P[19][23];
float P[20][20];
float P[20][21];
float P[20][22];
float P[20][23];
float P[21][21];
float P[21][22];
float P[21][23];
float P[22][22];
float P[22][23];
float P[23][23];
END

Para utilizar basta digitar no terminal dentro da pasta:
./str_proc <arquivo_de_entrada >arquivo_de_saida.txt
Desta forma, as estruturas estarao em arquivo_de_saida.txt



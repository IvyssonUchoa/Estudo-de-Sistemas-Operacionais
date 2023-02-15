import time

#leitura do arquivo
arq = open("arquivo.txt")
linhas = arq.readlines()
linhaDiv = []

#dividindo dados em listas e dicionarios
for linha in linhas:
  linhaDiv.append(linha.split(";"))

tempo = {}
prioridade = list()
processo = {}
for i in range(len(linhaDiv)):
  for j in range(len(linhaDiv)):
    if(j==0 or j==2):
      processo[linhaDiv[i][0]] = [linhaDiv[i][2]]
    if(j==2):
      prioridade.append(linhaDiv[i][2])
    if(j==2 or j==1):
      tempo[linhaDiv[i][1]] = [linhaDiv[i][2]]

#organizando em ordem de preferencia os dados
processo = sorted(processo, key = processo.get, reverse=True)
tempo = sorted(tempo, key = tempo.get, reverse=True)
prioridade.sort(reverse = True)

#Variáveis
fila_processo = []
quantum = 10 

#Funções
def cria_fila():
  for i in range(5): 
    fila_processo.append(dict()) #cria uma matriz

  for i in range(len(processo)):
      pri = int(prioridade[i])
      fila_processo[pri - 1][processo[i]] = int(tempo[i])

def imprime_fila():
  print("FILA DE PROCESSOS:")
  for i in range(len(fila_processo)):
    print(i + 1, end=" ")
    print(fila_processo[i])
  print()

def cpu():
  for pri in range((len(fila_processo)-1), -1, -1): #percorre as prioridades
    print("# Executando prioridade {} #".format(pri + 1))
    print()
    
    while(len(fila_processo[pri]) != 0): #enquanto houver processos dessa prioridade
      processos_concluido = []
      
      for processo_atual in fila_processo[pri]: #percorre os processos
        print("O processo {} está na CPU".format(processo_atual))
        tempo_processo = fila_processo[pri][processo_atual]
        
        if tempo_processo > quantum:
          print("Executando por {} segundos".format(quantum))
          time.sleep(quantum) #executa o processo
          fila_processo[pri][processo_atual] -= quantum #salva o valor restante de processamento
          
        else:
          print("Executando por {} segundos".format(tempo_processo))
          time.sleep(tempo_processo) #Executa o processo
          fila_processo[pri][processo_atual] = 0 #executou tudo
          processos_concluido.append(processo_atual)
          print("O processo {} foi concluido ".format(processo_atual))
          
        print("O processo {} saiu da CPU".format(processo_atual))
        print()

      for p in processos_concluido:
        fila_processo[pri].pop(p) #retira os processos encerrados da fila
        
    print("# Fim da execução de prioridade {} #".format(pri + 1)) 
    print()
#-----------------------Main-----------------------#
cria_fila()
imprime_fila()
cpu()
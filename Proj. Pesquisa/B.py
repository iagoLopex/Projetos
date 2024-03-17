import pandas as pd
from sklearn import preprocessing
from sklearn.preprocessing import MinMaxScaler
#import numpy as np
#import tensorflow as tf
#from sklearn.neighbors import NearestNeighbors
#from sklearn.model_selection import train_test_split
#from sklearn.neural_network import MLPClassifier
#from sklearn.metrics import accuracy_score
#from tensorflow.keras import regularizers
#from tensorflow.keras import initializers

#from tensorflow.keras.layers import Dense, Flatten, Add

df = pd.read_excel("casos-promote.xlsx", header=0)
#print(len(set(df.iloc[:, 1])))
#print(df)

df.drop(columns=["prontuario"], axis=1, inplace=True)
df.dropna(subset=[0], axis=1, inplace=True)
df["valor"] = df["valor"].str.upper()
#print(df)

#filtrando apenas com os tres formularios de triagem que vamos usar
data = df[df['formulario_tag'].isin(
    ['remotePrimaryScreeningInNewNeurology',
     'remoteScreeningTrackingNewNeurology',
     'presentialScreeningFormNeurology'])]

#numero de casos unicos
data['case_uuid'].unique().shape
#print(data)

#cria a formatação do novo dataset
unique_parameters = data['parametro_tag'].unique()

# Criar um novo DataFrame com colunas para cada valor único de parameter_tag e case_uuid
new_df = pd.DataFrame(columns=['case_uuid'] + list(unique_parameters))

# Preencher o novo DataFrame com valores do case_uuid do DataFrame original
new_df['case_uuid'] = data['case_uuid'].unique()

#preenche o restante das colunas com os respectivos valores quando existentes
for index, row in data.iterrows():
    id = row['case_uuid']
    value = row['valor']
    tag = row['parametro_tag']
    indice_linha = new_df.index[new_df['case_uuid'] == id].tolist()
    new_df.loc[indice_linha, tag] = value

#Ajuste na coluna com valores similares
new_df['patientFastingBetweenNineAndTwelveHours'].replace('1. SIM', 'SIM', inplace=True)
new_df['patientFastingBetweenNineAndTwelveHours'].replace('0. NÃO', 'NÃO', inplace=True)
#print(new_df)

#colunas eliminadas do dataset (não definitivas, apenas para teste)
colunas_para_eliminar = ['bodyMassIndexClassificationHmv',
                         'bodyMassIndicatorCalculatorHmv',
                         'cardiovascularRiskInTenYears',
                        'referenceHealthUnitPromote',
                        'doYouWantToFollowTheCompletionThisQuestionnaire',
                        'bodyMassIndicator',
                        'heartRate',
                        'secondBloodHeartRate',
                        'diastolicPressureCardiorespiratory',
                        'secondBloodDiastolicPressureCardiorespiratory',
                        'systolicBloodPressure',
                        'secondBloodSystolicBloodPressure',
                        'height',
                        'mass',
                        'controlAssistantNumeric',
                        'participatingInAnother']

new = new_df.drop(colunas_para_eliminar, axis=1)
#print(new)

#new.to_excel('dados.xlsx', index=False)        comando para queira baixar o dataset em planilha
new.shape #formato do dataset que sera usado pra criar o conjunto de pares

le=preprocessing.LabelEncoder()

# normalizar as colunas com valor real
colunas_reais = ['meanDiastolicBloodPressure', 'meanSystolicBloodPressure', 'averageHeartRate']
colunas_categoricas = [coluna for coluna in new.columns if coluna not in colunas_reais]
scaler = MinMaxScaler()
new[colunas_reais] = scaler.fit_transform(new[colunas_reais])
new[colunas_reais] = new[colunas_reais].round(1)

for column in new.columns:
    if new[column].dtype == 'O' and column not in colunas_reais: #é uma string
        categories = new[column].unique()
        contador = 0

        for category in categories:
            if(not(pd.isnull(category))):
                new[column].replace(category, contador, inplace=True)
                contador = contador + 1

#newColumn = le.fit_transform(data[column])
        #data[column]=newColumn
#le.inverse_transform(newClass)

new.fillna(-1, inplace = True)  #teste preenchendo Nan com -1


# teste deletando todas as colunas com valor unico
colunas_com_um_valor = new.nunique() == 1
CB = new.drop(columns=colunas_com_um_valor[colunas_com_um_valor].index)


# ____________________________ Variaveis ______________________________________

Mapa_group = {}
group = [(0, 0.2), (0.3, 0.5), (0.6, 0.8), (0.9, 1.0)]
categoric = {}
RulesIdx = []
freq = []
Prob = []
w = {}
w_linha = {}
atributos = CB.columns.tolist()
atributos.remove("controlParameterForPromoteStudy")
idx_Solucao = "controlParameterForPromoteStudy"
MAXN = 260

for i in atributos:
    if(i == 'meanDiastolicBloodPressure' or i == 'meanSystolicBloodPressure' or i == 'averageHeartRate'):
        categoric[i] = 0
    else:
        categoric[i] = 1
# -----------------------------------------------------------------------------

# _______________________ Similaridade ________________________________________
def similarity_Quant(Va, Vb, mx, mn):
    if (Va == Vb and Va != -1): 
        return 1.0
    elif (Va == -1 or Vb == -1): 
        return 0.0
    else: 
        return ((1.0 - abs(Va - Vb)/(mx - mn)))

def similarity_Nom(Va, Vb, idx):
    if (Va == Vb and Va != -1): 
        return 1.0
    elif (Va == -1 or Vb == -1): 
        return ( 1.0/ (CB[idx].nunique()) )
    else: 
        return (0.0)

def simFeature(Va, Vb, mx, mn, idx):
    if(categoric[idx] == 1):
        return similarity_Nom(Va, Vb, idx)
    else:
        return similarity_Quant(Va, Vb, mx, mn)

def simCases(Ca, Cb):
    #estou lidando Ca e Cb como variaveis que indicam a linha de cada caso
    soma, SumW = 0, sum(w)
    for i in range (0, atributos):
        mx, mn = -1000, 1000
        for j in range (0, len(CB)):
            if(CB.loc[j, i] != -1):
                mx = max(mx, CB.loc[j, i])
                mn = min(mn, CB.loc[j, i])
        
        soma = soma + (w[i] * simFeature(CB.loc[Ca, i], CB.loc[Cb, i], mx, mn, i) / SumW)
    return soma

# -----------------------------------------------------------------------------



# ____________________________ PESO ___________________________________________

def weight():
    for i in atributos: 
        
        mx, mn = -1000.0, 1000.0
        SH, SS, DH, DS = 0, 0, 0, 0
        
        for j in range (0, MAXN):
            if(CB.loc[j, i] != -1):
                mx = max(mx, CB.loc[j, i])
                mn = min(mn, CB.loc[j, i])
            
        for j in range (0, MAXN-1):
            for k in range (j+1, MAXN):
                
                similarity = simFeature(CB.loc[j, i], CB.loc[k, i], mx, mn, i)
                if(CB.loc[j, idx_Solucao] == CB.loc[k, idx_Solucao]):
                    if(similarity > 0.9):
                        SH += 1
                    else:
                        SS += 1
                else:
                    if(similarity > 0.9):
                        DH += 1
                    else:
                        DS += 1
        
        w_linha[i] = ((SH + DS) - (SS + DH))
        
def normalize():
    
    mx = max(w_linha.values())
    mn = min(w_linha.values())
        
    for i in w_linha:
        w[i] = ( (w_linha[i] - mn)/(mx-mn) )

weight()
normalize()
# -----------------------------------------------------------------------------


#_____________________________ RULES __________________________________________


def calcIdxRules():
    Aux = []
    for i in w:
        Aux.append((w[i], i))
    Aux = sorted(Aux, key=lambda x: x[0], reverse=True)
    for i in Aux:
        if(i[0] > 0):
            RulesIdx.append(i[1])
    
    for i in range (0, len(RulesIdx)):
        if RulesIdx[i] in colunas_reais:
            Mapa_group[i] = group

# 1 - diminuir os casos ao inrredutivel
# 2 - separá-los em duas estruturas 'RedS0' e 'RedS1'
#
# OBS: No artigo ele nao fala sobre os valores nulos entao vou assumir pra continuar buscando

RedS0 = []
RedS1 = []

def ReductionCases():
    PP = len(CB)
    for i in range(0, PP):
        idxLim = 1
        for j in range(0, PP):
            if(CB.loc[i, idx_Solucao] != CB.loc[j, idx_Solucao]):
                
                for k in range(0, len(RulesIdx)):
                    
                    v1 = CB.loc[i, RulesIdx[k]]
                    v2 = CB.loc[j, RulesIdx[k]]
                    
                    if(v1 != v2 and v1 != -1 and v2 != -1):
                        idxLim = max(idxLim, k+1)
                        break
                    
        new_case = []
        for j in range(0, idxLim):
            new_case.append(CB.loc[i, RulesIdx[j]])
        
        if(CB.loc[i, idx_Solucao] == 0):
            RedS0.append(new_case)
        else:
            RedS1.append(new_case)

calcIdxRules()
ReductionCases()

# -> Crio uma arvore de prefixo(Rule) para o 'RedS0' e uma para 'RedS1'
# -> É necessario modificar a chave para pair no caso de valores de ponto
#    flutuante ou range de idades (10, 20), (21, 30), ...

class TrieNode:
    def __init__(self):
        self.children = {}
        self.high = 0
        self.is_end_of_word = False

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, value):
        node = self.root
        altura = 0
        for num in value:
            
            # é um valor real entao eu vou ter que inserir um node do tipo grupo
            if altura in Mapa_group:
                for i, valor in enumerate(Mapa_group[altura]):
                    if num >= valor[0] and num <= valor[1]:
                        num = i + 100
            
            if num not in node.children:
                node.children[num] = TrieNode()
            node.children[num].high = node.high + 1
            node = node.children[num]
            altura += 1
        node.is_end_of_word = True

    def search(self, value):
        node = self.root
        for num in value:
            if num not in node.children:
                return False
            node = node.children[num]
        return node.is_end_of_word

    def starts_with_prefix(self, prefix):
        node = self.root
        for num in prefix:
            if num not in node.children:
                return False
            node = node.children[num]
        return True
    
    def _print_trie(self, node, prefix=[]):
        if node.is_end_of_word:
            print(" ".join(map(str, prefix)))

        for key, child_node in node.children.items():
            self._print_trie(child_node, prefix + [key])

    def printPrefixes(self):
        self._print_trie(self.root)

TreeS0 = Trie()
TreeS1 = Trie()

for i in RedS0:
    TreeS0.insert(i)
for i in RedS1:
    TreeS1.insert(i)

TreeS0.printPrefixes()
print("\n")
TreeS1.printPrefixes()

# -----------------------------------------------------------------------------


'''
1
Pedir ajuda para analisar os pesos das variaveis

2
colunas de valores unicos podem ser deletadas?

3
quais sao as variaveis Nominais e Quantitativas?
(foi feito um compress de indexagem, algumas variaveis quantitativas 
 foram substituidas pelo valor da primeira vez em que aparecem, isso
 nao gera um problema Quando o valor for mais proximo ou mais longe 
 do maximo ou minimo, perdendo o peso da mesma?)

4
O autor nao lida com problemas de divisao por zero, minha abordagem 
pra resolver faz sentido?

5
Apos resolver essas questoes ir ao teste: 
    Geração de Rules
    Insercao das Rules na Trie

#_________________________

3 variaveis reais que nao podem retirar as grandezas 
85.4  0.854  round(0.854, 1) 0.8
tirar os Max dos denominadores
all possible values

Interface
Dados com valores com valores constantes ou nulos (ex: somente nao e nulo)
Possibilidade de mais dados


#___________________________
13/
- Finalizada a implementaçao da arvore de regras
- Comprimi os nodes que sao de valores reais em sub-ranges
- Testei retirar todas as colunas que possuem um valor constante unico os
  os valores dos pesos agora fazem mais sentido


'''


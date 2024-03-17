# -*- coding: utf-8 -*-
"""
Created on Thu Feb  1 15:23:45 2024

@author: iago

------------------- Database --------------------------------------------------
1. BI-RADS assessment: 1 to 5 (ordinal, non-predictive!)  
2. Age: patient's age in years (integer)
3. Shape: mass shape: round=1 oval=2 lobular=3 irregular=4 (nominal)
4. Margin: mass margin: circumscribed=1 microlobulated=2 obscured=3 ill-defined=4 spiculated=5 (nominal)
5. Density: mass density high=1 iso=2 low=3 fat-containing=4 (ordinal)
6. Severity: benign=0 or malignant=1 (binominal, goal field!)

-------------------------------------------------------------------------------
"""

age = list(range(10))
age.append(-1)
Possible_values = [ [0, 1, 2, 3, 4, 5, 6, -1], 
                    age,
                    [1, 2, 3, 4, -1],
                    [1, 2, 3, 4, 5, -1],
                    [1, 2, 3, 4, -1],
                    [0, 1] ]

RulesIdx = []
freq = []
Prob = []
CB = []
w = []
w_linha = []
atributos = 5
idx_Solucao = 5
MAXN = 961

with open('mammographic_massesData.txt', 'r') as arquivo:
    for v in arquivo:
        alt = v.replace("?", "-1")
        sep = [int(j) for j in alt.split(",")]
        CB.append(sep)

#______________________ Ordem para passar no vetor ____________________________

def calcIdxRules():
    Aux = []
    for i in range (0, len(w_linha)):
        Aux.append((w_linha[i], i))
    Aux = sorted(Aux, key=lambda x: x[0], reverse=True)
    for i in Aux:
        if(i[0] > 0):
            RulesIdx.append(i[1])

# ____________________________ PESO ___________________________________________


def weight():
    for i in range (0, atributos): 
        
        mx, mn = -100.0, 100.0
        SH, SS, DH, DS = 0, 0, 0, 0
        
        for j in range (0, MAXN):
            if(CB[j][i] != -1):
                mx = max(mx, CB[j][i])
                mn = min(mn, CB[j][i])
            
        for j in range (0, MAXN-1):
            for k in range (j+1, MAXN):
                
                similarity = simFeature(CB[j][i], CB[k][i], mx, mn, i)
                if(CB[j][idx_Solucao] == CB[k][idx_Solucao]):
                    if(similarity > 0.5):
                        SH += 1
                    else:
                        SS += 1
                else:
                    if(similarity > 0.5):
                        DH += 1
                    else:
                        DS += 1
        
        w_linha.append((SH + DS) - (SS + DH))


# --------------------- Normalizacao ------------------------------------------
def normalize():
    mx, mn = -w_linha[0], w_linha[0]
    for i in w_linha:
        mx = max(mx, i)
        mn = min(mn, i)
    
    for i in w_linha:
        w.append( (i-mn)/(mx-mn) )


# ---------------------- Similaridade -----------------------------------------
def similarity_Quant(Va, Vb, mx, mn):
    if (Va == Vb): 
        return 1.0
    elif (Va == -1 or Vb == -1): 
        return 0.0
    else: 
        return ((1.0 - abs(Va - Vb)/(mx - mn)))

def similarity_Nom(Va, Vb, idx):
    if (Va == Vb): 
        return 1.0
    elif (Va == -1 or Vb == -1): 
        return ( 1.0/(sum(linha[idx] == -1 for linha in CB)) )
    else: 
        return (0.0)

def simFeature(Va, Vb, mx, mn, idx):
    if(idx != 1):
        return similarity_Nom(Va, Vb, idx)
    else:
        return similarity_Quant(Va, Vb, mx, mn)

def simCases(Ca, Cb):
    #estou lidando Ca e Cb como variaveis que indicam a linha de cada caso
    soma, SumW = 0, sum(w)
    for i in range (0, atributos):
        mx, mn = -100, 100
        for j in range (0, len(CB)):
            if(CB[j][i] != -1):
                mx = max(mx, CB[j][i])
                mn = min(mn, CB[j][i])
        
        soma = soma + (w[i] * simFeature(CB[Ca][i], CB[Cb][i], mx, mn, i) / SumW)
    
    return soma


weight()
normalize()
calcIdxRules()

#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# 1 - diminuir os casos ao inrredutivel
# 2 - separá-los em duas estruturas 'RedS0' e 'RedS1'
#
# OBS: No artigo ele nao fala sobre os valores nulos entao vou assumir pra continuar buscando

RedS0 = []
RedS1 = []

def ReductionCases():
    PP = 20
    for i in range(0, PP):
        idxLim = 1
        for j in range(0, PP):
            if(CB[i][idx_Solucao] != CB[j][idx_Solucao]): 
                
                for k in range(0, len(RulesIdx)):
                    
                    v1 = CB[i][RulesIdx[k]]
                    v2 = CB[j][RulesIdx[k]]
                    
                    if(v1 != v2 and v1 != -1 and v2 != -1):
                        idxLim = max(idxLim, k+1)
                        break
                    
        new_case = []
        for j in range(0, idxLim):
            new_case.append(CB[i][RulesIdx[j]])
        
        if(CB[i][idx_Solucao] == 0):
            RedS0.append(new_case)
        else:
            RedS1.append(new_case)
            
ReductionCases()

#------------------------------------------------------------------------------
# -> Crio uma arvore de prefixo(Rule) para o 'RedS0' e uma para 'RedS1'
# -> É necessario modificar a chave para pair no caso de valores de ponto
#    flutuante ou range de idades (10, 20), (21, 30), ...

class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, value):
        node = self.root
        for num in value:
            if num not in node.children:
                node.children[num] = TrieNode()
            node = node.children[num]
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
#------------------------------------------------------------------------------



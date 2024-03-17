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

------------------- Artigo ----------------------------------------------------
• t1 = BI-RADS: assessment refers to Breast Imaging Reporting
       and Data System. It is a categorical feature. Its possible values
       are {0, 1, 2, 3, 4, 5, 6, Ø}, where zero indicates incomplete assessment, One means that the mammogram is surely benign,
       up to five, which means that the mammogram is highly suggestive of malignancy.
• t2 = Age: patient’s age in years. A quantitative feature. It could
       be Ø where Ø represents the value null.
• t3 = mass shape. A categorical feature. Its possible values are
       {round, oval, lobular, irregular, Ø}.
• t4 = mass margin. A categorical feature. Its possible values
       are {circumscribed, micro-lobulated, obscured, ill-defined, speculated, Ø}.
• t5 = mass density. A categorical feature. Its possible values are
       {high, iso, low, fat-containing, Ø}.
• The set of solutions which represent the severity of mammographic mass is {benign, malignant}.

t1 - categorical
t2 - quantitative
t3 - categorical
t4 - categorical
t5 - categorical

-------------------------------------------------------------------------------
"""

age = list(range(100))
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
        
# ----------------------- Precalcular -----------------------------------------
    
def occ(coluna, value):
    cnt = 0
    for i in range (0, len(CB)):
        if(CB[i][coluna] == value):
            cnt += 1
    return cnt

def frequencia():
    for i in range (0, len(Possible_values)):
        mapa = {}
        for j in Possible_values[i]:
            mapa[j] = occ(i, j)
        freq.append(mapa)

def CalcProb():
    for i in range (0, len(freq)):
        mapa = {}
        for j in freq[i]:
            mapa[j] = (freq[i][j]/len(CB))
        Prob.append(mapa)

frequencia()
CalcProb()

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
# -----------------------------------------------------------------------------
  



# __________________________ REVISAO __________________________________________

# ------------------- Etapa Coerencia(1) -------------------------------------- 

def CalcProbCase(Ca):
    p = 1.0
    print(Ca)
    for i in range(0, atributos+1):
        p = p * Prob[i][CB[Ca][i]]
    return p

def same(Ca, tipo):
    den = 0.0
    cnt = 0
    for i in range (0, len(CB)):
        ok = 1
        for j in range (0, atributos):
            if(CB[Ca][j] != CB[i][j]):
                ok = 0
        if(ok == 1):
            cnt += 1
            den += (CalcProbCase(i))
    
    if(tipo == "contagem"):
        return cnt
    else:
        return den

# ----------------- Validacao Estocastica -------------------------------------

def significance(Ca, Cb):
    if(CB[Ca][idx_Solucao] == CB[Cb][idx_Solucao]):
        return simCases(Ca, Cb)
    else:
        return (1.0 - simCases(Ca, Cb))

def randomnessRatio(Ca):
    num = CalcProbCase(Ca)
    den = same(Ca, "den")
    return (num/den)

def frequencyRatio(Ca):
    frequency = 0
    for i in CB:
        if(i == CB[Ca]):
            frequency += 1
    SumFreq = same(Ca, "contagem")
    return (frequency/SumFreq)


#caso Ca é o gerado, caso Cb é o mais proximo na base de casos (fully valid)     
def stochasticValidity(Ca, Cb):
    return (frequencyRatio(Ca) + randomnessRatio(Ca) + significance(Ca, Cb)) / 3.0

# ------------------ Validacao Absoluta ---------------------------------------

# se o caso condiz com pelo menos uma regra ele é validado



# ___________________ RULE GENERATION _________________________________________

#---------------- Teste com arvore de decisao ---------------------------------
calcIdxRules()

import pandas as pd
from sklearn import tree

k = 10

mp = {}
for j in range (0, len(RulesIdx)):
    v = []
    for i in range(0, k):
       v.append(CB[i][RulesIdx[j]])
    mp[j] = v
    
aux = []
for i in range(0, k):
    aux.append(CB[i][idx_Solucao])
    mp[len(RulesIdx)] = aux

df = pd.DataFrame(mp)

X = df.iloc[:,:len(RulesIdx)]
y = df.iloc[:,-1]

clf = tree.DecisionTreeClassifier()

clf.fit(X, y)

tree.plot_tree(clf)
#-------------------------- fim -----------------------------------------------


'''
teste 2 pro peso
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
                
                x = CB[j][i]
                y = CB[k][i]
                solution = 1 if(CB[j][idx_Solucao] == CB[k][idx_Solucao]) else 0
                
                if(solution == 1):
                    if(categoric[i] == 0):    
                        if(x != -1 and y != -1 and abs(x-y) < 10):
                            SH += 1
                        else:
                            SS += 1
                    else:
                        if(x != -1 and y != -1 and x == y):
                            SH += 1
                        else:
                            SS += 1
                else:
                    if(categoric[i] == 0):    
                        if(x != -1 and y != -1 and abs(x-y) < 10):
                            DH += 1
                        else:
                            DS += 1
                    else:
                        if(x != -1 and y != -1 and x == y):
                            DH += 1
                        else:
                            DS += 1
        
        w_linha.append((SH + DS) - (SS + DH))
'''





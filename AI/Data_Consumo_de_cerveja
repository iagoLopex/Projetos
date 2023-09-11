import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import statsmodels.api as sm
import sklearn.metrics as sk
import numpy as np
import math as mt

df = pd.read_excel("Consumo_cerveja.xlsx")

for i in range(len(df['Consumo_de_cerveja'])):
    df['Consumo_de_cerveja'][i] /= 1000.0

index = []
for i in range(len(df)):
    index.append(i)

# fazer primeiras observações do df.head()
print(df.head())

# fazer ultimas observações do df.tail()
print(df.tail())

# dimensões da matriz [quantidade de cervejas][atributos das cervejas]
print(df.shape)

# verificar os valores nulos (IMPORTATE: sem isso a regressão fica zuada)
print(df.isna().sum())

# analise dos tipos das variaveis
print(df.dtypes)

# Correlacao entre variaveis
ind = df.loc[df.index >= 0]
corr_matrix = ind.corr()
print(corr_matrix)

# tabela descritiva das variaveis
print(df.describe())

# Grafico para a Variavel final de semana
values = df['Final_de_Semana'].value_counts()
y = [values[0], values[1]]
x = [0, 1]
plt.bar(x, y)
plt.xlabel("Fim de Semana")
plt.ylabel("Total de dias")
plt.show()

# Grafico de temperaturas 
y = df['Temperatura_Media']
x = index
plt.xlabel("Total de dias")
plt.ylabel("Temperatura")

plt.plot(x, y)
y = df['Temperatura_Minima']
plt.plot(x, y)
y = df['Temperatura_Maxima']
plt.plot(x, y)
y = df['Consumo_de_cerveja']
plt.plot(x, y)
plt.show()

# Grafico com variavel de precipitacao
x = index

plt.xlabel("Total de dias")
plt.ylabel("Precipitação")
y = df['Precipitacao']
plt.plot(x, y)
plt.show()

# Gerafico da variavel de consumo de cerveja
plt.xlabel("Total de dias")
plt.ylabel("Consumo de cerveja")
x = index
y = df['Consumo_de_cerveja'] 
plt.plot(x, y)
plt.show()

# Grafico Pearson
pearson = sns.heatmap(df.corr(), annot = True)
plt.show()

# Grafico Spearman
spearman = sns.heatmap(df.corr(), annot = True)
plt.show()

# Boxplot(verificacao de outliers)
a = ['Temperatura_Media', 'Temperatura_Minima', 'Temperatura_Maxima', 'Precipitacao', 'Consumo_de_cerveja']
df.boxplot(column = a, figsize=(15, 6))
plt.show()

# Grafico de Histograma
plt.hist(df['Temperatura_Media'], 50, facecolor='blue')
plt.title('Temperatura Media')
plt.xlabel("Temperatura Media")
plt.ylabel("Ocorrências")
plt.show()
plt.hist(df['Temperatura_Maxima'], 50)
plt.title('Temperatura Máima')
plt.xlabel("Temperatura Máxima")
plt.ylabel("Ocorrências")
plt.show()
plt.hist(df['Temperatura_Minima'], 50)
plt.title('Temperatura Mínima')
plt.xlabel("Temperatura Mímina")
plt.ylabel("Ocorrências")
plt.show()
plt.hist(df['Precipitacao'], 50)
plt.title('Precipitacção')
plt.xlabel("precipitação")
plt.ylabel("Ocorrências")
plt.show()
plt.hist(df['Consumo_de_cerveja'], 50)
plt.title('Consumo de cerveja')
plt.xlabel("Consumo de cerveja")
plt.ylabel("Ocorrências")
plt.show()

# Grafico de Dispersao
x = df['Consumo_de_cerveja']
y = df['Temperatura_Media']
plt.scatter(x, y, s=20)
plt.xlabel('Consumo de cerveja')
plt.ylabel('Temperatura Media')
plt.show()
x = df['Consumo_de_cerveja']
y = df['Temperatura_Minima']
plt.scatter(x, y, s=20)
plt.xlabel('Consumo de cerveja')
plt.ylabel('Temperatura Minima')
plt.show()
x = df['Consumo_de_cerveja']
y = df['Temperatura_Maxima']
plt.scatter(x, y, s=20)
plt.xlabel('Consumo de cerveja')
plt.ylabel('Temperatura Maxima')
plt.show()
x = df['Consumo_de_cerveja']
y = df['Precipitacao']
plt.scatter(x, y, s=20)
plt.xlabel('Consumo de cerveja')
plt.ylabel('Precipitacao')
plt.show()

# ---------------------------- MLR ---------------------------
# MMQ
X = []
Xt = []
y = df['Consumo_de_cerveja']
column = ['Temperatura_Media', 'Temperatura_Minima', 'Temperatura_Maxima', 'Precipitacao', 'Final_de_Semana']

for i in range(0, 5):
    aux = []
    for j in range(365):
        aux.append(df[column[i]][j])
    Xt.append(aux)
   
X = np.transpose(Xt)

# beta = (Xt*X)^-1 * (Xt*y)
prod1 = np.dot(Xt, X)     
inv = np.linalg.inv(prod1)
prod2 = np.dot(Xt, y)

Beta = np.dot(inv, prod2)
print("MMQ ", Beta)

# Metodo de gradiente descendente
def mean_squared_error(y_true, y_predicted):
    # Calculating the loss or cost
    cost = np.sum((y_true-y_predicted)**2) / len(y_true)
    return cost
  
# Gradient Descent Function
# Here iterations, learning_rate, stopping_threshold
# are hyperparameters that can be tuned
def gradient_descent(x, y, iterations = 500, learning_rate = 0.001, stopping_threshold = 1e-7):
      
    # Initializing weight, bias, learning rate and iterations
    current_weight = 0.1
    current_bias = 0.01
    iterations = iterations
    learning_rate = learning_rate
    n = float(len(x))
      
    costs = []
    weights = []
    previous_cost = None
      
    # Estimation of optimal parameters 
    for i in range(iterations):
          
        # Making predictions
        y_predicted = (current_weight * x) + current_bias
          
        # Calculationg the current cost
        current_cost = mean_squared_error(y, y_predicted)
  
        # If the change in cost is less than or equal to 
        # stopping_threshold we stop the gradient descent
        if previous_cost and abs(previous_cost-current_cost)<=stopping_threshold:
            break
          
        previous_cost = current_cost
  
        costs.append(current_cost)
        weights.append(current_weight)
          
        # Calculating the gradients
        weight_derivative = -(2/n) * sum(x * (y-y_predicted))
        bias_derivative = -(2/n) * sum(y-y_predicted)
          
        # Updating weights and bias
        current_weight = current_weight - (learning_rate * weight_derivative)
        current_bias = current_bias - (learning_rate * bias_derivative)
        
      
    return current_weight, current_bias
  
x = df['Consumo_de_cerveja']
y = df['Temperatura_Media']

estimated, bias = gradient_descent(x, y)

print("estimativa:", estimated);
print("bias:", bias);

# Making predictions using estimated parameters
y_pred = estimated * x + bias

plt.scatter(x, y)
plt.xlabel("Temperatura Media")
plt.ylabel("Consumo de cerveja")
plt.plot([min(x), max(x)], [min(y_pred), max(y_pred)])
plt.show()

#soma de erros quadraticos
SSE = 0
media = 0
colu = [df['Temperatura_Media'], df['Consumo_de_cerveja']]
media = colu[0].sum() / 365
for i in range(0, 365):
    SSE += (y_pred[i] - media) ** 2 
print("SSE ", SSE)

# Metrica R2
R2 = sk.r2_score(y, y_pred)
print("R2 ", R2)

# Metrica R2 ajustado
def calculeted_adjusted_r_squared(y, y_pred, num_features):
    n = len(y)
    residual_sum_of_squares = sum((y - y_pred) ** 2)
    total_sum_of_squares = sum((y - y.mean()) ** 2)
    r_squared = 1 - (residual_sum_of_squares / total_sum_of_squares)
    adjusted_r_squared = 1 - (1 - r_squared) * (n-1) / (n - num_features - 1)
    return adjusted_r_squared
adjusted_r_squared = calculeted_adjusted_r_squared(y, y_pred, 1)
print("R2 ajustado ", adjusted_r_squared)

# Metrica MSE
MSE = sk.mean_squared_error(y, y_pred)
print("MSE ", MSE)

# Metrica RMSE
RMSE = mt.sqrt(MSE)
print("RMSE ", RMSE)

# Metrica MAE
MAE = sk.mean_absolute_error(y, y_pred)
print("MAE ", MAE)

# Metrica MAPE
MAPE = np.mean(np.abs((y - y_pred) / y)) * 100
print("Valor percentual MAPE ", MAPE)

# Metrica RMSLE
RMSLE = sk.mean_squared_log_error(y, y_pred)
print("RMSLE ", RMSLE) 

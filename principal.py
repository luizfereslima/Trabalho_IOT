import requests
import tkinter as tk

# Função para obter e exibir os dados
def obter_dados():
    try:
        # Faz uma solicitação GET para obter os dados do CPD
        valoresMonitoramento = requests.get('http://10.21.1.21/')
        dados = valoresMonitoramento.text.strip().split('\n')  # Divide os dados em linhas e remove espaços em branco
        
        # Extrai os valores de valorUmidade, valorTemperatura e statusPorta e separa os ":"
        valorUmidade = dados[0].split(': ')[1]
        valorTemperatura = dados[1].split(': ')[1]
        statusPorta = dados[2].split(': ')[1]

        # Atualiza os rótulos com os novos dados
        labelUmidade.config(text=f"Umidade: {valorUmidade}")
        labelTemperatura.config(text=f"Temperatura: {valorTemperatura}")
        labelPorta.config(text=f"Porta: {statusPorta}")
    except Exception as e:
        print("Erro ao obter os dados:", e)

# Função para atualizar os dados a cada 0,7 segundos
def atualizar():
    obter_dados()
    root.after(700, atualizar)  # Chama a função novamente após 0,7 segundos

# Configurações da janela principal
root = tk.Tk()
root.title("Monitoramento do CPD")
root.geometry("300x150")

# Rótulos para exibir os dados
labelUmidade = tk.Label(root, text="Umidade: -")
labelUmidade.pack()

labelTemperatura = tk.Label(root, text="Temperatura: -")
labelTemperatura.pack()

labelPorta = tk.Label(root, text="Porta: -")
labelPorta.pack()

# Inicia a atualização dos dados
atualizar()

# Inicia o loop principal da interface gráfica
root.mainloop()

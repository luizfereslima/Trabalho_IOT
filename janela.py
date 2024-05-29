import requests
from bs4 import BeautifulSoup
import tkinter as tk

# Faz a solicitação HTTP para o site e obtém os dados
response = requests.get('http://example.com')
soup = BeautifulSoup(response.text, 'html.parser')

# Extrai os dados de umidade, temperatura, porta e presença do site
umidade = soup.find('div', {'class': 'umidade'}).text
temperatura = soup.find('div', {'class': 'temperatura'}).text
porta = soup.find('div', {'class': 'porta'}).text
presenca = soup.find('div', {'class': 'presenca'}).text

# Cria a janela e exibe os dados
root = tk.Tk()
root.title('Dados do Site')

label_umidade = tk.Label(root, text='Umidade:')
label_umidade.pack()
tk.Label(root, text=umidade).pack()

label_temperatura = tk.Label(root, text='Temperatura:')
label_temperatura.pack()
tk.Label(root, text=temperatura).pack()

label_porta = tk.Label(root, text='Porta:')
label_porta.pack()
tk.Label(root, text=porta).pack()

label_presenca = tk.Label(root, text='Presença:')
label_presenca.pack()
tk.Label(root, text=presenca).pack()

root.mainloop()
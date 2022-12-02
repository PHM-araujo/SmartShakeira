# Trabalho 1 - Simulação de algoritmos de Busca em Largura (BFS) e Busca em Profundidade (DFS)
- Esse é um projeto que visou a simulação de conceitos relacionados a solução de um labirinto por meio de algoritmos de busca em profundidade e em largura.

## Guia de Instalação e execução:
1. Extrair o arquivo zip
2. Edite o arquivo ```Matriz.txt``` com o labirinto desejado ou não edite e o programa executará com o arquivo padrão 
3. Acesse o diretório ```pathFinder``` e o abra no terminal 
4. Execute no terminal ```python3 main.py```
5. Entre com o algoritmo de busca desejado 
 	- 1 Busca em em largura
 	- 2 Busca em profunfidade 

## Pré-requisitos: 
1. Bibliotecas Utilizadas
	- NumPy
	- colorama
	- os
2. Sistema operacional: Linux 20.04
3. IDE : Visual Studio Code
4. Compilador: Python 3.8.10

## Como formatar o seu arquivo de entrada
1. Primeiramente, acesse o diretório ```pathFinder```
3. Em seguida, edite o arquivo ```Matriz.txt```, ele deve conter números separados somente por espaço, como no exemplo abaixo
	- 0 para paredes
	- 1 para caminhos livres
	- 2 para início do labirinto
	- 3 para final do labirinto 

```
2 0 0 0 1 0 0 0 0 0
1 0 0 0 1 0 0 0 0 0
1 0 0 0 1 0 0 0 0 0
1 1 1 1 1 1 1 1 0 0
0 0 0 1 0 1 0 1 0 0
0 0 0 1 0 1 0 1 0 0
0 0 1 1 1 1 0 1 0 0
0 0 1 0 0 0 0 1 0 0
0 0 1 0 0 0 0 1 0 0
0 0 1 3 1 1 1 1 0 0
```
	
## Autoria e constribuições:
- Esse projeto é autoria de Pedro Henrique Melo Araujo.
	
## Fontes:
- Stack Overflow, c2022. Disponível em: <stackoverflow.com>. Acesso em: 10 de setembro de 2022.
- MOREIRA, Benjamin Grando. Resolução de problemas por meio de busca. Joinville: Ufsc, 2022. 24 slides, color.
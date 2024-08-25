# LargeFileSorter

## Visão geral 
 Este trabalho foi desenvolvido com o propósito de organizar arquivos que possuem um grande volume de bytes, enquanto utilizamos uma quantidade limitada de memória RAM. Para atingir esse objetivo, empregamos a técnica de particionamento. Nesta abordagem, dividimos o arquivo em várias partes menores, onde cada uma dessas partes é ordenada separadamente utilizando o algoritmo quicksort. Após a ordenação, cada partição é associada a um buffer de entrada auxiliar. Em seguida, para recompor o arquivo original de maneira ordenada, aplicamos a técnica de intercalação k-vias, que é responsável por combinar os dados das diferentes partições e transferi-los para um buffer de saída, garantindo assim a ordenação correta e eficiente do arquivo como um todo.

### Para mais entendimento do algoritmo:
[RelatorioEd2 (1).pdf](https://github.com/user-attachments/files/16740638/RelatorioEd2.1.pdf)


### Clone este repositório: 
```
$ git clone https://github.com/pedro07conrado/LargeFileSorter
```

### Acesse a pasta do projeto no terminal
```
$ cd LargefileSorter
```
### Execute o makefile (linux)
```
$ make
```

### Execute o makefile (windows)
```
$ mingw32-make
```

### Possiveís problemas: 
Caso o seu compilador reclame ao executar o comando `Make` e o problema seja igual a esse: 
![WhatsApp Image 2024-08-25 at 11 11 57](https://github.com/user-attachments/assets/1a83e128-eeb4-464b-ba8a-05d0977cec01)

vá as configurações do ambiente C/C++ e faça oque se mostra na imagem a seguir:
![WhatsApp Image 2024-08-25 at 11 15 52](https://github.com/user-attachments/assets/be4466cb-60f2-4664-8357-cd91db51a6fc)


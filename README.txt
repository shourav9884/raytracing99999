- ALTERANDO ARQUIVO DA CENA:
A cena que ser� carregada est� definida no arquivo "initialScene.txt". Caso deseje-se alterar a cena a ser carragada, basta que o nome da cena contido neste arquivo seja alterada.


- CONTROLOES:
TECLADO:
'a' -> anda para a esquerda (na dire��o do vertor U da c�mera)
's' -> anda para a direita (na dire��o do vertor U da c�mera)
'd' -> anda para tr�s (na dire��o do vertor N da c�mera)
'w' -> anda para frente (na dire��o do vertor N da c�mera)
'r' -> sobe (na dire��o do vertor V da c�mera)
'f' -> desce (na dire��o do vertor V da c�mera)
['1','9'] -> altera a velocidade de deslocamento da camera

OBS: Caso a tecla "Caps Lock" esteja habilita os comandos acima n�o funcionaram, pois os caracteres devem ser min�sculos.

MOUSE:
eixo x + botao esquerdo -> rotaciona a c�mera para os lados (rotaciona vetor N em torno do vetor V da c�mera)
eixo y + botao esquerdo -> rotaciona a c�mera para cima e para baixo (rotaciona vetor N em torno do vetor U da c�mera)
eixo x + botao direito -> rotaciona a c�mera de modo a entort�-la (rotaciona vetor V em torno do vetor N da c�mera)



- ESQUEMA DA C�MERA:

     |V
     |
     |
   __|_
  |  | |
  |  o---------- U
  |_/__|
   /    Plano de vista
  /
 /N

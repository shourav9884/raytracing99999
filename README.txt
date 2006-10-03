- ALTERANDO ARQUIVO DA CENA:
A cena que será carregada está definida no arquivo "initialScene.txt". Caso deseje-se alterar a cena a ser carragada, basta que o nome da cena contido neste arquivo seja alterada.


- CONTROLOES:
TECLADO:
'a' -> anda para a esquerda (na direção do vertor U da câmera)
's' -> anda para a direita (na direção do vertor U da câmera)
'd' -> anda para trás (na direção do vertor N da câmera)
'w' -> anda para frente (na direção do vertor N da câmera)
'r' -> sobe (na direção do vertor V da câmera)
'f' -> desce (na direção do vertor V da câmera)
['1','9'] -> altera a velocidade de deslocamento da camera

OBS: Caso a tecla "Caps Lock" esteja habilita os comandos acima não funcionaram, pois os caracteres devem ser minúsculos.

MOUSE:
eixo x + botao esquerdo -> rotaciona a câmera para os lados (rotaciona vetor N em torno do vetor V da câmera)
eixo y + botao esquerdo -> rotaciona a câmera para cima e para baixo (rotaciona vetor N em torno do vetor U da câmera)
eixo x + botao direito -> rotaciona a câmera de modo a entortá-la (rotaciona vetor V em torno do vetor N da câmera)



- ESQUEMA DA CÂMERA:

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

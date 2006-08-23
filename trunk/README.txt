Controles:

Teclado:
a -> anda para a esquerda (na direção do vertor U da câmera)
s -> anda para a direita (na direção do vertor U da câmera)
d -> anda para trás (na direção do vertor N da câmera)
w -> anda para frente (na direção do vertor N da câmera)
r -> sobe (na direção do vertor V da câmera)
f -> desce (na direção do vertor V da câmera)

Mouse:
eixo x -> rotaciona a câmera para os lados (rotaciona em torno do vetor V da câmera)
eixo y -> rotaciona a câmera para cima e para baixo (rotaciona em torno do vetor U da câmera)



Esquema da câmera:

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




cesarlimap: -

u = (intersection.getY() - this->yMin->getPoint().getY()) /
                                       (this->yMax->getPoint().getY() - this->yMin->getPoint().getY());
                               v = (intersection.getZ() - this->zMax->getPoint().getZ()) /
                                       (this->zMin->getPoint().getZ() - this->zMax->getPoint().getZ());




tipo...esse eh um de tres casos... eh uma interpolação (axo q eh esse o nome)..
Sent at 8:08 PM on Tuesday
cesarlimap: pra achar o u e o v q serão usados pra mapear na matriz de pixels da imagem... só não estou entendendo quando usa as coordenadas y z ou x z ou x y pra fazer isso
# -*- coding: utf-8 -*-
import pandas as pd #manuseio de dataframes
import numpy as np  #para utilizar arrays e operações matemáticas
import os.path      #teste de existência de arquivos
import sys          #leitura via terminal





#leitura dos dados da simulção isotrópica no CRPropa
data = pd.read_csv(sys.argv[1],header=0, sep = '\s+', dtype ='a')

data = data.astype(float)

#raio da esfera
r = 3.8 #Mpc


"""
    Array de phi e theta(coordenadas esféricas) cotendo
    ,respectivamente, 36 e 72 elementos.Ou seja,
    tanto phi quanto theta variam 5 graus
"""
#phi = np.linspace(0,180 , 37)#modifiquei na reunião com o rogério

#theta = np.linspace(0, 360, 73)#sempre botar um mais pra dar a divisão certa

pixel = np.loadtxt(sys.argv[5])


final_eventos = None
final_cone = None

for i in range(0,3072):

    #Um ponto na esfera (também o vetor Origem -> Ponto)(coordenadas esféricas para cartesianas)
    x = r*np.cos(np.radians(pixel[i,1]))*np.sin(np.radians(pixel[i,0]))
    y = r*np.sin(np.radians(pixel[i,1]))*np.sin(np.radians(pixel[i,1]))
    z = r*np.cos(np.radians(pixel[i,0]))


    #Angulo entre a linha de visada e os ângulos de emissão de cada evento

    #produto interno
    p_int_px = ( (x * data.P0x) + (y * data.P0y) + (z * data.P0z) )

    #norma vetor linha divisada
    norma_p = np.sqrt( np.power(x,2) + np.power(y,2) + np.power(z,2))

    #Norma vetor direção de emissão
    norma_px = np.sqrt( ( np.power(data.P0x,2) ) + ( np.power(data.P0y,2) )+ ( np.power(data.P0z,2) ) )


    ang =  p_int_px / (norma_px * norma_p)

    """
        Criação de uma coluna contendo o angulo entre o vetores
        de emissão e a linha de visada, lembrando que a linha
        de visada varia pra cada pixel dentro do for
    """

    data['Ang_linha_de_visada'] = np.degrees( np.arccos( ang ) )


    #criando o cone

    ang_linha_centro_cone= int(sys.argv[2])
    ang_cone=5

    sup_ang_cone =ang_linha_centro_cone + ang_cone/2
    inf_ang_cone =ang_linha_centro_cone - ang_cone/2

    '''
        Apliquei uma ideia de ter o centro do meu cone em relação a linha divisada e subtrair e somar metade do ângulo
        do meu cone a esse ângulo.

    '''
    test = (data.Ang_linha_de_visada <= sup_ang_cone) & (data.Ang_linha_de_visada >= inf_ang_cone)
    cut = data[test]


    """
        A variável cut guarda todos os eventos que tiveram como retorno True no test
        da linha 77.
    """

    #criar uma coluna no cut com o angulo entre a linha divisada e os Vetores Origem -> (x,y,z)
    '''
        O raciocínio aqui é criar vetores entre a origem(emissor) e as coordenadas de chegada de cada evento,
        calcular o ângulo desses vetores com o vetor da linha de visada( o pixel das linhas 36,37 e 38) e acres-
        centar mais uma conluna na variável  cut.
        Logo após realizei um cut pra definir os pontos que estão dentro do pixel que desejo.
    '''

    p_int_px = ( (x * cut.X) + (y * cut.Y) + (z * cut.Z) )

    norma_p = np.sqrt( np.power(x,2) + np.power(y,2) + np.power(z,2))

    norma_px = np.sqrt( ( np.power(cut.X,2) ) + ( np.power(cut.Y,2) )+ ( np.power(cut.Z,2) ) )


    ang =  p_int_px / (norma_px * norma_p)

    cut['Dist_ang'] = np.degrees( np.arccos( ang ) )


    #distancia ângular (criação do pixel)
    cut_dist = (cut.Dist_ang <= 0.15) #pixel com distancia angular de 0.1 graus

    aux = cut[cut_dist]
    #final = cut[cut_dist]#mesma lógica da linha 78

    """"
            Abaixo eu somo todos os eventos para cada pixel em um file

    """


    if i == 0:

        final_eventos = aux
        final_cone = cut

    else:

        final_eventos = final_eventos.append(aux, ignore_index = True)
        final_cone = final_cone.append(cut, ignore_index = True)

#fim do for


np.savetxt(sys.argv[3], final_eventos,comments ='', fmt='%f', delimiter="\t", header="D	\tz	\tSN	\tID	\tE\t	X\t	Y\t	Z	\tPx\t	Py\t	Pz\t	SN0\t	ID0\t	E0\t	X0\t	Y0\t	Z0\t	P0x\t	P0y\t	P0z\t	SN1\t	ID1\t	E1\t	X1\t	Y1\t	Z1\t	P1x\t	P1y\t	P1z\t	W\t Ang_linha_de_visada  \t Dist_ang")
np.savetxt(sys.argv[4], final_cone,comments ='', fmt='%f', delimiter="\t", header="D	\tz	\tSN	\tID	\tE\t	X\t	Y\t	Z	\tPx\t	Py\t	Pz\t	SN0\t	ID0\t	E0\t	X0\t	Y0\t	Z0\t	P0x\t	P0y\t	P0z\t	SN1\t	ID1\t	E1\t	X1\t	Y1\t	Z1\t	P1x\t	P1y\t	P1z\t	W\t Ang_linha_de_visada ")

#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<GL/gl.h>
#include<GL/freeglut.h>
#include<math.h>
#include <iostream>

using namespace std;

typedef struct _ponto{ /*Estrutura que define um ponto, com as coordenadas 'x' e 'y'.*/
    float coordX;
    float coordY;
} ponto;

typedef struct _vetor{ /*Estrutura que define um vetor, com os pontos inicial e final*/
  ponto p1; /*Origem do vetor*/
  ponto p2; /*Fim do vetor*/
} vetor;

/*Prot�tipos das fun��es utilizadas*/
void display();
void mouse(int button, int state, int X, int Y);
void keyboard_cb(unsigned char key, int X, int Y);
ponto *resize(ponto *p, int Tamanho, int NovoTam);
void cabecalho();
float distancia_entre_pontos(ponto p1, ponto p2);

float pos_x = 0, pos_y = 0;
float scale_x = 0, scale_y = 0;

int maxWH = 1280;
int maxHT = 720;

/*Vari�veis globais*/
int cont = 0; /*Cont � a quantidade de pontos existentes*/
int tam = 100; /*Tamanho do array que vai guardar os pontos, inicialmente come�a com 100 e cresce conforme a necessidade.*/
int etapa = 1; /*Para controlar a etapa 1 (Construir o p�logono) e a etapa 2 (Escolher um ponto)*/
ponto p; /*Ponto que ser� utilizado para descobrir a localiza��o*/
ponto *pontos = (ponto *) malloc (sizeof(ponto)*tam);/*Aloca��o de mem�ria para o array de pontos*/
void myTranslatef(ponto *p, float,float);
void myScale(ponto *p, float, float);

int main(int argc, char **argv){

  if(!pontos){ /*Verifica se a mem�ria foi alocada para 'pontos'.*/
          printf("Erro: Nao foi poss�vel alocar mem�ria.\n");
          exit(1);
        }

    glutInit(&argc,argv); /*Esta fun��o � utilizada para iniciar a biblioteca GLUT.*/
    /*glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    /*glutInitWindowPosition(200,200); *//*Posi��o da janela na tela*/
    glutInitWindowSize (maxWH, maxHT); /*Tamanho da Janela*/
    glutCreateWindow("Editor de Poligonos 2D"); /*Nome da Janela*/
    glutKeyboardFunc(keyboard_cb);/*Fun��o que ser� chamada quando ocorrer um evento no teclado*/
    glutMouseFunc(mouse);/*Fun��o que ser� chamada quando ocorrer um evento no mouse*/
    glutDisplayFunc(display); /*Fun��o que ser� chamada quando houver a necessidade de atualizar a janela*/
    glutMainLoop(); /*Inicia o gerenciamento de eventos, aguardando que algum evento seja acionado.*/
    return EXIT_SUCCESS ;

}

void display(){/*Fun��o respons�vel por plotar na tela*/
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(8.0); /*Define o tamanho do ponto*/
  glLineWidth(4); /*Define a espessura da linha*/

  glLoadIdentity();
  //glTranslatef( pos_x, pos_y, 0.0 );
    myTranslatef(pontos, pos_x, pos_y);
    //myScale(pontos, scale_x, scale_y);
  glBegin(GL_LINE_STRIP); /*GL_LINE_STRIP respons�vel por liga os pontos por uma linha reta*/

    glColor3f(1.0,1.0,1.0);/*Define a cor das linhas*/
    for(int i = 0; i<cont-1; i++){
      glVertex2f(pontos[i].coordX,pontos[i].coordY); /*Respons�vel por plotar os pontos*/
    }
    if((cont>3) && (distancia_entre_pontos(pontos[0],pontos[cont-1]) < 0.05) && etapa == 1){ /*Verifica sempre se o �ltimo ponto escolhido est� pr�ximo do primeiro ponto do pol�gono*/
      glVertex2f(pontos[0].coordX,pontos[0].coordY);/*Caso esteja, conecta ao primeiro ponto do pol�gino*/
      etapa = 2; /*Ativa a etapa 2 e em seguida define o �timo ponto como sendo o primeiro*/
      pontos[cont-1].coordX = pontos[0].coordX;
      pontos[cont-1].coordY = pontos[0].coordY;
    }else if(cont > 1){
      glVertex2f(pontos[cont-1].coordX,pontos[cont-1].coordY); /*Respon�vel por plotar o �ltimo ponto*/
    }
  glEnd();
  glFlush();
  glutSwapBuffers();
}

void myTranslatef(ponto *p, float x, float y) {


    for(int i = 0; i<cont; i++){
        if (!(p[i].coordX + x > maxWH || p[i].coordY + y > maxHT)) {
            p[i].coordX += x;
            p[i].coordY += y;
        }
    }

}

void myScale(ponto *p, float x, float y) {
    for(int i = 0; i<cont; i++){
        p[i].coordX *= x;
        p[i].coordY *= y;
    }
}

void mouse(int button, int state, int X, int Y){
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && etapa == 1){
    if(cont >= tam){/*Verifica se existe espa�o para o novo ponto*/
      pontos = resize(pontos,cont, tam*2);
    }
    pontos[cont].coordX = (float)(2.*X)/1280 - 1; /*Necess�rio converter as coordenadas*/
    pontos[cont].coordY = (float)-(2.*Y)/720 + 1; /*Necess�rio converter as coordenadas*/
    cont++;/*Contador de pontos existentes*/
    glutPostRedisplay();/*Atualiza o frame chamando novamente a fun��o display*/
  }
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && etapa == 2){
    /*Caso a segunda etapa esteja ativa, nao e aceito mais o botao do mouse
        podemos usar o ultimo clique para salvar o poligono
    */
    //printf("Poligono Finalizado");
  }
}


void keyboard_cb(unsigned char key, int X, int Y){
    switch(key){
        case 27:         /*27 corresponde ao ESC, e est� sendo utilizado para sair*/
            exit (0);
            free(pontos); /*Libera o espa�o alocado para os pontos*/
            break;
        case 'f':
            printf("%d", cont);
            for(int c = 0; c < cont-1; c++){
                printf("X: %d\nY: %d\n", pontos[c].coordX, pontos[c].coordY);
            }
            break;
        case 'a':
            pos_x -= 0.1;
            break;
        case 'd':
            pos_x += 0.1;
            break;
        case 'w':
            pos_x = 0.0;
            pos_y += 0.1;
            break;
        case 's':
            pos_x = 0.0;
            pos_y -= 0.1;
            break;
        case 'm':
            scale_x += 0.1;
            scale_y += 0.1;
            break;
  }
  glutPostRedisplay();
}

ponto *resize(ponto *p, int Tamanho, int NovoTam){ /*Fun��o respons�vel por redimensionar o tamanho na mem�ria para os pontos*/
  ponto *temp;
  temp = p;
  p = (ponto *) malloc (sizeof(ponto)*NovoTam);/*Aloca o novo espa�o com o dobro da capacidade anterior */

  for(int i = 0; i<Tamanho; i++){/*Passa os pontos existentes para o novo espa�o alocado*/
    p[i].coordX = temp[i].coordX;
    p[i].coordY = temp[i].coordY;
  }

  tam = NovoTam; /*Atualiza a nova capacidade de pontos*/
  free(temp); /*Libera o espa�o alocado*/

  return p; /*Retorna o endere�o dos pontos com capacidade maior na mem�rai*/
}

float distancia_entre_pontos(ponto p1, ponto p2){
  return sqrt(pow(p1.coordX - p2.coordX,2)+pow(p1.coordY-p2.coordY,2)); /*Calcula a dist�ncia de ponto*/
}

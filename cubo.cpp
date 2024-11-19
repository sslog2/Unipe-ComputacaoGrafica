#include <GL/glut.h>

GLfloat angle = 0.0f;  // Ângulo de rotação
GLfloat fAspect;

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Limpa a janela e o depth buffer
    glLoadIdentity();  // Reseta a matriz de transformação

    gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);  // Posição da câmera

    glRotatef(angle, 1.0f, 1.0f, 0.0f);  // Aplica rotação ao cubo

    // Define a cor de emissão do cubo (laranja)
    GLfloat emissao[] = {1.0f, 0.5f, 0.0f, 1.0f};  // Cor de emissão (laranja)
    glMaterialfv(GL_FRONT, GL_EMISSION, emissao);  // Aplica a emissão ao material

    // Desenha o cubo
    glutSolidCube(2.0f);
    glColor3f(0.0f, 0.0f, 1.0f);

    glutSwapBuffers();  // Troca os buffers para exibir a cena
}

// Função para configurar a visualização
void EspecificaParametrosVisualizacao(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, fAspect, 0.1f, 100.0f);  // Define o campo de visão

    glMatrixMode(GL_MODELVIEW);
}

// Função callback chamada quando o tamanho da janela muda
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;  // Para evitar a divisão por zero
    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w / (GLfloat)h;
    EspecificaParametrosVisualizacao();
}

// Função para atualizar a rotação do cubo
void AtualizaRotacao(int value)
{
    angle += 2.0f;  // Aumenta o ângulo de rotação
    if (angle > 360.0f) angle -= 360.0f;  // Mantém o valor do ângulo dentro de 0-360
    glutPostRedisplay();  // Redesenha a cena
    glutTimerFunc(16, AtualizaRotacao, 0);  // Chama a função novamente após 16ms (~60 FPS)
}

// Função de inicialização
void Inicializa(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Cor de fundo
    glEnable(GL_DEPTH_TEST);  // Ativa o teste de profundidade
    glEnable(GL_LIGHTING);  // Ativa a iluminação
    glEnable(GL_LIGHT0);  // Ativa a luz número 0

    // Define a posição da luz
    GLfloat luzPosicao[] = {1.0f, 1.0f, 1.0f, 0.0f};  // Luz na posição (1, 1, 1)
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicao);

    // Define as propriedades da luz ambiente
    GLfloat luzAmbiente[] = {0.2f, 0.2f, 0.2f, 1.0f};  // Luz ambiente fraca
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);

    glShadeModel(GL_SMOOTH);  // Ativa o modelo de sombreamento suave
}

// Programa Principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);  // Inicializa o GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Modo de exibição com buffer duplo, RGB e profundidade
    glutInitWindowSize(400, 400);  // Tamanho da janela
    glutCreateWindow("Cubo com Emissão e Teste de Profundidade");  // Cria a janela com o título

    // Registra as funções callback
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutTimerFunc(25, AtualizaRotacao, 0);  // Define o tempo de atualização da rotação (a cada 25ms)
    
    Inicializa();  // Função de inicialização

    glutMainLoop();  // Inicia o loop principal do GLUT

    return 0;
}

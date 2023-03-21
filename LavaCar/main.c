#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#define R 3

void linhaCol(int lin, int col);
void box(int lin1, int col1, int lin2, int col2);
int menu(int lin1, int col1, int qtd, char lista[3][40]);
void textColor(int letras, int fundo);

///////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    char dono[15];
    char modelo[10];
    char placa[8];

} TCarro;

///////////////////////////////////////////////////////////////////////////////////
//COR DA LETRA
enum {BLACK,                //0
      BLUE,                  //1
      GREEN,                 //2
      CYAN,                  //3
      RED,                   //4
      MAGENTA,               //5
      BROWN,                 //6
      LIGHTGRAY,             //7
      DARKGRAY,              //8
      LIGHTBLUE,             //9
      LIGHTGREEN,            //10
      LIGHTCYAN,             //11
      LIGHTRED,              //12
      LIGHTMAGENTA,          //13
      YELLOW,                //14
      WHITE                  //15
     };
///////////////////////////////////////////////////////////////////////////////////
//COR DO FUNDO
enum {_BLACK=0,                //0
      _BLUE=16,                  //1
      _GREEN=32,                 //2
      _CYAN=48,                  //3
      _RED=64,                   //4
      _MAGENTA=80,               //5
      _BROWN=96,                 //6
      _LIGHTGRAY=112,             //7
      _DARKGRAY=128,              //8
      _LIGHTBLUE=144,             //9
      _LIGHTGREEN=160,            //10
      _LIGHTCYAN=176,             //11
      _LIGHTRED=192,              //12
      _LIGHTMAGENTA=208,          //13
      _YELLOW=224,                //14
      _WHITE=240                  //15
     };
///////////////////////////////////////////////////////////////////////////////////
//CORTENADAS
void iM(int x, int y)
{
    HANDLE h;
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, dwPos);
}
///////////////////////////////////////////////////////////////////////////////////

void textColor(int letra, int fundo)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letra + fundo);
}
///////////////////////////////////////////////////////////////////////////////////

void linhaCol(int lin, int col)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD)
    {
        col-1,lin-1
    });// coorddenada na tela
    //funcao para deixar o cursor invisivel
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
///////////////////////////////////////////////////////////////////////////////////

void box(int lin1, int col1, int lin2, int col2)
{
    int i,j, tamlin, tamcol;

    //atamanho do box
    tamlin = lin2 - lin1;
    tamcol = col2 - col1;

    //Monta o Box
    for (i=col1; i<=col2; i++)  // linhas
    {
        linhaCol(lin1,i);
        printf("%c",196);
        linhaCol(lin2,i);
        printf("%c",196);
    }
    for (i=lin1; i<=lin2; i++)  //colunas
    {
        linhaCol(i,col1);
        printf("%c",179);
        linhaCol(i,col2);
        printf("%c",179);
    }
    for (i=lin1+1; i<lin2; i++)
    {
        for(j=col1+1; j<col2; j++)
        {
            linhaCol(i,j);
            printf(" ");
        }
    }
//Posição dos cantos
    linhaCol(lin1,col1);
    printf("%c",218);
    linhaCol(lin1,col2);
    printf("%c",191);
    linhaCol(lin2,col1);
    printf("%c",192);
    linhaCol(lin2,col2);
    printf("%c",217);
}
///////////////////////////////////////////////////////////////////////////////////

int menu(int lin1, int col1, int qtd, char lista[5][40])
{
    int opc=1, lin2, col2, linha,i,tamMaxItem, tecla;
    //calcula as coordenadas
    tamMaxItem = strlen(lista[0]);

    //tamanho maximo do item
    for(i=1; i<qtd; i++)
    {
        if(strlen(lista[i])>tamMaxItem)
        {
            tamMaxItem = strlen(lista[i]);
        }
    }
    lin2 = lin1+(qtd*2+2);
    col2 = col1+tamMaxItem+4;

    //Monta Tela
    textColor(WHITE, _BLUE);
    setlocale(LC_ALL,"C");
    box(lin1,col1,lin2,col2);
    setlocale(LC_ALL,"");
    //laço das opcões
    while(1)
    {
        linha=lin1+2;
        for(i=0; i<qtd; i++)
        {
            if(i+1==opc)textColor(BLACK, _LIGHTGREEN);
            else textColor(WHITE, _BLUE);
            linhaCol(linha,col1+2);
            printf("%s",lista[i]);
            linha +=2;
        }
        //Aguarda tecla
        linhaCol(1,1);
        tecla = getch();
        linhaCol(22,1);
        //Opção
        if(tecla==27)  //ESC
        {
            opc=0;
            break;
        }
        else if(tecla==13)  //ENTER
        {
            break;
        }
        //Seta para cima
        else if(tecla==72)  //seta para cima
        {
            if(opc>1)opc--;  //pode voltar

        }
        else if(tecla==80 )         //seta para baixo
        {
            if (opc<qtd)opc++;                //Se opcao for menor que quantidade de itens, posso avançar


        }
    }
    return opc;
}
///////////////////////////////////////////////////////////////////////////////////

void adiciona(int *p, int *r, int QM)
{
    if (*p<QM)
    {
        *p=*p+1;
    }
    else if (*r<R)
    {
        *r=*r+1;
    }
}
///////////////////////////////////////////////////////////////////////////////////

void lavarcarro(int *p, int *r, int QM)
{
    if (*p>0)
    {
        if (*r==0)
        {
            *p=*p-1;
            textColor(WHITE, _BLUE);
            iM(2,0);
            printf("--------------------------------");
            iM(2,2);
            printf("--------------------------------");
            iM(2,1);
            printf("|Lavando o 1º carro do pátio...|");
        }
        else
        {
            *r=*r-1;
            textColor(WHITE, _BLUE);
            iM(2,0);
            printf("--------------------------------");
            iM(2,2);
            printf("--------------------------------");
            iM(2,1);
            printf("|Lavando o 1º carro do pátio...|");
        }
    }
    else
    {
        textColor(RED, _YELLOW);
        iM(2,0);
        printf("---------------------------------------------------------");
        iM(2,2);
        printf("---------------------------------------------------------");
        iM(2,1);
        printf("|Todos os carros lavados, pátio e fila de espera vazios!|");
    }
}
///////////////////////////////////////////////////////////////////////////////////

void leituraTC(TCarro *carro, int * c)
{

    textColor(WHITE, _BLUE);
    iM(7,0);
    printf("------------------------------");
    iM(7,2);
    printf("------------------------------");
    iM(7,1);
    printf("|Adicionando veiculo         |");
    iM(7,3);
    printf("Nome do Proprietário:         ");
    iM(7,4);
    printf ("Informe o modelo:             ");
    iM(7,5);
    printf ("Informe a placa:              ");
    iM(28,3);
    fgets(carro->dono, 15, stdin);
    carro->dono[strcspn(carro->dono, "\n")] = 0;
    iM(24,4);
    fgets(carro->modelo, 10, stdin);
    carro->modelo[strcspn(carro->modelo, "\n")] = 0;
    iM(23,5);
    fgets(carro->placa, 8, stdin);
    carro->placa[strcspn(carro->placa, "\n")] = 0;
    *c = *c+1;
}
///////////////////////////////////////////////////////////////////////////////////

void imprimeTCarro(TCarro c)
{

    textColor(WHITE, _GREEN);
    printf("| Proprietário    :%s\n", c.dono);
    printf("| Modelo do carro :%s\n", c.modelo);
    printf("| Placa do carro  :%s\n\n", c.placa);

}

///////////////////////////////////////////////////////////////////////////////////

void lavacarrotrue(int qtd, int *p, int *r, TCarro * carro, TCarro * carror)
{
    for(int i=1; i<=*p; i++)
    {
        memcpy(&carro[i-1], &carro[i], sizeof(TCarro));
    }
    memcpy(&carro[*p-1], &carror[0], sizeof(TCarro));
    for(int j=1; j<=*r; j++)
    {
        memcpy(&carror[j-1], &carror[j], sizeof(TCarro));
    }
}
///////////////////////////////////////////////////////////////////////////////////

void flush_in()
{
    int ch;
    while( (ch= fgetc(stdin)) != EOF && ch != '\n') {}

}
///////////////////////////////////////////////////////////////////////////////////

int main()
{
    int QMpatio, patio=0, rua=0, opc, c=0;
    TCarro * vetorP = (TCarro *) calloc(QMpatio, sizeof(TCarro));
    TCarro * vetorR = (TCarro *) calloc(R, sizeof(TCarro));

    system("color 0F");
    textColor(WHITE, _GREEN);
    iM(2,0);
    printf("-----------------------------------------");
    iM(2,1);
    printf("|Informe a capacidade maxima do patio:  |");
    iM(2,2);
    printf("-----------------------------------------");
    iM(2,3);
    printf("-----------------------------------------");
    iM(2,4);
    printf("|Informe numero de vagas na rua:3       |");
    iM(2,5);
    printf("-----------------------------------------");
    iM(40,1);
    scanf("%d", &QMpatio);

    system("cls");
    system("color 0F");

    int opca;
    char lista[5][40]= {"1-Adicionar carro na fila", "2-Lavar carro", "3-Consultar fila de lavagem", "4-Consultar fila de espera", "5-Encerrar"};

    setlocale(LC_ALL,"");

    do
    {

        textColor(WHITE, _BLUE);

        iM(7,0);
        printf("---------------------");
        iM(7,1);
        printf("| PATIO:%d  |", patio);
        iM(7,2);
        printf("---------------------");
        iM(19,1);
        printf("| RUA:%d |", rua);


        opc = menu(5,2,5,lista);
        switch(opc)
        {
        case (1) : //adiciona
            flush_in();
            system("cls");
            system("color 0F");
            if (patio<QMpatio)
            {
               leituraTC(&vetorP[patio], &c);
                adiciona(&patio, &rua, QMpatio);
            }
            else if (rua<R)
            {
                leituraTC(&vetorR[rua], &c);
                adiciona(&patio, &rua, QMpatio);
            }
            else
            {
                textColor(WHITE, _RED);
                iM(7,0);
                printf("------------------------------");
                iM(7,2);
                printf("------------------------------");
                iM(7,1);
                printf("Patio e a rua estão cheios   !");
                sleep(2);
            }
            system("cls");
            system("color 0F");
            break;

        case (2) : //remoção

            system("cls");
            system("color 0F");
            lavacarrotrue(QMpatio, &patio, &rua, vetorP, vetorR);
            lavarcarro(&patio, &rua, QMpatio);
            sleep(2);
            system("cls");
            system("color 0F");
            break;

        case (3) :
            flush_in();
            system("cls");
            system("color 0F");
            for(int i=0; i<patio; i++)
            {
                textColor(WHITE, _GREEN);
                printf("| Em %dº na fila:\n", i+1);
                imprimeTCarro(vetorP[i]);
            }
            sleep(4);
            system("cls");
            system("color 0F");
            break;

        case (4) :
            flush_in();
            system("cls");
            system("color 0F");
            for(int i=0; i<rua; i++)
            {
                textColor(WHITE, _GREEN);
                printf("| Em %dº na rua:\n", i+1);
                imprimeTCarro(vetorR[i]);
            }
            sleep(4);
            system("cls");
            system("color 0F");
            break;


        case (5) :
            system("cls");
            system("color 0F");
            textColor(WHITE, _GREEN);
            iM(7,0);
            printf("--------------------------");
            iM(7,1);
            printf("|  Programa Finalizado!  |");
            iM(7,2);
            printf("--------------------------");
            sleep(2);
            break;

        }
    }
    while (opc !=5);
    free(vetorR);
    free(vetorP);
    return 0;
    system("PAUSE");
}

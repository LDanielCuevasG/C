#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "util.h"


/**************************************************************
             MODULO DE CONTROL DEL PROGRAMA
**************************************************************/

void menuSelect(void)
{
    int choice = 1;
    int loop = 0;
    int tecla;
    textcolor(WHITE);
    do
    {
        tecla = getch();
        //CUANDO TECLA SEA ENTER, SE LLAMA SU RESPECTIVA FUCNCION
        if (tecla==13)
        {
            switch(choice)
            {
                case 1: //CREAR UN REGISTRO PARA NUEVO CLIENTE
                {
                    Sleep(50);
                    /*printf("se agrega una linea del input del usuario");
                    Sleep(150);
                    */
                    Registrar();
                    menuInterface(0);
                   break;
                }
                case 2: //ABRIR UN REGISTRO
                {
                    Sleep(50);
                    Abrir();
                    menuInterface(1);
                    break;
                }
                case 3: //SE LLAMA CREDITOS Y CIERRA EL PROGRAMA
                {
					Sleep(50);
					Creditos();
					return;
                }
                default: //EN CASO DE QUE EXISTA UN ERROR
                {
                    printf("HUBO UN ERROR");
                    break;
                }
            }
        }
        //CUANDO LA TECLA SEA CUALQUIER OTRA, VERIFICA SI FUE FLECHA ARRIBA
        //O SI FUE FLECHA ABAJO, ENTONCES LLAMARÁ A LA RESPECTIVA FUNCIÓN
        switch(choice)
        {
            case 1:
            {

                if(tecla==80)
                {
                    clrscr();
                    menuInterface(1);
                    choice++;
                    break;
                }
                break;
            }
            case 2:
            {
                //printf("Opcion %d", choice);

                if(tecla==80)
                {
                    clrscr();
                    menuInterface(2);
                    choice++;
                    break;
                }
                if(tecla==72)
                {
                    clrscr();
                    menuInterface(0);
                    choice--;
                    break;
                }
                break;
            }
            case 3:
            {
                //printf("Opcion %d", choice);

                if(tecla==72)
                {
                    clrscr();
                    menuInterface(1);
                    choice--;
                    break;
                }
                break;
            }

            default:
            {
                printf("error en algo");
                break;
            }
        }

    }while(loop==0);

    return;
}

/**************************************************************
                  MODULOS PRINCIPALES
**************************************************************/

void Registrar(void)
{

    char fila[100]="";
    int ID, x=30,y=5,s=0;
	char tecla;
    char line[200]="";
	char id[5];
    char cliente[20]="";
    char apellidos[20]="";
    char pet[25]="";
	char telefono[15]="";
    char visitas[4]="1";
    char espacio[5]="|";
    char next[]="\n";
    int *token;
    FILE *f;
    f= fopen("database.txt", "rt");
        if(f==NULL)
        {
        perror("EL error es: ");
        exit(1);
        }
    fgets(fila,100, f);
    fclose(f);

	clrscr();
	fflush(stdin);

	if(strlen(fila)==0)
        {
            ID=1;
        }
    else
        {
            ID = asignacionID()+1;
        }

	itoa(ID,id,10);


	InterfazRegistrar(0,x,y);
	gotoxy(x+30,9);
    gets(cliente);

	InterfazRegistrar(1,x,y);
	gotoxy(x+30,12);
    gets(apellidos);

	InterfazRegistrar(2,x,y);
    gotoxy(x+30,15);
    gets(pet);

	InterfazRegistrar(3,x,y);
	gotoxy(x+30,18);
	gets(telefono);

	OpcionesRegistrar(0);
	do
	{
		gotoxy(1,1);
		tecla=getch();
		if(tecla==77)
			{
				s=1;
				OpcionesRegistrar(1);
			}
		else if(tecla==75)
			{
				s=0;
				OpcionesRegistrar(0);
			}
		else if(tecla==13)
			{
				if(s==0)
				{
					if(strlen(cliente)==0 || strlen(apellidos)==0 || strlen(pet)==0 ||strlen(telefono)==0)
					{
						gotoxy(25,24);
						textbackground(RED);
						textcolor(WHITE);
						cprintf("   SE HAN REGISTRADO CAMPOS VACIOS, POR FAVOR, INTENTELO DE NUEVO   ");
						Sleep(2000);
						textbackground(BLACK);
					}
					else if(strlen(cliente)!=0 || strlen(apellidos)!=0 || strlen(pet)!=0 || strlen(telefono)!=0)
					{
						strupr(cliente);
						strupr(apellidos);
						strupr(pet);

						strcat(line, id);
						strcat(line, espacio);
						strcat(line, cliente);
						strcat(line, espacio);
						strcat(line, apellidos);
						strcat(line, espacio);
						strcat(line, pet);
						strcat(line, espacio);
						strcat(line, telefono);
						strcat(line, espacio);
						strcat(line, visitas);
                            if(strlen(fila)==0)
                            {
                                f= fopen("database.txt", "w");
                                if(f==NULL)
                                {
                                    perror("EL error es: ");
                                    exit(1);
                                }
                                fputs(line, f);
                                fclose(f);
                            }
							else if(strlen(fila)!=0)
                            {
                                f= fopen("database.txt", "a+");
                                if(f==NULL)
                                {
                                    perror("EL error es: ");
                                    exit(1);
                                }
                                fputs(next, f);
                                fputs(line, f);
                                fclose(f);
                            }

					}
				break;
				}
				else if(s==1)
				{
					break;
				}
			}
	}while(tecla!=27);

clrscr();
return;
}

void Abrir(void)
{

	char matriz[500][100]={{0}};
    int s=0, ID, count=0, limit=15,x=12,y=1;
    char tecla;
    char fila[100]="";

    clrscr();

    GetData(matriz);

	ID=asignacionID();

	gotoxy(1,100);

	textcolor(WHITE);
    gotoxy(x,y++);
    cprintf("----------------------------------------------------------------------------------------------\n\r");
	gotoxy(x,y++);
    cprintf("                                     LISTA DE CLIENTES                                        \n\r");
	gotoxy(x,y++);
    cprintf("----------------------------------------------------------------------------------------------\n\r");
	gotoxy(x,y++);
    cprintf("  ID    CLIENTE             APELLIDOS           MASCOTA             TELEFONO           VISITAS\n\r");
	gotoxy(x,y++);
    cprintf("----------------------------------------------------------------------------------------------\n\r");
	gotoxy(x,23);
	cprintf("----------------------------------------------------------------------------------------------\n\r");

    strcpy(fila, matriz[0]);
	if(strlen(fila)==0)
    {
        textcolor(WHITE);
        textbackground(RED);
        gotoxy(x,y+7);
        cprintf("                               NO HAY REGISTROS DISPONIBLES                                  \n\r");
        gotoxy(x,y+8);
        cprintf("                               REGRESANDO AL MENU PRINCIPAL                                  \n\r");
        textbackground(BLACK);
        OpcionesAbrir(3);
        MovimientoPagina(2);
        Sleep(3000);
        clrscr();
        return;
    }

    gotoxy(84,25);
    cprintf("----------------------\n\r");
    gotoxy(84,26);
    cprintf(" CLIENTES TOTALES: %i \n\r",ID);
	gotoxy(84,27);
	cprintf("----------------------\n\r");

	OpcionesAbrir(0);
	MovimientoPagina(0);
	Lista(matriz, count, limit);
	gotoxy(1,1);

	do
	{
		tecla=getch();
		if(tecla==77)
			{
				switch(s)
				{
					case 0:
					{
						s=1;
						OpcionesAbrir(1);
						break;
					}
					case 1:
					{
						s=2;
						OpcionesAbrir(2);
						break;
					}
					case 2:
					{
						s=3;
						OpcionesAbrir(3);
						break;
					}
				}
			}
		else if(tecla==75)
			{
				switch(s)
				{
					case 1:
					{
						s=0;
						OpcionesAbrir(0);
						break;
					}
					case 2:
					{
						s=1;
						OpcionesAbrir(1);
						break;
					}
					case 3:
					{
						s=2;
						OpcionesAbrir(2);
						break;
					}
				}

			}

		else if(tecla==80)
			{
				MovimientoPagina(1);
				if(limit>=ID)
					{
					}
				else
					{
					count=count+15;
					limit=limit+15;
					Lista(matriz, count, limit);
					}
				gotoxy(1,1);
			}

		else if(tecla==72)
			{
				MovimientoPagina(0);
				if(limit==15)
					{
					}
					else
					{
					count=count-15;
					limit=limit-15;
					Lista(matriz, count, limit);
					}
				gotoxy(1,1);
			}

		else if(tecla==13)
			{
				if(s==0)
				{
					AbrirBusqueda(matriz);
				}
				else if(s==1)
				{
					AbrirVisita(matriz);
					Lista(matriz, count, limit);
				}
				else if(s==2)
                {
                    AbrirModificar(matriz);
                    Lista(matriz, count, limit);
                }
				else if(s==3)
				{
					break;
				}
			}

	}while(tecla!=27);

	clrscr();
    return;
}

void Creditos(void)
 {

	int y=25, x=30;
	char c;
	clrscr();
    do
    {
        if(y>=20)
        {
            c=WHITE;
        }
        else if(y<20 && y>=14)
        {
            c=LIGHTGRAY;
        }
        else if(y<14 && y>=6)
        {
            c=DARKGRAY;
        }
        else if(y<6 && y>=0)
        {
            c=BLACK;
        }
        textcolor(c);
        gotoxy(x+20,y-2);
        cprintf("REALIZADO POR:\n\r");
        gotoxy(x,y-1);
        cprintf("CARLOS KASSAB ANDRE -----------LUIS DANIEL CUEVAS GARCIA\n\r");
        gotoxy(x+10,y);
        cprintf("UNIVERSIDAD AUTONOMA DE GUADALAJARA");
        Sleep(200);
        textcolor(BLACK);
        gotoxy(x+20,y-2);
        cprintf("REALIZADO POR:\n\r");
        gotoxy(x,y-1);
        cprintf("CARLOS KASSAB ANDRE -----------LUIS DANIEL CUEVAS GARCIA\n\r");
        gotoxy(x+10,y);
        cprintf("UNIVERSIDAD AUTONOMA DE GUADALAJARA");

    }while(--y>1);
    return;
}

/**************************************************************
                  MODULOS SECUNDARIOS
**************************************************************/
void Lista(char matriz[500][100], int count, int limit)
{
	int i,c=1, y=7, x, ID, paginas, actual;
	char *token;
	char fila[300];

	ID=asignacionID();
	paginas=ID/15;
	actual=limit/15;

	if(ID%15!=0)
		{
		paginas++;
		}
	gotoxy(109,18);
	cprintf("%i/%i", actual, paginas);

	for(i=0;i<15;i++)
		{
		gotoxy(1,7+i);
		printf("                                                                                                         ");
		}

	for(i=count;i<limit;i++)
		{
		strcpy(fila,matriz[i]);
		if(strlen(fila)==0)
			{
				break;
			}

		if(fila==NULL)
			{
				break;
			}

        token = strtok(fila, "|");

        do
        {
            switch(c)
            {
            case 1:
                {
                    c=2;
                    x=14;
                    break;
                }
            case 2:
                {
                    c=3;
                    x=20;
                    break;
                }
            case 3:
                {
                    c=4;
                    x=40;
                    break;
                }
            case 4:
                {
                    c=5;
                    x=60;
                    break;
                }
            case 5:
                {
                    c=6;
                    x=80;
                    break;
                }
			case 6:
				{
					c=1;
					x=99;
					break;
				}

            }
            gotoxy(x,y);
            printf("%s", token );

            token = strtok(NULL, "|");
        }while( token != NULL );
	y++;
	};
gotoxy(1,1);
return;
}

void AbrirBusqueda(char matriz[500][100])
{

	int cliente,ID,i,x=12,y=29,c=1, limit =0;
	char pet[25]="";
	char fila[300];
	char *token;
	char fila2[300];
	char *token2;


	fflush(stdin);

    BorrarAbrir(0);

    textcolor(WHITE);
	gotoxy(12,y++);
    cprintf("----------------------------------------------\n\r");
    gotoxy(12,y++);
    cprintf(" ID,NOMBRE O MASCOTA                          \n\r");
	gotoxy(12,y++);
	cprintf("----------------------------------------------\n\r");
	gotoxy(38,y-2);
	gets(pet);
	strupr(pet);
	ID=asignacionID();



	if(strlen(pet)==0)
		{
			textcolor(WHITE);
			textbackground(RED);
			gotoxy(60,y-3);
			cprintf("---------------------------\n\r");
			gotoxy(60,y-2);
			cprintf("   EL CLIENTE NO EXISTE    \n\r");
			gotoxy(60,y-1);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(BLACK);
		}

	else if(strlen(pet)!=0)
		{
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------------------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("  ID    CLIENTE             APELLIDOS           MASCOTA             TELEFONO           VISITAS\n\r");
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------------------------------------------\n\r");
			textcolor(BLACK);
			textbackground(BLACK);
			gotoxy(60,y-6);
			cprintf("---------------------------\n\r");
			gotoxy(60,y-5);
			cprintf("   EL CLIENTE NO EXISTE    \n\r");
			gotoxy(60,y-4);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(BLACK);

			for(i=0;i<ID;i++)
			{
				if(limit==6)
				{
					return;
				}
				strcpy(fila,"");
				strcpy(fila,matriz[i]);
				token = strtok(fila, "|");
				do
				{
					if(strcmp(token,pet)==0)
					{
								strcpy(fila2,matriz[i]);
								token2 = strtok(fila2, "|");
								do
								{

									switch(c)
									{
									case 1:
										{
											c=2;
											x=14;
											break;
										}
									case 2:
										{
											c=3;
											x=20;
											break;
										}
									case 3:
										{
											c=4;
											x=40;
											break;
										}
									case 4:
										{
											c=5;
											x=60;
											break;
										}
									case 5:
										{
											c=6;
											x=80;
											break;
										}
									case 6:
										{
											c=1;
											x=99;
											break;
										}

									}
									gotoxy(x,y);
									printf("%s", token2 );
									token2 = strtok(NULL, "|");
								}while( token2 != NULL );
							y++;
							limit++;
							strcpy(fila2,"");
					}
					token = strtok(NULL, "|");
				}while( token != NULL);
			};

		if(limit==0)
			{
			y=32;
			textcolor(BLACK);
			textbackground(BLACK);
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------------------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("  ID    CLIENTE             APELLIDOS           MASCOTA             TELEFONO           VISITAS\n\r");
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------------------------------------------\n\r");
			textcolor(WHITE);
			textbackground(RED);
			gotoxy(60,y-6);
			cprintf("---------------------------\n\r");
			gotoxy(60,y-5);
			cprintf("   EL CLIENTE NO EXISTE    \n\r");
			gotoxy(60,y-4);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(BLACK);
			}


		};
return;
}

void AbrirVisita( char matriz [500][100])
{

	int cliente, ID, e, visitas, x=12, y=29, c=1;
	char line[100]="";
	char linecpy[100]="";
	char fragment[20]="";
    char espacio[5]="|";
    char next[]="\n";
	char *token;
	fflush(stdin);

    textcolor(WHITE);
	gotoxy(12,y++);
    cprintf("----------------------------------------------\n\r");
    gotoxy(12,y++);
    cprintf(" ID  DEL CLIENTE                              \n\r");
	gotoxy(12,y++);
	cprintf("----------------------------------------------\n\r");
	gotoxy(38,y-2);
	scanf("%i",&cliente);
	ID=asignacionID();



	if(cliente==0)
		{
			textcolor(WHITE);
			textbackground(RED);
			gotoxy(60,y-3);
			cprintf("--------------------------\n\r");
			gotoxy(60,y-2);
			cprintf("   OPERACION CANCELADA    \n\r");
			gotoxy(60,y-1);
			cprintf("--------------------------\n\r");
			textcolor(WHITE);
			textbackground(BLACK);
		}

	if(cliente>ID)
		{
			textcolor(WHITE);
			textbackground(RED);
			gotoxy(60,y-3);
			cprintf("---------------------------\n\r");
			gotoxy(60,y-2);
			cprintf("    EL CLIENTE NO EXISTE   \n\r");
			gotoxy(60,y-1);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(BLACK);
		}

	else if(cliente<=ID && cliente!=0)
		{
			gotoxy(x,y++);
			cprintf("--------------------------------------------------------------------------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("  ID    CLIENTE             APELLIDOS           MASCOTA             TELEFONO           VISITAS +1 \n\r");
			gotoxy(x,y++);
			cprintf("--------------------------------------------------------------------------------------------------\n\r");
			textcolor(BLACK);
			textbackground(BLACK);
			gotoxy(60,y-6);
			cprintf("---------------------------\n\r");
			gotoxy(60,y-5);
			cprintf("   EL CLIENTE NO EXISTE    \n\r");
			gotoxy(60,y-4);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(BLACK);

            for(e=0;e<6;e++)
            {
                gotoxy(x,35+e);
                printf("                                                                                                  \n");
            }

			strcpy(line, matriz[cliente-1]);
			token = strtok(line, "|");

                    do
                    {

                        switch(c)
                        {
                            case 1:
                            {
                                c=2;
								gotoxy(14,y);
                                cprintf( "%s", token );
								strcpy(fragment,token);
                                strcat(linecpy, fragment);
                                strcat(linecpy, espacio);
                                break;
                            }
                            case 2:
                            {
                                c=3;
                                gotoxy(20,y);
                                cprintf("%s", token );
                                strcpy(fragment,"");
								strcpy(fragment,token);
                                strcat(linecpy, fragment);
                                strcat(linecpy, espacio);
                                break;
                            }
                            case 3:
                            {
                                c=4;
                                gotoxy(40,y);
                                cprintf( "%s", token );
                                strcpy(fragment,"");
								strcpy(fragment,token);
                                strcat(linecpy, fragment);
                                strcat(linecpy, espacio);
                                break;
                            }
                            case 4:
                            {
                                c=5;
                                gotoxy(60,y);
                                cprintf( "%s", token );
                                strcpy(fragment,"");
								strcpy(fragment,token);
                                strcat(linecpy, fragment);
                                strcat(linecpy, espacio);
                                break;
                            }
                            case 5:
                            {
								c=6;
								gotoxy(80,y);
								cprintf( "%s", token );
								strcpy(fragment,"");
								strcpy(fragment,token);
                                strcat(linecpy, fragment);
                                strcat(linecpy, espacio);
                                break;
                            }
							case 6:
							{

                                visitas= atoi(token);
                                visitas++;
                                itoa(visitas,token,10);
								gotoxy(99,y);
								cprintf( "%s", token );
								strcpy(fragment,"");
                                strcpy(fragment,token);
                                strcat(linecpy, fragment);
                                if(cliente!=ID)
                                {
                                    strcat(linecpy,next);
                                }
								strcpy(matriz[cliente-1], linecpy);
							}
                        }
                    token = strtok(NULL, "|");
                    }while( token != NULL );

			SetData(matriz);

			textcolor(WHITE);
			textbackground(GREEN);
			y=y+2;
			gotoxy(x+35,y++);
			cprintf("----------------------------\n\r");
			gotoxy(x+35,y++);
			cprintf("     REGISTRO EXITOSO       \n\r");
			gotoxy(x+35,y++);
			cprintf("----------------------------\n\r");
			textbackground(BLACK);
		}

Sleep(2000);

    BorrarAbrir(1);
gotoxy(1,1);
return;
}

void AbrirModificar(char matriz [500][100])
{
    int cliente, ID, e, visitas, x=12, y=29, c=0, s=0, o=0;
    char tecla;
	char line[100]="";

	char idcpy[20]="";
	char namecpy[20]="";
	char lastcpy[20]="";
	char numbercpy[20]="";
	char petcpy[20]="";
	char visitscpy[20]="";

    char espacio[5]="|";
    //char next[]="\n";
	char *token;
	fflush(stdin);

	textcolor(WHITE);
	gotoxy(12,y++);
    cprintf("-------------------------------------\n\r");
    gotoxy(12,y++);
    cprintf(" ID  DEL CLIENTE                     \n\r");
	gotoxy(12,y++);
	cprintf("-------------------------------------\n\r");
	gotoxy(38,y-2);
	scanf("%i",&cliente);
	ID=asignacionID();

	if(cliente>ID)
		{
			textcolor(WHITE);
			textbackground(RED);
			gotoxy(60,y-3);
			cprintf("---------------------------\n\r");
			gotoxy(60,y-2);
			cprintf("    EL CLIENTE NO EXISTE   \n\r");
			gotoxy(60,y-1);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(BLACK);
			Sleep(2000);
		}

	else if(cliente<=ID)
		{
            BorrarAbrir(0);
			gotoxy(x,y++);
			cprintf("--------------------------------------------------------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("  CLIENTE             APELLIDOS           MASCOTA             TELEFONO          \n\r");
			gotoxy(x,y++);
			cprintf("--------------------------------------------------------------------------------\n\r");
			textcolor(BLACK);
			textbackground(BLACK);
			gotoxy(60,y-6);
			cprintf("---------------------------\n\r");
			gotoxy(60,y-5);
			cprintf("   EL CLIENTE NO EXISTE    \n\r");
			gotoxy(60,y-4);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(BLACK);


            strcpy(line, matriz[cliente-1]);
			token = strtok(line, "|");

                    do
                        {
                        switch(c)
                        {

                            case 0:
                            {
                                c=1;
                                strcpy(idcpy,token);
                                break;
                            }
                            case 1:
                            {
                                c=2;
                                strcpy(namecpy,token);
                                break;
                            }
                            case 2:
                            {
                                c=3;
                                strcpy(lastcpy,token);

                                break;
                            }
                            case 3:
                            {
                                c=4;
                                strcpy(petcpy,token);
                                break;
                            }
                            case 4:
                            {
								c=5;
								strcpy(numbercpy,token);
                                break;
                            }
							case 5:
							{
							    c=0;
                                strcpy(visitscpy,token);
                                break;
							}
                        }
                        token = strtok(NULL, "|");
                        }while( token != NULL );

        c=0;
        MovimientoModificar(namecpy,lastcpy,petcpy,numbercpy,c);
        OpcionesModificar(2);
        do
        {
            fflush(stdin);
            tecla=getch();
            if(tecla==77)
                {
                    switch(c)
                    {
                        case 0:
                        {
                            c=1;
                            MovimientoModificar(namecpy,lastcpy,petcpy,numbercpy,c);
                            break;
                        }
                        case 1:
                        {
                            c=2;
                            MovimientoModificar(namecpy,lastcpy,petcpy,numbercpy,c);
                            break;
                        }
                        case 2:
                        {
                            c=3;
                            MovimientoModificar(namecpy,lastcpy,petcpy,numbercpy,c);
                            break;
                        }
                        case 3:
                        {
                            c=4;
                            s=1;
                            MovimientoModificar(namecpy,lastcpy,petcpy,numbercpy,c);
                            OpcionesModificar(0);
                            break;

                        }

                    }
                }

            else if(tecla==75)
                {
                    switch(c)
                    {
                        case 1:
                        {
                            c=0;
                            MovimientoModificar(namecpy,lastcpy,petcpy,numbercpy,c);
                            break;
                        }
                        case 2:
                        {
                            c=1;
                            MovimientoModificar(namecpy,lastcpy,petcpy,numbercpy,c);
                            break;
                        }
                        case 3:
                        {
                            c=2;
                            MovimientoModificar(namecpy,lastcpy,petcpy,numbercpy,c);
                            break;
                        }
                        case 4:
                        {
                            c=3;
                            s=0;
                            MovimientoModificar(namecpy,lastcpy,petcpy,numbercpy,c);
                            OpcionesModificar(2);
                            break;
                        }

                    }
                }

            else if(tecla==72)
                {
                    if(s==1)
                    {
                        o=0;
                        OpcionesModificar(0);
                    }
                }

            else if(tecla==80)
                {
                    if(s==1)
                    {
                        o=1;
                        OpcionesModificar(1);
                    }
                }

            else if(tecla==13)
                {
                    if(s==0)
                    {
                        fflush(stdin);
                        switch(c)
                        {
                            case 0:
                            {
                                gotoxy(14,y);
                                printf("                ");
                                strcpy(namecpy,"");
                                gotoxy(14,y);
                                gets(namecpy);
                                strupr(namecpy);
                                break;
                            }
                            case 1:
                            {
                                gotoxy(34,y);
                                printf("                ");
                                strcpy(lastcpy,"");
                                gotoxy(34,y);
                                gets(lastcpy);
                                strupr(lastcpy);
                                break;
                            }
                            case 2:
                            {
                                gotoxy(54,y);
                                printf("                ");
                                strcpy(petcpy,"");
                                gotoxy(54,y);
                                gets(petcpy);
                                strupr(petcpy);
                                break;
                            }
                            case 3:
                            {
                                gotoxy(74,y);
                                printf("                ");
                                strcpy(numbercpy,"");
                                gotoxy(74,y);
                                gets(numbercpy);
                                strupr(numbercpy);
                                break;
                            }

                        }
                    }

                    else if(s==1)
                    {
                        if(o==0)
                        {
                            strcpy(line,"");
                            strcat(line, idcpy);
                            strcat(line, espacio);
                            strcat(line, namecpy);
                            strcat(line, espacio);
                            strcat(line, lastcpy);
                            strcat(line, espacio);
                            strcat(line, petcpy);
                            strcat(line, espacio);
                            strcat(line, numbercpy);
                            strcat(line, espacio);
                            strcat(line, visitscpy);
                            /*if(cliente!=ID)
                                {
                                    strcat(line,next);
                                }*/
                            strcpy(matriz[cliente-1], line);
                            break;
                        }
                        else if(o==1)
                        {
                            break;
                        }
                    }
                }
        }while(tecla!=27);

        SetData(matriz);
    }


    BorrarAbrir(1);
	gotoxy(1,1);

return;
}

/**************************************************************
                MODULOS COMPLEMENTARIOS
**************************************************************/

int asignacionID(void)
{
    char fila[100];
    int ID=0;
    FILE *f;
	f= fopen("database.txt", "rt");
    if(f==NULL)
        {
            perror("EL error es: ");
            exit(1);
        }

    do
    {
          fgets(fila,100,f);
          ID++;
    }while(fscanf(f,"%[^\n]s",&fila)!=EOF);

    fclose(f);
return ID;

/** Local: **/
}

void BorrarAbrir(int s)
{
 int x=12, y, e;
     switch(s)
     {
        case 0:
            {
            y=32;
            break;
            }
        case 1:
            {
            y=29;
            break;
            }
        case 2:
            {
            y=35;
            break;
            }
     }

    for(e=0;e<12;e++)
	{
		gotoxy(x,y+e);
		printf("                                                                                                    \n");
	}

return;
}

void GetData(char matriz [500][100])
{
    int r=0;
    FILE *f;


	f= fopen("database.txt", "rt");
    if(f==NULL)
    {
        perror("EL error es: ");
        exit(1);
    }

	do
	{
        fgets(matriz[r],100, f);
		r++;
	}while(!feof(f));
	fclose(f);

return;
/** Local: **/
}

void SetData(char matriz [500][100])
{
    int w, ID;
    char line[100]="";
    FILE *f;
    ID=asignacionID();

    f= fopen("database.txt", "w+");
    if(f==NULL)
        {
            perror("EL error es: ");
            exit(1);
        }

    for(w=0;w<ID;w++)
        {
            strcpy(line,"");
            strcpy(line,matriz[w]);
            fputs(line, f);
        }

    fclose(f);
return;

/** Local: **/

}

/**************************************************************
                FUNCION DE INTERFAZ GRAFICA
                 PARA EL MODULO PRINCIPAL
**************************************************************/
void menuTitulo(void)
{
    int count=0;
    int x=20, y=10;
    do
    {
		textcolor(RED);
		gotoxy(x,y);
		cprintf("  _      _____ _______ _______ _      ______   _____  ______ _______ _____ ");
		gotoxy(x,y+1);
		cprintf(" | |    |_   _|__   __|__   __| |    |  ____| |  __ \|  ____|__   __/ ____|");
		gotoxy(x,y+2);
		cprintf(" | |      | |    | |     | |  | |    | |__    | |__) | |__     | | | (___  ");
		gotoxy(x,y+3);
		cprintf(" | |      | |    | |     | |  | |    |  __|   |  ___/|  __|    | |  \___ \ ");
		gotoxy(x,y+4);
		cprintf(" | |____ _| |_   | |     | |  | |____| |____  | |    | |____   | |  ____) |");
		gotoxy(x,y+5);
		cprintf(" |______|_____|  |_|     |_|  |______|______| |_|    |______|  |_| |_____/ ");

		Sleep(200);
		textcolor(WHITE);
		clrscr();
		gotoxy(x,y);
		cprintf("  _      _____ _______ _______ _      ______   _____  ______ _______ _____ ");
		gotoxy(x,y+1);
		cprintf(" | |    |_   _|__   __|__   __| |    |  ____| |  __ \|  ____|__   __/ ____|");
		gotoxy(x,y+2);
		cprintf(" | |      | |    | |     | |  | |    | |__    | |__) | |__     | | | (___  ");
		gotoxy(x,y+3);
		cprintf(" | |      | |    | |     | |  | |    |  __|   |  ___/|  __|    | |  \___ \ ");
		gotoxy(x,y+4);
		cprintf(" | |____ _| |_   | |     | |  | |____| |____  | |    | |____   | |  ____) |");
		gotoxy(x,y+5);
		cprintf(" |______|_____|  |_|     |_|  |______|______| |_|    |______|  |_| |_____/ ");
		Sleep(200);
		count++;
    }while(count<3);
    return;
}

/**************************************************************
               FUNCION DE INTERFAZ GRAFICA
                PARA EL MODULO DE CONTROL
**************************************************************/
void menuInterface(int s)
{
    int x=13, y=6;

switch(s)
{
    case 0:
        {
            textbackground(WHITE);
            textcolor(BLACK);
            gotoxy(x,y++);
            cprintf("-------------------------------------------");
            gotoxy(x,y++);
            cprintf("    ___ ___ ___ ___ ___ _____ ___  ___     ");
            gotoxy(x,y++);
            cprintf("   | _ \\ __/ __|_ _/ __|_   _| _ \\/ _ \\    ");
            gotoxy(x,y++);
            cprintf("   |   / _| (_ || |\\__ \\ | | |   / (_) |   ");
            gotoxy(x,y++);
            cprintf("   |_|_\\___\\___|___|___/ |_| |_|_\\\\___/    ");
            gotoxy(x,y++);
            cprintf("                                           ");
            gotoxy(x,y++);
            cprintf("-------------------------------------------");

            textbackground(BLACK);
            textcolor(WHITE);
            gotoxy(x,y++);
            cprintf("-------------------------------------------");
            gotoxy(x,y++);
            cprintf("    ___ _    ___ ___ _  _ _____ ___ ___    ");
            gotoxy(x,y++);
            cprintf("   / __| |  |_ _| __| \\| |_   _| __/ __|   ");
            gotoxy(x,y++);
            cprintf("  | (__| |__ | || _|| .` | | | | _|\\__ \\   ");
            gotoxy(x,y++);
            cprintf("   \\___|____|___|___|_|\\_| |_| |___|___/   ");
            gotoxy(x,y++);
            cprintf("                                           ");
            gotoxy(x,y++);
            cprintf("-------------------------------------------");

            gotoxy(x,y++);
            cprintf("-------------------------------------------");
            gotoxy(x,y++);
            cprintf("       ___ ___ ___ ___    _   ___          ");
            gotoxy(x,y++);
            cprintf("      / __| __| _ \\ _ \\  /_\\ | _ \\         ");
            gotoxy(x,y++);
            cprintf("     | (__| _||   /   / / _ \\|   /         ");
            gotoxy(x,y++);
            cprintf("      \\___|___|_|_\\_|_\\/_/ \\_\\_|_\\         ");
            gotoxy(x,y++);
            cprintf("                                           ");
            gotoxy(x,y++);
            cprintf("-------------------------------------------");
            break;
        }
    case 1:
        {

            gotoxy(x,y++);
            cprintf("-------------------------------------------");
            gotoxy(x,y++);
            cprintf("    ___ ___ ___ ___ ___ _____ ___  ___     ");
            gotoxy(x,y++);
            cprintf("   | _ \\ __/ __|_ _/ __|_   _| _ \\/ _ \\    ");
            gotoxy(x,y++);
            cprintf("   |   / _| (_ || |\\__ \\ | | |   / (_) |   ");
            gotoxy(x,y++);
            cprintf("   |_|_\\___\\___|___|___/ |_| |_|_\\\\___/    ");
            gotoxy(x,y++);
            cprintf("                                           ");
            gotoxy(x,y++);
            cprintf("-------------------------------------------");

            textbackground(WHITE);
            textcolor(BLACK);
            gotoxy(x,y++);
            cprintf("-------------------------------------------");
            gotoxy(x,y++);
            cprintf("    ___ _    ___ ___ _  _ _____ ___ ___    ");
            gotoxy(x,y++);
            cprintf("   / __| |  |_ _| __| \\| |_   _| __/ __|   ");
            gotoxy(x,y++);
            cprintf("  | (__| |__ | || _|| .` | | | | _|\\__ \\   ");
            gotoxy(x,y++);
            cprintf("   \\___|____|___|___|_|\\_| |_| |___|___/   ");
            gotoxy(x,y++);
            cprintf("                                           ");
            gotoxy(x,y++);
            cprintf("-------------------------------------------");

            textbackground(BLACK);
            textcolor(WHITE);
            gotoxy(x,y++);
            cprintf("-------------------------------------------");
            gotoxy(x,y++);
            cprintf("       ___ ___ ___ ___    _   ___          ");
            gotoxy(x,y++);
            cprintf("      / __| __| _ \\ _ \\  /_\\ | _ \\         ");
            gotoxy(x,y++);
            cprintf("     | (__| _||   /   / / _ \\|   /         ");
            gotoxy(x,y++);
            cprintf("      \\___|___|_|_\\_|_\\/_/ \\_\\_|_\\         ");
            gotoxy(x,y++);
            cprintf("                                           ");
            gotoxy(x,y++);
            cprintf("-------------------------------------------");
            break;
        }
    case 2:
        {
            gotoxy(x,y++);
            cprintf("-------------------------------------------");
            gotoxy(x,y++);
            cprintf("    ___ ___ ___ ___ ___ _____ ___  ___     ");
            gotoxy(x,y++);
            cprintf("   | _ \\ __/ __|_ _/ __|_   _| _ \\/ _ \\    ");
            gotoxy(x,y++);
            cprintf("   |   / _| (_ || |\\__ \\ | | |   / (_) |   ");
            gotoxy(x,y++);
            cprintf("   |_|_\\___\\___|___|___/ |_| |_|_\\\\___/    ");
            gotoxy(x,y++);
            cprintf("                                           ");
            gotoxy(x,y++);
            cprintf("-------------------------------------------");


            gotoxy(x,y++);
            cprintf("-------------------------------------------");
            gotoxy(x,y++);
            cprintf("    ___ _    ___ ___ _  _ _____ ___ ___    ");
            gotoxy(x,y++);
            cprintf("   / __| |  |_ _| __| \\| |_   _| __/ __|   ");
            gotoxy(x,y++);
            cprintf("  | (__| |__ | || _|| .` | | | | _|\\__ \\   ");
            gotoxy(x,y++);
            cprintf("   \\___|____|___|___|_|\\_| |_| |___|___/   ");
            gotoxy(x,y++);
            cprintf("                                           ");
            gotoxy(x,y++);
            cprintf("-------------------------------------------");

            textbackground(WHITE);
            textcolor(BLACK);
            gotoxy(x,y++);
            cprintf("-------------------------------------------");
            gotoxy(x,y++);
            cprintf("       ___ ___ ___ ___    _   ___          ");
            gotoxy(x,y++);
            cprintf("      / __| __| _ \\ _ \\  /_\\ | _ \\         ");
            gotoxy(x,y++);
            cprintf("     | (__| _||   /   / / _ \\|   /         ");
            gotoxy(x,y++);
            cprintf("      \\___|___|_|_\\_|_\\/_/ \\_\\_|_\\         ");
            gotoxy(x,y++);
            cprintf("                                           ");
            gotoxy(x,y++);
            cprintf("-------------------------------------------");
            textbackground(BLACK);
            textcolor(WHITE);
            break;
        }
}

gotoxy(1,1);
return;
}

/**************************************************************
              FUNCIONES DE INTERFAZ GRAFICA
                PARA MODULOS PRINCIPALES
**************************************************************/

void InterfazRegistrar(int s, int x, int y)
{
	textcolor(WHITE);
	textbackground(BLACK);
	gotoxy(x+56,9);
	printf("||\n\r");
	gotoxy(x+56,12);
	printf("||\n\r");
	gotoxy(x+56,15);
	printf("||\n\r");
	gotoxy(x+56,18);
	printf("||\n\r");
	switch(s)
	{
		case 0:
		{
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("||                       REGISTRO                       ||\n\r");
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------\n\r");
			textcolor(WHITE);
			textbackground(GREEN);
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| NOMBRE DEL CLIENTE    ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(BLACK);
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| APELLIDOS DEL CLIENTE ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| NOMBRE DE LA MASCOTA  ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| TELEFONO              ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------\n\r");
			break;
		}

		case 1:
		{
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("||                       REGISTRO                       ||\n\r");
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| NOMBRE DEL CLIENTE    ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(GREEN);
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| APELLIDOS DEL CLIENTE ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(BLACK);
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| NOMBRE DE LA MASCOTA  ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| TELEFONO              ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------\n\r");
			break;
		}

		case 2:
		{
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("||                       REGISTRO                       ||\n\r");
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| NOMBRE DEL CLIENTE    ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| APELLIDOS DEL CLIENTE ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(GREEN);
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| NOMBRE DE LA MASCOTA  ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(BLACK);
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| TELEFONO              ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------\n\r");
			break;
		}

		case 3:
		{
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("||                       REGISTRO                       ||\n\r");
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| NOMBRE DEL CLIENTE    ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| APELLIDOS DEL CLIENTE ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| NOMBRE DE LA MASCOTA  ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(GREEN);
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			gotoxy(x,y++);
			cprintf("|| TELEFONO              ||\n\r");
			gotoxy(x+27,y);
			printf("-------------------------------\n\r");
			gotoxy(x,y++);
			cprintf("---------------------------\n\r");
			textcolor(WHITE);
			textbackground(BLACK);
			gotoxy(x,y++);
			cprintf("----------------------------------------------------------\n\r");
			break;
		}
	}
return;
}

void OpcionesRegistrar(int s)
{
	int x=39, y=22;
	switch(s)
	{
		case 0:
		{
			textbackground(GREEN);
			textcolor(WHITE);
			gotoxy(x,y+1);
			cprintf("---------------\n\r");
			gotoxy(x,y+2);
			cprintf("||  ACEPTAR  ||\n\r");
			gotoxy(x,y+3);
			cprintf("---------------\n\r");
			textbackground(BLACK);
			textcolor(WHITE);
			gotoxy(x+24,y+1);
			cprintf("----------------\n\r");
			gotoxy(x+24,y+2);
			cprintf("||  CANCELAR  ||\n\r");
			gotoxy(x+24,y+3);
			cprintf("----------------\n\r");
			break;
		}
		case 1:
		{
			textbackground(BLACK);
			textcolor(WHITE);
			gotoxy(x,y+1);
			cprintf("---------------\n\r");
			gotoxy(x,y+2);
			cprintf("||  ACEPTAR  ||\n\r");
			gotoxy(x,y+3);
			cprintf("---------------\n\r");
			textbackground(RED);
			textcolor(WHITE);
			gotoxy(x+24,y+1);
			cprintf("----------------\n\r");
			gotoxy(x+24,y+2);
			cprintf("||  CANCELAR  ||\n\r");
			gotoxy(x+24,y+3);
			cprintf("----------------\n\r");
			textbackground(BLACK);
			break;
		}

	}

return;
}

void OpcionesAbrir(int s)
{
	int x=12, y=25;
	switch(s)
	{
		case 0:
		{
			textbackground(GREEN);
			textcolor(WHITE);
			gotoxy(x,y);
			cprintf("------------\n\r");
			gotoxy(x,y+1);
			cprintf("  BUSQUEDA  \n\r");
			gotoxy(x,y+2);
			cprintf("------------\n\r");
			textbackground(BLACK);
			textcolor(WHITE);
			gotoxy(x+15,y);
			cprintf("----------------\n\r");
			gotoxy(x+15,y+1);
			cprintf(" AGREGAR VISITA \n\r");
			gotoxy(x+15,y+2);
			cprintf("----------------\n\r");
			gotoxy(x+34,y);
			cprintf("--------------\n\r");
			gotoxy(x+34,y+1);
			cprintf("   MODIFICAR  \n\r");
			gotoxy(x+34,y+2);
			cprintf("--------------\n\r");
			gotoxy(x+51,y);
			cprintf("------------\n\r");
			gotoxy(x+51,y+1);
			cprintf("  REGRESAR  \n\r");
			gotoxy(x+51,y+2);
			cprintf("------------\n\r");
			break;
		}
		case 1:
		{
			gotoxy(x,y);
			cprintf("------------\n\r");
			gotoxy(x,y+1);
			cprintf("  BUSQUEDA  \n\r");
			gotoxy(x,y+2);
			cprintf("------------\n\r");
			textbackground(GREEN);
			textcolor(WHITE);
			gotoxy(x+15,y);
			cprintf("----------------\n\r");
			gotoxy(x+15,y+1);
			cprintf(" AGREGAR VISITA \n\r");
			gotoxy(x+15,y+2);
			cprintf("----------------\n\r");
			textbackground(BLACK);
			textcolor(WHITE);
			gotoxy(x+34,y);
			cprintf("--------------\n\r");
			gotoxy(x+34,y+1);
			cprintf("   MODIFICAR  \n\r");
			gotoxy(x+34,y+2);
			cprintf("--------------\n\r");
			gotoxy(x+51,y);
			cprintf("------------\n\r");
			gotoxy(x+51,y+1);
			cprintf("  REGRESAR  \n\r");
			gotoxy(x+51,y+2);
			cprintf("------------\n\r");
			break;
		}
		case 2:
		{
			gotoxy(x,y);
			cprintf("------------\n\r");
			gotoxy(x,y+1);
			cprintf("  BUSQUEDA  \n\r");
			gotoxy(x,y+2);
			cprintf("------------\n\r");
			gotoxy(x+15,y);
			cprintf("----------------\n\r");
			gotoxy(x+15,y+1);
			cprintf(" AGREGAR VISITA \n\r");
			gotoxy(x+15,y+2);
			cprintf("----------------\n\r");
			textbackground(GREEN);
			textcolor(WHITE);
			gotoxy(x+34,y);
			cprintf("--------------\n\r");
			gotoxy(x+34,y+1);
			cprintf("   MODIFICAR  \n\r");
			gotoxy(x+34,y+2);
			cprintf("--------------\n\r");
			textbackground(BLACK);
			textcolor(WHITE);
			gotoxy(x+51,y);
			cprintf("------------\n\r");
			gotoxy(x+51,y+1);
			cprintf("  REGRESAR  \n\r");
			gotoxy(x+51,y+2);
			cprintf("------------\n\r");
			break;
		}
		case 3:
		{
			gotoxy(x,y);
			cprintf("------------\n\r");
			gotoxy(x,y+1);
			cprintf("  BUSQUEDA  \n\r");
			gotoxy(x,y+2);
			cprintf("------------\n\r");
			gotoxy(x+15,y);
			cprintf("----------------\n\r");
			gotoxy(x+15,y+1);
			cprintf(" AGREGAR VISITA \n\r");
			gotoxy(x+15,y+2);
			cprintf("----------------\n\r");
			gotoxy(x+34,y);
			cprintf("--------------\n\r");
			gotoxy(x+34,y+1);
			cprintf("   MODIFICAR  \n\r");
			gotoxy(x+34,y+2);
			cprintf("--------------\n\r");
			textbackground(RED);
			textcolor(WHITE);
			gotoxy(x+51,y);
			cprintf("------------\n\r");
			gotoxy(x+51,y+1);
			cprintf("  REGRESAR  \n\r");
			gotoxy(x+51,y+2);
			cprintf("------------\n\r");
			textbackground(BLACK);
			textcolor(WHITE);
			break;
		}
	}

return;
}

void OpcionesModificar(int s)
{

	int x=95, y=31;
	switch(s)
	{
		case 0:
		{
			textbackground(GREEN);
			textcolor(WHITE);
			gotoxy(x,y+1);
			cprintf("----------------\n\r");
			gotoxy(x,y+2);
			cprintf("||  ACEPTAR   ||\n\r");
			gotoxy(x,y+3);
			cprintf("----------------\n\r");
			textbackground(BLACK);
			textcolor(WHITE);
			gotoxy(x,y+4);
			cprintf("----------------\n\r");
			gotoxy(x,y+5);
			cprintf("||  CANCELAR  ||\n\r");
			gotoxy(x,y+6);
			cprintf("----------------\n\r");
			break;
		}
		case 1:
		{
			textbackground(BLACK);
			textcolor(WHITE);
			gotoxy(x,y+1);
			cprintf("----------------\n\r");
			gotoxy(x,y+2);
			cprintf("||  ACEPTAR   ||\n\r");
			gotoxy(x,y+3);
			cprintf("----------------\n\r");
			textbackground(RED);
			textcolor(WHITE);
			gotoxy(x,y+4);
			cprintf("----------------\n\r");
			gotoxy(x,y+5);
			cprintf("||  CANCELAR  ||\n\r");
			gotoxy(x,y+6);
			cprintf("----------------\n\r");
			textbackground(BLACK);
			break;
		}
        case 2:
		{
		    textcolor(WHITE);
            textbackground(BLACK);
			gotoxy(x,y+1);
			cprintf("----------------\n\r");
			gotoxy(x,y+2);
			cprintf("||  ACEPTAR   ||\n\r");
			gotoxy(x,y+3);
			cprintf("----------------\n\r");
			gotoxy(x,y+4);
			cprintf("----------------\n\r");
			gotoxy(x,y+5);
			cprintf("||  CANCELAR  ||\n\r");
			gotoxy(x,y+6);
			cprintf("----------------\n\r");
			textbackground(BLACK);
			break;

		}
	}
return;
}

void MovimientoPagina(int r)
{
	int x=107, y=9;
	switch(r)
	{
		case 0:
		{
			textbackground(WHITE);
			textcolor(BLACK);
			gotoxy(x,y+1);
			cprintf("-------\n\r");
			gotoxy(x,y+2);
			cprintf("|| < ||\n\r");
			gotoxy(x,y+3);
			cprintf("-------\n\r");
			textbackground(BLACK);
			textcolor(WHITE);
			gotoxy(x,y+5);
			cprintf("-------\n\r");
			gotoxy(x,y+6);
			cprintf("|| > ||\n\r");
			gotoxy(x,y+7);
			cprintf("-------\n\r");
			break;
		}
		case 1:
		{
			textbackground(BLACK);
			textcolor(WHITE);
			gotoxy(x,y+1);
			cprintf("-------\n\r");
			gotoxy(x,y+2);
			cprintf("|| < ||\n\r");
			gotoxy(x,y+3);
			cprintf("-------\n\r");
			textbackground(WHITE);
			textcolor(BLACK);
			gotoxy(x,y+5);
			cprintf("-------\n\r");
			gotoxy(x,y+6);
			cprintf("|| > ||\n\r");
			gotoxy(x,y+7);
			cprintf("-------\n\r");
			textbackground(BLACK);
			textcolor(WHITE);
			break;
		}
		case 2:
		{
		    textbackground(BLACK);
			textcolor(WHITE);
			gotoxy(x,y+1);
			cprintf("-------\n\r");
			gotoxy(x,y+2);
			cprintf("|| < ||\n\r");
			gotoxy(x,y+3);
			cprintf("-------\n\r");
			gotoxy(x,y+5);
			cprintf("-------\n\r");
			gotoxy(x,y+6);
			cprintf("|| > ||\n\r");
			gotoxy(x,y+7);
			cprintf("-------\n\r");
			break;
		}
	}

return;

}

void MovimientoModificar(char namecpy[20],char lastcpy[20],char petcpy[20], char numbercpy[20], int c)
{
    int y=35;
    switch(c)
                {
                    case 0:
                    {
                        textcolor(BLACK);
                        textbackground(WHITE);
                        gotoxy(14,y);
                        cprintf("%s", namecpy );
                        textcolor(WHITE);
                        textbackground(BLACK);
                        gotoxy(34,y);
                        cprintf("%s", lastcpy );
                        gotoxy(54,y);
                        cprintf("%s", petcpy );
                        gotoxy(74,y);
                        cprintf("%s", numbercpy );
                        break;
                    }
                    case 1:
                    {
                        gotoxy(14,y);
                        cprintf("%s", namecpy );
                        textcolor(BLACK);
                        textbackground(WHITE);
                        gotoxy(34,y);
                        cprintf("%s", lastcpy );
                        textcolor(WHITE);
                        textbackground(BLACK);
                        gotoxy(54,y);
                        cprintf("%s", petcpy );
                        gotoxy(74,y);
                        cprintf("%s", numbercpy );
                        break;
                    }
                    case 2:
                    {
                        gotoxy(14,y);
                        cprintf("%s", namecpy );
                        gotoxy(34,y);
                        cprintf("%s", lastcpy );
                        textcolor(BLACK);
                        textbackground(WHITE);
                        gotoxy(54,y);
                        cprintf("%s", petcpy );
                        textcolor(WHITE);
                        textbackground(BLACK);
                        gotoxy(74,y);
                        cprintf("%s", numbercpy );
                        break;
                    }
                        case 3:
                    {
                        gotoxy(14,y);
                        cprintf("%s", namecpy );
                        gotoxy(34,y);
                        cprintf("%s", lastcpy );
                        gotoxy(54,y);
                        cprintf("%s", petcpy );
                        textcolor(BLACK);
                        textbackground(WHITE);
                        gotoxy(74,y);
                        cprintf("%s", numbercpy );
                        textcolor(WHITE);
                        textbackground(BLACK);
                        break;
                    }
                        case 4:
                    {
                        textcolor(WHITE);
                        textbackground(BLACK);
                        gotoxy(14,y);
                        cprintf("%s", namecpy );
                        gotoxy(34,y);
                        cprintf("%s", lastcpy );
                        gotoxy(54,y);
                        cprintf("%s", petcpy );
                        gotoxy(74,y);
                        cprintf("%s", numbercpy );
                        break;
                    }
                }
return;
}


/**************************************************************
                      FIN DEL PROGRAMA
**************************************************************/

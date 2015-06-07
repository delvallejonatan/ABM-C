#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------------------------------------------------------------------*/

#define ALTA 1
#define LISTA 3
#define SALIR 10
#define MODIFICAR 2
#define ESTADISTICA 4
#define MUESTRA 5
#define MUESTRAPOSICION 6
#define BAJA 7
#define ORDENAR 9

#define TAMDES 20

/*-------------------------------------------------------------------------------------------------*/

typedef struct {
	int d, m, a;
} fecha;

typedef struct {
	int codigo;
	char descripcion[TAMDES];
	int stock;
	fecha ingreso;
} articulo;

/*--------------------------------------------------------------------------------------------------*/

int menu();
void alta();
void lista();
void modificar ();
void estadistica();
void muestra();
void muestraposicion();
void baja ();
long int filesize(FILE *pf);
void ordenar();

/*--------------------------------------------------------------------------------------------------*/
int main(void)
{
	int opcion;
	while ((opcion = menu()) != SALIR)
	{
		switch(opcion)
		{
		case ALTA:
			alta();
			break;

		case LISTA:
			system("cls");
			lista();
			system("pause");
			printf("\n\n\n");
			system("cls");
			break;

		case MODIFICAR:
			system("cls");		    
			modificar();
			system("pause");	
			printf("\n\n\n");
			system("cls");
			break;

		case ESTADISTICA:
			system("cls");
			estadistica();
			system("pause");
			printf("\n\n\n");
			system("cls");
			break;

		case MUESTRA:
			system("cls");
			muestra();
			system("pause");
			printf("\n\n\n");
			system("cls");
			break;

		case MUESTRAPOSICION:
			system("cls");
			muestraposicion();
			system("pause");
			printf("\n\n\n");
			system("cls");
			break;


		case BAJA:
			system("cls");
			baja();
			system("pause");
			printf("\n\n\n");
			system("cls");
			break;

		case ORDENAR:
			system("cls");
			ordenar();
			system("pause");
			printf("\n\n\n");
			system("cls");
			break;

		}
	}
	return 0;
}
/*------------------------------------------------------------------------------------------------*/

int menu()
{
	int opcion;
	printf("\n       ALTA BAJA MODIFICACION DEL VALLE J. \n\n\n");
	printf("    |      [1]  Alta                       |\n");
	printf("    |      [2]  Modificar                  |\n");
	printf("    |      [3]  Lista                      |\n");
	printf("    |      [4]  Estadistica                |\n");
	printf("    |      [5]  Muestra                    |\n");
	printf("    |      [6]  MuestraPosicion            |\n");
	printf("    |      [7]  Baja                       |\n");
	printf("    |      [9]  Ordenar Alfabeticamente    |\n");
	printf("    |      [10] Salir                      |\n");
	printf(" \n          Diguite su opcion: ");
	scanf("%d", &opcion);
	if (opcion==1)
	{
		printf("\nLa carga del articulo se realizo en forma automatica con nombre aleatorio.\n (modifique si quiere cambiarlo) \n\n\n");
		system("pause");
	}
	return opcion;
}

/*------------------------------------------------------------------------------------------------*/
void alta()
{
	int i;
	FILE *pf;
	articulo varticulo;

	pf = fopen("articulos.dat", "ab");
	if (pf == NULL)
	{ 
		printf("NO SE PUDO ABRIR EL ARCHIVO");
		exit(1);
	}
	else 
	{	srand (time(NULL));
		varticulo.codigo= (rand()%(999-100+1) +100);
		varticulo.stock=  (rand()%(99-10+1) +10);  

		varticulo.ingreso.d= (rand()%(30-1+1) +1);
		varticulo.ingreso.m= (rand()%(12-1+1) +1);
		varticulo.ingreso.a= (rand()%(2012-2008+1) +2008);

		varticulo.descripcion[0]='\0';	 
		for (i=0;i<10;i++)
		{  
			varticulo.descripcion[i+1]='\0';
			varticulo.descripcion[i]=  (char)(rand()%('z'-'a') +'a' );

		}


		fseek(pf, 0L, SEEK_END);
		fwrite(&varticulo, sizeof(articulo), 1, pf);
		fclose(pf);
		system("cls");
	}
}

/*------------------------------------------------------------------------------------------------*/
void lista()
{
	FILE *pf;
	articulo varticulo;
	int cont=0;
	pf = fopen("articulos.dat", "rb");
	if (pf == NULL)
	{ 
		printf("NO SE PUDO ABRIR EL ARCHIVO");
		exit(1);
	}
	else 
	{
		fread(&varticulo, sizeof(articulo), 1, pf);
		printf("\n\n------------------------------------------------------------------------------\n");
		printf("                         LISTA DE ARTICULOS\n");
		printf("------------------------------------------------------------------------------\n\n");
		while(!feof(pf))
		{   
			cont++;
			printf("\n[%d] - DESCRIPCION: %s   STOCK:%d   CODIGO: %d    INGRESO: %d/%d/%d\n ",cont, varticulo.descripcion,varticulo.stock,varticulo.codigo, varticulo.ingreso.d, varticulo.ingreso.m, varticulo.ingreso.a);
			fread(&varticulo, sizeof(articulo), 1, pf);

		}
		fclose(pf);
		printf("\n\n\n\n\n\n");
	}
}
/*------------------------------------------------------------------------------------------------*/

void modificar ()
{
	int cod;

	FILE *pf;
	articulo varticulo;
	pf = fopen("articulos.dat","rb+");
	if (pf == NULL)
	{ 
		printf("NO SE PUDO ABRIR EL ARCHIVO");
		exit(1);
	}

	else
	{
		printf("\nIngrese codigo de articulo a modificar:\n(si ingresa '0' la modificacion se cancela)\n\n ");
		scanf("%d",&cod);
		if(cod == 0)
		{ return(0);}
		fflush(stdin);

		fread(&varticulo, sizeof(articulo), 1, pf);
		while(!feof(pf))
		{ 
			if (varticulo.codigo == cod)
			{
				printf("Modificacion de articulo con codigo: %d\n",cod);
				printf("introdusca nuevo codigo:");
				scanf("%d",&varticulo.codigo);
				printf("introdusca nueva cantidad en stock:");
				scanf("%d",&varticulo.stock);
				printf("introdusca nueva fecha de ingreso:\n");
				printf("dia:");
				scanf("%d",&varticulo.ingreso.d);
				
				while(varticulo.ingreso.d>31||varticulo.ingreso.d<1)
		{
			printf("\nEl ingreso tiene que ser menor a 31");
			printf("\nIngrese dia: ");
			scanf("%d",&varticulo.ingreso.d);
		}
				
				
				printf("mes:");
				scanf("%d",&varticulo.ingreso.m);
				
					
				while(varticulo.ingreso.m>12||varticulo.ingreso.d<1)
		{
			printf("\nEl ingreso tiene que ser menor a 12");
			printf("\nIngrese mes: ");
			scanf("%d",&varticulo.ingreso.m);
		}
				
				
				
				printf("año:");
				scanf("%d",&varticulo.ingreso.a);
				fflush(stdin);
				printf("\nintrodusca nueva descripcion:");
				gets(varticulo.descripcion);

				fseek(pf,((-1)*(int)sizeof(articulo)),SEEK_CUR);
				fwrite(&varticulo, sizeof(articulo),1,pf);
				fseek(pf,0,SEEK_CUR);
			
				fclose(pf);
				return(0);
			
			
			}
			fread(&varticulo, sizeof(articulo),1,pf);
			if (varticulo.codigo != cod)
			{	
				printf("\nARTICULO INEXISTENTE\n\n\n\n");
				fclose(pf);
				return(0);
			}
		}


		fclose(pf);	 
	}

}

/*------------------------------------------------------------------------------------------------*/
void estadistica()
{
	FILE *pf;
	articulo varticulo;

	int stockk;
	int numero=0 ;
	printf("\nAcontinuacion se contaran cuantos articulos hay con stock mayor a: ");
	printf("\nIngrese stock: ");
	scanf("%d",&stockk);
	fflush(stdin);
	printf("\n\nA estos articulos se le aumentara en 10 el codigo de item  \n\n");
	printf("LISTA DE ARTICULOS: \n\n\n");
	pf = fopen("articulos.dat", "rb+");
	if (pf == NULL)
	{ 
		printf("NO SE PUDO ABRIR EL ARCHIVO");
		exit(1);
	}
	else 
	{
		fread(&varticulo, sizeof(articulo), 1, pf);
		while(!feof(pf))
		{	
			if (varticulo.stock > stockk)
			{
				numero++;
				printf("\nel numero del item original es: %d" ,varticulo.codigo);
				varticulo.codigo= (varticulo.codigo + 10);
				printf("\nel numero del item aumentado en 10 es: %d" ,varticulo.codigo);
				fseek(pf,((-1)*(int)sizeof(articulo)),SEEK_CUR);
				fwrite(&varticulo, sizeof(articulo),1,pf);
				fseek(pf,0,SEEK_CUR);
			}
			fread(&varticulo, sizeof(articulo),1,pf);
		}

		printf("\n\nLA CANTIDAD DE ARTICULOS MODIFICADOS CUYO STOCK ES MAYOR A: %d ES: %d\n\n\n\n",stockk,numero);
	}

	fclose(pf);


}
/*------------------------------------------------------------------------------------------------*/
void muestra()
{
	FILE *pf;
	articulo varticulo;
	int stockk;
	printf("\nAcontinuacion se mostraran los articulos cuyo stock  es mayor a: ");
	printf("\nIngrese stock: ");
	scanf("%d",&stockk);
	fflush(stdin);

	pf = fopen("articulos.dat", "rb");
	if (pf == NULL)
	{ 
		printf("NO SE PUDO ABRIR EL ARCHIVO");
		exit(1);
	}
	else 
	{
		fread(&varticulo, sizeof(articulo), 1, pf);
		printf("\n\n--------------------------------------------------------------------------\n");
		printf("                   LISTA DE ARTICULOS CON STOCK MAYOR A: %d\n",stockk);
		printf("--------------------------------------------------------------------------\n\n");
		while(!feof(pf))
		{
			if(varticulo.stock > stockk)
			{

				printf("\n DESCRIPCION: %s   STOCK:%d   CODIGO: %d    INGRESO: %d/%d/%d\n ", varticulo.descripcion,varticulo.stock,varticulo.codigo, varticulo.ingreso.d, varticulo.ingreso.m, varticulo.ingreso.a);
			}
			fread(&varticulo, sizeof(articulo), 1, pf);

		}

	}
	fclose(pf);
	printf("\n\n\n\n\n\n");
}
/*------------------------------------------------------------------------------------------------*/
void muestraposicion()
{
	FILE *pf;
	articulo varticulo;
	int pos;
	int contador=0;

	printf("\nAcontinuacion se mostrara el articulo cuya posicion  es:\n(no ingrese un numero mayor al numero de articulos ingresado) ");
	printf("\nIngrese posicion: ");
	scanf("%d",&pos);
	fflush(stdin);

	pf = fopen("articulos.dat", "rb");
	if (pf == NULL)
	{ 
		printf("NO SE PUDO ABRIR EL ARCHIVO");
		exit(1);
	}
	else 
	{
		fread(&varticulo, sizeof(articulo), 1, pf);
		while(!feof(pf))
			{	
				contador++;
				fread(&varticulo, sizeof(articulo), 1, pf);
			}
		
		while(pos>contador)
		{
			printf("\nLA POSICION TIENE QUE SER MENOR A %d",contador);
			printf("\nIngrese posicion: ");
			scanf("%d",&pos);
		}
		
		
		
		
		fseek(pf,((pos-1)*(int)sizeof(articulo)),SEEK_SET);
		fread(&varticulo, sizeof(articulo), 1, pf);
		printf("\n\n--------------------------------------------------------------------------\n");
		printf("                   LISTA DE ARTICULO DE POSICION: %d\n",pos);
		printf("--------------------------------------------------------------------------\n\n");


		printf("\n DESCRIPCION: %s   STOCK:%d   CODIGO: %d    INGRESO: %d/%d/%d\n ", varticulo.descripcion,varticulo.stock,varticulo.codigo, varticulo.ingreso.d, varticulo.ingreso.m, varticulo.ingreso.a);

	}

	fclose(pf);
	printf("\n\n\n\n\n\n");
}
/*------------------------------------------------------------------------------------------------*/

void baja (void)
{
	FILE *pf, *pfaux;
	articulo varticulo;
	int codigoaux;
	pf = fopen("articulos.dat", "rb");
	pfaux = fopen("articulosaux.dat", "ab");
	printf("\nIngrese Codigo de articulo a dar de baja:");
	scanf("%d",&codigoaux);
	fflush(stdin);

	fread(&varticulo, sizeof(articulo), 1, pf);


	while(!feof(pf))
	{ 
		if (varticulo.codigo != codigoaux)
		{
			fseek(pfaux, 01, SEEK_END);
			fwrite(&varticulo, sizeof(articulo), 1, pfaux);
		}
		fread(&varticulo, sizeof(articulo), 1, pf);
	}
	fclose(pf);
	fclose(pfaux);
	remove("articulos.dat");
	rename("articulosaux.dat","articulos.dat");
	printf("La baja se realizo correctamente\n\n");
	return(0);
}
/*------------------------------------------------------------------------------------------------*/

long int filesize(FILE *pf)      /* Con esta funcion se averigua el tamanio del archivo */ 
{
	long int actual, anterior;   
	actual = ftell(pf);
	fseek(pf, 0, SEEK_END);
	anterior = ftell(pf);
	fseek(pf, actual, SEEK_SET);
	return anterior; /* anterior es el tamaño */ 
}

/*------------------------------------------------------------------------------------------------*/ 

void ordenar(void)
{
	FILE *pf;
	long int i, j, tam;
	articulo reg1, reg2;

	pf = fopen("articulos.dat", "r+b");
	if(pf == NULL)
	{
		printf("Error al abrir el archivo.");
		return 0;
	}

	tam = ((int)(filesize(pf)/sizeof(articulo)));
	for(i=0; i<tam-1; i++)
	{
		for(j=0; j<tam-1-i; j++)
		{
			fseek(pf, j*sizeof(articulo), SEEK_SET);
			fread(&reg1, sizeof(articulo), 1, pf);
			fread(&reg2, sizeof(articulo), 1, pf);

			if(strcmp(reg1.descripcion, reg2.descripcion) > 0)
			{
				fseek(pf, j*(int)sizeof(articulo), SEEK_SET);
				fwrite(&reg2, sizeof(articulo), 1, pf);
				fwrite(&reg1, sizeof(articulo), 1, pf);

			}
		}
	}
	fclose(pf);
	printf("El archivo se ordeno correctamente.\n\n");
}

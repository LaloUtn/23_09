
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#define MAX 2

#define EXISTE -1
#define CARGAR 1
#define MUESTRA 2
#define VENDER 3
#define MOSTRAR_STOCK 4
#define MOSTRAR_GENERO 5
#define SALIR 0
#define BAJO_STOCK 5

typedef struct
{
    int dia;
    int mes;
    int anio;
} fecha_t;
typedef struct
{
    int codigo;
    char titulo[100];
    char autor[50];
    char genero[30];
    fecha_t publicacion; // fecha d publicacion
    int cantidad; // cantidad en stock
    float precio; // precio por unidad
} libro_t;

void mostrar(libro_t[], int);
void cargar(libro_t[], int*);
int verificaCodigo(libro_t[],int,int);
int menu(void);
void mostrar_bajo_stock(libro_t[], libro_t[],int);
//void tecla(void);
void limpiarBuffer(void);
void vender(libro_t[],int*);
void mostrarPorGenero(libro_t[],int);

int main()
{
      libro_t libros[MAX]={0},libro_filtrado[MAX]={0};
     int posicion=0,opcion;
     do
     {
         opcion=menu();
         switch(opcion)
         {
         case CARGAR:
            cargar(libros,&posicion);
            break;
         case MUESTRA:
            mostrar(libros,posicion);
            break;
         case VENDER:
            vender(libros,&posicion);
            break;
         case MOSTRAR_STOCK:
            mostrar_bajo_stock(libros,libro_filtrado,posicion);
            break;
         case MOSTRAR_GENERO:
             mostrarPorGenero(libros,posicion);
             break;
          case SALIR:
            printf("Gracias por utilizar el programa\n");
            break;
         }

     }while(opcion!=0);

}

int menu(void)
{
    int op;
        printf("\n** MENU **\n");
        printf("< 1 >. Cargar libros\n");
        printf("< 2 >. Mostrar libros\n");
        printf("< 3 >. Vender libros\n");
        printf("< 4 >. Mostrar bajos stock\n");
        printf("< 5 >. Mostrar por Genero\n");
        printf("\nIngrese una opcion: ");
        scanf("%d",&op);
        while(op<0||op>5)
        {
         printf("***********************************************\n");
         printf("Debe ingresar una opcion valida entre [0] y [5]\n");
         printf("***********************************************\n");
        // tecla();
         printf("\n** MENU **\n");
         printf("< 1 >. Cargar libros\n");
         printf("< 2 >. Mostrar libros\n");
         printf("< 3 >. Vender libros\n");
         printf("< 4 >. Mostrar balos stock\n");
         printf("< 5 >. Mostrar por Genero\n");
         printf("< 0 >. Salir\n");
         printf("\nIngrese una opcion: ");
         scanf("%d",&op);


        }
        return op;
}

void cargar(libro_t libros[], int*posicion)
{
    int aux_cod,aux_dia,aux_mes,aux_anio,indice,cantidad=0;
      do
      {
            printf("Ingrese el codigo del libro o [0] para salir\n");
            scanf("%d",&aux_cod);
            if(aux_cod!=0)
            {
                if(verificaCodigo(libros,*posicion,aux_cod)==EXISTE && *posicion<MAX)
                {
                    libros[*posicion].codigo=aux_cod;
                    printf("Ingrese el Titulo\n");
                    limpiarBuffer();
                    scanf("%[^\n]",libros[*posicion].titulo);
                    printf("Ingrese el Autor\n");
                    limpiarBuffer();
                    scanf("%[^\n]",libros[*posicion].autor);
                    printf("Ingrese el genero\n");
                    limpiarBuffer();
                    scanf("%[^\n]",libros[*posicion].genero);
                     do
                        {
                            printf("Ingrese la fecha de publicacion\n");
                            printf("Ingrese dia\n");
                            scanf("%d",&aux_dia);
                            printf("Ingrese mes\n");
                            scanf("%d",&aux_mes);
                            printf("Ingrese anio\n");
                            scanf("%d",&aux_anio);

                        }while((aux_dia<1||aux_dia>31) ||(aux_mes>12) );
                         libros[*posicion].publicacion.dia=aux_dia;
                         libros[*posicion].publicacion.mes=aux_mes;
                         libros[*posicion].publicacion.anio=aux_anio;
                         printf("Ingrese cantidad a cargar en el stock\n");
                         scanf("%d",&libros[*posicion].cantidad);
                         printf("Ingrese precio del libro\n");
                         scanf("%f",&libros[*posicion].precio);
                         (*posicion)++;

                  }
                    else
                    {
                        if(verificaCodigo(libros,*posicion,aux_cod)!=EXISTE)
                        {
                            libros[indice].codigo=aux_cod;
                            printf("Ingrese cantidad a cargar en el stock\n");
                            scanf("%d",&cantidad);
                            do
                            {
                                printf("Ingrese dia\n");
                                scanf("%d",&aux_dia);
                                printf("Ingrese mes\n");
                                scanf("%d",&aux_mes);
                                printf("Ingrese anio\n");
                                scanf("%d",&aux_anio);

                           }while((aux_dia<1||aux_dia>31) ||(aux_mes>12) );
                         libros[indice].publicacion.dia=aux_dia;
                         libros[indice].publicacion.mes=aux_mes;
                         libros[indice].publicacion.anio=aux_anio;
                         libros[indice].cantidad+=cantidad;

                       }
                       else
                       {
                           printf("Capacidad completa para ingresar nuevos libros\n");
                           printf("Solo podra completar stock de libros existentes\n");
                       }
                    }
             }

    }while(aux_cod!=0 && *posicion<MAX);


}


int verificaCodigo(libro_t libros[],int posicion,int aux_cod)
{
    int indice=-1;
    for(int i=0;i<posicion;i++)
    {
        if(libros[i].codigo==aux_cod)
        {
            indice=i;
        }
    }
    return indice;
}

void mostrar(libro_t libros[], int posicion)
{
    float precio_total=0;
    for(int i=0 ; i<posicion;i++)
    {

       precio_total= libros[i].cantidad*libros[i].precio;
        printf("Codigo %d - Titulo %s - Autor %s - Genero %s - fecha %d/%d/%d - stock %d - Precio %.2f -Precio total %.2f\n",
        libros[i].codigo, libros[i].titulo, libros[i].autor, libros[i].genero, libros[i].publicacion.dia,
        libros[i].publicacion.mes, libros[i].publicacion.anio, libros[i].cantidad, libros[i].precio,precio_total );
    }
}

void vender(libro_t libros[],int*posicion)
{
    int cantidad,aux,indice;
    float monto;
     printf("Ingrese codigo del libro\n");
     scanf("%d",&aux);
     indice=verificaCodigo(libros,*posicion,aux);
     printf("indice %d\n",indice);
     if(indice!=EXISTE)

     {
        libros[indice].codigo=aux;
        printf("Ingrese cantidad a vender \n");
        scanf("%d",&cantidad);
        if(libros[indice].cantidad>=cantidad)
        {
            libros[indice].cantidad-=cantidad;
            monto=cantidad*libros[indice].precio;
            printf("Monto a pagar %.2f\n",monto);

        }
        else
            {
                printf("No hay suficiente stock\n");
            }
     }
     else
     {
         printf("El codigo no es valido\n");
     }
 }


 void mostrar_bajo_stock(libro_t libros[], libro_t libro_filtrado[],int posicion)
 {
     int j=0;
     for(int i=0;i<posicion;i++)
     {
         if(libros[i].cantidad<BAJO_STOCK)
         {
             libro_filtrado[j]=libros[i];
             j++;

         }
      }
       mostrar(libro_filtrado,j);


 }

 void mostrarPorGenero(libro_t libros[],int posicion)
 {
     libro_t aux;
     for(int i=0;i <posicion-1;i++)
     {
         for(int j=0;j<posicion-i-1;j++)
         {
           if(strcasecmp(libros[j].genero,libros[j+1].genero)>0)
           {
             aux=libros[j];
             libros[j]=libros[j+1];
             libros[j+1]=aux;
            }
         }

     }
      mostrar(libros,posicion);

 }



void tecla(void)
{
    printf("\n\n...PRESIONE CUALQUIER TECLA PARA CONTINUAR...\n");
    getch();
    system("cls");
}
void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {

    }

}


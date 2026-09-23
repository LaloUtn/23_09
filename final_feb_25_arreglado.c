#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para funciones de manejo de cadenas
#define p printf
#define s scanf
#define topeMax 100 // Esto es lo máximo que podrá cargar de productos el vector o inventario

typedef struct
{
    int codigo;         // Código único del producto
    char nombre[50];    // Nombre del producto
    char categoria[20]; // Categoría del producto
    float precio;       // Precio unitario
    int stock;          // Cantidad en stock
} Producto;

void pausa(void);
void AltaDeProducto(Producto[topeMax], int *);
void ActualizaProducto(Producto[topeMax], int);
void GeneroReporte(Producto[topeMax], int);
int menu(void);
int VerificaCodigoDeProducto(int, Producto[topeMax], int);
void limpiarBuffer(void);

int main()
{
    Producto inventario[topeMax]; // Vector para almacenar hasta 100 productos
    int totalProductos = 0, op;   // Contador de productos reales en el inventario
    do
    {
        op = menu();
        switch (op)
        {
        case 1:
            AltaDeProducto(inventario, &totalProductos);
            break;
        case 2:
            ActualizaProducto(inventario, totalProductos);
            break;
        case 3:
            GeneroReporte(inventario, totalProductos);
            break;
        case 4:
            return 0; // Salir del programa
        default:
            p("Ingreso una opcion equivocada\n");
            break;
        }
    } while (op < 5);

    return 0;
}

void pausa(void)
{
    printf("\nPresione Enter para continuar...\n");
    while (getchar() != '\n') // Limpiar el buffer de entrada
        ;
    getchar(); // Captura el 'Enter'
}

int menu(void)
{
    int op;
    do
    {
        p("MEN%c DE OPCIONES\n", 233);
        printf("\n****************** MENU *******************\n");
        printf("< 1 >. Agregar un nuevo producto\n");
        printf("< 2 >. Actualizar el stock de un producto\n");
        printf("< 3 >. Generar reporte de inventario\n");
        printf("< 4 >. Salir\n");
        printf("*******************************************\n");
        s("%d", &op);
    } while (op < 1 || op > 4);
    return op;
}

void AltaDeProducto(Producto in[topeMax], int *totalProductos)
{

int opcionCategoria,aux_cod,indice,aux_cantidad;
float aux_precio;

    // Mostrar las categorías precargadas
    //ESTE PARTE DEL CODIGO SE LAS DEJO PARA QUE PUEDAN CARGAR LA CATEGORIA
    // LA IDEA LA PODRAN TAMBIEN POSIBLEMENTE USAR EN OTRA PARTE DEL CODIGO
    printf("Ingrese el codigo del producto\n");
    scanf("%d",&aux_cod);
    indice=VerificaCodigoDeProducto(aux_cod,in,*totalProductos);
    if(indice==-1)
    {
        in[*totalProductos].codigo=aux_cod;
        do
         {
            printf("Seleccione la categoría del producto:\n");
            printf("1. Smartphones\n");
            printf("2. Laptops\n");
            printf("3. Accesorios\n");
            s("%d", &opcionCategoria);
        } while (opcionCategoria < 1 || opcionCategoria > 3);

         // Asignar la categoría según la opción elegida
        switch (opcionCategoria)
         {
           case 1:
              strcpy(in[*totalProductos].categoria, "Smartphones");
              break;
           case 2:
              strcpy(in[*totalProductos].categoria, "Laptops");
              break;
           case 3:
              strcpy(in[*totalProductos].categoria, "Accesorios");
              break;
          }
        // LES DEJO UNA MANERA DE CAPTURAR UN DATO MAS COMODA
         p("Ingrese Nombre del Producto: ");
         limpiarBuffer();
             scanf(" %[^\n]",in[*totalProductos].nombre);
        /*getchar(); // Limpiar el buffer
        fgets(in[*totalProductos].nombre, sizeof(in[*totalProductos].nombre), stdin);
        in[*totalProductos].nombre[strcspn(in[*totalProductos].nombre, "\n")] = '\0'; // Eliminar salto de línea
        //desde aca lo continuo yo para ver si el producto existe o no*/
        do
         {
            printf("Ingrese el precio del producto\n");
            scanf("%f",&aux_precio);
         }while(aux_precio<=0);
        in[*totalProductos].precio=aux_precio;
        do
         {
            printf("Ingrese la cantidad del producto\n");
            scanf("%d",&aux_cantidad);
         }while(aux_cantidad<=0);
        in[*totalProductos].stock=aux_cantidad;
        (*totalProductos)++;
    }
    else
        {
            printf("Producto ya existente en inventario\n");
        }



    pausa();
}

void ActualizaProducto(Producto in[topeMax], int totalProductos)
{
// AQUI TENDRAN QUE ACTUALIZAR ALGUNPRODUCTO QEWU SE ELIJA
// SI EXISTE
// SI NO TENDRAN QUE AVISARLO
// RECORDAR QUE SE PUEDE DISMINUIR O AUMENTAR
//esto lo hice yo
int cod,indice,cant,op;
 printf("Ingrese el codigo del producto\n");
 scanf("%d",&cod);
 indice=VerificaCodigoDeProducto(cod,in,totalProductos);
 if(indice>=0)
    {
        do
        {
           printf("Ingrese [1] para agregar stock o [2] para restar stock\n");
           scanf("%d",&op);
        }while(op<1||op>2);
        switch(op)
          {
            case 1:
                  do
                  {
                    printf("Ingrese la cantidad del producto\n");
                    scanf("%d",&cant);
                    printf("cant %d\n",cant);
                  }while(cant<=0);
                  printf("Cantidad antes de stock %d\n",in[indice].stock);
                  in[indice].stock+=cant;
                  printf("cantidad %d\n",cant);
                  printf("Cantidad despues de stock %d\n",in[indice].stock);
                  break;
              case 2:
                   do
                   {
                     printf("Ingrese la cantidad del producto\n");
                     scanf("%d",&cant);
                   }while(cant<=0);
                   if(in[indice].stock>=cant)
                   {
                      in[indice].stock-=cant;
                   }
                   else
                    {
                       printf("No hay stock suficiente\n");

                    }
                  break;
         }
   }
    else
        {
            printf("Producto no existente en inventario\n");
        }
    pausa();
    return;


}


void GeneroReporte(Producto inventario[topeMax], int totalProductos)
{
    float acu=0;
    for (int i = 0; i < totalProductos; i++)
    {
      acu+=(inventario[i].precio)*(inventario[i].stock);
    }
     printf("   \n          Reporte de inventario por categoria\n");
    printf("         *************************************\n");
          printf("  \n                 Smartphones\n");
    for (int i = 0; i < totalProductos; i++)
    {
       if (strcmp(inventario[i].categoria, "Smartphones") == 0)
        {
            printf("************************************************************\n");
            printf("Codigo: %d   Nombre: %s   Precio: %.2f   Stock: %d\n",
            inventario[i].codigo, inventario[i].nombre,
            inventario[i].precio, inventario[i].stock);
            printf("*************************************************************\n");

        }
    }
           printf("  \n                Accesorios\n");
    for (int i = 0; i < totalProductos; i++)

     {

      if (strcmp(inventario[i].categoria, "Accesorios") == 0)
        {
            printf("*************************************************************\n");

            printf("Codigo: %d   Nombre: %s   Precio: %.2f   Stock: %d\n",
            inventario[i].codigo, inventario[i].nombre,
            inventario[i].precio, inventario[i].stock);
            printf("************************************************************\n");

        }
     }

            printf(" \n                  Laptops\n");
    for (int i = 0; i < totalProductos; i++)

     {
      if (strcmp(inventario[i].categoria, "Laptops") == 0)
        {
            printf("**************************************************************\n");
            printf("Codigo: %d   Nombre: %s   Precio: %.2f   Stock: %d\n",
            inventario[i].codigo, inventario[i].nombre,
            inventario[i].precio, inventario[i].stock);
            printf("**************************************************************\n");
         }
     }
      printf("\n**************************************************************\n");
      printf("\nEl valor total de todo el inventario es de $ %f\n",acu);
      printf("**************************************************************\n");
    pausa();
}


int VerificaCodigoDeProducto(int codigo, Producto inventario[topeMax], int totalProductos)
{
    // AQUI TENDRAN QUE REALIZAR LA VERIFICACION DE LA EXISTENCIA DEL PRODUCTO
   //esto lo hice yo
   int indice=-1;
    for(int i=0;i<totalProductos;i++)
    {
        if(inventario[i].codigo==codigo)
        {
            indice=i;
            //return indice;
        }
    }
    return indice;
}

void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)

    {

    }

}

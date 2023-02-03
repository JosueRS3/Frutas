#include "tdafrutas.h"

void InicioOperacion(int argc, char** argv){
    int opcion= 0, pos =0, tamarreglo=0, cont =0, tam =0, opcioncompra=0, numero=0;
    Fruta *ArregloF;
    ArregloF = (Fruta*)calloc(1, sizeof(Fruta));


    do
    {
        FILE* Productos =fopen("productos.txt","r");
         if (Productos == NULL)
            {
                perror(ROJO_T"\n No existe el archivo \n"RESET_COLOR);
                Productos = fopen("productos.txt","a");
                if (Productos != NULL){
                    printf(VERDE_T"Se creo el archivo correctamente \n"RESET_COLOR);
                }
                else{
                    printf(ROJO_T"No se pudo crear el archivo\n"RESET_COLOR);
                }  
            }
            else{
                printf(AMARILLO_T"\n Existe un archivo con  productos anteriormente registrados\n"RESET_COLOR);
                char ca;
                int cont =0;
                while((ca = fgetc(Productos)) != EOF){
                    if( ca == '\n')
                    cont++;
                }
                printf("Existen en inventario %i frutas \n", cont);
                fclose(Productos);
                if (cont==0)
                {
                    if(remove("productos.txt")==0){ // Eliminamos el archivo

                        Productos = fopen("productos.txt","a");
                        if (Productos != NULL){
                            printf(VERDE_T"Se creo el archivo correctamente \n"RESET_COLOR);
                        }
                        else{
                            printf(ROJO_T"No se pudo crear el archivo\n"RESET_COLOR);
                        }  
                    }
                }
                else{
                    tam = cont;
                    ArregloF= Llenarlista(ArregloF,cont);
                    printf("Se ha llenado el arreglo con los productos existentes \n");
                }
        }
    
    fflush(Productos);
    fclose(Productos);
   
        
    printf(CYAN_T"\nMenu para agregaregar nuevas frutas o comprar \n"RESET_COLOR);
    printf(" Seleccions una de las sigueites opciones \n");
    printf(" 0. Salir del programa \n");
    printf(" 1. Agregar una fruta \n");
    printf(" 2. Visualizar frutas disponibles  \n");
    printf(" 3. Comprar una fruta \n");
    printf(" 4. Eliminar una fruta \n");
    printf(" 5. Actualizar datos de producto. \n");
    printf(" 6. Buscar una fruta \n");

    scanf("%i",&opcion);

        switch (opcion)
        {
        case 1:

            ArregloF = RegistrarFruta(cont+1, ArregloF);
            fflush(stdin);

            break;
        case 2:
            ArregloF= OrdenarPrecio(ArregloF, tam);
            Imprimir(ArregloF, tam);
            
            break;
        case 3:
            ArregloF=ComprarFruta(ArregloF,tam);
            if(remove("productos.txt")==0) // Eliminamos el archivo
                printf("Se esta actualizando el archivo...\n");
            Actualizartxt(ArregloF,tam);    
            
            break;
        case 4:
            EliminarFruta(ArregloF, tam);

            break;
        case 5:
            numero =0;
            printf("Cuentas con los siguientes productos : \n");
            for (int i = 0; i < tam; i++)
            {
                printf("%i. %s\n",i+1, ArregloF[i].nombre);
            }

            printf(" Intoduce el numero de la fruta que deseas actalizar: ");
            fflush(stdin);
            scanf("%i", &numero);
            if (numero-1>=0 && numero-1<= tam)
            {
                ArregloF=ActualizaTDA(ArregloF, numero-1);
            }
            else
                printf(ROJO_T"No exite el producto con el numero %i"RESET_COLOR, numero);
            
            
            if(remove("productos.txt")==0) // Eliminamos el archivo
                printf("Se esta actualizando el archivo...\n");
            Actualizartxt(ArregloF,tam);   

            break;
        case 6:
            BuscarFruta(ArregloF,tam);
        break;
        default:
            printf("Terminado programa....");
            exit(1);
            break;
        }
    } while (opcion!=0);
    
}


Fruta* RegistrarFruta(int pos, Fruta *lista){
    FILE* flujo = fopen("productos.txt","a");

    printf("Nombre de la fruta: ");
    fflush(stdin);
    scanf("%s",lista[pos].nombre);

    printf("Color de la fruta: ");
    fflush(stdin);
    gets(lista[pos].color);

    printf("Cantidad de la fruta en inventario: ");
    fflush(stdin);
    scanf("%i",&lista[pos].cantidadinv);

    printf("Precio de la fruta por unidad: ");
    fflush(stdin);
    scanf("%f",&lista[pos].precio);

    printf("Se registro la fruta correctamente \n");

    fprintf(flujo, "%s %s %i %f \n",lista[pos].nombre, lista[pos].color, lista[pos].cantidadinv, lista[pos].precio);

    fflush(flujo);
    fclose(flujo);

    return lista;
}

Fruta* Llenarlista(Fruta lista[], int cantidad){
    
    lista = (Fruta*)realloc(lista,cantidad*sizeof(Fruta));
    
    FILE* flujo2 = fopen("productos.txt","rb");
    if (flujo2==NULL)
    {
        perror(ROJO_T"Error a la hora de abrir el archivo\n"RESET_COLOR);
    }
    else{
        printf(VERDE_T"Se logro abrir el archivo\n"RESET_COLOR);
        int i =0;
        while (feof(flujo2)==0)
        {
            fscanf(flujo2,"%s%s%i%f",&lista[i].nombre, &lista[i].color, &lista[i].cantidadinv, &lista[i].precio);
            i++;
        }
    }
    
    fclose(flujo2); 
    return lista;   
}

Fruta* ComprarFruta(Fruta lista[], int cantidad){
    int cantfrutas;
    float cuenta , total=0;

    
    for (int i = 0; i < cantidad; i++)
    {
        cantfrutas=0;
        cuenta =0;
        printf("¿Cuantas %ss deseas comprar ",lista[i].nombre);
        fflush(stdin);
        scanf("%i",&cantfrutas);

        while (lista[i].cantidadinv-cantfrutas<0)
        {
            printf(ROJO_T"Solo se puede comprar un maximo de %i %ss \n"RESET_COLOR,lista[i].cantidadinv, lista[i].nombre);
            printf("Vuelva a ingresar el numero de %ss ",lista[i].nombre);
            fflush(stdin);
            scanf("%i",&cantfrutas);
        }
        
        cuenta = cantfrutas*lista[i].precio;
        lista[i].cantidadinv = lista[i].cantidadinv-cantfrutas;
        total = total + cuenta;
       
    }
    
    printf(AMARILLO_T"\n Total a pagar: %f"RESET_COLOR,total);
    
    return lista;
}

void Actualizartxt(Fruta lista[], int can){
    FILE* flujo = fopen("productos.txt","a");
    for (int pos = 0; pos < can; pos++)
    {
        fprintf(flujo, "%s %s %i %f \n",lista[pos].nombre, lista[pos].color, lista[pos].cantidadinv, lista[pos].precio);
    }
    
    printf(VERDE_T"\n Se ha actualizado la lista de productos correctamente \n"RESET_COLOR );

    fflush(flujo);
    fclose(flujo);

}

Fruta* ActualizaTDA(Fruta lista[], int pos){

    int op=0, cantidad=0, opcion =0;
    fflush(stdin);

    printf ("Estas seguro  de que deseas realizar cambios en %s \n", lista[pos].nombre);
        printf ("1. Si\n");
        printf("0. No\n");
        fflush (stdin);
        scanf("%i", &opcion);
        if ( opcion == 1)
        {
            do
            {
                printf("1. Modificar nombre \n");
                printf("2. Modificar color \n");
                printf("3. Modificar precio \n");
                printf("4. Modificar cantidad \n");
                printf("0. Dejar de modificar\n");

                fflush(stdin);
                scanf("%i",&op);

                switch (op)
                {
                case 1:
                    printf("Ingresa el nuevo nombre de %s :", lista[pos].nombre);
                    fflush(stdin);
                    gets(lista[pos].nombre);
                    printf("Se ha actualizado el nombre con exito \n");
                
                    break;
                case 2:
                    printf("Ingresa el nuevo color de %s :", lista[pos].nombre);
                    fflush(stdin);
                    gets(lista[pos].color);
                    printf("Se ha actualizado el color con exito \n");

                    break;
                case 3:
                    printf("Ingresa el nuevo precio de %s :", lista[pos].nombre);
                    fflush(stdin);
                    scanf("%f", &lista[pos].precio);
                    printf("Se ha actualizado el precio con exito \n");

                    break;
                case 4:
                    
                    printf("Ingresa el la nueva cantidad en inventario de %s :", lista[pos].nombre);
                    fflush(stdin);
                    scanf("%i", &cantidad);
                    if (cantidad >= 0)
                    {
                        lista[pos].cantidadinv= cantidad;
                        printf("Se ha actualizado la cantidad con exito \n");
                    }
                    else
                        printf(ROJO_T"No se puede ingresar un numero menor a 0, por favor verifica los valores\n"RESET_COLOR);
                    
                    break;
                
                default:
                    op=0;
                    break;
                }

            } while (op !=0 );
            
    
        }
        else
        return lista;

    return lista;
}

Fruta* OrdenarPrecio(Fruta lista[], int pos){

    int opcion;
    Fruta auxiliar;

    printf("Como deseas ordenar los productos\n");
    printf("1. por cantidad\n");
    printf("2. por precio\n");

    fflush(stdin);
    scanf("%i", &opcion);

    if (opcion == 1)
    {
        for(int i = 1; i <= pos - 1; i++){
            for(int j = i; j > 0 && lista[j - 1].cantidadinv > lista[j].cantidadinv; j--){
                auxiliar = lista[j];
                lista[j]= lista[j - 1];
                lista[j - 1]= auxiliar;
            }
        }
        return lista;
    }
    else if (opcion == 2)
    {
        for(int i = 1; i <= pos - 1; i++){
            for(int j = i; j > 0 && lista[j - 1].precio > lista[j].precio; j--){
                auxiliar = lista[j];
                lista[j] = lista[j - 1];
                lista[j - 1] = auxiliar;
            }
        }
        return lista;
    }
    else{
        printf("Los productos no tienen ningun orden es especial \n");
    
        return lista;
    }
    
}

void EliminarFruta(Fruta *lista, int cantidad){

    int resp=0; 

        printf ("Antes de iniciar este proceso, deseas crear una copia de seguridad? 0-No 1-Si :");
        fflush(stdin);
        scanf("%i", &resp);

        if (resp !=0)
        {
            Crearcopia(lista, cantidad);
        }
        
    
        printf(AMARILLO_T" Cuentas con las siguientes frutas\n"RESET_COLOR);

        for (int  i = 0; i < cantidad; i++)
        {
            printf("%i. %s\n", i+1, lista[i].nombre);
        }

        printf("Ingresa el numero de la fruta que deseas eliminar");
        fflush(stdin);
        scanf("%i", &resp);
        resp = resp-1;


    do
    {
        if (resp > cantidad || resp < 0)
        {
            printf(" Ingresa un numero de fruta valido \n");
            fflush(stdin);
            scanf("%i", &resp);
            resp = resp-1;

        }
        
    } while (resp > cantidad || resp < 0);
    
        
        if(remove("productos.txt")==0) // Eliminamos el archivo
                printf("Se esta actualizando el archivo...\n");
        FILE* flujo = fopen("productos.txt","a");
        if (flujo == NULL)
        {
            perror("No se pudo eliminar le producto");
        }
        else{
            
            for (int i = 0; i < cantidad; i++)
            {
                if (i != resp)
                {
                    fprintf(flujo, "%s %s %i %f \n",lista[i].nombre, lista[i].color, lista[i].cantidadinv, lista[i].precio);
                }
            
            }
            fclose(flujo);
            printf(VERDE_T"Se ha actualiza la lista de articulos con exito\n"RESET_COLOR);
        }     
}

void Crearcopia(Fruta lista[], int can){
    char nombre[20];
    printf("Dame el nombre con el que deseas guardar la copia :");
    fflush(stdin);
    gets(nombre);

    FILE* flujo = fopen(nombre,"w");

    for (int pos = 0; pos < can; pos++)
    {
        fprintf(flujo, "%s %s %i %f \n",lista[pos].nombre, lista[pos].color, lista[pos].cantidadinv, lista[pos].precio);
    }
    
    printf(VERDE_T"\n Se ha creado la copia de seguridad con exito \n"RESET_COLOR );

    fflush(flujo);
    fclose(flujo);

}
    
void BuscarFruta( Fruta *lista, int tam){

    int arregloIndices[255]={0}; 
    char Frutaabuscar[50];
    int limiteInfBusq;
    int limiteSupBusq;
    bool flag=false;
    int j=0;

    printf("Ordenando los productos...\n");
    OrdenarNombre(lista, tam);
    FILE* flujo= fopen("productos.txt","w");
    Actualizartxt(lista,tam);  
    fclose(flujo); 
    GenerarIndices(arregloIndices);
    printf("Dame un titulo a buscar:");
    fflush(stdin);
    scanf("%s",Frutaabuscar);

    //reducir la busqueda
    limiteInfBusq=arregloIndices[(int)Frutaabuscar[0]];
    if(limiteInfBusq>0){
        for(j=(int)(Frutaabuscar[0]+1);j<255;j++){
            if(arregloIndices[j]>0){
                flag=true;
                break;
            }
        }
        if(flag==true)
            limiteSupBusq=arregloIndices[j];
        else{
            //El limite superior estaria dado por el ultimo título
            limiteSupBusq=tam+1;
        }

        printf("buscando...");
        for(int fru=limiteInfBusq-1;fru<(limiteSupBusq-1);fru++){
            if(strcmp(Frutaabuscar,lista[fru].nombre)==0){
                printf("\nSe encontro la fruta en la pos %d",fru+1);
            } else{
                printf("...");
            }
        }
    }
    else{
        puts("No se encontro la fruta, indice en 0");
    }
}

void GenerarIndices(int *arregloindices){
    Generartxtindices();
    char caracter;
    int valor;
    FILE *indices=fopen("indices.txt","r");
    if (indices==NULL)
    {
        perror("no se pudo abrir el archivo");
        exit(1);
    }
    
    printf("transfiriendo indices...\n");
    while(!feof(indices)){
        fscanf(indices,"%c,%d",&caracter,&valor);
        arregloindices[(int)caracter]=valor;
    }
    
}

void OrdenarNombre(Fruta* lista, int cantidad){
       Fruta aux ;

    for (int i = 0; i < cantidad-1; i++)
    {
        for (int j = i+1; j < cantidad; j++)
        {
            if ((int)ConvertirLetra(lista[j].nombre[0])<(int)ConvertirLetra(lista[i].nombre[0]))
            {
                aux = lista[i];
                lista[i]= lista[j];
                lista[j]= aux;
            }
            else if ((int)ConvertirLetra(lista[j].nombre[0])==(int)ConvertirLetra(lista[i].nombre[0]))
            {
                int letra = 0;
                while ((int)ConvertirLetra(lista[j].nombre[letra])==(int)ConvertirLetra(lista[i].nombre[letra]))
                {
                    letra++;
                }

                if ((int)ConvertirLetra(lista[j].nombre[letra])<(int)ConvertirLetra(lista[i].nombre[letra]))
                {
                    aux = lista[i];
                    lista[i]= lista[j];
                    lista[j]= aux;
                }


            }
            
        }
    }
    Imprimir(lista, cantidad);
}

char ConvertirLetra(char minuscula){
    
    char letra;
        
    letra = toupper(minuscula);
        
    return letra;
}

void Imprimir(Fruta* lista, int tam){
    printf(AMARILLO_T"\n               Inventario: \n "RESET_COLOR);
            
        for (int i = 0; i < tam; i++)
        {
            printf("Nombre: %s Color: %s Cantidad: %i Precio: %f \n",lista[i].nombre,lista[i].color,lista[i].cantidadinv, lista[i].precio);
        }

}

void Generartxtindices(){
    FILE *indices = fopen("indices.txt","w");
    FILE *productos = fopen("productos.txt","r");

    if (indices == NULL || productos==NULL)
    {
        perror(ROJO_T"No se han podido abrir los archivos\n"RESET_COLOR);
        exit(1);
    }

    char letra;
    char basura[100];
    int cont=0;
    int vuelta =-1;
    char aux;

   while (!feof(productos))
   {
    if (vuelta==-1)
    {
       cont =1;
       letra=fgetc(productos);
       fprintf(indices,"%c,%d\n",letra,cont);
       fgets(basura,100,productos);
       vuelta=1;
    }
    else{
        aux=fgetc(productos);
        if ((int)aux==(int)letra)
        {
            cont++;
            fgets(basura,100,productos);
        }
        else{
            letra=aux;
            cont++;
            if (((int)letra>64 && (int)letra<91)||((int)letra>96 && (int)letra<123))
            {
                fprintf(indices,"%c,%d\n",letra,cont);
            }
            fgets(basura,100,productos);
        }
        
    }
    }
    fclose(productos); 
    fclose(indices);  
    strcpy(basura,"");
}
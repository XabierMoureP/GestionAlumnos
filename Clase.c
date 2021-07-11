#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Clase.h"

void inicializar(clase *claseLocal)
{
    int i=0, j=0, numeroAlumnosFichero=0;
    char cadena[100];
    char aux='0';    //Lo usaremos para ir guardando los caracteres de los nombres de los alumnos
    char aux2='0';    //Lo usaremos para guardar en algun lugar los saltos de linea que no nos interesa mantener
    FILE *miFichero;
    miFichero=fopen("DatosIniciales.txt", "r");     //Abrimos el fichero en formato de lectura
    while(!feof(miFichero))     //Con este bucle contamos el número de alumnos que tendremos
    {
        fgets(cadena, 100, miFichero);
        numeroAlumnosFichero++;
    }
    claseLocal->totalAlumnos=(numeroAlumnosFichero/11);     //Asignamos memoria dinámica
    claseLocal->conjuntoAlumnos=malloc(sizeof(datosAlumnos)*claseLocal->totalAlumnos);
    rewind(miFichero);     //Nos colocamos al inicio del fichero para poder leer los nombres
    vaciarCadena(&cadena);    //Vaciamos "cadena" para poder utilizarla para guardar los nombres temporalmente
    for(i=0;!feof(miFichero);i++)
    {
        aux='\0';
        for(j=0;aux!='\n';j++)
        {
            aux=fgetc(miFichero);    //Guardamos en "aux" el carácter en cuestión
            if(aux!='\n') cadena[j]=aux;
            else cadena[j]='\0';
        }
        claseLocal->conjuntoAlumnos[i].nombreAlumno=malloc(sizeof(char)*strlen(cadena));   //Asignamos memoria dinámica al nombre
        strcpy(claseLocal->conjuntoAlumnos[i].nombreAlumno, cadena);
        vaciarCadena(&cadena);
        for(j=0;j<10;j++)
        {
            fscanf(miFichero, "%d", &claseLocal->conjuntoAlumnos[i].notas[j]);   //Guardamos las notas de una en una
        }
        aux2=fgetc(miFichero);   //Guardamos en "aux2" el salto de línea después de la última nota, ya que no lo queremos
    }
    fclose(miFichero);    //Cerramos el fichero
}

void vaciarCadena (char *cadenaLocal)
{
    int i=0;
    for(i=0;i<100;i++)
    {
        cadenaLocal[i]='\0';   //"Vaciamos" la cadena carácter a carácter
    }
}

void mostrarAlumno(datosAlumnos datoAlumnoLocal)
{
    int i=0;
    printf("\n\t%s\n\tNotas: ", datoAlumnoLocal.nombreAlumno);
    for(i=0;i<10;i++)
    {
        printf("%d   ", datoAlumnoLocal.notas[i]);
    }
    printf("\n");
}

void mostrarClase (clase alumnoLocal)
{
    int i=0;
    for(i=0;i<alumnoLocal.totalAlumnos;i++)
    {
        mostrarAlumno(alumnoLocal.conjuntoAlumnos[i]);   //Llamamos a la función que muestra un alumno para que los muestre todos
    }
}

void eliminarAlumnos (clase *alumnoLocal, char *eliminarAlumnoLocal)
{
    datosAlumnos *vectorEliminarAlumno;    //Aquí guardaremos la información de todos los alumnos excepto del que queremos eliminar
    int i=0, j=0;
    vectorEliminarAlumno=malloc(sizeof(datosAlumnos)*(alumnoLocal->totalAlumnos-1));  //Asignamos memoria dinámica de acuerdo a la nueva situación
    for(i=0;i<alumnoLocal->totalAlumnos;i++)
    {
        if(strcmp(eliminarAlumnoLocal, alumnoLocal->conjuntoAlumnos[i].nombreAlumno)!=0)   //Comprobamos si es el alumno que queremos eliminar
        {
            vectorEliminarAlumno[j]=alumnoLocal->conjuntoAlumnos[i];
            j++;
        }
        else  //En caso de tratarse del alumno que queremos eliminar, liberamos la memoria asignada para su nombre
        {
            if(alumnoLocal->conjuntoAlumnos[i].nombreAlumno!=NULL) free(alumnoLocal->conjuntoAlumnos[i].nombreAlumno);  //Nos protegemos ante un posible error
        }
    }
    if(alumnoLocal->conjuntoAlumnos!=NULL) free(alumnoLocal->conjuntoAlumnos);  //Liberamos la memoria asignada a la totalidad de los alumnos
    alumnoLocal->conjuntoAlumnos=vectorEliminarAlumno;   //Hacemos que conjuntoAlumnos apunte al vector donde tenemos guardada toda la información
    alumnoLocal->totalAlumnos--;    //Reducimos en uno el número de alumnos que tenemos
}

void anadirAlumno(clase *alumnoLocal)
{
    int i=0, j=0, comprobar=0, longitud=0;
    char guardarAlumno[50];
    j=alumnoLocal->totalAlumnos;  //Damos este valor a j para simplificar la escritura del código más adelante
    alumnoLocal->totalAlumnos++;
    alumnoLocal->conjuntoAlumnos=realloc(alumnoLocal->conjuntoAlumnos, sizeof(datosAlumnos)*(alumnoLocal->totalAlumnos));  //Asignamos memoria dinámica de acuerdo a la nueva situación
    printf("\n\tIntroduce el nombre del nuevo alumno: ");
    gets(guardarAlumno);
    alumnoLocal->conjuntoAlumnos[j].nombreAlumno=malloc(sizeof(char)*(strlen(guardarAlumno)+1));  //Asignamos memoria dinámica al nombre
    strcpy(alumnoLocal->conjuntoAlumnos[j].nombreAlumno, guardarAlumno);
    do   //El bucle se repite mientras alguna de las notas introducidas no sea válida
    {
        for(i=0;i<10;i++)
        {
            printf("\n\tIntroduzca la nota: ");
            scanf("%d", &alumnoLocal->conjuntoAlumnos[j].notas[i]);
            if(alumnoLocal->conjuntoAlumnos[j].notas[i]>10 || alumnoLocal->conjuntoAlumnos[j].notas[i]<0)  //Comprobamos la nota
            {
                printf("\n\tEsa nota no es valida. Recuerde que debe estar entre 0 y 10.");
                comprobar=0;
                i--;  //Como no es válida, la siguiente nota que introduzca el usuario debe ir en la misma posición
            }
            else comprobar=1;
        }
    }while(!comprobar);
    printf("\n\tSe ha anadido correctamente el alumno %s", alumnoLocal->conjuntoAlumnos[j].nombreAlumno);
}

float calcularNotaMedia (datosAlumnos alumnoLocal)
{
    int i=0;
    float suma=0.0, media=0.0;
    for(i=0;i<10;i++)
    {
        suma=suma+alumnoLocal.notas[i];   //Guardamos en suma la suma de todas las notas
    }
    media=suma/10;   //Dividimos entre 10 para poder calcular la nota media
    return (media);    //Queremos que devuelva el valor de la nota media para comprobarla en futuras funciones
}

void listarNotaMedia (clase alumnoLocal, float mediaLocal)
{
    int i=0;
    for(i=0;i<alumnoLocal.totalAlumnos;i++)
    {
        if(calcularNotaMedia(alumnoLocal.conjuntoAlumnos[i])>=mediaLocal)  //Comprobamos si el alumno supera la nota media deseada
        {
            printf("\n\tMedia a superar: %.2f  ----------  Media alumno: %.2f", mediaLocal, calcularNotaMedia(alumnoLocal.conjuntoAlumnos[i]));
            mostrarAlumno(alumnoLocal.conjuntoAlumnos[i]);
        }
    }
}

void eliminarAprobados (clase *alumnoLocal)
{
    int i=0, j=0, k=0, numeroAlumnos=0, nota=0;
    datosAlumnos *vectorEliminarAprobados;   //Aquí guardaremos la información de los alumnos con todas las asignaturas aprobadas
    for(i=0;i<alumnoLocal->totalAlumnos;i++)   //Primero debemos saber cuántos alumnos tendrá nuestra estructura
    {
        for(j=0;j<10;j++)
        {
            if(alumnoLocal->conjuntoAlumnos[i].notas[j]<5)
            {
                nota=1;
            }
        }
        if(nota==1)  //En caso de que al menos una de las notas sea menor que 5, es un alumno que queremos conservar
        {
            numeroAlumnos++;
        }
        nota=0;   //Igualamos nota a 0 para poder volver a hacer la comprobación de las notas con el siguiente alumno
    }
    vectorEliminarAprobados=malloc(sizeof(datosAlumnos)*(numeroAlumnos));   //Asignamos memoria dinámica según la nueva situación
    for(i=0;i<alumnoLocal->totalAlumnos;i++)   //Volvemos a realizar el bucle para poder liberar la memoria asignada a los nombres
    {
        for(j=0;j<10;j++)
        {
            if(alumnoLocal->conjuntoAlumnos[i].notas[j]<5)
            {
                nota=1;
            }
        }
        if(nota==1)  //Si alguna de las notas del alumno es menor que 5, lo copiamos en nuestro vector auxiliar
        {
            vectorEliminarAprobados[k]=alumnoLocal->conjuntoAlumnos[i];
            k++;
        }
        else   //Si ninguna de las notas es menor que 5, liberamos la memoria asignada para su nombre
        {
            if(alumnoLocal->conjuntoAlumnos[i].nombreAlumno!=NULL) free(alumnoLocal->conjuntoAlumnos[i].nombreAlumno);
        }
        nota=0;   //Igualamos nota a 0 para poder volver a hacer la comprobación
    }
    if(alumnoLocal->conjuntoAlumnos!=NULL) free(alumnoLocal->conjuntoAlumnos);  //Liberamos la memoria asignada a nuestra estructura
    alumnoLocal->conjuntoAlumnos=vectorEliminarAprobados;  //Hacemos que apunte al vector que contiene toda la información
    alumnoLocal->totalAlumnos=numeroAlumnos;   //Guardamos el nuevo número de alumnos que tenemos
}

void escribirAFichero(clase claseLocal)
{
    int i=0, j=0;
    char nombreFichero[50];
    printf("\n\tEscriba el nombre del fichero donde desea guardar los datos de los alumnos actuales.\n\tAl final del nomrbe, agregue la extension \".txt\": ");
    fflush(stdin);
    gets(nombreFichero);
    FILE *ficheroUsuario=fopen(nombreFichero, "w");   //Creamos el fichero con el nombre que nos da el usuario en formato de escritura
    for(i=0;i<claseLocal.totalAlumnos;i++)    //Escribimos en el fichero todos los datos de los que disponemos
    {
        fprintf(ficheroUsuario,"%s\n", claseLocal.conjuntoAlumnos[i].nombreAlumno);
        for(j=0;j<10;j++)
        {
            fprintf(ficheroUsuario,"%d\n", claseLocal.conjuntoAlumnos[i].notas[j]);
        }
    }
    fclose(ficheroUsuario);       //Cerramos el fichero
    printf("\n\tEl fichero ha sido creado correctamente.\n\tPodra encontrarlo en la misma carpeta en la que se encuentra este archivo.");
}

void sobreescribirFicheroInicial(clase claseLocal)
{
    int i=0,j=0;
    remove("DatosIniciales.txt");   //Borramos el fichero inicial que contiene la información de los primeros alumnos
    FILE *miFichero=fopen("DatosIniciales.txt","w");    //Creamos un nuevo fichero en formato de escritura con el mismo nombre
    for(i=0;i<claseLocal.totalAlumnos;i++)   //Colocamos en el fichero los datos de todos los alumnos
    {
        fprintf(miFichero,"%s\n", claseLocal.conjuntoAlumnos[i].nombreAlumno);
        for(j=0;j<10;j++)
        {

            if(i==(claseLocal.totalAlumnos-1) && j==9)  //Si es la ultima nota del ultimo alumno, eliminamos el salto de linea para poder leerlo bien al inicio del programa
            {
                fprintf(miFichero, "%d", claseLocal.conjuntoAlumnos[i].notas[j]);
            }
            else fprintf(miFichero,"%d\n", claseLocal.conjuntoAlumnos[i].notas[j]);
        }
    }
    fclose(miFichero);     //Cerramos el fichero
    printf("\n\tLos datos del fichero han sido sobreescritos correctamente.");
}

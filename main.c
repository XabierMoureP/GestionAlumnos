#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Clase.h"

int main()
{
    int i=0, eleccion=0, error=0;
    float media=0;       //Es de tipo float porque la media introducida puede ser un numero decimal
    char eliminarAlumno[100];
    clase miClase;       //Creamos nuestra variable de tipo clase
    inicializar(&miClase);   //Inicializamos miClase para cargar los datos de los primeros 10 alumnos desde un fichero
    mostrarClase(miClase);
    do     //Todo el programa estará dentro de este bucle para que se repita indefinidamente hasta que el usuario decida salir
    {
        do     //En este bucle se muestra el menu y se comprueba que se elije una opcion correcta
        {
            printf("\n\n\n\tElija una de las opciones:\n\n\t[1]: ELIMINAR ALUMNO\n\n\t[2]: NUEVO ALUMNO\n\n\t[3]: LISTAR ALUMNOS\n\n\t");
            printf("[4]: LISTAR ALUMNOS QUE SUPEREN UNA NOTA MEDIA\n\n\t[5]: ELIMINAR ALUMNOS CON TODAS LAS ASIGNATURAS APROBADAS\n\n\t");
            printf("[6]: GUARDAR SOLICITANDO NOMBRE\n\n\t[7]: GUARDAR DATOS\n\n\t[8]: SALIR\n\t");
            scanf("%d", &eleccion);
            if(eleccion>8 || eleccion<1) printf("\n\tEsa opcion no existe. Elija una de las dadas.");
        }while(eleccion>8 || eleccion<1);
        fflush(stdin);      //Vaciamos el búffer de entrada porque más adelante pedimos cadenas de carácteres
        switch (eleccion)      //Se comprueba qué ha elegido el usuario y se ejecutan las líneas de código que correspondan
        {
    case 1:    //El caso 1 corresponde a eliminar un alumno
        do     //Este bucle se repetirá mientras el usuario introduzca un nombre incorrecto
        {
            printf("\n\tIntroduzca el nombre del alumno que desea eliminar. Incluya mayusculas para la busqueda: ");
            gets(eliminarAlumno);    //Guardamos el nombre con gets porque previsiblemente contendrá espacios
            for(i=0;i<miClase.totalAlumnos;i++)
            {
                if(strcmp(eliminarAlumno,miClase.conjuntoAlumnos[i].nombreAlumno)!=0) //Comprobamos si el nombre introducido coincide con uno guardado
                {
                    error=1;
                }
                else   //En caso de que el nombre coincide con uno de los guardados
                {
                    error=0;
                    i=miClase.totalAlumnos-1;     //Con esta línea hacemos que deje de iterar para comprobar si el nombre coincide
                    eliminarAlumnos(&miClase, &eliminarAlumno);      //Llamada a la función que elimina un alumno
                    printf("\n\tEsta es la lista actualizada:\n\n");          //Se le da feedback al usuario
                    mostrarClase(miClase);
                    printf("\n\tEl alumno %s ha sido eliminado correctamente de la lista.", eliminarAlumno);
                }
            }
            if(error==1)  //Si tras la última iteración el valor de error sigue siendo 1, es porque el nombre introducido no coincide con ninguno
            {
                printf("\n\tEse nombre no coincide con niguno guardado.");
            }
        }while(error==1);
        break;   //Finalizamos case 1 del switch
    case 2:    //Corresponde a añadir un alumno
        anadirAlumno(&miClase);     //Llamada a la funcion que añade un nuevo alumno
        printf("\n\tEsta es la lista actualizada:\n\n");    //Se da feedback al usuario
        mostrarClase(miClase);
        break;    //Finalizamos case 2 del switch
    case 3:     //Corresponde a mostrar una lista de los alumnos de los que se dispone información
        printf("\n\tLista de todos los alumnos de los que se dispone de informacion:\n\n");     //Se da feedback al usuario
        mostrarClase(miClase);
        break;   //Finalizamos case 3 del switch
    case 4:    //Corresponde a mostrar los alumnos que superan la nota media que el usuario introduce
        do     //El bucle se repetirá hasta que el usuario introduzca un valor válido como nota media
        {
            printf("\n\tIntroduzca la nota media deseada: ");
            scanf("%f", &media);
            if(media<0.0 || media>10.0)   //Comprobamos si la nota introducida es válida
            {
                printf("\n\tEsa nota no es valida. Recuerde que debe estar entre 0 y 10.");
                error=0;
            }
            else error=1;
        }while(!error);
        printf("\n\tEsta es la lista actualizada:\n\n");   //Se da feedback al usuario
        listarNotaMedia(miClase, media);     //Llamada a la función que muestra alumnos según su nota media
        break;      //Finalizamos case 4 del switch
    case 5:     //Corresponde a eliminar a los alumnos con todas las asignaturas aprobadas
        eliminarAprobados(&miClase);      //Llamada a la función que elimina a los alumnos con todas las asignaturas aprobadas
        printf("\n\tLos alumnos con todas las asignaturas aprobadas han sido eliminados correctamente.");
        printf("\n\tEsta es la lista actualizada:\n\n");     //Se da feedback al usuario
        mostrarClase(miClase);
        break;   //Finalizamos case 5 del switch
    case 6:   //Corresponde a volcar los datos en un fichero
        escribirAFichero(miClase);
        break;   //Finalizamos case 6 del switch
    case 7:   //Corresponde a sobreescribir los datos del fichero inicial
        sobreescribirFicheroInicial(miClase);
        break;   //Finalizamos case 7 del switch
    case 8:    //Corresponde a cerrar el programa
        printf("\n\tEl programa se ha cerrado.\n\n");
        return 0;
        }
    }while(eleccion>=1 && eleccion<=8);
}

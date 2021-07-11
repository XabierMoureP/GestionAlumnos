#ifndef CLASE_H_INCLUDED
#define CLASE_H_INCLUDED

//Creamos una estructura para almacenar los datos de cada un de los alumnos
typedef struct
{
    int notas[10];
    char *nombreAlumno;
}datosAlumnos;

//Creamos otra estructura con la que almacenamos los datos de todos alumnos (clase)
typedef struct
{
    datosAlumnos *conjuntoAlumnos;
    int totalAlumnos;
}clase;

void inicializar (clase *);   //Carga los datos de los 10 primeros alumnos
void mostrarAlumno (datosAlumnos);    //Muestra los datos de un unico alumno
void mostrarClase (clase);     //Muestra los datos de todos los alumnos
void eliminarAlumnos (clase *, char *);    //Elimina el alumno que el usuario quiera
void eliminarAprobados (clase *);     //Elimina los alumnos que tengan todas las asignaturas aprobadas
void anadirAlumno (clase *);    //Añade un nuevo alumno
float calcularNotaMedia (datosAlumnos);     //Funcion que devuelve la nota media de un alumno que se le pasa como argumento
void listarNotaMedia (clase, float);    //Muestra los alumnos que superen la nota media que quiera el usuario
void vaciarCadena (char *);    //Vacía una cadena de máximo 100 carácteres
void escribirAFichero (clase);     //Volcamos los datos de los alumnos de los que se dispone información en ese momento
void sobreescribirFicheroInicial(clase);     //Sobreescribimos los datos del fichero inicial para utilizarlos la próxima vez que se ejecte el programa

#endif // CLASE_H_INCLUDED

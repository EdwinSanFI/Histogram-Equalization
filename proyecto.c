// Dada un archivo de imagen en formato jpg, genera una nueva imagen con el histograma
// ecualizado a partir de la imagen original. Además, generar un archivo csv con el histograma orginal y el ecualizado
// Usar programacion secuencial y paralela. Utilizar STB para leer la imagen y escribir la imagen.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb-master/stb_image_write.h"

#define L 256
#define RESET_COLOR "\x1b[0m"
#define ROJO_T "\x1b[31m"
#define VERDE_T "\x1b[32m"
#define AZUL_T "\x1b[34m"
#define MAGENTA_T "\x1b[35m"
#define CYAN_T "\x1b[36m"

int width, height, channels,n_threads;
double time_inicial, time_secuencial, time_parallel, n_pixels, time_load_initial, time_load_final, time_save_image_secuencial_initial;
double time_save_image_secuencial_final, time_save_image_parallel_initial, time_save_image_parallel_final, time_create_csv_secuencial_initial, time_create_csv_secuencial_final, time_create_csv_parallel_initial, time_create_csv_parallel_final;
void equalize_secuencial(unsigned char *srcImage, char *filename);
void equalize_parallel(unsigned char *srcImage, char *filename);

void main( int argc, char *argv[]) {
    printf("\n\n");
    printf(CYAN_T "\t Proyecto Final - Ecualizacion de Histogramas en Imagenes \n" RESET_COLOR);

    // Guarda el nombre de la imagen
    char *filename = argv[1];

    // Si no se ingresa el nombre de la imagen, se termina el programa
    if (filename == NULL) {
        printf(ROJO_T"\nFalta el nombre de la imagen como parametro\n" );
        printf("Favor de agregar el nombre, ejemplo: " RESET_COLOR "./proyecto imagen.jpg\n");
    }

    // Lee la imagen
    time_load_initial = omp_get_wtime();
    unsigned char *image = stbi_load(filename, &width, &height, &channels, 0);
    time_load_final = omp_get_wtime();

    if (image == NULL) {
        // Mensaje de error
        printf(ROJO_T"\nError al leer la imagen, revise el nombre de la imagen\n\n" RESET_COLOR);
    } else {
        // Tamaño de la imagen, número de pixeles
        n_pixels = width * height;
        // Mensaje de confirmación
        printf("\n Imagen cargada %dx%d, %d canales, %f megapixeles\n", width,height,channels,n_pixels/1000000);


        // Equalizacion de histograma secuencial
        equalize_secuencial(image, filename);

        // Equalizacion de histograma paralela
        equalize_parallel(image, filename);

        // Libera la memoria
        stbi_image_free(image);


        // Imprime los resultados obtenidos
        printf(MAGENTA_T"\n\n\t\t RESULTADOS \n\n"RESET_COLOR);
        // Resultado de tiempos
        printf(VERDE_T" Secuencial: %f segundos\n" RESET_COLOR, time_secuencial);
        printf(VERDE_T" Paralelo: %f segundos\n" RESET_COLOR, time_parallel);
        // Resultado de hardware
        printf(AZUL_T"\n Numero de procesadores: %d", n_threads);
        double speedUp = time_secuencial / time_parallel;
        printf("\n SPEED UP: %f",speedUp);
        double overhead = time_parallel - time_secuencial/n_threads;
        printf("\n OVERHEAD: %f",overhead);
        printf("\n Eficiencia de la ejecucion: %f\n"RESET_COLOR, speedUp/(double)n_threads);

        printf("\nTiempo de caraga de la imagen:" VERDE_T " %f segundos\n" RESET_COLOR, time_load_final - time_load_initial);
        printf("\nTiempo de generacion de imagen secuencial:" VERDE_T " %f segundos\n" RESET_COLOR, time_save_image_secuencial_final - time_save_image_secuencial_initial);
        printf("\nTiempo de generacion de imagen paralelo:" VERDE_T " %f segundos\n" RESET_COLOR, time_save_image_parallel_final - time_save_image_parallel_initial);
        printf("\nTiempo de generacion de de archivo csv secuencial:" VERDE_T " %f segundos\n" RESET_COLOR, time_create_csv_secuencial_final - time_create_csv_secuencial_initial);
        printf("\nTiempo de generacion de de archivo csv paralelo:" VERDE_T " %f segundos\n" RESET_COLOR, time_create_csv_parallel_final - time_create_csv_parallel_initial);

        printf("\n\n");
    }
}

void equalize_secuencial(unsigned char *srcImage, char *filename) {
    time_inicial = omp_get_wtime();

    int histogram[L];
    int newHistogram[L];
    int cdf[L];
    int eqCdf[L];
    int i;

    // 2. Inicializar el histograma
    for (i = 0; i < L; i++) {
        histogram[i] = 0;
        newHistogram[i] = 0;
        cdf[i] = 0;
        eqCdf[i] = 0;
    }

    unsigned char *imaRed2 = malloc(n_pixels * channels * sizeof(unsigned char));
    // Si la imagen es un RGB, se convierte a gris usando el canal rojo
    if (channels == 3) {
        // Crea una imagen en rojo y otra en gris
        unsigned char *imaRed = malloc(n_pixels * channels * sizeof(unsigned char));
        for (i = 0; i < n_pixels; i++) {
            // Obtiene valores de los rgb
            unsigned char r = srcImage[i * channels];
            unsigned char g = srcImage[i * channels + 1];
            unsigned char b = srcImage[i * channels + 2];

            // Crea la imagen en rojo
            imaRed[i * channels] = r;
            imaRed[i * channels + 1] = 0;
            imaRed[i * channels + 2] = 0;

            // Guarda la imagen rojo convirtiendola en una imagen en gris
            imaRed2[i] = imaRed[i * channels];
            // // Crea la imagen en gris
            // imaRed2[i * channels] = (r + g + b) / 3;
            // imaRed2[i] = 0.3 * r + 0.59 * g + 0.11 * b;
        }
        for (i = 0; i < n_pixels; i++) {
            histogram[imaRed2[i]]++;
        }
    } else {
        for (i = 0; i < n_pixels; i++) {
            histogram[srcImage[i]]++;
        }
    }


    // 3. Generar Cumulative Distribution Function
    for (i = 1; i < L; i++) {
        cdf[i] = (histogram[i] + cdf[i - 1]);
    }

    // 4. Encontrar el minimo cdf que no sea 0
    int min = 5;
    for (i = 0; i < L; i++) {
        if (min>cdf[i] && cdf[i]!=0) {
            min = cdf[i];
        }
    }

    // 5. Genera el nuevo cdf
    for (i = 0; i < L; i++) {
        eqCdf[i] = round((((cdf[i] - min)/(n_pixels - min)) * (L-2)))+1;
    }

    // 6. Generar la imagen con el histograma ecualizado
    unsigned char *outputImage = malloc(n_pixels * sizeof(unsigned char));

    if(channels == 3) {
        for (i = 0; i < n_pixels; i++)
            {
                outputImage[i] = eqCdf[imaRed2[i]];
        }
    } else {
        for (i = 0; i < n_pixels; i++)
            {
                outputImage[i] = eqCdf[srcImage[i]];
            }
    }

    // 7. Generar nuevo histograma
    for (i = 0; i < n_pixels; i++) {
        newHistogram[outputImage[i]]++;
    }

    // Termina el conteo de tiempo
    time_secuencial = omp_get_wtime() - time_inicial;

    time_save_image_secuencial_initial = omp_get_wtime();

    // Elimina el ".jpg" del nombre de la imagen
    filename = strtok(filename, ".");
    // Extension para el nombre de la imagen
    char *extension = "_eq_secuencial.jpg";
    // Variable para el nombre de la imagen
    char *newFilename= (char *) malloc(sizeof(char) * (strlen(filename) + strlen(extension) + 1));
    // Copia el nombre de la imagen sin ".jpg" en newFilename
    strcpy(newFilename, filename);
    // Agrega la extension a newFilename
    strcat(newFilename, extension);

    // Imprimir nombre de archivo
    printf("\nSe creo la imagen:" AZUL_T " %s" RESET_COLOR, newFilename);

    // 8. Guarda la imagen
    // Nombre de la imagen, ancho, alto, canales, imagen, calidad
    stbi_write_jpg(newFilename, width, height, 1, outputImage, 100);
    // Liberar la memoria
    free(outputImage);

    time_save_image_secuencial_final = omp_get_wtime();

    time_create_csv_secuencial_initial = omp_get_wtime();

    // Extension para el nombre del archivo CSV
    char *extensionCSV = "_histo_secuencial.csv";
    // Variable para el nombre del archivo CSV
    char *newCSVname= (char *) malloc(sizeof(char) * (strlen(filename) + strlen(extensionCSV) + 1));
    // Copia el nombre de la imagen sin ".jpg" en newCSVname
    strcpy(newCSVname, filename);
    // Agrega la extension a newCSVname
    strcat(newCSVname, extensionCSV);

    // 9. Guarda el histograma en un archivo CSV
    // Crea el archivo CSV
    FILE *fp;

    // Abre el archivo en modo escritura
    fp = fopen(newCSVname, "w+");

    if (fp == NULL) {
        // Mensaje de error
        printf(ROJO_T"\nError al crear el archivo %s\n" RESET_COLOR,newCSVname);
    } else {
        // Mensaje de confirmacion
        printf("\nSe creo el archivo:" AZUL_T " %s\n" RESET_COLOR, newCSVname);
    }

    // Escribe el histograma de la imagen original y de la imagen ecualizada en el archivo csv
    for (int i = 0; i < L; i++) {
        fprintf(fp, "%d,%d,%d\n", i, histogram[i], newHistogram[i]);
    }

    // Cierra el archivo
    fclose(fp);

    time_create_csv_secuencial_final = omp_get_wtime();
}

void equalize_parallel(unsigned char *srcImage, char *filename) {
    time_inicial = omp_get_wtime();

    int histogram[L];
    int newHistogram[L];
    int cdf[L];
    int eqCdf[L];
    int i, tid, inicio, fin;

    // 2. Inicializar el histograma
    for (i = 0; i < L; i++) {
        histogram[i] = 0;
        newHistogram[i] = 0;
        cdf[i] = 0;
        eqCdf[i] = 0;
    }

    unsigned char *imaRed2 = malloc(n_pixels * channels * sizeof(unsigned char));

    // Obtiene el numero de nucleos
    n_threads = omp_get_num_procs();
    // Asigna el numero de hilos
    omp_set_num_threads(n_threads);


    // Si la imagen es de 3 canales, entonces se debe convertir a gris usando al canal rojo
    if (channels == 3) {
        // Crea una imagen en rojo desde la imagen original
        unsigned char *imaRed = malloc(n_pixels * channels * sizeof(unsigned char));
        // Recorre el numero de pixeless de la imagen original
        for (i = 0; i < n_pixels; i++) {
            // Obtiene valores de los rgb
            unsigned char r = srcImage[i * channels];
            unsigned char g = srcImage[i * channels + 1];
            unsigned char b = srcImage[i * channels + 2];

            // Crea la imagen en rojo
            imaRed[i * channels] = r;
            imaRed[i * channels + 1] = 0;
            imaRed[i * channels + 2] = 0;

            // Guarda la imagen rojo convirtiendola en una imagen en gris
            imaRed2[i] = imaRed[i * channels];
        }
        for (i = 0; i < n_pixels; i++) {
            histogram[imaRed2[i]]++;
        }
    } else {
        for (i = 0; i < n_pixels; i++) {
            histogram[srcImage[i]]++;
        }
    }


    // 3. Generar Cumulative Distribution Function
    for (i = 1; i < L; i++) {
        cdf[i] = (histogram[i] + cdf[i - 1]);
    }

    int min = 5;
    for (i = 0; i < L; i++) {
        if (min>cdf[i] && cdf[i]!=0) {
            min = cdf[i];
        }
    }

    // 5. Genera el nuevo cdf
    for (i = 0; i < L; i++) {
        eqCdf[i] = round((((cdf[i] - min)/(n_pixels - min)) * (L-2)))+1;
    }

    // 6. Generar la imagen con el histograma ecualizado
    unsigned char *outputImage = malloc(n_pixels * sizeof(unsigned char));

    #pragma omp parallel private(tid, i, inicio, fin)
    {
        tid = omp_get_thread_num();
        inicio = tid * (n_pixels / n_threads);
        fin = (tid + 1) * (n_pixels / n_threads) - 1;


        if(channels == 3) {
            for (i = inicio; i < fin; i++)
                {
                    outputImage[i] = eqCdf[imaRed2[i]];
            }
        } else {
            for (i = inicio; i < fin; i++)
                {
                    outputImage[i] = eqCdf[srcImage[i]];
                }
        }

    }
    // Genera nuevo histograma
    for (i = 0; i < n_pixels; i++) {
        newHistogram[outputImage[i]]++;
    }

    // * Termina el conteo de tiempo
    time_parallel = omp_get_wtime() - time_inicial;

    time_save_image_parallel_initial = omp_get_wtime();

    // Elimina el ".jpg" del nombre de la imagen
    filename = strtok(filename, ".");
    // Extension para el nombre de la imagen
    char *extension = "_eq_parallel.jpg";
    // Variable para el nombre de la imagen
    char *newFilename= (char *) malloc(sizeof(char) * (strlen(filename) + strlen(extension) + 1));
    // Copia el nombre de la imagen sin ".jpg" en newFIleName
    strcpy(newFilename, filename);
    // Agrega la extension a newFilename
    strcat(newFilename, extension);

    // Imprimir nombre de archivo
    printf("\nSe creo la imagen:" AZUL_T " %s" RESET_COLOR, newFilename);

    // 8. Guarda la imagen
    // Nombre de la imagen, ancho, alto, canales, imagen, calidad
    stbi_write_jpg(newFilename, width, height, 1, outputImage, 100);
    // Liberar la memoria
    free(outputImage);

    time_create_csv_parallel_initial = omp_get_wtime();

    time_create_csv_parallel_initial = omp_get_wtime();

    // Extension para el nombre del archivo CSV
    char *extensionCSV = "_histo_parallel.csv";
    // Variable para el nombre del archivo CSV
    char *newCSVname= (char *) malloc(sizeof(char) * (strlen(filename) + strlen(extensionCSV) + 1));
    // Copia el nombre de la imagen sin ".jpg" en newCSVname
    strcpy(newCSVname, filename);
    // Agrega la extension a newCSVname
    strcat(newCSVname, extensionCSV);

    // 9. Guarda el histograma en un archivo CSV
    // Crea el archivo CSV
    FILE *fp;

    // Abre el archivo en modo escritura
    fp = fopen(newCSVname, "w+");

    if (fp == NULL) {
        // Mensaje de error
        printf(ROJO_T"\nError al crear el archivo %s\n" RESET_COLOR, newCSVname);
    } else {
        // Mensaje de confirmacion
        printf("\nSe creo el archivo:" AZUL_T " %s\n" RESET_COLOR, newCSVname);
    }

    // Escribe el histograma de la imagen original y de la imagen ecualizada en el archivo csv
    for (int i = 0; i < L; i++) {
        fprintf(fp, "%d,%d,%d\n", i, histogram[i], newHistogram[i]);
    }

    // Cierra el archivo
    fclose(fp);

    time_create_csv_parallel_final = omp_get_wtime();
}
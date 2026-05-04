#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <libgen.h>

#define SIZE 9

void load_image(const char* filepath, unsigned char** image_data, size_t* width, size_t* height);
void save_image(const char* filepath, unsigned char* image, size_t width, size_t height);

//calcul de la position dans le tableau 1D à partir des coordonées x et y
int index_from_x_y(int x, int y, int width)
{
    return (x + y * width) * 3;
}

int process_image(const char* filepath, const char* output_dir)
{
    unsigned char* image = NULL;
    unsigned char* out_image = NULL;
    char* filename = strdup(filepath);
    char* image_name = basename(filename);
    char* output_filename = malloc(strlen(output_dir) + strlen(image_name)+ 2);
    memset(output_filename,0,strlen(output_dir) + strlen(image_name) + 2);
    strcat(output_filename,output_dir);
    strcat(output_filename,"/");
    strcat(output_filename,image_name);
    size_t width = 0;
    size_t height = 0;

    load_image(filepath, &image, &width, &height);
    out_image = malloc((width*height*3) * sizeof(unsigned char));

    /*
     * Tableau contenant les décallage pour obtenir les
     * voisins de n'importe quel pixel
     * 
     * |(-1,-1)|( 0,-1)|( 1,-1)|
     * |(-1, 0)|( 0, 0)|( 1, 0)|
     * |(-1, 1)|( 0, 1)|( 1, 1)|
     */
    char offset[2*SIZE] = {-1,-1, 0,-1, 1,-1,
        -1, 0, 0, 0, 1, 0,
        -1, 1, 0, 1, 1, 1};
    /* Coefficient pour la convolution */
    char matrix[SIZE] = {1,1,1,
        1,1,1,
        1,1,1};

    //Parcours de toute les lignes
    for(unsigned int y = 0; y < height; y++)
    {
        //parcours pour chaque ligne de chaque colonnes
        for(unsigned int x = 0; x < width; x++)
        {
            //somme de chaque composante de la couleur
            int somme_r = 0;
            int somme_g = 0;
            int somme_b = 0;

            //compteur de pixel traversé par la convolution (max 9)
            int cpt = 0;
            //on parcours offset et coefficient pour calculer la convolution
            for(int i = 0; i < SIZE; i++)
            {
                //position des voisins du pixel en x,y
                int neightbor_x = x + offset[2*i];
                int neightbor_y = y + offset[2*i+1];
                //vérification que le pixel voisin considéré est bien dans l'image. 
                if (neightbor_x >= 0 && neightbor_x < (int)width && neightbor_y >= 0 && neightbor_y < (int)height)
                {
                    int index = index_from_x_y(neightbor_x,neightbor_y,width);
                    //calcul pour le voisin avec le coefficient de la matrice et la composante couleur (r,g,b)
                    somme_r += matrix[i] * image[index];
                    somme_g += matrix[i] * image[index+1];
                    somme_b += matrix[i] * image[index+2];
                    cpt++;
                }
            }
            //calcul du résultat pour le pixel x y et enregistrement dans l'image de sortie
            int index = index_from_x_y(x,y,width);
            out_image[index] = somme_r / cpt;
            out_image[index+1] = somme_g / cpt;
            out_image[index+2] = somme_b / cpt;
        }
    }
    srand(getpid());
    int t = rand() % 10 + 20;

    sleep(t);

    save_image(output_filename, out_image, width, height);
    free(image);
    free(out_image);
    free(filename);
    free(output_filename);
    return 0;
}

char* readline(int fd)
{
    int offset = 0;
    size_t size;
    char dummy;
    do {
        size = read(fd,&dummy,1);
        offset += size;
    } while(size != 0 && dummy != '\n' && dummy != EOF);

    char* line = malloc(offset * sizeof(char)+1);
    lseek(fd,-offset,SEEK_CUR);
    read(fd,line,offset);
    line[offset]='\0';
    return line;
}

void load_image(const char* filepath, unsigned char** image_data, size_t* width, size_t* height)
{
    int fd = open(filepath,O_RDONLY);
    if (fd == -1)
    {
        perror("Can't open input file");
        exit(-1);
    }
    char* line = readline(fd);
    if ( strncmp("P6", line, 2) != 0)
    {
        fputs("Input File is not a ppm file\n", stderr);
        free(line);
        exit(-1);
    }
    free(line);
    do {
        line = readline(fd);
        if (line[0] == '#')
        {
            free(line);
            continue;
        }
        int success = sscanf(line,"%lu %lu",width,height);
        if (success != 2)
        {
            fputs("Input File is not a valid ppm file\n", stderr);
            free(line);
            exit(-1);
        }
        free(line);
    } while(*width == 0);
    int dummy = 0;
    do {
        line = readline(fd);
        if (line[0] == '#')
        {
            free(line);
            continue;
        }
        int success = sscanf(line,"%d",&dummy);
        if (success != 1)
        {
            fputs("Input File is not a valid ppm file\n", stderr);
            free(line);
            exit(-1);
        }
        free(line);
    } while(dummy == 0);

    unsigned data_size = 3 * (*width) * (*height);
    *image_data = malloc(data_size * sizeof(unsigned char));

    read(fd,*image_data,3*(*width)*(*height));
}

void save_image(const char* filepath, unsigned char* image, size_t width, size_t height)
{
    int fd = open(filepath,O_CREAT|O_WRONLY,0644);
    if (fd == -1)
    {
        perror("Can't open output file");
        exit(-1);
    }
    write(fd,"P6\n",3);
    char* size = NULL;
    asprintf(&size,"%lu %lu\n",width, height);
    write(fd,size,strlen(size));
    free(size);
    write(fd,"255\n",4);
    usleep(500000);
    write(fd,image,3*width*height);
    write(fd,"\n",1);
    close(fd);

}


/**Verilen bir metni bmp dosyası icerisine saklayan program
 * last update: 10.03.2024
 * author: Hilal Nur Albayrak 22120205056
 */

/*Fonksiyon tasarimlarinda ders notlarindan ve chatgpt'den yardim alinmistir.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "lab4bmp.h"

/**main fonksiyonundan gelen dosyayı okuyarak pixellerini
 * dizi icerisine saklayan fonksiyon
*/
Image *imread(char *fname) {
    FILE *f = fopen(fname, "rb");
    if (f == NULL) {
        perror("the file not found!");
        return NULL;
    }

    Image *im = (Image *)malloc(sizeof(Image));

    if (im == NULL) {
        perror("memory allocation failed!");
        fclose(f);
        return NULL;
    }

    im = (Image *)malloc(sizeof(Image) + sizeof(Pixel)* 488 * 800);
    if (im->pixels == NULL) {
        perror("memory allocation failed!");
        fclose(f);
        free(im);
        return NULL;
    }

    im->nplanes = 0;
    im->nbits = 0;

    fseek(f, 10, SEEK_CUR);  
    fread(&im->offset, 4, 1, f);
    fread(&im->headersize, 4, 1, f);
    fread(&im->width, 4, 1, f);
    fread(&im->height, 4, 1, f);
    fread(&im->nplanes, 2, 1, f);
    fread(&im->nbits, 2, 1, f);
    fseek(f, im->offset, SEEK_SET);

    int i, j;
    for(i = (im->height) - 1; i >= 0; i--){
        for(j = 0; j < (im->width); j++){
            fread(&im->pixels[i * (im->width) + j].pixel, 4, 1, f);
        }
    }

    fclose(f);

    return im;
}

/** resim icin acilan bellegi bosaltan fonksiyon */
int imclose(Image *im) {
    free(im);
    return 0;
}

/**hidemsg fonksiyonundan gonderilen pixel ile gizlenecek
 * metnin bir charını alarak pixel icine saklayan fonksiyon
*/
int hideinpixel(Pixel *p, unsigned char c) {
    unsigned char mask = 0xC0;

    p->b = (p->b & 0xFC) | ((c & mask) >> 6);
    mask >>= 2;
    p->g = (p->g & 0xFC) | ((c & mask) >> 4);
    mask >>= 2;
    p->r = (p->r & 0xFC) | ((c & mask) >> 2);
    mask >>= 2;
    p->a = (p->a & 0xFC) | (c & mask);

    return 0;
}

/**main den resim ve mesaj alarak mesajin her harfini saklanmak
 * uzere hideinpixel fonksiyonuna gonderen fonksiyon
*/
int hidemsg(Image *im, unsigned char *msg) {
    int uzunluk = strlen(msg);
    int i;
    for(i = 0; i <= (im->width * im->height) - 1; i++){
        hideinpixel(&im->pixels[i], msg[i % uzunluk]);
    }
    return 0;
}

/**hideinpixel in tam tersi calisan, gelen pixeldeki gizli 
 * harfi okuyan fonksiyon
*/
char readcharinpixel(Pixel *p) {
    char c = 0;
    unsigned char mask = 0x03;
    c |= (p->b & mask) << 6;
    c |= (p->g & mask) << 4;
    c |= (p->r & mask) << 2;
    c |= (p->a & mask);

    return c;
}

/**harfleri readcharinpixel den alarak mesaji mainden gelen
 * dizi icine kaydeden fonksiyon
*/
int readmsg(Image *im, unsigned char msg[], int maxlength) {
    int i;

    for(i = 0; i <= (im->width * im->height) - 1; i++){
        if(i < maxlength){
            msg[i] = readcharinpixel(&im->pixels[i]);
        } else {
            msg[i] = '\0'; 
            break;
        }
    }
    
    return maxlength;
}

/*pixelleri yazan fonksiyon*/
int printpixel(Pixel *p) {
    printf("r:%d-g:%d-b:%d-a:%d", p->r, p->g, p->b, p->a);
    return 0;
}

/**programın main fonksiyonu
 * bir adet Image olusturarak fonksiyonlara ileten fonksiyon
*/
int main(void) {
    char *msg = "hello";
    char dizi[100];
    char fname[] = "cute-animals32bit.bmp";
    int length = strlen(msg);
    Image *im = imread(fname);
    hidemsg(im, msg);
    readmsg(im, dizi, length);
    /*printf("okunan metin: %s\n", dizi);*/
    
    return 0;
}

[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/6J2MKqY6)
# Lab4- working with BMPStructs, I/O, Shifts, Memory
## :warning: test.c de ve Makefile da bir degisiklik yapmayiniz, github uzerinde autogradingde kullanilmaktadir.

## Bilinmesi gerekenler
- BMP file
- File I/O
- Structs, unions, typedef
- Pointers
- Shifts
## Detaylar
Bu labda sizden bir resmin icerisine verilen mesaji saklamaniz istenmektedir.
Mesajin her bir karakteri 8-bit uzunlugunda varsayilarak;
- resmin icerisindeki ARGB yada XRGB seklinde herbiri 8er bitten toplamda 32-bit uzunlugundaki pixel degerlerine saklamaniz istenmektedir.
- Burada size verilen asagidaki data structure bir pixel degerini tutacaktir. **XBGR formatinda**:

  ```C
    typedef union {
        uint32_t pixel;
        struct {
            uint8_t a : 8;      /* a or x in argb, xrgb   */
            uint8_t b : 8;      
            uint8_t g : 8;
            uint8_t r : 8;
        } __attribute__((packed));
    } Pixel;
    ```
    
- Tum resmi saklamak icin,asagidaki type tanimlanmistir.
    ```C
    typedef struct image {
        int offset;     /* starting address in image file.              */
        int headersize; /* header size                                  */
        int width;      /* image width in pixels                        */
        int height;     /* image height in pixels                       */
        int nplanes;    /* number of color planes-1                     */
        int nbits;      /* 32-24-16 etc                                 */
        Pixel pixels[];   /* pointer to image, remaining part of bmp data */
    } __attribute__((packed)) Image;
    ```
## Yapilmasi Gerekenler
Size verilen main.c dosyasindaki fonksiyonlari tamamlayarak, bir mesaji image datasi icerisine saklamayi, ve cikarmayi gerceklestiriniz.
## Degerlendirme
- Lab oncelikle test.c de size verilen acik testler calistirilarak testten gecirilecektir. Bu testlerden gecmeyenler icin tekrardan ayrica bir degerlendirme yapilmayacaktir.
- Labda bu testlerden gecenler icin gerektiginde ayrica gizli testler calistirilarak ayrica bir degerlendirme yapilabilecektir.
- Testlerden gecse dahi kodda belirlenen hatalardan veya yanlis kodlamalardan veya kodlama standartlarindan puan kirilacaktir.
# English:
## Prerequisites
- BMP file
- File I/O
- Structs, unions, typedef
- Pointers
- Shifts
## Details
In this lab, you are required to hide a given msg into an image.
We will assume each char is 8 bit long, and a pixel is saved as XBGR format. For this format we define the following type in ``lab4bmp.h``:
   
  ```C
    typedef union {
        uint32_t pixel;
        struct {
            uint8_t a : 8;      /* a or x in argb, xrgb   */
            uint8_t b : 8;      
            uint8_t g : 8;
            uint8_t r : 8;
        } __attribute__((packed));
    } Pixel;
  ```
    
- For the full image file, we define:
    ```C
    typedef struct image {
        int offset;     /* starting address in image file.              */
        int headersize; /* header size                                  */
        int width;      /* image width in pixels                        */
        int height;     /* image height in pixels                       */
        int nplanes;    /* number of color planes-1                     */
        int nbits;      /* 32-24-16 etc                                 */
        Pixel pixels[];   /* pointer to image, remaining part of bmp data */
    } __attribute__((packed)) Image;
    ```
## What you need to do
Given file main.c includes a few functions, you need to complete them to complete the desired task: i.e. hiding and extracting msg into/from image data.

## Grading
- Your main.c will be graded first by using the test cases in test.c. If you cannot get pass this tests, no further testing is going to be done for grading!
- If main.c passes every test in test.c, then we may further test your program with some tests which are not given to you in github (this tests may be posted later).
- Therefore, your final grade may be lower than what you expect them or as you see them on github. 
- Even if your program passes every tests, we may still deduct points from coding standards or some different mistakes/errors.

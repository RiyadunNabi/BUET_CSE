#include <stdio.h>

int putImage(int *image, char filename[], int h, int w)
{
  FILE *file = fopen(filename, "wb");

  if (file == NULL)
  {
    return 0;
  }
  if (fwrite(&h, sizeof(int), 1, file) != 1)
    return 0;
  if (fwrite(&w, sizeof(int), 1, file) != 1)
    return 0;
  if (fwrite(image, sizeof(int), h * w, file) != h * w)
    return 0;
  if (fclose(file) == EOF)
    return 0;
  return 1;
}

int correctPixel(char filename[], int row, int col, int correction, int h, int w)
{
  FILE *file = fopen(filename, "rb+");

  if (file == NULL)
  {
    return 0;
  }
  fseek(file, 2 * sizeof(int), SEEK_SET);

  fseek(file, sizeof(int) * (row * w + col ), SEEK_CUR);

  fwrite(&correction, sizeof(int), 1, file);

  fclose(file);

  return 1;
}

void showImage(char filename[])
{
  FILE *file = fopen(filename, "rb");
  int h, w;
  fread(&h, sizeof(int), 1, file);
  fread(&w, sizeof(int), 1, file);
  int image[h * w];
  printf("%d %d\n",h,w);
  fread(image, sizeof(int), h * w, file);

  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      printf("%d ", image[i * w + j]);
    }
    printf("\n");
  }

  fclose(file);
}

int main()
{
  int h, w;
  printf("Enter height and width(which will later be h and w): ");
  scanf("%d%d", &h, &w);
  int arr[h][w];
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      scanf("%d", &arr[i][j]);
    }
  }

  char filename[50];
  int error;
  fflush(stdin);
  printf("Give the name file:");
  gets(filename);
  printf("Give the number of erraneous pixels:");
  scanf("%d", &error);
  putImage((int *)arr, filename, h, w);
  showImage(filename);

  for (int i = 0; i < error; i++)
  {
    printf("Enter the pixel to be corrected[row,col,corrected value]:");
    int x, y, c;
    scanf("%d%d%d", &x, &y, &c);
    correctPixel(filename, x, y, c, h, w);
  }

  showImage(filename);

  return 0;
}
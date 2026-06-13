#include <stdio.h>
int main()
{
    printf("\n\n");
    /**********************************************/
    // NULL File Pointer if the file doesn't exit
    FILE *fp_in_0;
    fp_in_0 = fopen("sample_input_0.txt", "r"); // if "w" , then it will create that file
    if (fp_in_0 == NULL)
    {
        printf("file_0 doesn't exist\n");
    }
    else
        fclose(fp_in_0);

    /**************************************************/
    FILE *fp_in_1 = fopen("sample_input_1.txt", "r");
    char ch;

    fscanf(fp_in_1, "%c", &ch);
    printf("ch = %c\n", ch);
    fscanf(fp_in_1, "%c", &ch);
    printf("ch = %c\n", ch);
    fscanf(fp_in_1, "%c", &ch);
    printf("ch = %c\n", ch);
    fscanf(fp_in_1, "%c", &ch);
    printf("ch = %c\n", ch);

    fclose(fp_in_1);
    /**********************************************/
    FILE *fp_in_2 = fopen("sample_input_2.txt", "r");
    int n;

    fscanf(fp_in_2, "%d", &n); // will scan until it found any space
    printf("n = %d\n", n);
    fscanf(fp_in_2, "%d", &n);
    printf("n = %d\n", n);
    fscanf(fp_in_2, "%d", &n);
    printf("n = %d\n", n);
    fscanf(fp_in_2, "%d", &n);
    printf("n = %d\n", n);

    fclose(fp_in_2);
    /**********************************************/
    FILE *fp_in_3 = fopen("sample_input_3.txt", "w"); // if "w", then it will overwrite every time
                                                      // if "a", then it will append,means=add (something) to the end of a written document.
    char ch_3 = 'R';                                  // if ch_3 = 'Riyad', overflow in implicit constant conversion,
                                                      // then last char 'd' will be stored;
    int n_3 = 123;
    fprintf(fp_in_3, "%c isss %d\n", ch_3, n_3);
    fprintf(fp_in_3, "My name is Riyad %d\n", n_3);
    // will print all in that file at the same time
    fprintf(fp_in_3, "%c", 'B');
    fprintf(fp_in_3, "%c", 'O');
    fprintf(fp_in_3, "%c", 'e');
    fprintf(fp_in_3, "%c\n\n", 't');

    fclose(fp_in_3);
    /**********************************************/
    /***********fgetc***********************************/
    FILE *fp_in_4_r = fopen("sample_input_4_r.txt", "r");
    char ch_4 = fgetc(fp_in_4_r);
    printf("ch_4 = %c\n", ch_4);
    ch_4 = fgetc(fp_in_4_r);
    printf("ch_4 = %c\n", ch_4);
    ch_4 = fgetc(fp_in_4_r);
    printf("ch_4 = %c\n", ch_4);

    printf("ASCII of ' ' = %d\n", fgetc(fp_in_4_r));

    int n_4 = fgetc(fp_in_4_r);
    printf("ASCII of '1' = %d\n", n_4); // ASCII of 1 = 49
    printf("ch_4(numeric char) = %c\n", fgetc(fp_in_4_r));
    printf("ASCII of '0' = %d\n", fgetc(fp_in_4_r)); // 48

    fclose(fp_in_4_r);
    /**********************************************/
    /**************fputc()********************************/
    FILE *fp_in_4_w = fopen("sample_input_4_w.txt", "w");
    char ch_4_w = 'l';

    fputc('H', fp_in_4_w);
    fputc('e', fp_in_4_w);
    fputc(ch_4_w, fp_in_4_w);
    fputc(ch_4_w, fp_in_4_w);
    fputc('o', fp_in_4_w);

    fclose(fp_in_4_w);
    /********************EOF=End of File*****************************************************************************************/
    FILE *fp_in_4_3 = fopen("sample_input_4.3_strings.txt", "r");
    char ch4 = fgetc(fp_in_4_3);
    while (ch4 != EOF)
    {
        printf("%c", ch4);
        ch4 = fgetc(fp_in_4_3);
    }
    fclose(fp_in_4_3);
/************************fputs**********************************************************************************/
    FILE *fp_in_5_w = fopen("sample_input_5.1_strings.txt", "w");
    char str5_1[50] = "This is a string named str5_1.";
    fputs(str5_1, fp_in_5_w);
    fclose(fp_in_5_w);
/*************************fgets*******************************************************************************/
    FILE *fp_in_5_r = fopen("sample_input_5.2_strings.txt", "r");
    char str5_2[100];

    fgets(str5_2, 100, fp_in_5_r);
    fclose(fp_in_5_r);
    //printf("%s",str5_2);
    puts(str5_2);
/*******************************************************************/
    printf("\n\n");
    return 0;
}
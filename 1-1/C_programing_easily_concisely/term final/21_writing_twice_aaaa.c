#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *fp_sample = fopen("21_writing_twice.txt", "r");
    if (fp_sample == NULL)
    {
        printf("Failed Null pointer\n");
        exit(1);
    }
    /*********************************fscanf,fprintf*******************************************************************************/
    char fc;
    FILE *fp_out = fopen("21_writing_twice1.txt", "w");
    for (int i = 0; i < 2; i++)
    {
        // while(fscanf(fp_sample,"%c",&c) != EOF)
        while (fscanf(fp_sample, "%c", &fc) == 1)
        {
            // fscanf(fp_sample,"%c",&c);  //no need
            fprintf(fp_out, "%c", fc);
        }
        fprintf(fp_out, "\n");
        fseek(fp_sample, 0, SEEK_SET);
    }
    //fclose(fp_sample);
    fclose(fp_out);
    /********************************************************************************************************************************/
    /***********************************fgetc,fputc**********************************************************************************/
    FILE *fp_out_2=fopen("21_writing_twice2.txt","w");
    char c;
    for(int i=0; i<7; i++)
    {
        /*if i use like this, then   c=fgetc(fp_sample);   should be written again inside the loop

        c=fgetc(fp_sample);
        while(c != EOF)
        {
            //code

            c=fgetc(fp_sample);
        }
        
        */

        while((c = fgetc(fp_sample)) != EOF)   //would be best
        {
            fputc(c,fp_out_2);
            //fprintf(fp_out_2,"%c",c);   // both can be used
        }
        fprintf(fp_out_2, "\n");
        //fputc("\n",fp_out_2); // error,cannot use
        fseek(fp_sample, 0, SEEK_SET);
    }

    fclose(fp_sample);
    fclose(fp_out_2);
    /*************************************************************************************************/
    /*****************************using string - fgets,fputs********************************************************************/
    FILE *fp_sample_backspace = fopen("21_writing_twice_backspaced.txt","r");
    FILE *fp_out_3=fopen("21_writing_twice3.txt","w");
    char str[100];
    fgets(str,100,fp_sample_backspace);
    for(int i=0; i<10; i++)
    {
        fputs(str,fp_out_3);
        //fprintf(fp_out_3,"\n");  
    }
    fclose(fp_out_3);
    return 0;
}
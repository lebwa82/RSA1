#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void key(mpz_t p,mpz_t q,mpz_t e,mpz_t d,mpz_t n)
{
    mpz_t p1,q1,fun;
    mpz_init(p1);
    mpz_init(q1);
    mpz_init(fun);
    mpz_mul(n, p, q);
    mpz_init_set_str(d,"257",10);
    mpz_sub_ui(p1,p,1);
    mpz_sub_ui(q1,q,1);
    mpz_mul(fun, p1, q1);
    mpz_invert(e,d,fun);
    //gmp_printf("d=%Zd n=%Zd\n",d,n);
    //gmp_printf("e=%Zd n=%Zd\n",e,n);
}

void encode(mpz_t e,mpz_t n,char* encode_str,char*output_str)
{
    int x;
    mpz_t k,res;
    mpz_init(k);
    mpz_init(res);
    FILE*input_file=fopen(encode_str,"rb");
    FILE*output_file=fopen(output_str,"wb");
    while(1)
    {
        fread(&x, sizeof(char), 1, input_file);
        //printf("x=%d ",x);
        if(feof(input_file))
        {
            break;
        }
        mpz_set_ui(k,x);
        mpz_powm(res,k,e,n);
        mpz_out_str(output_file,10,res);
        fprintf(output_file," ");
    }
    fclose(input_file);
    fclose(output_file);

}

void decipher(mpz_t d,mpz_t n,char*data,char*output_str)
{
    FILE*data_file=fopen(data,"rb");
    FILE*output_file=fopen(output_str,"wb");
    mpz_t a;
    mpz_init(a);
    mpz_t res;
    mpz_init(res);
    char s[10000];
    int x,i=0;
    while(1)
    {
        fscanf(data_file,"%s",s);
        if(feof(data_file))
        {
            //printf("i=%d\n",i);
            break;
        }
        i++;
        mpz_init_set_str(a,s,10);
        mpz_powm(res,a,d,n);
        x=mpz_get_ui(res);
        fprintf(output_file,"%c",x);
    }
    fclose(data_file);
    fclose(output_file);
}

int main(int argc, char*argv[])
{
    mpz_t p,q,n,d,e,fun,p1,q1;
    mpz_init_set_str(p,argv[4],10);
    mpz_init_set_str(q,argv[5],10);
    mpz_init_set_ui(d,257);
    mpz_init(n);
    mpz_init(e);
    mpz_init(p1);
    mpz_init(q1);
    mpz_init(fun);

    key(p,q,e,d,n);


    char input[]="1.txt";
    //char*input=argv[1];
    char code[]="2.txt";
    //char*code=argv[2];
    char output[]="3.txt";
    //char*output=argv[3];
    encode(e,n,input,code);
    decipher(d,n,code,output);
    FILE*file1=fopen(input,"rb");
    FILE*file2=fopen(output,"rb");
    char x,c;
    int count=0;
    while(feof(file1)==0)
    {
        fread(&x,1,1,file1);
        fread(&c,1,1,file2);
        if(x!=c)
        {
            count++;
           // printf("x=%d c=%d x=%c c=%c\n",x,c,x,c);
        }
    }
    if(count==0)
    {
      printf("all actions were performed correctly\n");
    }




}

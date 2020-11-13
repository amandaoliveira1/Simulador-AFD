#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

    void dadosArquivo(int ***matrizTransicao,int **estadoFinal,int *nEstados,int *estadoInicial,int *nEstadosFinais){

        FILE *arquivo = NULL;

        char nomeArquivo[50], tipo[3], alfabeto[10];
        int  i, j, x, aux;
        char y;
                gets(nomeArquivo);

            printf ("\n                                       ____________________________________________________________________________________ \n");

        arquivo = fopen(nomeArquivo, "r");

        if(arquivo == NULL){
            printf("\n\n                                                             !!! ATENCAO: Arquivo nao encontrado !!!");
            printf("\n                                                      Favor verificar se os dados (nome e extensao do arquivo)\n");
            printf("                                                                  fornecidos estao corretos.\n\n\n\n");
                exit(1);
         }

    // Extrai as informações do arquivo .txt

        fscanf(arquivo, "%s", tipo);
        fscanf(arquivo, "%d", nEstados);

        int	*estados  = (int *)malloc((*nEstados)*sizeof(int));
            if(estados == NULL)
                exit(1);

            for(i=0; i<=(*nEstados); i++){
                fscanf(arquivo, "%d", &aux);
                estados[aux] = aux;
            }

        fscanf(arquivo, "%s", alfabeto);
        fscanf(arquivo, "%d", estadoInicial);
        fscanf(arquivo, "%d", nEstadosFinais);

        int	  *estadosFinais  = (int *)malloc((*nEstadosFinais)*sizeof(int));
            if(estadosFinais == NULL)
                exit(1);

            for(i=0; i<(*nEstadosFinais); i++){
                fscanf(arquivo, "%d", &aux);
                estadosFinais[aux] = aux;
            }

    // Aloca a matriz que irá armazenar as transições

         int **transicao = (int **)malloc((*nEstados)*sizeof(int *));
            if(transicao == NULL)
                exit(1);

                for(i=0; i<(*nEstados); i++){
                    transicao[i] = (int *)malloc(strlen(alfabeto)*sizeof(int));

                        if(transicao[i] == NULL)
                            exit(1);
                }

    //Extrai as transições especificadas no arquivo .txt

            for(i=0; i<(*nEstados); i++){
                for(j=0; j<strlen(alfabeto); j++){
                    fscanf(arquivo, "%i %c %i", &x, &y, &transicao[i][j]);
                }
            }

            (*matrizTransicao) = transicao;
            (*estadoFinal)  = estadosFinais;

                fclose(arquivo);
                free(estados);
    }


    void verificador(int ***matrizTransicao,int **estadoFinal,int *estadoInicial,char palavra[50]){

        FILE *arquivo = NULL;
        int estado, **transicao, *estadosFinais;

        transicao = *matrizTransicao;
        estadosFinais= *estadoFinal;
        estado= (*estadoInicial);

            for (int i=0; i <strlen(palavra); i++)
                estado = transicao[estado][palavra[i] - 'a'];

        // Cria o arquivo texto para gravação e acrescenta novos dados ao final

            arquivo = fopen("saida.txt", "a");
                if (arquivo == NULL)
                    exit(1);

            if(estadosFinais[estado] == estado){
                printf("\n                                                A palavra %s foi ACEITA.", palavra);
                    // Grava no arquivo saida.txt
                    fprintf(arquivo, "%s aceita \n", palavra);
                }

                else{
                    printf("\n                                                A palavra %s foi REJEITADA.", palavra);
                        // Grava no arquivo saida.txt
                        fprintf(arquivo, "%s rejeita \n", palavra);
                }

            fclose(arquivo);
        }

    int main(){

        FILE *arquivo    = NULL;
        int **transicao, *estadosFinais;
        int  i, estadoInicial, nEstados, nEstadosFinais;
        char palavra[50];


            fflush(stdin); //Limpeza do buffer

        printf ("\n\n\n\n\n                                                             ---====  INFORMACOES DO PROJETO  ====---\n\n");
       	printf ("                                                                           Simulador AFD\n\n");
            printf ("                                                Desenvolvido por: \n");
            printf ("                                                Amanda Oliveira Nascimento - 5149\n");
            printf ("                                                Marcos Aurelio Duarte - 5165\n");

        printf ("                                       ____________________________________________________________________________________ \n");
        printf ("\n                                             -===                        SEJA BEM - VINDO(A)!                      ===- \n\n");
        printf ("                                                Insira aqui o nome do seu arquivo (Exemplo: teste.txt): ");

        dadosArquivo(&transicao,&estadosFinais,&nEstados,&estadoInicial,&nEstadosFinais);

            fflush(stdin);

            arquivo = fopen("palavras.txt", "r");

            printf("\n                                                De acordo com os dados contidos no arquivo: \n");

            while (!feof(arquivo)){
                fscanf(arquivo, "%s", palavra);
                verificador(&transicao,&estadosFinais,&estadoInicial,palavra);
            }

            printf ("\n\n                                       ____________________________________________________________________________________ \n\n\n");

            for(i=(nEstados-1); i>=0; i--)
                free(transicao[i]);

            fclose(arquivo);
            free(transicao);
            free(estadosFinais);

            system("Pause");
        }

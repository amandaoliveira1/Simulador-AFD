#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    void menu(char *nomeArquivo){

        FILE *arquivo;

        printf ("\n\n\n\n\n                                                             ---====  INFORMACOES DO PROJETO  ====---\n\n");
       	printf ("                                                                           Simulacao de AFD\n\n");
            printf ("                                                Desenvolvido por: \n");
            printf ("                                                Amanda Oliveira Nascimento - 5149\n");
            printf ("                                                Marcos Aurelio Duarte - 5165\n");

        printf ("                                       ____________________________________________________________________________________ \n");
        printf ("\n                                             -===                        SEJA BEM - VINDO(A)!                      ===- \n\n");
        printf ("                                                Insira aqui o nome do seu arquivo (Exemplo: teste.txt): ");

        gets(nomeArquivo);

             printf ("\n                                       ____________________________________________________________________________________ \n");

    }

    void dadosArquivo(int ***matrizTransicao,int **estadoFinal,int *nEstados,int estInicial,int *nEstadosFinais, char *nomeArquivo){

        FILE *arquivo;

            int tipo[4], i, tamAlfabeto, *estFinais, **transicao, aux1, j, x;
            char str[50], alfabeto[10], aux, y;

            arquivo= fopen(nomeArquivo, "r");

                if(arquivo == NULL){
                    printf("\n\n                                                             !!! ATENCAO: Arquivo nao encontrado !!!");
                    printf("\n                                                      Favor verificar se os dados (nome e extensao do arquivo)\n");
                    printf("                                                                  fornecidos estao corretos.\n\n\n\n");
                        exit(1);
                 }

            // Extrai as informações do arquivo .txt

                fscanf(arquivo, "%s", &tipo);
                    fgets(str, 50, arquivo);

                fscanf(arquivo, "%d", nEstados);
                    fgets(str, 53, arquivo);

                fscanf(arquivo, "%d", &tamAlfabeto);

                    while(i<tamAlfabeto){
                        fscanf(arquivo, "%c", &aux);
                            if(aux != ' '){
                                alfabeto[i]= aux;
                                 i++;
                            }
                     }

                    fgets(str, 50, arquivo);

                fscanf(arquivo, "%d", &estInicial);
                    fgets(str, 50, arquivo);

                fscanf(arquivo, "%d", nEstadosFinais);

                    estFinais  = (int *)malloc((*nEstadosFinais)*sizeof(int));
                        if(estFinais == NULL)
                            exit(1);

                        for(i=0; i<(*nEstadosFinais); i++){
                            fscanf(arquivo, "%d", &aux1);
                            estFinais[aux1] = aux1;
                        }

                    fgets(str, 50, arquivo);

            // Aloca a matriz que irá armazenar as transições

                transicao = (int **)malloc((*nEstados)*sizeof(int *));
                    if(transicao == NULL)
                        exit(1);

                    for(i=0; i<(*nEstados); i++){
                        transicao[i] = (int *)malloc(tamAlfabeto*sizeof(int));
                            if(transicao[i] == NULL)
                            exit(1);
                    }

            //Extrai as transições especificadas no arquivo .txt

                for(i=0; i<(*nEstados); i++){
                    for(j=0; j<tamAlfabeto; j++){
                        fscanf(arquivo, "%i %c %i", &x, &y, &transicao[i][j]);
                        fgets(str, 50, arquivo);
                    }
                }

                (*matrizTransicao) = transicao;
                (*estadoFinal)  = estFinais;

                fclose(arquivo);
        }

    void verificador(int ***matrizTransicao,int **estadoFinal,int *estadoInicial,char palavra[50],int *nEstadosFinais){

        FILE *arquivo = NULL;
        int estado, **transicao, *estadosFinais;

        transicao = *matrizTransicao;
        estadosFinais= *estadoFinal;
        estado= (*estadoInicial);

            for (int i=0; i < strlen(palavra); i++)
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
                int  i, estadoInicial, nEstados, *nEstadosFinais;
                char palavra[50], *nomeArquivo;

                    menu(&nomeArquivo);
                    dadosArquivo(&transicao,&estadosFinais,&nEstados,&estadoInicial,&nEstadosFinais, &nomeArquivo);

                    arquivo = fopen("palavras.txt", "r");

                        printf("\n                                                De acordo com os dados contidos no arquivo: \n");

                            while (!feof(arquivo)){
                                fscanf(arquivo, "%s", palavra);
                                verificador(&transicao,&estadosFinais,&estadoInicial,palavra,&nEstadosFinais);
                            }

                        printf ("\n\n                                       ____________________________________________________________________________________ \n\n\n");


                        for(i=(nEstados-1); i>=0; i--)
                            free(transicao[i]);

                        fclose(arquivo);
                        free(transicao);
                        free(estadosFinais);

            return 0;
        }

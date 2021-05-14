#include <stdio.h>
#include <stdlib.h>

//#include<string.h>

const char* INPUT_FMT = "%5000s";
const int tsize = 5001;

char const *enter_text_encrypted_with = "Enter text that will be encrypted with";
char const *will_be_saved_in = "will be saved in the corresponding file\nat the same with program directory";

void ask_for_character_to_continue()
{
    printf("\nPress any key\n"
           "\n"
           "[Input]: ");
    fflush(stdin);
    getchar();
}

int my_strcmp(char const *first, char const *second)
{
    int i;
    for(i= 0; first[i] != '\0' && second[i] != '\0'; i++)
    {
        if(first[i] < second[i])
            return -1;
        else if(first[i] > second[i])
            return 1;
    }
    return 0;
}

int my_strlen(char const *s)
{
    int i;
    for(i = 0; s[i] != '\0'; i++);
    return i;
}

//string length without counting spaces
//(specifically for vigenere cipher)
int my_strlensp(char const *s)
{
    int i, j= 0;
    for(i = 0; s[i] != '\0'; i++)
        if(s[i] != ' ') j++;
    return j;
}

//
int caesar_shift(char *text, int shft)
{
    char ch;

    for(int i = 0; text[i] != '\0'; ++i)
    {
        ch = text[i];

        if(ch >= 'a' && ch <= 'z')
        {
            if(shft >= 0)
                ch = 'a' + (ch - 'a' + shft)%26;
            else
                ch = 'a' + (ch - 'a' + 26 + shft%26)%26;
        }
        else if(ch >= 'A' && ch <= 'Z')
        {
            if(shft >= 0)
                ch = 'A' + (ch - 'A' + shft)%26;
            else
                ch = 'A' + (ch - 'A' + 26 + shft%26)%26;
        }
        text[i] = ch;
    }
    return 0;
}

int caesar(char *crypt_mode)
{
    char text[tsize], ch;
	int n;

	if(my_strcmp(crypt_mode, "encr") == 0)
    {
        FILE *fptext = fopen("1.1.text.txt", "a");
        //where entered text will be saved
        FILE *fpencr = fopen("1.1.text.encr.txt", "a");
        //where encrypted text will remain

        printf("%s Caesar cipher\n", enter_text_encrypted_with);
        printf("\n[Input]: ");

//        scanf (INPUT_FMT, text);
        gets(text);

        fprintf(fptext, "%s\n", text);
        //saving original text in the corresponding file

        printf("\nEnter shift value (an integer)\n"
               "\n[Input]: ");
        fflush(stdin);
        scanf("%d", &n);

        caesar_shift(text, n);

        printf("\n[Output]: %s\n\nEncrypted text %s", text, will_be_saved_in);

        fprintf(fpencr, "%s\n", text);

        fclose(fptext);
        fclose(fpencr);
    }

    else if(my_strcmp(crypt_mode, "decr") == 0)
    {
        printf("Enter encrypted text\n"
               "\n[Input]: ");
        gets(text);

        FILE *fpencr = fopen("1.2.text.encr.txt", "a");
        fprintf(fpencr, "%s\n", text);
        //for saving encrypted text that in this case could be
        //made not in Caesar cypher method
        int t = 1;
        while(t)
        {
            printf("\nDo you know the shift value of the encrypted text? [y/n]: ");
            fflush(stdin);
            scanf("%c", &ch);
            if(ch == 'n' || ch == 'N')
            {
                printf("\nAll possible decrypted texts: \n\n");

                for(int i = 0; i < 26; i++)
                {
                    caesar_shift(text, 1);
                    printf("%2d. %s - shift value: %2d\n", i + 1, text, 25 - i);
                }

                caesar_shift(text, 1);
                // to make full cycle and return to starting text

                printf("\nEnter the number of correct decryption "
                        "if such exists among all variants\nOr zero if not: ");

                while(1)
                {
                    fflush(stdin);
                    scanf("\n%d", &n);

                    if ( n < 0 || n > 25 ) { printf("Make your choice correctly please: "); continue; }

                    /*
                    while(n < 0 || n > 25)
                    {
                        printf("Make your choice correctly please: ");
                        fflush(stdin);
                        scanf("%d", &n);
                    }*/

                    if(n == 0)
                    {
                        fclose(fpencr);
                        return -1;
                    }

                    caesar_shift(text, n-1);

                    printf("\nIs your choice: \n%d. %s [y/n]: ", n, text);
                    ch = getchar();
                    while( ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')
                    {
                        fflush(stdin);
                        ch = getchar();
                    }
                    if (ch == 'y' || ch == 'Y')
                    {
                        t = 0;
                        break;
                    }
                    else
                    {
                        printf("\nMake your choice: ");
                        caesar_shift(text, (26-n+1) % 26);
                        continue;
                    }
                }
            }
            else if(ch == 'y' || ch == 'Y')
            {
                printf("\nEnter what shift value was used to encrypt following text\n"
                       "\n[Input]: ");
                scanf("%d", &n);

                caesar_shift(text, 26 - n%26);

                printf("\n[Output]: %s\n\nIs this text decrypted? [y/n]: ", text);
                fflush(stdin);
                scanf("%c", &ch);
                if(ch == 'y' || ch == 'Y')
                    break;
                else
                    caesar_shift(text, n%26);
            }
        }

        printf("\nDecrypted text %s", will_be_saved_in);
        FILE *fpdecr = fopen("1.2.text.decr.txt", "a");
        fprintf(fpdecr, "%s\n", text);
        fclose(fpencr);
        fclose(fpdecr);
    }
}

int vigenere_character_add(char *ch, char k, char *crypt_mode)
{
    if(k >= 'a' && k <= 'z')
        k -= 'a';
    else if(k >= 'A' && k <= 'Z')
        k -= 'A';

    if(my_strcmp(crypt_mode, "encr") == 0)
    {
        if(*ch >= 'a' && *ch <= 'z')
            *ch = 'a' + (*ch-'a'+k)%26;
        else if(*ch >= 'A' && *ch <= 'Z')
            *ch = 'A' + (*ch -'A'+k)%26;
        return 0;
    }

    if(my_strcmp(crypt_mode, "decr") == 0)
    {
       if(*ch >= 'a' && *ch <= 'z')
            *ch = 'a' + (*ch - 'a' + 26 - k)%26;
       else if(*ch >= 'A' && *ch <= 'Z')
            *ch = 'A' + (*ch -'A' + 26 - k )%26;
        return 0;
    }
}

/*
int keycorrectness2(char *key)
{
    int status = 0;
    int i, j;

    for(i = 0; key[i] != '\0'; i++)
    {
        char c = key[i];
        if( isspace( c ) ) {
          key[i]

        } else {
            if( !isalpha( c ) ) { status = 1; break };
        }
    }
}*/

int keycorrectness(char *key)
{
    int i, j;

    for(i = 0; key[i] != '\0'; i++)
    {
        if(key[i] == ' ' )
        {
            j = i;
            while(key[j] != '\0')
            {
                key[j] = key[j+1];
                j++;
            }
            i--;
        }
    }

    i = 0;

    while(key[i] != '\0')
    {
        if(!(key[i] >= 'a' && key[i] <= 'z') && !(key[i] >= 'A' && key[i]<= 'Z'))
            return 1;
        i++;
    }
    if(key[0] == '\0')
        return 1;
    return 0;
}

int vigenere(char *text, char *key, char *mode)
{
    if(my_strlensp(text) < my_strlen(key))
        key[my_strlensp(text)] = '\0';
    int i, klength = my_strlen(key);
    int j = 0;

    if(my_strcmp(mode, "encr") == 0)
    {
        for(i = 0; text[i] != '\0'; i++)
        {
            if((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
            {
                vigenere_character_add((text+i), key[j%klength], "encr"); j++;
            }
        }
        return 0;
    }

    else if(my_strcmp(mode, "decr") == 0)
    {
        for(i = 0; text[i] != '\0'; i++)
        {
            if((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
            {
                vigenere_character_add((text+i), key[j%klength], "decr");
                j++;
            }
        }
        return 0;
    }
    return 0;
}


int main()
{
    int ch0, ch1, ch2, ch3;
    int lvl0, lvl1, lvl2, lvl3;
    lvl0 = lvl1 = lvl2 = lvl3 = 1;

    char text[tsize], key[tsize];

    while(lvl0)
    {
        fflush(stdin);
        system("cls");
        printf("Choose your cipher\n"
               "\n"
               "1.Caesar cipher\n"
               "2.Vigenere cipher\n"
               "3.Info\n"
               "4.Exit\n");
        printf("\n[Input]: ");
        fflush(stdin);
        scanf("%d", &ch0);
        switch(ch0)
        {
        case 1:
            lvl1 = 1;
            while(lvl1)
            {
                system("cls");
                printf("Caesar cipher\n"
                       "\n"
                       "1.Encryption mode\n"
                       "2.Decryption mode\n"
                       "3.Info\n"
                       "4.Back\n");
                printf("\n[Input]: ");
                fflush(stdin);
                scanf("%d", &ch1);
                switch(ch1)
                {
                    case 1:
                        system("cls");
                        fflush(stdin);
                        caesar("encr");
                        ask_for_character_to_continue();
                        break;
                    case 2:
                        system("cls");
                        fflush(stdin);
                        caesar("decr");
                        ask_for_character_to_continue();
                        break;
                    case 3:
                        system("cls");
                        printf("Some information about this cipher method\n"
                               "\n"
                               "\n");
                        ask_for_character_to_continue();
                        break;
                    case 4:
                        system("cls");
                        lvl1 = 0;
                        break;
                    default:
                        system("cls");
                        break;
                }
            }
            break;

        case 2:
            lvl2 = 1;
            while(lvl2)
            {
                system("cls");
                printf("Vigenere cipher\n"
                       "\n"
                       "1.Encryption mode\n"
                       "2.Decryption mode\n"
                       "3.Info\n"
                       "4.Back\n");
                printf("\n[Input]: ");
                fflush(stdin);
                scanf("%d", &ch2);
                switch(ch2)
                {
                    case 1:
                        system("cls");
                        printf("%s Vigenere cipher\n", enter_text_encrypted_with);
                        printf("\n[Input]: ");
                        fflush(stdin);
                        gets(text);

                        int tr = 1;

                        while(tr)
                        {
                            printf("\nEnter key string\n");
                            printf("\n[Input]: ");
                            fflush(stdin);
                            gets(key);

                            if(keycorrectness(key) == 1)
                            {
                                printf("\n!Please note: key must contain only letters"
                                       "\n");
                                continue;
                            }
                            tr = 0;
                        }

                        FILE *fptext = fopen("clear_text.txt", "a");
                        FILE *fpencr = fopen("encrypted_text.txt", "a");
                        FILE *fpkey = fopen("key.txt", "a");

                        fprintf(fptext, "%s\n", text);
                        vigenere(text, key, "encr");
                        fprintf(fpencr, "%s\n", text);

                        fprintf(fpkey, "%s\n", key);

                        fclose(fptext);
                        fclose(fpencr);
                        fclose(fpkey);
                        printf("\n[Output]: %s\n\nEncrypted text and key %s", text, will_be_saved_in);
                        ask_for_character_to_continue();
                        break;

                    case 2:
                        system("cls");
                        printf("Enter encrypted text\n"
                                "\n[Input]: ");
                        fflush(stdin);
                        gets(text);
                        FILE *fpencr2 = fopen("2.2text.encr.txt", "a");
                        fprintf(fpencr2, "%s\n", text);
                        int correct = 0;

                        while(!correct)
                        {
                            tr = 1;
                            while(tr)
                            {
                                printf("\nEnter key\n"
                                       "\n[Input]: ");
                                fflush(stdin);
                                gets(key);
                                if(keycorrectness(key))
                                {
                                    printf("\nKey is incorrect. It must contain only letters\n");
                                    continue;
                                }
                                tr = 0;
                            }

                            vigenere(text, key, "decr");
                            printf("\n\n[Output]: %s\n\nIs the text decrypted? [y/n]: ", text);
                            fflush(stdin);
                            char chr;
                            fflush(stdin);
                            scanf("%c", &chr);
                            while(chr != 'n' && chr != 'N' && chr != 'y' && chr != 'Y')
                            {
                                fflush(stdin);
                                printf("\nIs the text decrypted? [y/n]: ");
                                scanf("%c", &chr);
                            }

                            if(chr == 'n' || chr == 'N')
                                vigenere(text, key, "encr");
                            else
                                correct = 1;
                        }

                        FILE *fpdecr2 = fopen("2.2text.decr.txt", "a");
                        FILE *fpkey2 = fopen("2.2key.txt", "a");
                        fprintf(fpdecr2, "%s\n", text);
                        fprintf(fpkey2, "%s\n", key);

                        fclose(fpdecr2);
                        fclose(fpencr2);
                        fclose(fpkey2);
                        printf("\nDecrypted text and key %s", will_be_saved_in);
                        ask_for_character_to_continue();
                        break;

                    case 3:
                        system("cls");
                        printf("Some information about this cipher method\n\n\n");
                        ask_for_character_to_continue();
                        break;
                    case 4:
                        system("cls");
                        lvl2 = 0;
                        break;
                    default:
                        fflush(stdin);
                        system("cls");
                        break;
                }
            }
            break;
        case 3:
            system("cls");
            printf("Some information about the program and how to use it\n"
                   "\n"
                   "\t\t\t- 2021 -"
                   "\n");
            printf("\nPress any key\n\n[Input]: ");
            fflush(stdin);
            getchar();
            break;
        case 4:
            lvl0 = 0;
            break;
        default:
            system("cls");
            break;
        }
    }
	return 0;
}

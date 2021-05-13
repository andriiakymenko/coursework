#include<stdio.h>
#include<stdlib.h>

#define clb(); fflush(stdin);
#define cls(); system("cls");

const int tsize = 5000;

void put(char *s)
{
    printf("\n[%sput]:  ", s);
}

void encrypted(char *s)
{
    printf("Enter text that will be encrypted with %s\n", s);
}

void saved(char *s)
{
    printf("\n**%s will be saved in the corresponding file\nat the same with program directory\n", s);
}

void cntn()
{
    printf("\nPress any key\n");
    put("In");
    clb();
    getchar();
}

int scmp(char const *first, char const *second)
{
    int i, ret;
    for(i= 0; first[i] != '\0' && second[i] != '\0'; i++)
    {
        if(first[i] < second[i])
            return -1;
        else if(first[i] > second[i])
            return 1;
    }
    return 0;
}

int slen(char const *s)
{
    int i;
    for(i = 0; s[i] != '\0'; i++);
    return i;
}

//string length without counting spaces
//(specifically for vigenere cipher)
int slensp(char const *s)
{
    int i, j= 0;
    for(i = 0; s[i] != '\0'; i++)
    {
        if(s[i] != ' ')
            j++;
    }
    return j;
}

int shift(char *text, int shft, char *lang_mode)
{
    char ch;

    if(scmp(lang_mode,"eng") == 0)
    {
        for(int i = 0; text[i] != '\0'; ++i)
        {
            ch = text[i];

            if(ch >= 'a' && ch <= 'z')
                ch = 'a' + (ch - 'a' + shft)%26;

            else if(ch >= 'A' && ch <= 'Z')
                ch = 'A' + (ch - 'A' + shft)%26;

            text[i] = ch;
        }
        return 0;
    }
}

int caesar(char *lang_mode, char *crypt_mode)
{
    char text[tsize], ch;
	int n;

	if(scmp(crypt_mode, "encr") == 0)
    {
        FILE *fptext = fopen("1.1.text.txt", "a");
        //where entered text will be saved
        FILE *fpencr = fopen("1.1.text.encr.txt", "a");
        //where encrypted text will remain

        encrypted("Caesar cipher");
        put("In");
        gets(text);

        fprintf(fptext, "%s\n", text);
        //saving original text in the corresponding file

        printf("\nEnter shift\n");
        clb();
        put("In");
        scanf("%d", &n);

        if(scmp(lang_mode, "eng") == 0)
            shift(text, n, "eng");

        put("Out");
        printf("%s\n", text);

        saved("Encrypted text");

        fprintf(fpencr, "%s\n", text);

        fclose(fptext);
        fclose(fpencr);
    }

    else if(scmp(crypt_mode, "decr") == 0)
    {
        printf("Enter encrypted text\n");
        put("In");
        gets(text);
        int e = !scmp(lang_mode, "eng");

        FILE *fpencr = fopen("1.2.text.encr.txt", "a");
        fprintf(fpencr, "%s\n", text);
        //for saving encrypted text that in this case could be
        //made not in Caesar cypher method
        int t = 1;
        while(t)
        {
            printf("\nDo you know the shift value of the encrypted text? [y/n]: ");
            clb();
            scanf("%c", &ch);
            if(ch == 'n' || ch == 'N')
            {
                printf("\nAll possible decrypted texts: \n\n");

                for(int i = 0; i < 25; i++)
                {
                    if(e)
                        shift(text, 1, "eng");
                    printf("%2d. %s\n", i+1, text);
                }
                if(e)
                    shift(text, 1, "eng");
                // to make full cycle and return to starting text

                printf("\nEnter the number of correct decryption "
                        "if such exists among all variants\nOr zero if not: ");

                while(1)
                {
                    scanf("\n%d", &n);

                    while(n < 0 || n > 25)
                    {
                        printf("Make your choice correctly please: ");
                        scanf("%d", &n);
                        clb();
                    }

                    if(n == 0)
                    {
                        fclose(fpencr);
                        return -1;
                    }

                    if(e)
                        shift(text, n, "eng");

                    printf("\nIs your choice: \n%d. %s [y/n]: ", n, text);
                    ch = getchar();
                    while( ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')
                    {
                        clb();
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
                        if(e) shift(text, (26-n) % 26, "eng");
                        continue;
                    }
                }
            }
            else if(ch == 'y' || ch == 'Y')
            {
                printf("\nEnter what shift value was used to encrypt following text\n");
                put("In");
                scanf("%d", &n);
                if(n >= 0)
                {
                    if(e)
                        shift(text, 26 - n%26, "eng");
                }

                else
                    continue;

                put("Out");
                printf("%s\n", text);
                printf("\nIs this text decrypted? [y/n]: ");
                clb();
                scanf("%c", &ch);
                if(ch == 'y' || ch == 'Y')
                    break;
                else
                {
                    if(e) shift(text, (n)%26, "eng");
                }
            }
        }

        saved("Decrypted text");
        FILE *fpdecr = fopen("1.2.text.decr.txt", "a");
        fprintf(fpdecr, "%s\n", text);
        fclose(fpencr);
        fclose(fpdecr);
    }
}

int cadd(char *ch, char k, char *lang_mode, char *crypt_mode)
{
    if(scmp(lang_mode, "eng") == 0)
    {
        if(k >= 'a' && k <= 'z')
            k -= 'a';
        else if(k >= 'A' && k <= 'Z')
            k -= 'A';

        if(scmp(crypt_mode, "encr") == 0)
        {
            if(*ch >= 'a' && *ch <= 'z')
                *ch = 'a' + (*ch-'a'+k)% ('z' - 'a' + 1);
            else if(*ch >= 'A' && *ch <= 'Z')
                *ch = 'A' + (*ch -'A'+k)%('Z' - 'A' + 1);
            return 0;
        }

        if(scmp(crypt_mode, "decr") == 0)
        {
           if(*ch >= 'a' && *ch <= 'z')
                *ch = 'a' + (*ch - 'a' + 26 - k)%26;
           else if(*ch >= 'A' && *ch <= 'Z')
                *ch = 'A' + (*ch -'A' + 26 - k )%26;
            return 0;
        }
    }
}

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

int vigenere(char *text, char *key, char *lang_mode, char *mode)
{
    int eng = !(scmp(lang_mode, "eng"));

    if(slensp(text) < slen(key))
        key[slensp(text)] = '\0';
    int i, klength = slen(key);
    int j = 0;

    if(scmp(mode, "encr") == 0 && eng)
    {
        for(i = 0; text[i] != '\0'; i++)
        {
            if((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
            {
                cadd((text+i), key[j%klength], "eng", "encr");
                j++;
            }
        }
        return 0;
    }

    else if(scmp(mode, "decr") == 0 && eng)
    {
        for(i = 0; text[i] != '\0'; i++)
        {
            if((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
            {
                cadd((text+i), key[j%klength], "eng", "decr");
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
        cls();
        printf("Choose your cipher\n"
               "\n"
               "1.Caesar cipher\n"
               "2.Vigenere cipher\n"
               "3.Info\n"
               "4.Exit\n");
        put("In");
        clb();
        scanf("%d", &ch0);
        switch(ch0)
        {
        case 1:
            lvl1 = 1;
            while(lvl1)
            {
                cls();
                printf("Caesar cipher\n"
                       "\n"
                       "1.Encryption mode\n"
                       "2.Decryption mode\n"
                       "3.Info\n"
                       "4.Back\n");
                put("In");
                clb();
                scanf("%d", &ch1);
                switch(ch1)
                {
                    case 1:
                        cls();
                        clb();
                        caesar("eng", "encr");
                        cntn();
                        break;
                    case 2:
                        cls();
                        clb();
                        caesar("eng", "decr");
                        cntn();
                        break;
                    case 3:
                        cls();
                        printf("Some information about this cipher method\n"
                               "\n"
                               "\n");
                        cntn();
                        break;
                    case 4:
                        cls();
                        lvl1 = 0;
                        break;
                    default:
                        cls();
                        break;
                }
            }
            break;

        case 2:
            lvl2 = 1;
            while(lvl2)
            {
                cls();
                printf("Vigenere cipher\n"
                       "\n"
                       "1.Encryption mode\n"
                       "2.Decryption mode\n"
                       "3.Info\n"
                       "4.Back\n");
                put("In");
                clb();
                scanf("%d", &ch2);
                switch(ch2)
                {
                    case 1:
                        cls();
                        encrypted("Vigenere cipher");
                        put("In");
                        clb();
                        gets(text);

                        int tr = 1;

                        while(tr)
                        {
                            printf("\nEnter key string\n");
                            put("In");
                            clb();
                            gets(key);

                            if(keycorrectness(key) == 1)
                            {
                                printf("\n!Please note: key must contain only letters"
                                       "\n");
                                continue;
                            }
                            tr = 0;
                        }

                        FILE *fptext = fopen("2.1.text.txt", "a");
                        FILE *fpencr = fopen("2.1.text.encr.txt", "a");
                        FILE *fpkey = fopen("2.1.key.txt", "a");

                        fprintf(fptext, "%s\n", text);
                        vigenere(text, key, "eng", "encr");
                        fprintf(fpencr, "%s\n", text);

                        fprintf(fpkey, "%s\n", key);

                        fclose(fptext);
                        fclose(fpencr);
                        fclose(fpkey);
                        put("Out");
                        printf("%s\n", text);
                        saved("Encrypted text and key");
                        cntn();

                        break;

                    case 2:
                        cls();
                        printf("Enter encrypted text\n");
                        put("In");
                        clb();
                        gets(text);
                        FILE *fpencr2 = fopen("2.2text.encr.txt", "a");
                        fprintf(fpencr2, "%s\n", text);
                        int correct = 0;

                        while(!correct)
                        {
                            tr = 1;
                            while(tr)
                            {
                                printf("\nEnter key\n");
                                put("In");
                                clb();
                                gets(key);
                                if(keycorrectness(key))
                                {
                                    printf("\nKey is incorrect. It must contain only letters\n");
                                    continue;
                                }

                                tr = 0;
                            }

                            vigenere(text, key, "eng", "decr");
                            printf("\n\n");
                            put("Out");
                            printf("%s\n", text);
                            printf("\nIs the text decrypted? [y/n]: ");
                            clb();
                            char chr;
                            clb();
                            scanf("%c", &chr);
                            while(chr != 'n' && chr != 'N' && chr != 'y' && chr != 'Y')
                            {
                                clb();
                                printf("\nIs the text decrypted? [y/n]: ");
                                scanf("%c", &chr);
                            }

                            if(chr == 'n' || chr == 'N')
                                vigenere(text, key, "eng", "encr");
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
                        saved("Encrypted text and key");
                        cntn();

                        break;

                    case 3:
                        cls();
                        printf("Some information about this cipher method\n"
                               "\n"
                               "\n");
                        printf("\nPress any key\n");
                        put("In");
                        clb();
                        getchar();
                        break;
                    case 4:
                        cls();
                        lvl2 = 0;
                        break;
                    default:
                        clb();
                        cls();
                        break;
                }
            }
            break;
        case 3:
            cls();
            printf("Some information about the program and how to use it\n"
                   "\n"
                   "\t\t\t- 2021 -"
                   "\n");
            printf("\nPress any key\n");
            put("In");
            clb();
            getchar();
            break;
        case 4:
            lvl0 = 0;
            break;
        default:
            cls();
            break;
        }
    }
	return 0;
}

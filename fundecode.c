#include <stdio.h>//this program decodes (caesar and backwards) encrypted text
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char caesar(string s, int i, int c);
bool check_word(string s);
void first_word(string s);
void backwards(string s);

int main(void)
{
    string text = get_string("Text: \n");
    int length = strlen(text);
    bool deciphered = false;
    char decypher[length];//this is the string that goes through the caesar keys
    char word[length];//will be used only for the first word, hence why it is called word
    string back = text;
    for (int c = 0; c < 26; c++)//repeats for each decode 'key' that can be used with caesar
    {
        for (int i = 0; i < length + 1; i++)//repeats for each char in string
        {
            decypher[i] = caesar(text, i, c);
            word[i] = decypher[i];
        }

        first_word(word);//makes word, the string, into its first word to be checked with the checkword function
        if (check_word(word) == true)//if the word is a word
        {
            printf("%s\n", decypher);
            deciphered = true;
        }
    }
    backwards(back);//makes the word into backwards form, so if it is backwards it will restore the word to the original form.
    string firstback = back;
    first_word(firstback);
    if (check_word(firstback) == true)//if the word is a word
    {
        printf("%s\n", back);
        deciphered = true;
    }
    if (deciphered == false)//if the word is not a word
    {
        printf("This is not a word in caesar or backwards.");
    }
}

char caesar(string s, int i, int c)//this function changes each char by the caesar "key" that is inputted
{
    char new = 'a';
    if (s[i] >= 65 && s[i] <= 90)//if it is between A(65) and Z(90)
    {
        new = ((int)s[i] - 65 + c) % 26 + 97;
    }
    else if (s[i] >= 97 && s[i] <= 122) //if it is between a(97) and z(122)
    {
        new = ((int)s[i] - 97 + c) % 26 + 97;
    }
    else if (isalpha(s[i]) == 0)//if it is not a letter, then it remains the same
    {
        new = s[i];
    }
    return new;
}

bool check_word(string s)
{
    int count = 25323;//length of popular.txt file
    int max_length = 20;
    FILE *fp;
    char str[max_length];
    char words[count][max_length];
    fp = fopen("popular.txt", "r");

    for (int i = 0; i < count; i++) //for all words of popular.txt
    {
        fgets(str, 20, fp);
        strcpy(words[i], strtok(str, "\n"));
        if (strcmp(words[i], s) == 0)//if the input matches the set of words
        {
            return true;//then clearly it must be a word
        }
    }
    fclose(fp);
    return false;
}

void first_word(string s) //This function gets the first word of the string input
//This is then used with check_word in the main code
{
    int i = 0;
    char first_word[20];
    while (isalpha(s[i]) != 0) //while the string is made of letters
    {
        first_word[i] = s[i];
        i++;
    }
    sprintf(s, "%s", first_word);
}

void backwards(string s)
{
    int len = strlen(s);
    char temp[len];
    for( int k = 0; k < len +1; k++)
    {
        temp[k] = s[k];
    }
    for( int i = 0; i < len; i++)
    {
        temp[i] = s[len-i-1];
    }
    sprintf(s, "%s", temp);
}

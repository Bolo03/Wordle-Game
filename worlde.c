#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void show_title()
{
   int a[7][42] = {{201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187},
                      {186,  32, 219,  32,  32,  32,  32,  32, 219,  32, 219, 219, 219, 219, 219, 219,  32, 219, 219, 219, 219,  32,  32, 219, 219, 219, 219,  32,  32, 219,  32,  32,  32,  32,  32, 219, 219, 219, 219, 219,  32, 186},
                      {186,  32, 219,  32,  32,  32,  32,  32, 219,  32, 219,  32,  32,  32,  32, 219,  32, 219,  32,  32,  32, 219,  32, 219,  32,  32,  32, 219,  32, 219,  32,  32,  32,  32,  32, 219,  32,  32,  32,  32,  32, 186},
                      {186,  32, 219,  32,  32, 219,  32,  32, 219,  32, 219,  32,  32,  32,  32, 219,  32, 219, 219, 219, 219,  32,  32, 219,  32,  32,  32, 219,  32, 219,  32,  32,  32,  32,  32, 219, 219, 219, 219,  32,  32, 186},
                      {186,  32, 219,  32,  32, 219,  32,  32, 219,  32, 219,  32,  32,  32,  32, 219,  32, 219,  32,  32,  32, 219,  32, 219,  32,  32,  32, 219,  32, 219,  32,  32,  32,  32,  32, 219,  32,  32,  32,  32,  32, 186},
                      {186,  32,  32, 219, 219,  32, 219, 219,  32,  32, 219, 219, 219, 219, 219, 219,  32, 219,  32,  32,  32, 219,  32, 219, 219, 219, 219,  32,  32, 219, 219, 219, 219, 219,  32, 219, 219, 219, 219, 219,  32, 186},
                      {200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188}};
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
  for(int i = 0; i < 7; i++)
  {
    for(int j = 0; j < 42; j++)
    {
      printf("%c", a[i][j]);
    }
  printf("\n");
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  printf("\n");
}

int is_letter_in_word(char letter, char *word)
{
  int ok = 0;
  for(int i = 0; i < 6; i++)
  {
    if(letter == word[i])
    {
      ok = 1;
      break;
    }
  }
  return ok;

}

void show_words(char list[][6], char *word)
{
  for(int i = 0; i < 6; i++)
  {
    printf("\t\t");
    for(int j = 0; j < 5; j++)
    {
      if(is_letter_in_word(list[i][j], word))
      {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        if(list[i][j] == word[j])
        {
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        }
      }
      printf("%c ", list[i][j]);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
  printf("\n");
  }
}

int verify_word_in_file(char *input, FILE *f)
{
  char file_word[6];
  int ok = 0;

  while(!feof(f))
  {
    fscanf(f, "%s", file_word);
    if(strcmp(file_word, input) == 0)
    {
      ok = 1;
      break;
    }
  }
  fseek(f, 0, SEEK_SET);
  return ok;
}

int main()
{
  FILE *f;
  if((f = fopen("text.txt", "rt")) == NULL)
  {
    printf("Teapa!");
    exit(1);
  }
 
  char input[6], word_list[6][6] ={{'_', '_', '_', '_', '_', '_'},
                                   {'_', '_', '_', '_', '_', '_'},
                                   {'_', '_', '_', '_', '_', '_'},
                                   {'_', '_', '_', '_', '_', '_'},
                                   {'_', '_', '_', '_', '_', '_'},
                                   {'_', '_', '_', '_', '_', '_'}};
  int i;

  //read a random word from text.txt
  srand(time(NULL));
  int word_nr = rand() % 500;
  char word[6];

  fseek(f, (word_nr - 1) * sizeof(word), SEEK_SET);
  fscanf(f, "%s", word);
  fseek(f, 0, SEEK_SET);

  show_title();
  printf(">> Press ENTER to Start the Game <<\n");
  getchar();

  
  for(i = 0; i < 7; i++)
  {
    system("cls");
    show_title();

    show_words(word_list, word);
    printf("\n");

    if(strcmp(word, input) == 0)
    {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
      printf("GG!\n");
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
      Sleep(3000);
      break;
    }

     if(i == 6)
      {
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
          printf("Game over!\n");
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
          printf("The word was %s.", word);
          Sleep(3000);
          break;
      }

    printf("Insert your word here: ");
    scanf("%s", input);
    strcpy(input, strlwr(input));
    
    if(verify_word_in_file(input, f))
    {
      for(int j = 0; j < 6; j++)
      {
        word_list[i][j] = input[j];
      }
    }
    else
    {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
      printf("Invalid word!\n");
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
      i--;
      Sleep(1000);
    }
  }

  return 0;
}
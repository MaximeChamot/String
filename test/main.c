#include <stdio.h>
#include "string.h"

int		main()
{
  char		toto[5] = "toto";
  char		titi[5] = "titi";
  char		test[5] = "test";
  char		tititototiti[13] = "tititototiti";
  char		azerty[7] = "azerty";
  char		buf[100] = "";
  char		**tab;
  char		str[20] = "tata,tete,titi";
  struct String	*sStrings;
  size_t	i = 0;

  String	s1;
  String	s2;

  // Constructor  
  StringInit(&s1, toto);
  StringInit(&s2, titi);
  
  // assign_s
  printf("--- assign_s ---\n");
  s1.assign_s(&s1, &s2);
  printf("s2 : %s | s1 : %s\n", s2.c_str(&s2), s1.c_str(&s1));
  s1.assign_c(&s1, toto);
  printf("\n");

  // assign_c
  printf("--- assign_c ---\n");
  s1.assign_c(&s1, azerty);
  printf("%s | s1 : %s\n", azerty, s1.c_str(&s1));
  s1.assign_c(&s1, toto);
  printf("\n");

  // append_s
  printf("--- append_s ---\n");
  s1.append_s(&s1, &s2);
  printf("tototiti | s1 : %s\n", s1.c_str(&s1));
  s1.assign_c(&s1, toto);
  printf("\n");

  // append_s
  printf("--- append_c ---\n");
  s1.append_c(&s1, azerty);
  printf("totoazerty | s1 : %s\n", s1.c_str(&s1));
  s1.assign_c(&s1, toto);
  printf("\n");

  // at
  printf("--- at ---\n");
  printf("t | s1 : %c\n", s1.at(&s1, 3));
  printf("o | s1 : %c\n", s1.at(&s1, 2));
  printf("-1 | s1 : %d\n", s1.at(&s1, 30));
  printf("-1 | s1 : %d\n", s1.at(&s1, -30));
  printf("\n");

  // clear
  printf("--- clear ---\n");
  s1.clear(&s1);
  printf("[] | s1 : [%s]\n", s1.c_str(&s1));
  s1.assign_c(&s1, toto);
  printf("\n");

  // size
  printf("--- size ---\n");
  printf("4 | s1 : %d\n", s1.size(&s1));
  printf("\n");

  // compare_s
  printf("--- compare_s ---\n");
  s1.assign_s(&s1, &s2);
  printf("0 | s1 : %d\n", s1.compare_s(&s1, &s2));
  s1.assign_c(&s1, toto);
  printf("\n");

  // compare_c
  printf("--- compare_c ---\n");
  printf("0 | s1 : %d\n", s1.compare_c(&s1, toto));
  printf("19 | s1 : %d\n", s1.compare_c(&s1, azerty));
  printf("10 | s1 : %d\n", s1.compare_c(&s1, test));
  printf("\n");
  
  // copy
  printf("--- copy ---\n");
  s1.assign_c(&s1, azerty);
  s1.copy(&s1, buf, 4, 0);
  printf("azer | %s\n", buf);
  s1.copy(&s1, buf, 4, 1);
  printf("zert | %s\n", buf);
  s1.copy(&s1, buf, 10, 5);
  printf("y | %s\n", buf);
  s1.assign_c(&s1, toto);
  printf("\n");
  
  // c_str
  printf("--- c_str ---\n");
  printf("toto | s1 : %s\n", s1.c_str(&s1));
  printf("titi | s2 : %s\n", s2.c_str(&s2));
  printf("\n");

  // empty
  printf("--- empty ---\n");
  printf("-1 | s1 : %d\n", s1.empty(&s1));
  s1.clear(&s1);
  printf("1 | s1 : %d\n", s1.empty(&s1));
  s1.assign_c(&s1, toto);
  printf("\n");

  // find_s
  printf("--- find_s ---\n");
  s2.assign_c(&s2, tititototiti);
  printf("4 | s2 : %d\n", s2.find_s(&s2, &s1, 0));
  printf("4 | s2 : %d\n", s2.find_s(&s2, &s1, 4));
  printf("-1 | s2 : %d\n", s2.find_s(&s2, &s1, 6));
  s1.assign_c(&s1, toto);
  s2.assign_c(&s2, titi);
  printf("\n");

  // find_c
  printf("--- find_c ---\n");
  printf("0 | s1 : %d\n", s1.find_c(&s1, toto, 0));
  printf("-1 | s1 : %d\n", s1.find_c(&s1, titi, 0));
  printf("\n");

  // insert_s
  printf("--- insert_s ---\n");
  s1.insert_s(&s1, 2, &s2);
  printf("totitito | s1 : %s\n", s1.c_str(&s1));
  s1.assign_c(&s1, toto);
  s2.assign_c(&s2, titi);
  printf("\n");

  // insert_c
  printf("--- insert_c ---\n");
  s1.insert_c(&s1, 1, azerty);
  printf("tazertyoto | s1 : %s\n", s1.c_str(&s1));
  s1.insert_c(&s1, 100, azerty);
  printf("tazertyotoazerty | s1 : %s\n", s1.c_str(&s1));
  s1.assign_c(&s1, toto);
  s2.assign_c(&s2, titi);
  printf("\n");

  // split_s
  printf("--- split_s ---\n");
  s1.assign_c(&s1, str);
  sStrings = s1.split_s(&s1, ',');
  i = 0;
  while (sStrings[i].empty(&sStrings[i]) == -1)
    {
      printf("%s\n", sStrings[i].s);
      i += 1;
    }
  s1.assign_c(&s1, toto);
  printf("\n");

  // split_c
  printf("--- split_c ---\n");
  s1.assign_c(&s1, str);
  tab = s1.split_c(&s1, ',');
  while (tab != NULL && *tab)
    {
      printf("%s\n", *tab);
      tab += 1;
    }
  s1.assign_c(&s1, toto);
  printf("\n");

  // aff
  printf("--- aff ---\n");
  s1.aff(&s1);
  printf("\n");
  s1.assign_c(&s1, toto);
  printf("\n");

  // join_s
  printf("--- join_s ---\n");
  s1.join_s(&s1, ',', sStrings);
  printf("[toto,tata,tete,titi] | [%s]\n", s1.s);
  printf("\n");

  // substr
  printf("--- substr ---\n");
  sStrings = s1.substr(&s1, 5, 4);
  printf("tata | %s\n", sStrings->c_str(sStrings));
  printf("\n");  

  // Destructor
  StringDestroy(&s1);
  StringDestroy(&s2);
  
  return (0);
}

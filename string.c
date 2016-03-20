#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"

/* Methods declaration */
static void		assign_s(struct String *this, struct String const *s);
static void		assign_c(struct String *this, char const *s);
static void		append_s(struct String *this, struct String const *ap);
static void		append_c(struct String *this, char const *ap);
static char		at(struct String *this, size_t pos);
static void		clear(struct String *this);
static int		size(struct String *this);
static int		compare_s(struct String *this, struct String const *s);
static int		compare_c(struct String *this, char const *s);
static size_t		copy(String *this, char *s, size_t n, size_t pos);
static char const *	c_str(struct String *this);
static int		empty(struct String *this);
static int		find_s(struct String *this, struct String const *str, size_t pos);
static int		find_c(struct String *this, char const *str, size_t pos);
static void		insert_s(struct String *this, size_t pos, struct String const *str);
static void		insert_c(struct String *this, size_t pos, char const *str);
static int		to_int(struct String *this);
static struct String *	split_s(struct String *this, char separator);
static char **		split_c(struct String *this, char separator);
static void		aff(struct String *this);
static void		join_s(struct String *this, char delim, struct String *tab);
static void		join_c(struct String *this, char delim, char const **tab);
struct String *		substr(struct String *this, int offset, int length);

/* Internal functions */
static void		initMethodPtr(struct String *this);
static size_t		countTokens(char *s, char separator);

/* Constructor */
void			StringInit(String *this, char const *s)
{
  if (this != NULL)
    {
      if (s != NULL)
	{
	  this->len = strlen(s);
	  this->s = strndup(s, this->len);
	}
      else
	{
	  this->len = 0;
	  this->s = NULL;
	}
      initMethodPtr(this);
    }
}

static void		initMethodPtr(struct String *this)
{
  this->assign_s = &assign_s;
  this->assign_c = &assign_c;
  this->append_s = &append_s;
  this->append_c = &append_c;
  this->at = &at;
  this->clear = &clear;
  this->size = &size;
  this->compare_s = &compare_s;
  this->compare_c = &compare_c;
  this->copy = &copy;
  this->c_str = &c_str;
  this->empty = &empty;
  this->find_s = &find_s;
  this->find_c = &find_c;
  this->insert_s = &insert_s;
  this->insert_c = &insert_c;
  this->to_int = &to_int;
  this->split_s = &split_s;
  this->split_c = &split_c;
  this->aff = &aff;
  this->join_s = &join_s;
  this->join_c = &join_c;
  this->substr = &substr;
}

struct String *		NewString(char const *s)
{
  struct String *	newString = NULL;

  if ((newString = malloc(sizeof(struct String))) != NULL)
    StringInit(newString, s);
  return (newString);
}

/* Destructor */
void			StringDestroy(struct String *this)
{
  if (this != NULL)
    {
      if (this->s != NULL)
	{
	  free(this->s);
	  this->s = NULL;
	}
      this->len = 0;
    }
}

/* Methods body */
static void		assign_s(struct String *this, struct String const *s)
{
  assign_c(this, s->s);
}

static void		assign_c(struct String *this, char const *s)
{
  StringDestroy(this);
  StringInit(this, s);
}

static void		append_s(struct String *this, struct String const *ap)
{
  append_c(this, ap->s);
}

static void		append_c(struct String *this, char const *ap)
{
  char			*newString = NULL;

  if (ap != NULL && (newString = malloc(sizeof(char) * (this->len + strlen(ap) + 1))) != NULL)
    {
      strcpy(newString, this->s);
      strcat(newString, ap);
      StringDestroy(this);
      StringInit(this, newString);
      free(newString);
    }
}

static char		at(struct String *this, size_t pos)
{
  char			c = -1;

  if (this->s != NULL && pos < this->len)
    c = this->s[pos - 1];
  return (c);
}

static void		clear(struct String *this)
{
  if (this->s != NULL)
    {
      memset(this->s, '\0', this->len);
      this->len = 0;
    }
}

static int		size(struct String *this)
{
  return (this->len);
}

static int		compare_s(struct String *this, struct String const *s)
{
  return (compare_c(this, s->s));
}

static int		compare_c(struct String *this, char const *s)
{
  return (strcmp(this->s, s));
}

static size_t		copy(struct String *this, char *s, size_t n, size_t pos)
{
  size_t		i = 0;

  while (this->s != NULL && s != NULL && pos < this->len && this->s[pos + i] != '\0' && i < n)
    {
      s[i] = this->s[pos + i];
      i += 1;
    }
  s[i] = '\0';
  return (i);
}

static char const *	c_str(struct String *this)
{
  return (this->s);
}

static int		empty(struct String *this)
{
  int			res = 1;

  if (this->s != NULL && this->len > 0)
    res = -1;
  return (res);
}

static int		find_s(struct String *this, struct String const *str, size_t pos)
{
  return (find_c(this, str->s, pos));
}

static int		find_c(struct String *this, char const *str, size_t pos)
{
  int			n = -1;
  char			*p = NULL;

  if (this->s != NULL && str != NULL && pos < this->len && (p = strstr(&this->s[pos], str)) != NULL)
    n = p - this->s;
  return (n);
}

static void		insert_s(struct String *this, size_t pos, struct String const *str)
{
  insert_c(this, pos, str->s);
}

static void		insert_c(struct String *this, size_t pos, char const *str)
{
  char			*newString = NULL;

  if (str != NULL && (newString = malloc(sizeof(char) * (this->len + strlen(str) + 1))) != NULL)
    {
      if (pos >= this->len)
	append_c(this, str);
      else
	{
	  strncpy(newString, this->s, pos);
    	  strcat(newString, str);
	  strcat(newString, &this->s[pos]);
	  StringDestroy(this);
	  StringInit(this, newString);	  
	  free(newString);
	}
    }
}

static int		to_int(struct String *this)
{
  return (atoi(this->s));
}

static struct String *	split_s(struct String *this, char separator)
{
  struct String		*tab = NULL;
  char			**tokens = NULL;
  size_t		n = 0;

  tokens = split_c(this, separator);
  n = countTokens(this->s, separator);
  if (tokens != NULL && n > 0 && (tab = malloc(sizeof(struct String) * (n + 1))) != NULL)
    {
      n = 0;
      while (tokens[n] != '\0')
      	{
      	  StringInit(&tab[n], tokens[n]);
 	  n += 1;
      	}
      StringInit(&tab[n], NULL);
    }
  return (tab);
}

static char **		split_c(struct String *this, char separator)
{
  char			**tab = NULL;
  char			*token = NULL;
  char			*ptr;
  int			n = 0;

  if (this->empty(this) == -1)
    {
      n = countTokens(this->s, separator);
      if (n > 0 && (tab = malloc(sizeof(char *) * (n + 1))) != NULL)
      	{
      	  n = 0;
      	  ptr = strndup(this->s, strlen(this->s));
      	  token = strtok(ptr, &separator);
      	  while (token != NULL)
      	    {
      	      tab[n] = token;
      	      n += 1;
      	      token = strtok(NULL, &separator);
      	    }
      	  tab[n] = '\0';
      	}
    }
  return (tab);
}

static void		aff(struct String *this)
{
  write(STDOUT_FILENO, this->s, this->len);
}

static void		join_s(struct String *this, char delim, struct String *tab)
{
  char const		**tmp = NULL;
  size_t		i = 0;

  if (tab != NULL)
    {
      while (tab[i].empty(&tab[i]) == -1)
	i += 1;
      if ((tmp = malloc(sizeof(char *) * (i + 1))) != NULL)
	{
	  i = 0;
	  while (tab[i].empty(&tab[i]) == -1)
	    {
	      tmp[i] = tab[i].c_str(&tab[i]);
	      i += 1;
	    }
	  join_c(this, delim, tmp);
	  free(tmp);
	}
    }
}

static void		join_c(struct String *this, char delim, char const **tab)
{
  char			*newString = NULL;
  size_t		len = 0;
  size_t		i = 0;

  if (tab != NULL)
    {
      len = this->size(this);
      while (tab[i] != '\0')
  	{
  	  len += (strlen(tab[i]) + 1);
  	  i += 1;
  	}
      if ((newString = malloc(sizeof(char) * len)) != NULL)
  	{
	  strcpy(newString, this->s);
  	  i = 0;
  	  while (tab[i] != '\0')
  	    {
	      len = strlen(newString);
	      newString[len] = delim;
	      strcat(newString, tab[i]);
  	      i += 1;
  	    }
	  StringDestroy(this);
    	  StringInit(this, newString);
	  free(newString);
    	}
    }
}

struct String *		substr(struct String *this, int offset, int length)
{
  struct String		*newString = NULL;
  char			*tmp = NULL;
  
  if (offset < 0)
    offset = this->len + offset;
  if (length < 0)
    {
      if (offset + length > 0)
	offset += length;
      else
	offset = 0;
      length *= -1;
    }
  tmp = strndup(&this->s[offset], length);
  newString = NewString(tmp);
  if (tmp != NULL)
    free(tmp);
  return (newString);
}

/* Internal functions */
static size_t		countTokens(char *s, char separator)
{
  size_t		n = 0;

  if (s != NULL)
    {
      n += 1;
      while ((s = strchr(s, separator)) != NULL)
	{
	  s += 1;
	  n += 1;
	}
    }
  return (n);
}

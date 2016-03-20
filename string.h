#ifndef _STRING_H_
# define _STRING_H_

typedef struct		String
{
  /* Properties */
  char			*s;
  size_t		len;

  /* Methods */
  void			(*assign_s)(struct String *this, struct String const *s);
  void			(*assign_c)(struct String *this, char const *s);
  void			(*append_s)(struct String *this, struct String const *ap);
  void			(*append_c)(struct String *this, char const *ap);
  char			(*at)(struct String *this, size_t pos);
  void			(*clear)(struct String *this);
  int			(*size)(struct String *this);
  int			(*compare_s)(struct String *this, struct String const *s);
  int			(*compare_c)(struct String *this, char const *s);
  size_t		(*copy)(struct String *this, char *s, size_t n, size_t pos);
  char const *		(*c_str)(struct String *this);
  int			(*empty)(struct String *this);
  int			(*find_s)(struct String *this, struct String const *str, size_t pos);
  int			(*find_c)(struct String *this, char const *str, size_t pos);
  void			(*insert_s)(struct String *this, size_t pos, struct String const *str);
  void			(*insert_c)(struct String *this, size_t pos, char const *str);
  int			(*to_int)(struct String *this);
  struct String *	(*split_s)(struct String *this, char separator);
  char **		(*split_c)(struct String *this, char separator);
  void			(*aff)(struct String *this);
  void			(*join_s)(struct String *this, char delim, struct String *tab);
  void			(*join_c)(struct String *this, char delim, char const **tab);
  struct String *	(*substr)(struct String *this, int offset, int length);
}			String;

void			StringInit(struct String *this, char const *s);
struct String *		NewString(char const *s);
void			StringDestroy(struct String *this);

#endif /* _STRING_H_ */

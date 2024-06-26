#ifndef ATOM_H
#define ATOM_H

const char *atom_string(char *str);
const char *atom_int   (long n);
const char *atom_create(char *str, int len);
int         atom_length(const char *str);

#endif // ATOM_H

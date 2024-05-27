#ifndef SLUGIFY_H
#define SLUGIFY_H

#include <stdbool.h>
#include <wchar.h>

#define DEFAULT_REMOVE L"$*_+~.()\"'!?-:@"
#define MAX_BUFFER_SIZE 1024
#define MAX_CHAR_MAP 1024
#define MAX_LOCALE_MAP 128
#define MAX_LOCALES 16

typedef struct {
  const wchar_t key;
  const char *value;
} CharMapEntry;

typedef struct {
  const char *locale;
  CharMapEntry entries[MAX_LOCALE_MAP];
  int size;
} Locale;

typedef struct {
  char replacement;
  const wchar_t *remove;
  bool lower;
  bool strict;
  const char *locale;
  bool trim;
} SlugifyOptions;

void slugify(const wchar_t *input, char *output, const SlugifyOptions *options);

#endif // SLUGIFY_H

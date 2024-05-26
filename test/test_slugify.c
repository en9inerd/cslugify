#include "../cslugify.h"
#include <stdio.h>

int main() {
  wchar_t input[] = L"Hello, World!";
  char output[50];
  SlugifyOptions options = {L'-', NULL, 1, 0, NULL, 1};

  slugify(input, output, &options);

  printf("Slugified: %s\n", output);
  return 0;
}

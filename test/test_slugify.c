#include "../cslugify.h"
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#define TEST_BUFFER_SIZE 1024

void test_slugify(const wchar_t *input, const char *expected_output,
                  const SlugifyOptions *options) {
  char output[TEST_BUFFER_SIZE];
  slugify(input, output, options);
  if (strcmp(output, expected_output) == 0) {
    printf("Test passed: '%ls' -> '%s'\n", input, output);
  } else {
    printf("Test failed: '%ls' -> '%s' (expected: '%s')\n", input, output,
           expected_output);
  }
}

int main() {
  // Set locale to support wide characters
  setlocale(LC_ALL, "");

  SlugifyOptions default_options = {'-', NULL, 1, 0, NULL, 1};

  test_slugify(L"Hello World", "hello-world", &default_options);
  test_slugify(L"  Leading and trailing spaces  ",
               "leading-and-trailing-spaces", &default_options);
  test_slugify(L"Special $ & chars", "special-dollar-and-chars",
               &default_options);
  test_slugify(L"Multilingüe Ñandú", "multilingue-nandu", &default_options);

  // it's still failing
  SlugifyOptions no_trim_options = {'-', NULL, 1, 0, NULL, 0};
  test_slugify(L"  No trim  ", "-no-trim-", &no_trim_options);

  SlugifyOptions no_lower_options = {'-', NULL, 0, 0, NULL, 1};
  test_slugify(L"Hello World", "Hello-World", &no_lower_options);

  SlugifyOptions custom_replacement_options = {'_', NULL, 1, 0, NULL, 1};
  test_slugify(L"Hello World", "hello_world", &custom_replacement_options);

  SlugifyOptions strict_options = {'-', NULL, 1, 1, NULL, 1};
  test_slugify(L"Hello! World?", "hello-world", &strict_options);

  SlugifyOptions remove_options = {'-', L"o", 1, 0, NULL, 1};
  test_slugify(L"Hello World", "hell-wrld", &remove_options);

  SlugifyOptions locale_fr_options = {'-', NULL, 1, 0, "fr", 1};
  test_slugify(L"5% & < > | ¢ £ ¤ ₣ ∑ ∞ ♥",
               "5pourcent-et-plus-petit-plus-grand-ou-centime-livre-devise-"
               "franc-somme-infini-amour",
               &locale_fr_options);

  SlugifyOptions locale_bg_options = {'-', NULL, 1, 0, "bg", 1};
  test_slugify(L"Й Ц Щ Ъ Ь й ц щ ъ ь", "y-ts-sht-a-y-y-ts-sht-a-y",
               &locale_bg_options);

  SlugifyOptions locale_vi_options = {'-', NULL, 1, 0, "vi", 1};
  test_slugify(L"Đây là tiếng Việt", "day-la-tieng-viet", &locale_vi_options);

  return 0;
}

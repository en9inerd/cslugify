# CSlugify

CSlugify is a simple slugifier implemented in C. It converts input strings into URL-friendly slugs.

## Features

- UTF-8 support
- Character and locale-specific mappings
- Customizable replacement characters
- Options for case conversion, strict alphanumeric filtering, and trimming
- Support for removal of unwanted characters

## Usage

```c
#include <stdio.h>
#include "cslugify.h"

int main() {
  const wchar_t *input = L"Hello, World!";
  char output[MAX_BUFFER_SIZE];
  SlugifyOptions options = {
                            .replacement = '-',
                            .remove = L"$*_+~.()\"'!?-:@",
                            .lower = true,
                            .strict = true,
                            .locale = NULL,
                            .trim = true
                          };
  slugify(input, output, &options);
  printf("%s\n", output); // hello-world
  return 0;
}
```

### Slugify Options

- `replacement`: Character used to replace spaces and unwanted characters.
- `remove`: Set of characters to remove from the input string (default: $*_+~.()"'!?-:@).
- `lower`: Convert output to lowercase.
- `strict`: Remove non-alphanumeric characters.
- `locale`: Locale-specific mappings to apply.
- `trim`: Trim leading and trailing spaces or replacement characters.

## Contributing

Contributions are welcome! Feel free to submit a pull request or open an issue for any improvements or bug fixes.

# ft_nm

This project is about recreating the `nm` command, which lists symbols from object files. It displays the symbol table of ELF files, showing symbol names, values, and types. The project uses the GNU nm utility as a reference (with the environment variable `LC_ALL` set to `C`) and implements core functionality for analyzing ELF object files.

## Usage

```bash
$> make
$> ./ft_nm --help
Usage: ft_nm [-p] [-r] [-u] [-g] [-h] [--usage] FILES...

List symbols in [FILES...] (a.out by default).

Options:
  -p, --no-sort         do not sort the symbols
  -r, --reverse         reverse the sense of the sort
  -u, --undefined-only  display only undefined symbols
  -g, --extern-only     display only external symbols
  -h, --help            give this help list
      --usage           give a short usage message
```

## Examples

```bash
# Basic symbol listing
$> ./ft_nm a.out

# List symbols from multiple files
$> ./ft_nm file1.o file2.o libexample.a

# Display only external symbols
$> ./ft_nm -g program

# Display only undefined symbols
$> ./ft_nm -u library.so

# Reverse sort order
$> ./ft_nm -r executable

# No sorting (preserve order from symbol table)
$> ./ft_nm -p object.o

# Combine options
$> ./ft_nm -gu program.o
```

## Symbol Types

The program displays symbols with their type characters:

- **U, w, v**: Undefined symbols
- **A-Z**: External symbols (global)
- **a-z**: Local symbols
- **Other characters**: Various symbol types based on ELF specification

## Grading

This project is part of the advanced curriculum at 42 School.

- **Date of completion:** Ongoing
- **Grade:** N/A

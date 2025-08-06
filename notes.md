# Symbol types
```
Symbol type 	Description
A 				Global absolute symbol
a 				Local absolute symbol
B 				Global bss symbol
b 				Local bss symbol
D 				Global data symbol
d 				Local data symbol
f 				Source file name symbol
R 				Global read-only symbol
r 				Local read-only symbol
T 				Global text symbol
t 				Local text symbol
U 				Undefined symbol
```

# ELF File Layout
```
┌─────────────────┐ ← offset 0
│   ELF Header    │ (ehdr)
│   (64 bytes)    │
├─────────────────┤
│                 │
│   Sections      │ (.text, .data, .symtab, etc.)
│                 │
├─────────────────┤
│ Section Header  │ ← ehdr->e_shoff
│     Table       │ (array of shdr)
│ [0] .null       │
│ [1] .text       │
│ [2] .data       │
│ [3] .symtab     │
│ [4] .strtab     │
│ [5] .shstrtab   │ ← ehdr->e_shstrndx points here
│     ...         │
└─────────────────┘
```

# What to search for
SHT_SYMTAB then follow the link to the strtab
SHT_DYNSYM then follow the link to the strtab

# First line of an ELF file description
Example hexdump of the first 16 bytes of a typical ELF file:
```
00000000  7f 45 4c 46 02 01 01 00  00 00 00 00 00 00 00 00  |.ELF............|
```

Where:
```
  7f          = Magic number (ELF identification)
  45 4c 46    = ASCII for 'E' 'L' 'F'
  02          = EI_CLASS (2 = 64-bit, 1 = 32-bit)
  01          = EI_DATA (1 = little endian, 2 = big endian)
  01          = EI_VERSION (1 = original version)
  00          = EI_OSABI (0 = System V)
  00          = EI_ABIVERSION
  00 00 00 00 00 00 00 = Padding (EI_PAD)
```
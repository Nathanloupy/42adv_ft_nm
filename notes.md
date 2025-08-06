# Symbol types
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

# ELF File Layout
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

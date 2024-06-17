FPV Ground station
==============================
Zadání
-------------------------------
<img title="a title" alt="TEXt Zadání" src="/iScreen Shoter - Google Chrome - 240617092447.jpg">

Vývojový diagram funkce main
------------------------------------
<img title="a title" alt="TEXt Zadání" src="/vyvoják.jpg">


K dispozici jsou celkem tři `Makefile` v adresáři `.make`. Na začátku si musíte
jeden z nich vybrat:

```bash
make sdcc       # nebo
make sdcc-gas   # nebo
make sdccrm     # nebo
```

**Pokud si nejste jistí, co vybrat, vyberte si `sdcc`** a napište
```bash
make sdcc
```
Schéma zapojení
------------------------------------
<img title="a title" alt="TEXt Zadání" src="/iScreen Shoter - Acrobat - 240617092623.jpg">




Závislosti
---------------

* [GNU Make](https://www.gnu.org/software/make/)
* [GNU Bash](https://www.gnu.org/software/bash/) -- ten se na Windows
  dá nainstalovat společně s [Git](https://git-scm.com/download/win)em.
* [SDCC](http://sdcc.sourceforge.net/)
  nebo [SDCC-gas](https://github.com/XaviDCR92/sdcc-gas)
* [STM8 binutils](https://stm8-binutils-gdb.sourceforge.io) (`stm8-gdb`, `stm8-ln`)
* [OpenOCD](https://openocd.org/) pro `flash` a `debug`
  nebo [STVP](https://www.st.com/en/development-tools/stvp-stm8.html)
  pro `flash` na Windows.
* ([stm8flash](https://github.com/vdudouyt/stm8flash) pro `flash2`)

### Na Windows

[`choco`](https://chocolatey.org/)` install git make vscode mingw`


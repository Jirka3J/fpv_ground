FPV Ground station
==============================
Zadání
-------------------------------
<img title="a title" alt="TEXt Zadání" src="/iScreen Shoter - Google Chrome - 240617092447.jpg">

Vývojový diagram funkce main
------------------------------------
<img title="a title" alt="TEXt Zadání" src="/vyvoják.jpg">


** V hlavní smyčce pro demonstraci měním jednu souřadnici aby byla viditelná funkčnost výpočtů a ovladání serva

```c
lastPWM = toPWM(getAngle());
        TIM2_SetCompare1(lastPWM);
        iteration = milis()-iteration;
        if (milis() - time > 10 ) {
            latitude += 10;
            if (latitude-40000> lockedLatitude){
                latitude = lockedLatitude;
            }
        }
```
**Mou hlavní pýchou je funkce arctan,
kterou počítám zapomocí iterací v taylorově řadě, a s čísly v pevné řadové čárce.
algoritmus je optimalizovaný tak aby výpočet trval 5ms.


```c
int32_t arctan_fixed(int32_t x, uint8_t N) {
    int64_t arctan_x = 0;
    int32_t x_pow = x;  

    for (uint8_t n = 0; n < N; n++) {
        int32_t term = x_pow / (2 * n + 1);
        if (n % 2 == 0) {
            arctan_x += term;
        } else {
            arctan_x -= term;
        }
        x_pow = (x_pow * x / SCALE) * x / SCALE;
    }

    return arctan_x;
}
int32_t arctan(int32_t x, uint8_t N) {
    if (x > SCALE||x<-SCALE) {
        int64_t reciprocal = SCALE2/x;  
        return (15707 - arctan_fixed(reciprocal, N))*1800/3141;
    } else {
        return arctan_fixed(x, N)*1800/3141;
    }
}
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


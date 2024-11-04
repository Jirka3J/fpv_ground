FPV Ground station
==============================
Zadání
-------------------------------
<img title="a title" alt="TEXt Zadání" src="/iScreen Shoter - Google Chrome - 240617092447.jpg">

Blokové schéma
------------------------------------
<img title="a title" alt="Blokové schéma" src="/iScreen Shoter - Acrobat - 241021132707.jpg">


Vývojový diagram funkce main
------------------------------------
<img title="a title" alt="vývojový diagram" src="/Flowchart-_1_.svg">


## V hlavní smyčce pro demonstraci měním jednu souřadnici aby byla viditelná funkčnost výpočtů a ovladání serva

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
## Mou hlavní pýchou je funkce arctan,
kterou počítám zapomocí iterací v taylorově řadě, a s čísly v pevné řadové čárce.
algoritmus je optimalizovaný tak aby výpočet trval 5ms. Pro správnou funkci ještě musíme hodnoty větší než jedna inverovat a výsledek přepočítat


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
## Převod souřadnic na úhel
zanedbávám zakřivení země protože v fpv se lzed pohybovat jeno v určitém rozsahu, který je dostatečně nízký aby jsme ho mohli zanedbat.
případně pokud by jste používali kartézskou soustavu souřadnic tak není co zanedbávat a výpočet by byl relativně přesný.
```c
int32_t getDiff(int32_t now,int32_t locked){
    return now - locked; 
}

int getAngle(){
    int32_t a = getDiff(latitude,lockedLatitude);
    int32_t b = getDiff(longitude,lockedLongitude);
    int64_t decimal = a*SCALE/b;
    int32_t x = arctan(decimal,20);
    return x;
}
```

## převod na duty cycle
```c
uint16_t toPWM(int32_t degrees){
    if(degrees>6000||degrees<0){
        return lastPWM;
    }else{
        return degrees*833/10000+500;
    }
}
```

## Na UART kvůli debugu vypisuji úhel ve stupních duty cycle a čas výpočtu





Schéma zapojení
------------------------------------
<img title="a title" alt="TEXt Zadání" src="/iScreen Shoter - Acrobat - 240617092623.jpg">


Závěr
------------------------------------
Projekt funguje dle očekávání. Na základě vstupu kartézských souřadnic přepočítává na úhel. Jako výstup je zapojené servo ,které otáčí anténou, podle úhlu který počítá mikroprocesor. Pro přepočet používám funkci arctangens kterou jsem napsal zapomocí iteračního algoritmu.





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




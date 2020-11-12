# Simple Sudoku solver in C

I ported my JavaScript-based Sudoku solver to C to see how much faster it is. The answer: a lot.

| Board | JavaScript | C |
|---|---|---|
| Easy | 2.002ms | 0.062ms |
| Hard | 15.628ms | 2.152ms |
| Empty | 3.050ms | 0.128ms |

## How to compile and run

```
make
./sudoku
```

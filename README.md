# Conway's Life Game Simulator
## About the project
`Cellular Automata` implementation in `C++` using class and game loop pattern.

The game is a zero-player game, the evolution is determined by a pattern. One interacts with the Game of Life by creating an initial configuration and observing how it evolves.
## Rules
Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
5. Births and deaths occur simultaneously.

## Compile
Clone the repository
```bash
$ git clone https://github.com/OnofreTZK/Conways-LifeGame
```

In root
```bash
$ cmake -S . -Bbuild && cd build/
$ make
````

### Running

Default running:
```bash
$ ./glife <initial_config_file.dat>
````
Check directory `data/` to see all config files.

Options running:
```bash
$ ./glife --help
````
To see extra running options

## Authorship
* [Tiago Onofre](https://github.com/OnofreTZK)
* [Rafael Fortunato](https://github.com/Obelixlelul)





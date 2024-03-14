# Jakdojade

Finding the shortest route between cities.

## Input

The input consists of the following sections:

1. **Map**: The first line contains the dimensions of the map: width `w` and height `h`. The next `h` lines (each containing `w` characters) describe the map. Each character represents:
   - `.`: Empty field
   - `#`: Road
   - `*`: City
   - Letter or number: Part of the city name

2. **Flight Connections**: The next line contains a single integer `k` - the number of flight connections. The following `k` lines describe the connections in the format `source destination time`, where `source` is the name of the starting city, `destination` is the name of the destination city, and `time` is the flight time in minutes.

3. **Queries**: The next line contains a single integer `q` - the number of queries. Each query appears on a separate line and has the format `source destination type`. The `type` indicates the query type:
   - If `type` is zero, the query is only for the time.
   - If `type` is one, the route should also be provided.

## Output

For each query, the output should be as follows:

- If the query type is zero, output one line with the number representing the shortest travel time between the cities.
- If the query type is one, output one line with the number representing the shortest travel time between the cities, followed by the intermediate cities (excluding the starting and ending cities) in the order they were visited, separated by spaces.

## Example

### Input:
```
20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
0
3
KIELCE KRAKOW 0
KRAKOW GDANSK 0
KRAKOW GDANSK 1
```

### Output:
```
5
40
40 KIELCE SZCZECIN
```


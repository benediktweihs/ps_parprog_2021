## General Considerations

So first of all it might be interesting to think about cache misses.
By looking at the sequential implementation we may conclude that it could be helpful to transpose B
in the very beginning. Because then, the innermost command would be
```C
C[IND(i,j)] += A[IND(i,k)] * B[IND(j,k)];
```
and the number of cache misses would hence be minimized (not a cache miss during every iteration of the innermost loop).

## Loop Transformations and Dependency Graph
The dependency graph is fully disconnected so in principle it is possible to perfrom add the corresponding values to $C_{i, j}$ in any order we prefer. Since a high degree of data locality can already be realized by summing over $k$ for fixed $i$ and $j$ and iterating over $k$ I didn't perform any transformations other than transposing matrix $B$ (but already in the beginning).

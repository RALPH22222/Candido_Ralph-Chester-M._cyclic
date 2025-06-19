# Cycle Detection in Undirected Graphs (DFS & BFS)

## Two Approaches to Detect Cycles

### 1.Depth-First Search (DFS)

**How it works:**

- Explore the graph deeply before backtracking.
- Track visited vertices and their *parent* (san ka nag galing).
- If you revisit a vertex that isn't your parent — a **cycle is detected**!

**Cycle Detection Logic:**

> Imagine walking through a maze and leaving breadcrumbs (para alam mo saan ka dumaan).  
> If you encounter a breadcrumb that wasn’t from your last step, you’ve looped — that’s a cycle!

**Cycle Path Reconstruction:**

- Backtrack using parent pointers to rebuild the path.
- Print the cycle from the start to the detection point.

---

### 2. Breadth-First Search (BFS)

**How it works:**

- Explore level-by-level (ano yung malapit).
- Track visited vertices and their parents.
- If you find an edge to a visited vertex that’s **not** your parent — that’s a cycle!

**Key Difference from DFS:**

- BFS explores all immediate neighbors first (may find shorter cycles earlier).

**Cycle Path Reconstruction:**

- Trace back from **both vertices** in the cycle to find their common ancestor.
- Combine the two paths to form the complete cycle.

---

## Input Format

Applies to both programs:

1. **Enter the number of graphs** to test.
2. For each graph:
   - Enter number of **vertices (N)**
   - Enter an **N×N adjacency matrix**, where:
     - `1` = edge exists
     - `0` = no edge

---

## Example Walkthrough

**Sample Input:**
```
Number of graphs: 1
Vertices: 4
Adjacency Matrix:
0 1 1 0
1 0 1 1
1 1 0 0
0 1 0 0
```

**What happens:**

- Start at vertex 0
- Visit neighbors 1 and 2
- At vertex 1, detect vertex 2 already visited and not parent → **cycle detected**: `0-1-2-0`

**Sample Output (DFS):**
```
Graph contains cycle: 0 -> 1 -> 2 -> 0
```

**Sample Output (BFS):**
```
Graph contains cycle: 2 -> 0 -> 1 -> 2
```

---

## When to Use Which

| Approach | Pros | Notes |
|----------|------|-------|
| DFS | Simple to implement | Works well for most use cases |
| BFS | Finds shorter cycles first | Slightly more complex |

Both run in **O(V + E)** time (V = vertices, E = edges)

---

## Important Notes

- These programs are for **undirected graphs**.
- The cycle paths might **differ** between DFS and BFS.
- Ensure the **adjacency matrix is symmetric** (i.e., if A is connected to B, then B must be connected to A).

---

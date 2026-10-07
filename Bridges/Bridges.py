"""Iterative low-link analysis of undirected multigraphs."""


def bridges_and_articulation_points(size, edges):
    """Return (sorted bridge edge IDs, sorted articulation vertices)."""
    edges = list(edges)
    graph = [[] for _ in range(size)]
    for identifier, (first, second) in enumerate(edges):
        graph[first].append((second, identifier))
        graph[second].append((first, identifier))
    entered, low = [-1] * size, [0] * size
    parent, parent_edge, children = [-1] * size, [-1] * size, [0] * size
    bridges, articulation, timer = [False] * len(edges), [False] * size, 0
    for root in range(size):
        if entered[root] != -1:
            continue
        entered[root] = low[root] = timer
        timer += 1
        stack = [(root, iter(graph[root]))]
        while stack:
            vertex, neighbors = stack[-1]
            edge = next(neighbors, None)
            if edge is not None:
                neighbor, identifier = edge
                if identifier == parent_edge[vertex]:
                    continue
                if entered[neighbor] != -1:
                    low[vertex] = min(low[vertex], entered[neighbor])
                    continue
                parent[neighbor], parent_edge[neighbor] = vertex, identifier
                children[vertex] += 1
                entered[neighbor] = low[neighbor] = timer
                timer += 1
                stack.append((neighbor, iter(graph[neighbor])))
                continue
            stack.pop()
            ancestor = parent[vertex]
            if ancestor == -1:
                if children[vertex] > 1:
                    articulation[vertex] = True
                continue
            low[ancestor] = min(low[ancestor], low[vertex])
            if low[vertex] > entered[ancestor]:
                bridges[parent_edge[vertex]] = True
            if parent[ancestor] != -1 and low[vertex] >= entered[ancestor]:
                articulation[ancestor] = True
    return (
        [identifier for identifier, is_bridge in enumerate(bridges) if is_bridge],
        [
            vertex
            for vertex, is_articulation in enumerate(articulation)
            if is_articulation
        ],
    )

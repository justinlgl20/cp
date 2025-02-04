def dfs(graph, u, b, k, path_weights):
    # Perform DFS, maintaining the largest k weights along the path.
    visited = set()
    stack = [(u, [])]  # Start from node u with an empty path
    while stack:
        node, current_weights = stack.pop()
        if node == b:
            if len(current_weights) >= k:
                return True
            continue
        for neighbor, weight in graph[node]:
            if neighbor not in visited and weight <= threshold:
                visited.add(neighbor)
                new_weights = current_weights + [weight]
                new_weights.sort(reverse=True)  # Sort weights in descending order
                if len(new_weights) > k:
                    new_weights = new_weights[:k]  # Keep only the top k weights
                stack.append((neighbor, new_weights))
    return False

def solve_queries(graph, queries):
    # Step 1: Binary search over possible edge weights
    max_weight = max(weight for u in graph for v, weight in graph[u])
    answers = []
    for a, b, k in queries:
        low, high = 0, max_weight
        result = -1
        while low <= high:
            mid = (low + high) // 2
            if dfs(graph, a, b, k, mid):
                result = mid
                high = mid - 1
            else:
                low = mid + 1
        answers.append(result)
    return answers

t = int(input()); 
for _ in range(t):
	n, m, q = map(int, input().split())
	adj = [[] for i in range(n+4)]
	for i in range(m):
		u, v, w = map(int, input().split())
		adj[u].push_back([v, w]);
		adj[v].push_back([u, w]);
	print(solve(adj, queries));

# struct
``` C++
struct name{
    --
} name_list[#];
```

# Ordered Set
``` C++
struct Compare {
	bool operator() (const name& a, const name& b) const {
		return a < b // sorts set in ascending order
	}
};

set<Student, Compare> set_list[3][2];
```

# Erase in Map
erase : if map, with key, O(logN), with iter, O(1)<br>
Does not matter for unordered_map

# To find something same or bigger than target
```C++
it = set.lower_bound(target);
```

# pair for graph
```C++
typedef pair<int, int> pii;
vector<vector<pii>> graph; // global
vector<vector<pii>> new_graph(N); // init
```

# Bucket
sqrt(max_cnt) is max efficiency<br>
There are two situations.<br>
<li>
All in one bucket -> separate 
<li>
Split in diff buckets -> all handled same
</li><br>

# SetCompare VS QueCompare
Set : uses less. If true, a -> b.<br>
Queue : uses greater. If true, b -> a.

# Clearing DataSturctures
Set : clear()<br>
Queue/Vector : re-initialize

# Emplace vs Push
Emplace : directly uses the object<br>
Push : uses a copy of an object

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
it = set.lower_bound(target);
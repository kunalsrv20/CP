/* 
Usage: Node* tr = new Node(v, 0, sz(v));
finds max in a range, [L, R)
*/
// Either globally or in a single class:
// static char buf[450 << 20];
// void* operator new(size_t s) {
// 	static size_t i = sizeof buf;
// 	assert(s < i);
// 	return (void*)&buf[i -= s];
// }
// void operator delete(void*) {}


//---- Classical problems using segment tree ----
// Find the number of unique numbers in a given range (actually using mergesort tree)
// Find the maximum and the number of occurences of it.
// Flip the binary numbers in a given range (maintain a variable LAZY_FLIP).
// max subarray sum (storing prefix and suffix).
// List removals  (CSES).
// Walking on a segment tree range: [1, i]. (logN)^2 -> (logN) optimization
// Non commutative combiner functions (which are associative)
// 2-D segment tree


const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	ll lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vll& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	ll query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

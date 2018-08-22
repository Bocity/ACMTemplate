template <class T>
struct RMQ
{
  static const int npos = -1;

  int n, m;
  vector<T> d;
  RMQ() {}
  RMQ(int n_, const T init = T()) : n(n_), m(2 << __lg(max(1, n))), d(2 * m, init) {}
  template <class Iter>
  void build(Iter begin, Iter end, const T init = T())
  {
    n = end - begin;
    m = 2 << __lg(max(1, n));
    d.resize(2 * m);
    for (int i = 0; begin != end; ++begin, i++)
      d[i + m] = *begin;
    for (int i = n; i < m; i++)
      d[i + m] = init;
    for (int i = m; --i;)
      d[i] = min(d[i * 2 + 1], d[i * 2]);
  };

  const T at(int i) const { return d[i + m]; }

  void modify(int i, const T v)
  {
    i += m;
    d[i] = v;
    for (i >>= 1; i; i >>= 1)
      d[i] = min(d[i * 2 + 1], d[i * 2]);
  }

  T min_v(int l, int r) const
  {
    l += m;
    r += m;
    T ret = d[l++];
    for (; l < r; l >>= 1, r >>= 1)
    {
      if (l & 1)
      {
        amin(ret, d[l]);
        l++;
      }
      if (r & 1)
      {
        r--;
        amin(ret, d[r]);
      }
    }
    return ret;
  }

  int min_i(int l, int r) const
  {
    return first_less_equal(l, min_v(l, r));
  }

  // for i in [l .. n-1]:
  //   if at(i) <= v: return i;
  // return npos;
  int first_less_equal(int l, const T v) const
  {
    int r = 2 * m;
    for (l += m; l < r; l >>= 1, r >>= 1)
    {
      if (l & 1)
      {
        if (d[l] <= v)
          break;
        l++;
      }
    }
    if (l >= r)
      return npos;
    for (; l < m;)
    {
      if (d[l * 2] <= v)
        l = l * 2;
      else
        l = l * 2 + 1;
    }
    return l - m;
  }
};
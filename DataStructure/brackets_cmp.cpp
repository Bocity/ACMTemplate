bool cmp(node x, node y) {
    if (x.l >= x.r && y.l < y.r) return false;
    if (x.l < x.r && y.l >= y.r) return true;
    if (x.l >= x.r && y.l >= y.r) return x.r > y.r;
    return x.l < y.l;
}

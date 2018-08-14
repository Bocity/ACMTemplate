struct LinearBase {
    vector<long long> base;
    int insert(LL x) {
        int k = 0;
        for (int i = 0; i < (int) base.size(); i++) {
            if ((x ^ base[i]) < x) k++;
            x = min(x, x ^ base[i]);
        }
        if (x) {
            base.pb(x);
            return true;
        } else
            return false;
    }
    long long max_element() {
        sort(base.begin(), base.end());
        long long ret = 0;
        for (int i = (int) base.size() - 1; i >= 0; i--) {
            ret = max(ret, ret ^ base[i]);
        }
        return ret;
    }
    long long min_element() {
        sort(base.begin(), base.end());
        return base[0];
    }
    long long kth_elment(int k) {
        sort(base.begin(), base.end());
        for (int i = (int) base.size() - 1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                base[i] = min(base[i], base[i] ^ base[j]);
            }
        }
        LL ret = 0;
        if (k > (1ll << base.size())) return -1;
        int i = 0;
        while (k) {
            if (k & 1) ret ^= base[i];
            i++;
            k >>= 1;
        }
        return ret;
    }
} LB;
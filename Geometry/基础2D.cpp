const double eps = 1e-8;
const double pi = acos(-1.0);
inline int sgn(const double &x) {
    return x < -eps ? -1 : x > eps;
}
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    void input() {
        scanf("%lf%lf", &x, &y);
    }
    bool operator<(const Point &p) const {
        return sgn(x - p.x) < 0 || (!sgn(x - p.x) && sgn(y - p.y) < 0);
    }
    bool operator==(const Point &p) const {
        return !sgn(x - p.x) && !sgn(y - p.y);
    }
    Point operator+(const Point &p) const {
        return Point(x + p.x, y + p.y);
    }
    Point operator-(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    Point operator*(const double c) const {
        return Point(x * c, y * c);
    }
    friend Point operator*(double c, const Point &p) {
        return p * c;
    }
    Point operator/(double c) {
        return Point(x / c, y / c);
    }
    double operator^(const Point &p) const { //叉积向量长度
        return x * p.y - y * p.x;
    }
    double operator%(const Point &p) const { //点积
        return x * p.x + y * p.y;
    }
    double len() {
        return sqrt(x * x + y * y);
    }
    double arg() { //返回弧度 （-pi,pi】
        return atan2(y, x);
    }
};
//两个向量的夹角,【0，pi）
double Angle(Point A, Point B) {
    return acos((A % B) / A.len() / B.len());
}
//逆时针旋转
Point Rotate(Point A, double rad) {
    Point B = Point(sin(rad), cos(rad));
    return Point(A ^ B, A % B);
}
//向量的单位法向量
Point Normal(Point A) {
    double L = A.len();
    return Point(-A.y / L, A.x / L);
}

// 直线交点，v和w为两个直线的方向向量，
// 设交点的参数为P+vt,Q+wt,连立方程解t
// 线段，射线对这个t的参数有限制，很好理解。
Point GetLineIntersection(Point P, Point v, Point Q, Point w) {
    Point u = P - Q;
    double t = (w ^ u) / (v ^ w);
    return P + v * t;
}
// 点到直线有向距离，这里直线是用两个点表示的
double DistancePointToLine(Point P, Point A, Point B) {
    Point v = B - A;
    return (v ^ (P - A)) / v.len();
}
// 点到线段距离，就是上面的代码判断一下P在AB上投影的位置。
double DistancePointToSegment(Point P, Point A, Point B) {
    if (A == B) return (P - A).len();
    Point v1 = B - A, v2 = P - A, v3 = P - B;
    if (sgn(v1 % v2) < 0) return v2.len();
    if (sgn(v1 % v3) > 0) return v3.len();
    return fabs(v1 ^ v2) / v1.len();
}
// 返回点在直线上的投影
Point GetLineProjection(Point P, Point A, Point B) {
    Point v = B - A;
    return A + v * (v % (P - A) / (v % v));
}
//两线段相交判断
// 2 规范相交
// 1 非规范相交
// 0 不相交
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2) {
    int d1 = sgn((a2 - a1) ^ (b1 - a1));
    int d2 = sgn((a2 - a1) ^ (b2 - a1));
    int d3 = sgn((b2 - b1) ^ (a1 - b1));
    int d4 = sgn((b2 - b1) ^ (a2 - b1));
    if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return 2;
    return (d1 == 0 && sgn((b1 - a1) * (b1 - a2)) <= 0) || (d2 == 0 && sgn((b2 - a1) * (b2 - a2)) <= 0) || (d3 == 0 && sgn((a1 - b1) * (a1 - b2)) <= 0) || (d4 == 0 && sgn((a2 - b1) * (a2 - b2)) <= 0);
}
// 点是否在线段上,判定方式为到两个端点的方向是否不一致。
bool OnSegment(Point P, Point A, Point B) {
    A = A - P, B = B - P;
    return sgn(A ^ B) == 0 && sgn(A % B) <= 0;
}
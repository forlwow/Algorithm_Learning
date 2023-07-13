int gcd(int a, int b){
    return b ? gcd(b, a%b): a;
}

int exgcd(int a, int b, int &x, int &y){
    /*
    // ax + by = d; d为最小公倍数
    // x = x0 - b/d
    // y = y0 + a/d
    */
    if (b){
        int res = exgcd(b, a%b, y, x);
        y -= a / b * x;
        return res;
    }
    else{
        x = 1; y = 0;
        return a;
    }
}
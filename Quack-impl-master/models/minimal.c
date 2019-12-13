//
// Tiniest example for procedure call and return
//

int max3(int x, int y, int z) {
    if (x > y && y > z) {
        return x;
    } else if (x > y) {
        return z;
    } else {
        return y;
    }
}

int inc(int x) {
    return x + 1;
}

int sum(int a, int b) {
    int x;
    int y = 42;
    int z = 84;
    x = a + b;
    x = inc(x);
    return x;
}


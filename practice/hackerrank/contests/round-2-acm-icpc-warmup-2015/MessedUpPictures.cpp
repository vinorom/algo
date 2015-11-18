/**
 * https://www.hackerrank.com/contests/round-2-acm-icpc-warmup-2015/challenges/messed-up-pictures
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct size
{
    int x, y;

    size(int x = 0, int y = 0): x(x), y(y) {}
};

struct image_params: public size
{
    int k;

    image_params(int x = 0, int y = 0, int k = 0): size(x, y), k(k) {}

    bool operator<(image_params rhv) const
    {
        if (x * y != rhv.x * rhv.y) return x * y < rhv.x * rhv.y;
        if (x != rhv.x) return x < rhv.x;
        return k < rhv.k;
    }
};

image_params repair_image(size image, size ratio)
{
    int x = image.x, y = image.y;
    int rx = ratio.x, ry = ratio.y;

    // cropped
    int g = (int)ceil(max((double)x / rx, (double)y / ry));
    image_params opt(rx * g, ry * g, 1);

    // rotated and cropped
    g = (int)ceil(max((double)x / ry, (double)y / rx));
    opt = min(opt, image_params(rx * g, ry * g, 2));

    // untouched
    if (x * ry == y * rx) opt = min(opt, image_params(x, y, 0));

    // rotated
    if (x * rx == y * ry) opt = min(opt, image_params(y, x, 1));

    return opt;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int M, N;
        cin >> M;

        vector<size> ratios(M);
        for (int i = 0; i < M; ++i) cin >> ratios[i].x >> ratios[i].y;

        cout << "Case " << t << ":\n";

        cin >> N;
        while (N--)
        {
            size image;
            cin >> image.x >> image.y;

            size opt_ratio = *min_element(begin(ratios), end(ratios),
                [&image](size lhv, size rhv)
                {
                    return repair_image(image, lhv) < repair_image(image, rhv);
                });

            image_params repaired = repair_image(image, opt_ratio);

            cout << repaired.x << ' ' << repaired.y << ' ' << repaired.k << '\n';
        }
    }

    return 0;
}

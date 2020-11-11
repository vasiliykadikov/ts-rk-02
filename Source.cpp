#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
//v1, mutation 30%, 4 doats
class Generation {
public:
    double x_chrom;
    double y_chrom;
    double FIT;
};
double function(double& x, double & y) {
    return sin(x) / (1 + x * x + y * y);
}
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
bool returnmaxfit(Generation& g1, Generation& g2) {
    return  g1.FIT < g2.FIT;
}
void crossover(std::vector<Generation>& generations) {
    Generation g_1 = generations[3];
    Generation g_2 = generations[2];
    Generation g_3 = generations[1];
    generations[0].x_chrom = g_1.x_chrom;
    generations[0].y_chrom = g_2.y_chrom;
    generations[1].x_chrom = g_2.x_chrom;
    generations[1].y_chrom = g_1.y_chrom;
    generations[2].x_chrom = g_1.x_chrom;
    generations[2].y_chrom = g_3.y_chrom;
    generations[3].x_chrom = g_3.x_chrom;
    generations[3].y_chrom = g_1.y_chrom;
    for (auto i = 0; i < 4; ++i) {
        generations[i].FIT = function(generations[i].x_chrom, generations[i].y_chrom);
    }
    std::sort(generations.begin(), generations.end(), returnmaxfit);
}
void mutation(std::vector <Generation>& generations, const double& x_min,
    const double& y_min, const double& x_max, const double& y_max) {
    if (fRand(0., 10.) <= 3.) {
        generations[1].x_chrom = fRand(x_min, x_max);
        generations[1].y_chrom = fRand(y_min, y_max);
        generations[1].FIT = function(generations[1].x_chrom, generations[1].y_chrom);
    }
    std::sort(generations.begin(), generations.end(), returnmaxfit);
}
double middleFIT(std::vector<Generation>& generations) {
    double mid = 0;
    for (auto i = 0; i < 4; ++i) {
        mid += generations[i].FIT;
    }
    return mid / 4;
}

int main() {
    const double x_min = -2;
    const double y_min = -2;
    const double x_max = 2;
    const double y_max = 2;
    
    std::vector <Generation> generations;
    for (auto i = 0; i < 4; ++i) {
        Generation G;
        G.x_chrom = fRand(x_min, x_max);
        G.y_chrom = fRand(y_min, y_max);
        G.FIT = function(G.x_chrom, G.y_chrom);
        generations.push_back(G);
    }
    std::sort(generations.begin(), generations.end(), returnmaxfit);
    std::cout << "N  X      Y           FIT\n";
    std::cout << "0";
    for (auto i = 0; i < 4; ++i) {
        std::cout << "   " << generations[i].x_chrom << " " << generations[i].y_chrom << " " << generations[i].FIT << "\n";
    }
    std::cout << "   max: " << generations[3].FIT << " middle: " << middleFIT(generations);
    for (auto i = 0; i < 100; ++i) {
        mutation(generations, x_min, y_min, x_max, y_max);
        crossover(generations);
        if (i <= 10 || i % 10 == 9) {
            std::cout << "\n" << i + 1;
            for (auto i = 0; i < 4; ++i) {
                std::cout << "   " << generations[i].x_chrom << " " << generations[i].y_chrom << " " << generations[i].FIT << "\n";
            }
            std::cout << "   max: " << generations[3].FIT << " middle: " << middleFIT(generations);
        }
    }
    return 0;
}
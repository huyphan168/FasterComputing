#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
#include <algorithm>

class Accumulator
{
public:
    explicit Accumulator(float initial_sum = 0) : sum(initial_sum) {}

    float operator()(float num)
    {
        sum += num;
        return sum;
    }

private:
    float sum;
};

int main()
{
    std::vector<float> pdf = {0.1, 0, 0.2, 0.3, 0.15, 0, 0.05, 0.2};
    
    float pdf_sum = std::accumulate(pdf.begin(), pdf.end(), 0.0f);
    assert(std::abs(pdf_sum - 1.0f) < 1e-6);

    std::vector<float> cdf(pdf.size());
    std::transform(pdf.begin(), pdf.end(), cdf.begin(), Accumulator());

    for (float value : cdf)
    {
        std::cout << value << " ";
    }

    return 0;
}

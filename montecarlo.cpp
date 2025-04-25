// Monte Carlo tester, pulls functions from final.cpp, compile in the same folder.

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Pull functions from main chatbot file
#define MONTE
#include "final.cpp"
#undef MONTE

int main()
{
    srand((unsigned)time(nullptr));
    // Initialize
    startProccess();
    stateNode* node = findNode(1);

    long TRIALS = 1000000;
    long counts[3] = {0,0,0};

    // Run trials
    for (long i = 0; i < TRIALS; ++i)
    {
        ostringstream oss;
        std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
        out_put(node);
        std::cout.rdbuf(old);
        string resp = oss.str();

        // Checks response with each state, counts for which it matches.
        if (resp == node->response[0])
            ++counts[0];
        else if (resp == node->response[1])
            ++counts[1];
        else
            ++counts[2];
    }

    // Output results
    cout << "Response 1: " << counts[0]
        << " (" << counts[0] * 100.0 / TRIALS << "%)\n";
    cout << "Response 2: " << counts[1]
        << " (" << counts[1] * 100.0 / TRIALS << "%)\n";
    cout << "Response 3: " << counts[2]
        << " (" << counts[2] * 100.0 / TRIALS << "%)\n";

    return 0;
}
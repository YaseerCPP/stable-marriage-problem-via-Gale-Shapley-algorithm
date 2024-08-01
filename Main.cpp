#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> // for std::pair

using namespace std;

// Function to find the index of the man in the woman's preference list
int findRank(const vector<int>& preferences, int man) {
    for (int i = 0; i < preferences.size(); ++i) {
        if (preferences[i] == man) {
            return i;
        }
    }
    return -1; // Should never reach here if input is valid
}

// Gale-Shapley algorithm to solve the stable marriage problem
void stableMarriage(const vector<vector<int>>& menPreferences,
                    const vector<vector<int>>& womenPreferences) {
    int n = menPreferences.size(); // Number of men (and women)
    
    // Tracking current engagements (matches)
    vector<int> womenPartner(n, -1); // -1 means no current match
    vector<vector<int>> menNextProposal(n, vector<int>(n, 0)); // Track next proposal for each man
    vector<bool> menFree(n, true); // Track if a man is free
    
    bool allMatched = false;
    while (!allMatched) {
        allMatched = true;
        
        // Iterate over all men
        for (int man = 0; man < n; ++man) {
            if (menFree[man]) {
                allMatched = false;
                // Find the next woman to propose to
                int woman = menPreferences[man][menNextProposal[man][man]];
                
                // Propose to the woman
                menNextProposal[man][man]++;
                
                if (womenPartner[woman] == -1) {
                    // Woman is free and accepts the proposal
                    womenPartner[woman] = man;
                    menFree[man] = false;
                } else {
                    // Woman is currently matched, check if she prefers the new man
                    int currentPartner = womenPartner[woman];
                    int newManRank = findRank(womenPreferences[woman], man);
                    int currentManRank = findRank(womenPreferences[woman], currentPartner);
                    
                    if (newManRank < currentManRank) {
                        // Woman prefers the new man
                        womenPartner[woman] = man;
                        menFree[man] = false;
                        menFree[currentPartner] = true; // Current partner is now free
                    }
                }
            }
        }
    }
    
    // Output the results
    cout << "Stable matching pairs (man, woman):\n";
    for (int woman = 0; woman < n; ++woman) {
        cout << "Man " << womenPartner[woman] << " is matched with Woman " << woman << endl;
    }
}

int main() {
    int n = 3; // Number of men and women
    
    // Men preferences
    vector<vector<int>> menPreferences = {
        {1, 0, 2}, // Man 0 prefers Woman 1, Woman 0, Woman 2
        {0, 1, 2}, // Man 1 prefers Woman 0, Woman 1, Woman 2
        {0, 1, 2}  // Man 2 prefers Woman 0, Woman 1, Woman 2
    };
    
    // Women preferences
    vector<vector<int>> womenPreferences = {
        {1, 0, 2}, // Woman 0 prefers Man 1, Man 0, Man 2
        {0, 1, 2}, // Woman 1 prefers Man 0, Man 1, Man 2
        {0, 1, 2}  // Woman 2 prefers Man 0, Man 1, Man 2
    };
    
    stableMarriage(menPreferences, womenPreferences);
    
    return 0;
}

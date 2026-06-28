class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if (hand.size() % groupSize != 0) {
            return false;
        }

        map<int, int> card_counts;
        for (int card : hand) {
            card_counts[card]++;
        }

        for (auto it = card_counts.begin(); it != card_counts.end(); ++it) {
            if (it->second > 0) {
                int start_card = it->first;
                int count = it->second;

                for (int i = 0; i < groupSize; ++i) {
                    int current_card = start_card + i;
                    if (card_counts[current_card] < count) {
                        return false;
                    }
                    card_counts[current_card] -= count;
                }
            }
        }

        return true;
    }
};
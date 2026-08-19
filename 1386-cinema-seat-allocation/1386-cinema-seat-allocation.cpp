class Solution {
public:
    int maxNumberOfFamilies(int n, std::vector<std::vector<int>>& reservedSeats) {
        std::unordered_map<int, int> row_masks;

        // Bitwise representation for occupied seats (seats 2 through 9 matter)
        for (const auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];
            if (col >= 2 && col <= 9) {
                row_masks[row] |= (1 << col);
            }
        }

        // Rows without any reservations can accommodate 2 families each
        int total_families = (n - row_masks.size()) * 2;

        // Bitmasks for the three possible seat blocks
        const int LEFT_MASK   = (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5); // 2, 3, 4, 5
        const int RIGHT_MASK  = (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9); // 6, 7, 8, 9
        const int MIDDLE_MASK = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7); // 4, 5, 6, 7

        for (const auto& [row, mask] : row_masks) {
            bool left_free   = (mask & LEFT_MASK) == 0;
            bool right_free  = (mask & RIGHT_MASK) == 0;
            bool middle_free = (mask & MIDDLE_MASK) == 0;

            if (left_free && right_free) {
                total_families += 2;
            } else if (left_free || right_free || middle_free) {
                total_families += 1;
            }
        }

        return total_families;
    }
};
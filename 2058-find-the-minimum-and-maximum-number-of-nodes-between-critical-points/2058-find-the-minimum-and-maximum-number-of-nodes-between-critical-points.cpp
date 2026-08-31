/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int firstIdx = -1, prevIdx = -1;
        int minDist = INT_MAX;
        
        ListNode* prevNode = head;
        ListNode* curNode = head->next;
        int idx = 1; // index of curNode
        
        while (curNode->next != nullptr) {
            bool isMax = curNode->val > prevNode->val && curNode->val > curNode->next->val;
            bool isMin = curNode->val < prevNode->val && curNode->val < curNode->next->val;
            
            if (isMax || isMin) {
                if (firstIdx == -1) {
                    firstIdx = idx; // record the very first critical point
                } else {
                    minDist = min(minDist, idx - prevIdx); // gap from the last critical point seen
                }
                prevIdx = idx; // update "last critical point seen" to this one
            }
            
            prevNode = curNode;
            curNode = curNode->next;
            idx++;
        }
        
        if (firstIdx == -1 || firstIdx == prevIdx) {
            // fewer than 2 critical points found
            return {-1, -1};
        }
        
        int maxDist = prevIdx - firstIdx;
        return {minDist, maxDist};
    }
};
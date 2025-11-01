/*
 * ZCO PREPARATION - ALGORITHMS: Greedy Algorithms
 * 
 * Greedy algorithm patterns and common problems
 * Make locally optimal choices to find global optimum
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// ===== ACTIVITY SELECTION PROBLEM =====
// Select maximum number of non-overlapping activities

struct Activity {
    int start, finish;
};

int activitySelection(vector<Activity> &activities) {
    // Sort by finish time
    sort(activities.begin(), activities.end(), 
         [](const Activity &a, const Activity &b) {
             return a.finish < b.finish;
         });
    
    int count = 1;  // First activity always selected
    int lastFinish = activities[0].finish;
    
    for(int i = 1; i < activities.size(); i++) {
        if(activities[i].start >= lastFinish) {
            count++;
            lastFinish = activities[i].finish;
        }
    }
    
    return count;
}

// ===== FRACTIONAL KNAPSACK =====
// Maximize value with fractional items allowed

struct Item {
    int weight, value;
    double ratio;  // value/weight
};

double fractionalKnapsack(int capacity, vector<Item> &items) {
    // Sort by value/weight ratio (descending)
    sort(items.begin(), items.end(),
         [](const Item &a, const Item &b) {
             return (double)a.value / a.weight > (double)b.value / b.weight;
         });
    
    double totalValue = 0;
    
    for(auto &item : items) {
        if(capacity >= item.weight) {
            // Take entire item
            totalValue += item.value;
            capacity -= item.weight;
        } else {
            // Take fraction of item
            totalValue += (double)item.value * capacity / item.weight;
            break;
        }
    }
    
    return totalValue;
}

// ===== MINIMUM COINS PROBLEM =====
// Find minimum coins to make a sum (greedy works for certain denominations)

int minCoinsGreedy(vector<int> &coins, int amount) {
    // Assumes coins are sorted in descending order
    sort(coins.begin(), coins.end(), greater<int>());
    
    int count = 0;
    for(int coin : coins) {
        if(amount >= coin) {
            count += amount / coin;
            amount %= coin;
        }
    }
    
    return (amount == 0) ? count : -1;
}

// Note: Greedy doesn't always work for all denominations
// Use DP for general case

// ===== HUFFMAN CODING (Using Priority Queue) =====
// Build optimal prefix code tree

struct Node {
    char data;
    int freq;
    Node *left, *right;
    
    Node(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// ===== MEETING ROOMS PROBLEM =====
// Find minimum meeting rooms needed

int minMeetingRooms(vector<pair<int, int>> &intervals) {
    sort(intervals.begin(), intervals.end());
    
    priority_queue<int, vector<int>, greater<int>> pq;  // Min heap of end times
    
    for(auto &interval : intervals) {
        if(!pq.empty() && pq.top() <= interval.first) {
            pq.pop();  // Reuse room
        }
        pq.push(interval.second);
    }
    
    return pq.size();
}

// ===== INTERVAL SCHEDULING =====
// Maximum non-overlapping intervals

int maxNonOverlapping(vector<pair<int, int>> &intervals) {
    sort(intervals.begin(), intervals.end(),
         [](const pair<int, int> &a, const pair<int, int> &b) {
             return a.second < b.second;
         });
    
    int count = 0;
    int lastEnd = INT_MIN;
    
    for(auto &interval : intervals) {
        if(interval.first >= lastEnd) {
            count++;
            lastEnd = interval.second;
        }
    }
    
    return count;
}

// ===== JUMP GAME =====
// Can you reach the end?

bool canJump(vector<int> &nums) {
    int maxReach = 0;
    
    for(int i = 0; i < nums.size(); i++) {
        if(i > maxReach) return false;  // Can't reach position i
        maxReach = max(maxReach, i + nums[i]);
        if(maxReach >= nums.size() - 1) return true;
    }
    
    return true;
}

// Minimum jumps to reach end
int minJumps(vector<int> &nums) {
    int jumps = 0;
    int currentEnd = 0;
    int farthest = 0;
    
    for(int i = 0; i < nums.size() - 1; i++) {
        farthest = max(farthest, i + nums[i]);
        
        if(i == currentEnd) {
            jumps++;
            currentEnd = farthest;
        }
    }
    
    return jumps;
}

// ===== GAS STATION PROBLEM =====
// Find starting gas station to complete circuit

int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int totalGas = 0, totalCost = 0;
    int start = 0, tank = 0;
    
    for(int i = 0; i < gas.size(); i++) {
        totalGas += gas[i];
        totalCost += cost[i];
        tank += gas[i] - cost[i];
        
        if(tank < 0) {
            start = i + 1;
            tank = 0;
        }
    }
    
    return (totalGas >= totalCost) ? start : -1;
}

// ===== TASK SCHEDULER =====
// Schedule tasks with cooldown period

int leastInterval(vector<char> &tasks, int n) {
    vector<int> freq(26, 0);
    for(char task : tasks) {
        freq[task - 'A']++;
    }
    
    sort(freq.begin(), freq.end(), greater<int>());
    
    int maxFreq = freq[0];
    int idleSlots = (maxFreq - 1) * n;
    
    for(int i = 1; i < 26 && freq[i] > 0; i++) {
        idleSlots -= min(freq[i], maxFreq - 1);
    }
    
    return tasks.size() + max(0, idleSlots);
}

// ===== MINIMUM PLATFORMS =====
// Find minimum platforms needed for trains

int minPlatforms(vector<int> &arrival, vector<int> &departure) {
    sort(arrival.begin(), arrival.end());
    sort(departure.begin(), departure.end());
    
    int platforms = 1, maxPlatforms = 1;
    int i = 1, j = 0;
    
    while(i < arrival.size() && j < departure.size()) {
        if(arrival[i] <= departure[j]) {
            platforms++;
            i++;
        } else {
            platforms--;
            j++;
        }
        maxPlatforms = max(maxPlatforms, platforms);
    }
    
    return maxPlatforms;
}

// ===== PARTITION LABELS =====
// Partition string into as many parts as possible

vector<int> partitionLabels(string s) {
    vector<int> last(26, -1);
    
    // Store last occurrence of each character
    for(int i = 0; i < s.length(); i++) {
        last[s[i] - 'a'] = i;
    }
    
    vector<int> result;
    int start = 0, end = 0;
    
    for(int i = 0; i < s.length(); i++) {
        end = max(end, last[s[i] - 'a']);
        
        if(i == end) {
            result.push_back(end - start + 1);
            start = i + 1;
        }
    }
    
    return result;
}

// ===== TWO CITY SCHEDULING =====
// Minimize cost to send people to two cities

int twoCitySchedCost(vector<vector<int>> &costs) {
    // Sort by difference (costA - costB)
    sort(costs.begin(), costs.end(),
         [](const vector<int> &a, const vector<int> &b) {
             return (a[0] - a[1]) < (b[0] - b[1]);
         });
    
    int total = 0;
    int n = costs.size() / 2;
    
    // Send first n to city A, rest to city B
    for(int i = 0; i < n; i++) {
        total += costs[i][0];
    }
    for(int i = n; i < 2 * n; i++) {
        total += costs[i][1];
    }
    
    return total;
}

// ===== MAIN FUNCTION =====
int main() {
    // Activity Selection Example
    vector<Activity> activities = {{1,2}, {3,4}, {0,6}, {5,7}, {8,9}, {5,9}};
    cout << "Maximum activities: " << activitySelection(activities) << endl;
    
    // Fractional Knapsack Example
    vector<Item> items = {{10,60}, {20,100}, {30,120}};
    cout << "Maximum value: " << fractionalKnapsack(50, items) << endl;
    
    // Jump Game Example
    vector<int> jumps = {2, 3, 1, 1, 4};
    cout << "Can jump: " << canJump(jumps) << endl;
    cout << "Minimum jumps: " << minJumps(jumps) << endl;
    
    return 0;
}


#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <iomanip>

using namespace std;

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

int main() {
    cout << "========================================================\n";
    cout << "  Empirical Huffman Compression Engine (Greedy + Heap)  \n";
    cout << "========================================================\n";

    string text = "google research deepmind foundational algorithmic optimization "
                  "and information theory benchmark for efficient data encoding";
    
    string corpus = "";
    for(int i = 0; i < 50; ++i) corpus += text + " ";

    auto start_time = chrono::high_resolution_clock::now();

    unordered_map<char, int> freqMap;
    for (char c : corpus) freqMap[c]++;

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;
    for (auto pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

        HuffmanNode* internalNode = new HuffmanNode('$', left->freq + right->freq);
        internalNode->left = left;
        internalNode->right = right;
        minHeap.push(internalNode);
    }

    HuffmanNode* root = minHeap.top();

    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    int encodedBits = 0;
    for (char c : corpus) {
        encodedBits += huffmanCodes[c].length();
    }

    auto end_time = chrono::high_resolution_clock::now();
    double latency_us = chrono::duration<double, micro>(end_time - start_time).count();

    int originalBits = corpus.length() * 8;
    double compressionRatio = (1.0 - ((double)encodedBits / originalBits)) * 100.0;

    cout << "Corpus Length (Characters)   : " << corpus.length() << " chars\n";
    cout << "Original Uncompressed Bits   : " << originalBits << " bits (" << originalBits / 8 << " bytes)\n";
    cout << "Huffman Encoded Bits         : " << encodedBits << " bits (" << encodedBits / 8 << " bytes)\n";
    cout << "Space Reduction (Ratio)      : " << fixed << setprecision(2) << compressionRatio << "%\n";
    cout << "Encoding Pipeline Latency    : " << fixed << setprecision(2) << latency_us << " microseconds\n";
    cout << "========================================================\n";

    return 0;
}
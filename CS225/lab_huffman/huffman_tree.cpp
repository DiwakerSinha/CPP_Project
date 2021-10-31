/**
 * @file huffman_tree.cpp
 * Implementation of a Huffman Tree class.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

#include "huffman_tree.h"

using namespace std;

HuffmanTree::HuffmanTree(vector<Frequency> frequencies)
{
    std::stable_sort(frequencies.begin(), frequencies.end());
    buildTree(frequencies);
    vector<bool> path;
    buildMap(root_, path);
}

HuffmanTree::HuffmanTree(const HuffmanTree& other)
{
    copy(other);
}

HuffmanTree::HuffmanTree(BinaryFileReader& bfile)
{
    root_ = readTree(bfile);
    vector<bool> path;
    buildMap(root_, path);
}

HuffmanTree::~HuffmanTree()
{
    clear(root_);
}

const HuffmanTree& HuffmanTree::operator=(const HuffmanTree& rhs)
{
    if (this != &rhs) {
        clear(root_);
        copy(rhs);
    }
    return *this;
}

void HuffmanTree::clear(TreeNode* current)
{
    if (current == NULL)
        return;
    clear(current->left);
    clear(current->right);
    delete current;
}

void HuffmanTree::copy(const HuffmanTree& rhs)
{
    root_ = copy(rhs.root_);
}

HuffmanTree::TreeNode* HuffmanTree::copy(const TreeNode* current)
{
    if (current == NULL)
        return NULL;
    TreeNode* node = new TreeNode(current->freq);
    node->left = copy(current->left);
    node->right = copy(current->right);
    return node;
}

HuffmanTree::TreeNode*
HuffmanTree::removeSmallest(queue<TreeNode*>& singleQueue,
                            queue<TreeNode*>& mergeQueue)
{
    TreeNode * to_return_smallest = NULL;
  
    if (singleQueue.size() == 0 && mergeQueue.size() == 0) {
      return to_return_smallest;
    } else if (singleQueue.size() == 0) {
      to_return_smallest = mergeQueue.front();
      mergeQueue.pop();
      return to_return_smallest;
    } else if (mergeQueue.size() == 0) {
      to_return_smallest = singleQueue.front();
      singleQueue.pop();
      return to_return_smallest;
    }
    
    
    
    if (singleQueue.front()->freq.getFrequency() <= mergeQueue.front()->freq.getFrequency()) {
      to_return_smallest = singleQueue.front();
      singleQueue.pop();
    } else {
      to_return_smallest = mergeQueue.front();
      mergeQueue.pop();
    }
    return to_return_smallest;
}

void HuffmanTree::buildTree(const vector<Frequency>& frequencies)
{
    
    if (frequencies.size() == 0) {
      return;
    }
    
    queue<TreeNode*> singleQueue; // Queue containing the leaf nodes
    queue<TreeNode*> mergeQueue;  // Queue containing the inner nodes
    
    for (size_t i = 0; i < frequencies.size(); i++) { //already sorted
      TreeNode * temp = new TreeNode(frequencies.at(i));
      singleQueue.push(temp);
    }
    //Now the vector is stored in the queue with the front containing the least frequencies.
    
    while (singleQueue.size() + mergeQueue.size() > 1) {
      TreeNode * left_node = removeSmallest(singleQueue, mergeQueue);
      TreeNode * right_node = removeSmallest(singleQueue, mergeQueue);
      
      TreeNode * merged = new TreeNode(left_node->freq.getFrequency() + right_node->freq.getFrequency());
      merged->left = left_node;
      merged->right = right_node;
      
      mergeQueue.push(merged);
    }
    root_ = mergeQueue.front();
    mergeQueue.pop();
}

string HuffmanTree::decodeFile(BinaryFileReader& bfile)
{
    stringstream ss;
    decode(ss, bfile);
    return ss.str();
}

void HuffmanTree::decode(stringstream& ss, BinaryFileReader& bfile)
{
    TreeNode* current = root_;
    while (bfile.hasBits()) {
      
      if (bfile.getNextBit() == 0) {
        current = current->left;
      } else {
        current = current->right;
      }
      
      if (current->left == NULL && current->right == NULL) {
        ss << current->freq.getCharacter();
        current = root_;
      }
    }
}

void HuffmanTree::writeTree(BinaryFileWriter& bfile)
{
    writeTree(root_, bfile);
}

void HuffmanTree::writeTree(TreeNode* current, BinaryFileWriter& bfile)
{
  if (current == NULL) {
    return;
  }
  if (current->left == NULL && current->right == NULL) {
    bfile.writeBit(1);
    bfile.writeByte(current->freq.getCharacter());
  } else {
    bfile.writeBit(0);
    writeTree(current->left, bfile);
    writeTree(current->right, bfile);
  }
}

HuffmanTree::TreeNode* HuffmanTree::readTree(BinaryFileReader& bfile)
{
    while(bfile.hasBits()) {
      if (bfile.getNextBit() == 0) {
        
        TreeNode * to_return = new TreeNode(0);
        to_return->left = readTree(bfile);
        to_return->right = readTree(bfile);
        return to_return;
        
      } else {
        TreeNode * to_return = new TreeNode(Frequency(bfile.getNextByte(), 0));
        return to_return;
      }
    }

    return NULL;
}

void HuffmanTree::buildMap(TreeNode* current, vector<bool>& path)
{   
    // Base case: leaf node.
    if (current->left == NULL && current->right == NULL) {
        bitsMap_[current->freq.getCharacter()] = path;
        return;
    }

    // Move left
    path.push_back(false);
    buildMap(current->left, path);
    path.pop_back();

    // Move right
    path.push_back(true);
    buildMap(current->right, path);
    path.pop_back();
}

void HuffmanTree::printInOrder() const
{
    printInOrder(root_);
    cout << endl;
}

void HuffmanTree::printInOrder(const TreeNode* current) const
{
    if (current == NULL)
        return;
    printInOrder(current->left);
    cout << current->freq.getCharacter() << ":" << current->freq.getFrequency()
         << " ";
    printInOrder(current->right);
}

void HuffmanTree::writeToFile(const string& data, BinaryFileWriter& bfile)
{
    for (auto it = data.begin(); it != data.end(); ++it)
        writeToFile(*it, bfile);
}

void HuffmanTree::writeToFile(char c, BinaryFileWriter& bfile)
{
    vector<bool> bits = getBitsForChar(c);
    for (auto it = bits.begin(); it != bits.end(); ++it)
        bfile.writeBit(*it);
}

vector<bool> HuffmanTree::getBitsForChar(char c)
{
    return bitsMap_[c];
}

// class for generic printing

template <typename TreeNode>
class HuffmanTreeNodeDescriptor
    : public GenericNodeDescriptor<HuffmanTreeNodeDescriptor<TreeNode>>
{
  public:
    HuffmanTreeNodeDescriptor(const TreeNode* root) : subRoot_(root)
    { /* nothing */
    }

    string key() const
    {
        std::stringstream ss;
        char ch = subRoot_->freq.getCharacter();
        int freq = subRoot_->freq.getFrequency();

        // print the sum of the two child frequencies
        if (ch == '\0')
            ss << freq;
        // print the leaf containing a character and its count
        else {
            if (ch == '\n')
                ss << "\\n";
            else
                ss << ch;
            ss << ":" << freq;
        }
        return ss.str();
    }

    bool isNull() const
    {
        return subRoot_ == NULL;
    }
    HuffmanTreeNodeDescriptor left() const
    {
        return HuffmanTreeNodeDescriptor(subRoot_->left);
    }
    HuffmanTreeNodeDescriptor right() const
    {
        return HuffmanTreeNodeDescriptor(subRoot_->right);
    }

  private:
    const TreeNode* subRoot_;
};

int HuffmanTree::height(const TreeNode* subRoot) const
{
    if (subRoot == NULL)
        return -1;
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

void HuffmanTree::print(std::ostream& out) const
{
    int h = height(root_);
    if (h > _max_print_height) {
        out << "Tree is too big to print. Try with a small file (e.g. "
               "data/small.txt)"
            << endl;
        return;
    }

    printTree(HuffmanTreeNodeDescriptor<TreeNode>(root_), out);
}

Frequency
HuffmanTree::testRemoveSmallest(vector<Frequency> single,
                                vector<Frequency> merge)
{
    queue<TreeNode*> singleQueue;
    queue<TreeNode*> mergeQueue;
    for (auto it = single.begin(); it != single.end(); ++it) {
         singleQueue.push(new TreeNode(*it));
    }
    for (auto it = merge.begin(); it != merge.end(); ++it) {
         mergeQueue.push(new TreeNode(*it));
    }

    TreeNode* testNode = removeSmallest(singleQueue, mergeQueue);
    Frequency testFreq = testNode->freq;

    delete testNode;
    while (!singleQueue.empty()) {
        delete singleQueue.front();
        singleQueue.pop();
    }
    while (!mergeQueue.empty()) {
        delete mergeQueue.front();
        mergeQueue.pop();
    }

    return testFreq;
}

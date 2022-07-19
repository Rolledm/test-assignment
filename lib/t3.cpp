#include "t3.h"
#include <map>
#include <vector>

namespace Utilities {

    void List::Serialize(FILE* file) {
        if (!file) return;
        fwrite(&count, sizeof(count), 1, file);

        std::map<ListNode*, int> nodePointers;
        auto node = head;
        for (int i = 0; i < count; i++) {
            nodePointers.emplace(node, i);
            node = node->next;
        }

        node = head;
        for (int i = 0; i < count; i++) {
            auto len = node->data.length();
            fwrite(&len, sizeof(len), 1, file);
            fwrite(node->data.c_str(), sizeof(char), len, file);
            auto randomNode = (node->rand) ? nodePointers[node->rand] : -1;
            fwrite(&randomNode, sizeof(randomNode), 1, file);
            node = node->next;
        }
    }

    void List::Deserialize(FILE* file) {
        if (!file) return;
        fread(&count, sizeof(count), 1, file);
        if(!count) return;

        std::vector<ListNode*> nodePointers(count);
        std::vector<int> randomNodes(count);
        ListNode* node;

        for (int i = 0; i < count; i++) {
            unsigned long len;
            fread(&len, sizeof(len), 1, file);

            char* data = (char*)malloc(len * sizeof(char));
            fread(data, sizeof(char), len, file);

            node = new ListNode;
            node->data = data;
            nodePointers[i] = node;
            fread(&randomNodes[i], sizeof(int), 1, file);
        }

        head = nodePointers[0];
        head->prev = nullptr;
        tail = nodePointers[count - 1];
        tail->next = nullptr;
        if (count > 1) {
            head->next = nodePointers[1];
            tail->prev = nodePointers[count - 2];
            for (int i = 1; i < count - 1; i++) {
                nodePointers[i]->next = nodePointers[i+1];
                nodePointers[i]->prev = nodePointers[i-1];
            }
        }

        for (int i = 0; i < count; i++) {
            nodePointers[i]->rand = (randomNodes[i] == -1) ? nullptr : nodePointers[randomNodes[i]];
        }
    }

    std::string List::GetDBGData() {
        std::string str;
        std::map<ListNode*, int> nodePointers;
        auto node = head;
        for (int i = 0; i < count; i++) {
            nodePointers.emplace(node, i);
            node = node->next;
        }

        node = head;
        for (int i = 0; i < count; i++) {
            auto randomNode = (node->rand) ? nodePointers[node->rand] : -1;
            str += node->data + ' ' + std::to_string(randomNode) + '\n';
            node = node->next;
        }
        return str;
    }

}
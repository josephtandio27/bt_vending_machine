#pragma once

#include "behaviortree_cpp/behavior_tree.h"

struct ItemDetail
{
    std::string name;
    double price;
};

// Inherit from SyncActionNode
class VendingMachineSystem
{
public:
    // Constructor
    VendingMachineSystem() : _user_selection(0), _item_name(""), _item_price(0)
    {
        initializeInventory();
    }

    BT::NodeStatus getUserInput(BT::TreeNode &self);
    BT::NodeStatus processUserInput(BT::TreeNode &self);
    BT::NodeStatus OutputProduct(BT::TreeNode &self);

private:
    int _user_selection;
    std::string _item_name;
    int _item_price;

    std::map<int, ItemDetail> inventory_;

    // Private helper function to initialize the inventory
    void initializeInventory();

    // 4. Get the name and price of an item by its key
    bool getItemDetails(int key, std::string &name_out, int &price_out) const;
};
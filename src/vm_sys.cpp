#include "vm_sys.h"
#include <iostream>

void VendingMachineSystem::initializeInventory()
{
    // Use an initializer list to populate the map.
    // We use -1.0 to denote the "Shutdown" status (no price).
    inventory_ = {
        {0, {"Shutdown", -1}},
        {1, {"Chips", 5}},
        {2, {"Soda", 2}},
        {3, {"Water", 1}},
        {4, {"Juice", 3}},
        {5, {"Choco Bar", 3}}};
}

bool VendingMachineSystem::getItemDetails(int key, std::string& name_out, int& price_out) const
{
    // Find the key in the map
    auto it = inventory_.find(key);

    if (it != inventory_.end())
    {
        // Key was found!
        name_out = it->second.name;
        price_out = it->second.price;
        return true;
    }
    else
    {
        // Key was not found (Invalid item code)
        name_out = "N/A";
        price_out = 0.0;
        return false;
    }
}

BT::NodeStatus VendingMachineSystem::getUserInput(BT::TreeNode &self)
{
    std::cout << "Vending machine options:\n";
    std::cout << "0: Shutdown vending machine\n";
    std::cout << "1: Chips [$5]\n";
    std::cout << "2: Soda [$2]\n";
    std::cout << "3: Water [$1]\n";
    std::cout << "4: Juice [$3]\n";
    std::cout << "5: Choco bar [$3]\n";
    std::cout << "Please enter a selection (0-5): ";
    std::cin >> _user_selection;

    // Validate input
    if (_user_selection < 0 || _user_selection > 5)
    {
        std::cout << "Invalid selection. Please choose a number between 0 and 5." << std::endl;
    }

    // Set the output port value
    self.setOutput("selection", _user_selection);
    return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus VendingMachineSystem::processUserInput(BT::TreeNode &self)
{
    if (getItemDetails(_user_selection, _item_name, _item_price))
    {
        if (_item_name == "Shutdown")
        {
            /* code */
            std::cout << "Vending machine is shutting down." << std::endl;
            self.setOutput("flag_name", true);
            return BT::NodeStatus::FAILURE;
        }
        
        std::cout << "Item " << _user_selection << ": " << _item_name << " - Price: $" << _item_price << std::endl;
        self.setOutput("price", _item_price);
    }
    return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus VendingMachineSystem::OutputProduct()
{
    if (getItemDetails(_user_selection, _item_name, _item_price))
    {
        std::cout << "Dispensing your " << _item_name << ". Enjoy!" << std::endl;
        _item_name = "";
        _item_price = 0;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return BT::NodeStatus::SUCCESS;
}
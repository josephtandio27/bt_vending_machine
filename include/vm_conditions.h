#pragma once

#include "behaviortree_cpp/condition_node.h"

// BT::NodeStatus IsTerminatedCheck(BT::TreeNode &self)
// {
//     std::cout << "[Condition] Checking termination flag: " << std::endl;
//     // Logic to check Blackboard for terminated_status
//     BT::Expected<bool> terminated_status = self.getInput<bool>("flag_name");
//     return terminated_status ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
// }

BT::NodeStatus ReceivedUserInputCheck(BT::TreeNode &self)
{
    // Logic to check Blackboard for product ID
    BT::Expected<int> selection_num = self.getInput<int>("selection");
    if (!selection_num)
    {
        throw BT::RuntimeError("missing required input [selection]: ", selection_num.error());
    }
    // 2. Read the boolean value
    int num = selection_num.value();

    if (num <= 5 && num >= 1)
    {
        std::cout << "[Condition] Valid user input.\n";
        return BT::NodeStatus::SUCCESS;
    }
    else
    {
        std::cout << "[Condition] Invalid user input.\n";
        return BT::NodeStatus::FAILURE;
        
    }
}

BT::NodeStatus PaymentSuccessfulCheck(BT::TreeNode &self)
{
    // Logic to check if payment is sufficient
    BT::Expected<int> price = self.getInput<int>("price");
    BT::Expected<int> customer_money = self.getInput<int>("customer_money");

    if (!price)
    {
        throw BT::RuntimeError("missing required input [price]: ", price.error());
    }
    if (!customer_money)
    {
        throw BT::RuntimeError("missing required input [customer_money]: ", customer_money.error());
    }

    if (customer_money.value() == price.value())
    {
        std::cout << "[Condition] Payment sufficient.\n";
        self.setOutput<bool>("success", true);
        return BT::NodeStatus::SUCCESS;
    }
    else if (customer_money.value() > price.value())
    {
        int change = customer_money.value() - price.value();
        self.setOutput<bool>("success", true);
        std::cout << "[Condition] Payment sufficient.\n";
        std::cout << "Dispensing change: $" << change << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
    else
    {
        std::cout << "[Condition] Payment insufficient.\n";
        self.setOutput<bool>("success", false);
        return BT::NodeStatus::FAILURE;
    }
}
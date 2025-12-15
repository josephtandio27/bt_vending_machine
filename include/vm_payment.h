#pragma once

#include "behaviortree_cpp/behavior_tree.h"

class VendingMachinePayment : public BT::SyncActionNode
{
public:
    // Constructor
    VendingMachinePayment(const std::string &name, const BT::NodeConfig &config) : SyncActionNode(name, config) {}

    static BT::PortsList providedPorts()
    {
        return {BT::OutputPort<int>("customer_money", "Money given by the customer")};
    }

    BT::NodeStatus tick() override
    {
        std::cout << "Please insert payment (in whole dollars): ";
        std::cin >> _customer_money;

        if (_customer_money > 0)
        {
            setOutput("customer_money", _customer_money);
            std::cout << "Payment of $" << _customer_money << " received." << std::endl;
            return BT::NodeStatus::SUCCESS;
        }
        else
        {
            std::cout << "No payment received. Transaction cancelled." << std::endl;
            return BT::NodeStatus::FAILURE;
        }
    }

private:
    int _customer_money;
};
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/utils/shared_library.h"
// #include "behaviortree_cpp/behavior_tree.h"

#include "vm_conditions.h"
#include "vm_payment.h"
#include "vm_sys.h"
#include <iostream>

int main()
{
    // Create the vending machine system
    VendingMachineSystem vm_system;

    // Create Behavior Tree factory
    BT::BehaviorTreeFactory factory;

    /* TERMINATION CHECK */
    // Define ports for termination check
    BT::PortsList termination_port_in = { BT::InputPort<bool>("flag_name", false, "Name of the blackboard flag to check termination") };
    // Register IsTerminated condition
    // factory.registerSimpleCondition("IsTerminated", IsTerminatedCheck, termination_port_in);
    // factory.registerSimpleCondition("IsTerminated", [&](BT::TreeNode& self) { return IsTerminatedCheck(self); });

    /* GET USER INPUT */
    BT::PortsList selection_port_out = { BT::OutputPort<int>("selection", "The user's input selection (0-5)") };
    factory.registerSimpleAction("GetUserInput", std::bind(&VendingMachineSystem::getUserInput, &vm_system, std::placeholders::_1), selection_port_out);
    // factory.registerSimpleAction("GetUserInput", [&](BT::TreeNode& self) { return vm_system.getUserInput(self); }, selection_port_out);

    /* USER INPUT CHECK */
    BT::PortsList selection_port_in = { BT::InputPort<int>("selection", "The user's input selection (0-5)") };
    factory.registerSimpleCondition("ReceivedUserInput", ReceivedUserInputCheck, selection_port_in);

    /* PROCESS USER INPUT*/
    BT::PortsList process_ports = {
        BT::OutputPort<bool>("flag_name", "Flag to indicate termination"),
        BT::OutputPort<int>("price", "Price of the selected item"),
    };
    factory.registerSimpleAction("ProcessUserInput", std::bind(&VendingMachineSystem::processUserInput, &vm_system, std::placeholders::_1), process_ports);
    

    /* MAKE PAYMENT */
    factory.registerNodeType<VendingMachinePayment>("VendingMachinePayment");

    /* CHECK PAYMENT */
    BT::PortsList payment_check_ports = {
        BT::InputPort<int>("price", "Price of the selected item"),
        BT::InputPort<int>("customer_money", "Money given by the customer"),
    };
    factory.registerSimpleCondition("PaymentSuccessful", PaymentSuccessfulCheck, payment_check_ports);

    /* OUTPUT PRODUCT */
    factory.registerSimpleAction("OutputProduct", [&](BT::TreeNode&){ return vm_system.OutputProduct(); });

    // Load the Behavior Tree from XML
    auto tree = factory.createTreeFromFile("./vending_machine_tree.xml");

    // Execute the Behavior Tree
    tree.tickWhileRunning();

    return 0;
}
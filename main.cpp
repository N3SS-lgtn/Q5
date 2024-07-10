#include "mbed.h"

// Define the button pin and event queue
InterruptIn button(PC_13);
EventQueue queue;

// Initialize a counter
volatile int press_count = 0;

// Define a function to handle the button press
void button_pressed() {
    press_count++;
    queue.call(printf, "Button pressed %d times\n", press_count);
}

int main() {
    // Attach the button press handler to the rising edge interrupt
    button.rise(&button_pressed);

    // Start the event queue in a separate thread
    Thread eventThread;
    eventThread.start(callback(&queue, &EventQueue::dispatch_forever));

    // Keep the main function alive
    while (true) {
        // Sleep to save power while waiting for interrupts
        ThisThread::sleep_for(100ms);
    }
}
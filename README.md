A smarter approach to handling GPIO inputs in embedded systems using function pointers and mapping tables.<br> Instead of writing nested if/else or switch blocks, this project modularizes logic by linking each button to a specific LED behavior (toggle/blink/etc.) through a structured mapping system.
Most beginner firmware handles button inputs with hardcoded conditionals. This project demonstrates a more scalable and maintainable polling based method using a button-action mapping table.<br> It’s similar to how real-world devices like microwaves assign functions to each button press.

Key Concepts:<br>
Structs for organizing button-to-action mappings.

Function pointers for modular design.

Separation of logic from behavior.

Scalable and clean embedded firmware.

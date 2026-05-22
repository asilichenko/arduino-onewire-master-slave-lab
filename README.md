# arduino-onewire-master-slave-lab
Arduino-based 1-Wire bus experiment with custom master/slave implementation and oscilloscope-level analysis of reset, read/write timing, and signaling behavior.

## Connection

<img width="600" alt="connection" src="https://github.com/user-attachments/assets/80fae6d4-2883-40d6-b582-789753523f69" />

## Presence Pulse

### Slave is absent
<img width="600" alt="send-reset-no-response" src="https://github.com/user-attachments/assets/deca35f2-7a49-4cb0-9523-e9dcca9c44c0" />

### Slave is present
<img width="600" alt="presence pulse" src="https://github.com/user-attachments/assets/b017c2e3-24a4-466c-81f0-a305bac9df18" />

## Read/Write `1`

<img width="600" alt="1" src="https://github.com/user-attachments/assets/ada4de73-afc2-4222-91a4-2d9d06a313b9" />

## Read/Write `0`

<img width="600" alt="0" src="https://github.com/user-attachments/assets/de1d7cf1-3ea9-445c-ab08-bf6cea7cc0c4" />

## 0xAC (0b10101100)

<img width="600" alt="0xAC (0b10101100)" src="https://github.com/user-attachments/assets/f1b3a86e-6923-4ac2-9d4a-8f5b488a42e8" />

## 0x0F (0b00001111)

<img width="600" alt="0x0F (0b00001111)" src="https://github.com/user-attachments/assets/d61ec441-89ec-4e61-9e7f-a14e5aed9f9c" />

## Write 0x0F + Read 0xF0

<img width="600" alt="Write 0x0F + Read 0xF0" src="https://github.com/user-attachments/assets/b1cb6b43-26dc-4f10-a424-0e839be0075c" />

## License

MIT License © 2026

See [LICENSE](LICENSE) for details.

# References
- Article:
- Arduino OneWire Lib: https://github.com/PaulStoffregen/OneWire

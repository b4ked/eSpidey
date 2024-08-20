const dgram = require('dgram');
const express = require('express');
const bodyParser = require('body-parser');

const app = express();
const port = 3000;
const udpPort = 41234; // Port for UDP communication

app.use(express.static('public'));
app.use(bodyParser.json());

// Create a UDP client
const udpClient = dgram.createSocket('udp4');

// Endpoint to receive UDP messages
app.post('/send', (req, res) => {
  const { legId, jointPositions, ip, port } = req.body;

  // Validate input
  if (legId < 0 || legId > 3 || jointPositions.length !== 4) {
    return res.status(400).send('Invalid input');
  }

  // Create a buffer for the UDP packet
  const buffer = Buffer.alloc(25); // 8 bytes header + 1 byte checksum + 16 bytes data

  // Fill the header
  buffer.writeUInt8(0xAA, 0); // Start of Packet
  buffer.writeUInt8(0x01, 1); // Command ID for Joint Position Demand
  buffer.writeUInt16BE(17, 2); // Length of data (including header and checksum)

  // Write the data
  buffer.writeUInt8(legId, 4); // Leg ID

  // Write joint positions (4 joints × 4 bytes each = 16 bytes)
  for (let i = 0; i < 4; i++) {
    buffer.writeInt32LE(jointPositions[i], 5 + i * 4);
  }

  // Calculate and write checksum (simple example: sum of all bytes, modulo 256)
  const checksum = buffer.reduce((acc, byte) => acc + byte, 0) & 0xFF;
  buffer.writeUInt8(checksum, 13); // Write checksum in the last byte

  // Send the buffer
  udpClient.send(buffer, port, ip, (err) => {
    if (err) {
      console.error('Error sending UDP message:', err);
      res.status(500).send('Error sending UDP message');
    } else {
      res.send('UDP message sent successfully');
    }
  });
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});

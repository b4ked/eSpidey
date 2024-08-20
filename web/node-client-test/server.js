const express = require('express');
const dgram = require('dgram');
const cors = require('cors');
const path = require('path');
const app = express();
const udpClient = dgram.createSocket('udp4');

app.use(cors()); // Enable CORS
app.use(express.json());

// Serve static files from the 'public' directory
app.use(express.static(path.join(__dirname, 'public')));

app.post('/send-udp', (req, res) => {
    const { message, ip, port } = req.body;
    
    udpClient.send(message, port, ip, (err) => {
        if (err) {
            console.error('Error sending UDP packet:', err);
            return res.status(500).send('Error sending UDP packet.');
        }
        res.send('UDP packet sent successfully.');
    });
});

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});

const app = require('express')();
const http = require('http').Server(app);
const io = require('socket.io')(http);
const port = process.env.PORT || 3939;

const SerialPort = require('serialport');
const Readline = SerialPort.parsers.Readline;
const serial = new SerialPort('/dev/cu.usbmodem1451', {baudRate: 19200});
const serialRecv = serial.pipe(new Readline({ delimiter: '\r\n' }))

serialRecv.on('data', data => {
  console.log("Recieved: ", data.toString());
  io.sockets.emit('receive', data.toString());
});

serial.on('open', () => {
  io.sockets.emit('receive', 'connected!');
});

/* ===========================================
*
* Setup a simple server.
*
=========================================== */

app.get('/', (req, res) => {
  res.sendFile(process.cwd()+'/index.html');
});

http.listen(port, () => {
  console.log(`listening on *:${port}`);
});

/* ===========================================
*
*  Socket.io stuff
*
=========================================== */

io.on('connection', (socket) => {
  console.log('a user connected');

  /**
   * Socket listener to determine whether or not to send HIGH / LOW
   * values to Arduino.
   */
  socket.on('message', (msg) => {
    if (msg == 'restart') {
      serial.once('close', () => {
        process.nextTick( () => {
          console.log('about to open');
          serial.open();
          console.log('should have opened');
        })
      })
      serial.close();
    } else {
      console.log('Sending: ', msg);
      serial.write(new Buffer(msg));
    }
  });
});

/* ===========================================
*
* Serialport stuff
*
=========================================== */

serial.on('close', () => {
  console.log('Serial port disconnected.');
  io.sockets.emit('receive', 'disconnected!');
});
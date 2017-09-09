const app = require('express')();
const http = require('http').Server(app);
const io = require('socket.io')(http);
const port = process.env.PORT || 3939;

const StepperMotor = require('./lib/stepper_motor');
const StepperMotorSocket = require('./lib/stepper_motor_socket');
StepperMotorSocket.initialize(io,
  new StepperMotor('Base', 11, 13, 200),
  new StepperMotor('Shoulder', 15, 16, 400),
  new StepperMotor('Elbow', 18, 22, 400)
);

app.get('/', (req, res) => {
  res.sendFile(process.cwd()+'/index.html');
});

http.listen(port, () => {
  console.log(`listening on *:${port}`);
});

io.on('connection', (socket) => {
  console.log('a user connected');
  socket.on('message', (msg) => {

  });
});

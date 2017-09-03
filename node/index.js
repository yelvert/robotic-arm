var five = require("johnny-five");
var board = new five.Board();

board.on("ready", function() {
  console.log("Ready event. Repl instance auto-initialized!");

  // var led = new five.Led(13);

  // this.repl.inject({
  //   // Allow limited on/off control access to the
  //   // Led instance from the REPL.
  //   on: function() {
  //     led.on();
  //   },
  //   off: function() {
  //     led.off();
  //   }
  // });

  function time () {
    var x = process.hrtime(time.last);
    time.last = x;
    console.log(diff[0] * 1e9 + diff[1]);
  }

  board.loop(0, time);
});

board.on("message", function(event) {
  /*
    Event {
      type: "info"|"warn"|"fail",
      timestamp: Time of event in milliseconds,
      class: name of relevant component class,
      message: message [+ ...detail]
    }
  */
  console.log("Received a %s message, from %s, reporting: %s", event.type, event.class, event.message);
});
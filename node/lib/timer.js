function setTimeoutMicro (cb, waitTime) {
  var timer = setTimeoutMicro.timers.length;
  var time = 0;
  function tick () {
    var diff = process.hrtime(tick.last);
    time += (diff[0] * 1e6) + (diff[1] / 1e3);
    if (time >= waitTime) {
      delete setTimeoutMicro.timers[timer];
      return cb(time);
    }
    tick.last = process.hrtime();
    nextTick();
  }
  function nextTick () { setTimeoutMicro.timers[timer] = setImmediate(tick) }
  tick.last = process.hrtime();
  nextTick();
  return timer;
}
setTimeoutMicro.timers = [];
function clearTimeoutMicro (timer) { clearImmediate(setTimeoutMicro.timers[timer]) }

function setIntervalMicro (cb, intervalTime) {
  var timer = setIntervalMicro.timers.length;
  function wrappedCb (time) {
    cb(time);
    nextTimer();
  }
  function nextTimer () { setIntervalMicro.timers[timer] = setTimeoutMicro(wrappedCb, intervalTime) }
  nextTimer();
  return timer;
}
setIntervalMicro.timers = [];
function clearIntervalMicro (timer) { clearTimeoutMicro(setIntervalMicro.timers[timer]) }

module.exports = {
  setTimeoutMicro,
  clearTimeoutMicro,
  setIntervalMicro,
  clearIntervalMicro
};
